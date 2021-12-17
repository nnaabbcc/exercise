import json
import os
import sys
import base64
import urllib.request
import shutil
import subprocess

def save_icon(s, path):
    icon = base64.b64decode(s)
    with open(path, 'wb') as f:
        f.write(icon)

def generate_icons(folder, s):
    if not os.path.exists(folder):
        os.makedirs(folder)

    if 'icon' in s:
        save_icon(s['icon'],
            os.path.join(folder, 'icon.png'))

    if 'icon2x' in s:
        save_icon(s['icon2x'],
            os.path.join(folder, 'icon@2x.png'))

def generate_meta(folder, s):
    m = {}
    m['name'] = s['name']
    m['title'] = s['title']
    if len(s['versions']) > 0:
        m['version'] = s['versions'][0]
    m['revision'] = s['revision']
    if 'extra' in s:
        m['extra'] = s['extra']

    if not os.path.exists(folder):
        os.makedirs(folder)
    path = os.path.join(folder, 'meta.json')
    with open(path, 'w') as f:
        json.dump(m, f, indent=4)

def clean_up(folder):
    shutil.rmtree(folder)

def download_progress(block_number, block_size, total_size):
    percent = 100 * block_number * block_size / total_size
    if percent > 100:
        percent = 100

    print('downloading {:.2f}%'.format(percent))

def find_contents(folder):
    for item in os.listdir(folder):
        path = os.path.join(folder, item)
        if item == 'Contents':
            return path
        if os.path.isdir(path):
            return find_contents(path)
    return None

def unpack_archive(filepath, folder):
    bashpath = "C:\\Program Files\\Git\\bin\\bash.exe"
    tarcmd = "tar --force-local -xzvf \"" + filepath + "\" -C \"" + folder + "\""
    cmd = bashpath + " -c '" + tarcmd + "'"
    subprocess.run(cmd)

def extract_docset(filename, folder):
    if not os.path.exists(filename):
        return False

    if not os.path.exists(folder):
        os.makedirs(folder)

    # shutil.unpack_archive(filepath, folder)
    unpack_archive(filename, folder)

    src = find_contents(folder)
    if src is None:
        return False
    shutil.move(src, os.path.join(folder, 'Contents'))

    for item in os.listdir(folder):
        if item != 'Contents':
            p = os.path.join(folder, item)
            if os.path.isdir(p):
                shutil.rmtree(p)
            elif os.path.isfile(p):
                os.remove(p)
            else:
                return False

    return True

def download_docset_impl(folder, s):
    if not os.path.exists(folder):
        os.makedirs(folder)
    filename = s['name'] + '.tgz'
    url = 'http://singapore.kapeli.com/feeds/' + filename
    print('downloading ', url)
    filepath = os.path.join(folder, filename)
    urllib.request.urlretrieve(url,
        filepath,
        reporthook=download_progress)
    return extract_docset(filepath, folder)

def download_docset(folder, s):
    if download_docset_impl(folder, s):
        generate_icons(folder, s)
        generate_meta(folder, s)
        return True
    else:
        clean_up(folder)
        return False

def do_update_docset(folder, s):
    folder_name = os.path.basename(folder)
    parent_folder = os.path.dirname(folder)

    # backup
    bak_folder = os.path.join(parent_folder, folder_name + '.bak')
    print(folder, bak_folder)
    os.rename(folder, bak_folder)

    if download_docset(folder, s):
        clean_up(bak_folder)
        return True
    else:
        clean_up(folder)
        os.rename(bak_folder, folder)
        return False

def compare_version(o, n):
    ol = o.split('.')
    nl = n.split('.')
    for i in range(len(ol)):
        if i < len(nl):
            ov = int(ol[i])
            nv = int(nl[i])
            if ov < nv:
                return True
    return False

def need_update(m, s):
    if 'version' in m:
        if 'versions' in s:
            if len(s['versions']) > 0:
                o = m['version']
                n = s['versions'][0]
                # print(s['name'], o, n)
                return compare_version(o, n)
            else:
                return True
        else:
            return True
    elif 'revision' in m:
        if 'revision' in s:
            o = m['revision']
            n = s['revision']
            # print(s['name'], 'revision', o, n)
            return o < n
        else:
            return True
    else:
        print(m, s)
    return False

def update_docset_impl(docset_root, doc_folder, s):
    folder = os.path.join(docset_root, doc_folder)
    if not os.path.exists(folder):
        return download_docset_impl(folder, s)

    meta_path = os.path.join(folder, 'meta.json')
    if os.path.exists(meta_path):
        meta = None
        with open(meta_path) as f:
            meta = json.load(f)
        # print(meta)
        if not meta['name'] == s['name']:
            return False
        if need_update(meta, s):
            return do_update_docset(folder, s)
        else:
            return True
    else:
        return do_update_docset(folder, s)

def update_docset_of(docset_root, doc_folder, jsonset):
    name = doc_folder
    if doc_folder.endswith(".docset"):
        name = doc_folder[:-7]
    for s in jsonset:
        if s['name'] == name:
            return update_docset_impl(docset_root, doc_folder, s)
    return False

def update_all_docsets_main(cachefile, docsetroot):
    if not os.path.exists(cachefile):
        return False
    if not os.path.isfile(cachefile):
        return False

    if not os.path.exists(docsetroot):
        return False
    if not os.path.isdir(docsetroot):
        return False

    with open(cachefile) as f:
        jsonset = json.load(f)
        if len(jsonset) == 0:
            return False
        items = os.listdir(docsetroot)
        for d in items:
            if not update_docset_of(docsetroot, d, jsonset):
                return False
    return True

def download_docset_by_name(folder, cachefile, name):
    if not os.path.exists(cachefile):
        return False
    if not os.path.isfile(cachefile):
        return False

    if not os.path.exists(folder):
        os.makedirs(folder)

    with open(cachefile) as f:
        jsonset = json.load(f)
        for s in jsonset:
            if s['name'] == name:
                return download_docset(os.path.join(folder, name + '.docset'), s)

    return False

def update_docset_main(cachefile, docsetroot, name):
    if not os.path.exists(cachefile):
        return False
    if not os.path.isfile(cachefile):
        return False

    if not os.path.exists(docsetroot):
        return False
    if not os.path.isdir(docsetroot):
        return False

    items = os.listdir(docsetroot)
    found = False
    folder = None
    for item in items:
        item_path = os.path.join(docsetroot, item)
        meta_path = os.path.join(item_path, 'meta.json')
        meta = None
        with open(meta_path, 'r') as f:
            meta = json.load(f)
        if 'name' in meta:
            if name == meta['name']:
                found = True
                folder = item
    if found:
        with open(cachefile) as f:
            jsonset = json.load(f)
            return update_docset_of(docsetroot, folder, jsonset)
    else:
        return download_docset_main(cachefile, docsetroot, name)

def list_docsets_main(p, cachefile, docsetroot, type):
    if type == 'local':
        return list_docsets_local(docsetroot)
    elif type == 'remote':
        return list_docsets_remote(cachefile)
    elif type == 'update':
        return list_docsets_update(cachefile, docsetroot)
    else:
        usage_main(p)
        return False

def list_docsets_local(docsetroot):
    if not os.path.exists(docsetroot):
        return False
    if not os.path.isdir(docsetroot):
        return False

    items = os.listdir(docsetroot)
    for item in items:
        item_path = os.path.join(docsetroot, item)
        meta_path = os.path.join(item_path, 'meta.json')
        meta = None
        with open(meta_path, 'r') as f:
            meta = json.load(f)
        print(item)
        if 'name' in meta:
            print('  name:', meta['name'])
        if 'title' in meta:
            print('  title:', meta['title'])
        if 'version' in meta:
            print('  version:', meta['version'])
        if 'revision' in meta:
            print('  revision:', meta['revision'])
        if 'extra' in meta:
            print('  extra:')
            for key in (meta['extra']):
                print('    ', key + ':', meta['extra'][key])
        print('  path:', item_path)

    return True

def list_docsets_remote(cachefile):
    if not os.path.exists(cachefile):
        return False
    if not os.path.isfile(cachefile):
        return False

    j = None
    with open(cachefile, 'r') as f:
        j = json.load(f)

    for d in j:
        if 'name' in d:
            print(d['name'])
        for key in d:
            if key in ['icon', 'icon2x']:
                pass
            elif key == 'extra':
                print('  extra:')
                for k in d['extra']:
                    print('    ', k + ':', d['extra'][k])
            else:
                print('  ', key + ':', d[key])

    return True


def list_docsets_update(cachefile, docsetroot):
    if not os.path.exists(cachefile):
        return False
    if not os.path.isfile(cachefile):
        return False

    if not os.path.exists(docsetroot):
        return False
    if not os.path.isdir(docsetroot):
        return False

    j = None
    with open(cachefile, 'r') as f:
        j = json.load(f)

    items = os.listdir(docsetroot)
    for item in items:
        item_path = os.path.join(docsetroot, item)
        meta_path = os.path.join(item_path, 'meta.json')
        m = None
        with open(meta_path, 'r') as f:
            m = json.load(f)
        for s in j:
            if ('name' in m) and ('name' in s) and (m['name'] == s['name']):
                if need_update(m, s):
                    print(m['name'])
                    if ('version' in m) and ('versions' in s):
                        print('  version:', m['version'], '->', s['versions'])
                    if ('revision' in m) and ('revision' in s):
                        print('  revision', m['revision'], '->', s['revision'])

    return True

def download_docset_main(cachefile, docsetroot, name):
    if not os.path.exists(docsetroot):
        return False
    if not os.path.isdir(docsetroot):
        return False

    items = os.listdir(docsetroot)
    found = False
    for item in items:
        item_path = os.path.join(docsetroot, item)
        meta_path = os.path.join(item_path, 'meta.json')
        meta = None
        with open(meta_path, 'r') as f:
            meta = json.load(f)
        if 'name' in meta:
            if name == meta['name']:
                found = True
    if found:
        print(name, 'already exists, please use update command')
        return False
    else:
        return download_docset_by_name(docsetroot, cachefile, name)

def usage_main(p):
    print('Usage:')
    print('  python', p, 'update')
    print('  python', p, 'update', '<name>')
    print('  python', p, 'list', '<local>')
    print('  python', p, 'list', '<remote>')
    print('  python', p, 'list', '<update>')
    print('  python', p, 'download', '<name>')


if __name__ == '__main__':
    app_data_path = os.environ.get('LOCALAPPDATA')
    zeal_data_path = os.path.join(app_data_path, 'Zeal', 'Zeal')
    cachefile = os.path.join(zeal_data_path, 'cache', 'com.kapeli.json')
    docsetroot = os.path.join(zeal_data_path, 'docsets')

    action = None
    if len(sys.argv) > 1:
        action = sys.argv[1]

    if action == 'update':
        if len(sys.argv) > 2:
            d = sys.argv[2]
            update_docset_main(cachefile, docsetroot, d)
        else:
            update_all_docsets_main(cachefile, docsetroot)
    elif action == 'list':
        c = 'local'
        if len(sys.argv) > 2:
            c = sys.argv[2]
        list_docsets_main(os.path.basename(sys.argv[0]), cachefile, docsetroot, c)
    elif action == 'download':
        if len(sys.argv) > 2:
            n = sys.argv[2]
            download_docset_main(cachefile, docsetroot, n)
        else:
            usage_main(os.path.basename(sys.argv[0]))
    else:
        usage_main(os.path.basename(sys.argv[0]))
