# _*_ coding: utf-8 _*_
# This is demo for Hello word, not Hello World. just kidding
# 一些中文的注释也是可以用的

import os


def main():
    print 'Hello word, not Hello world, just kiding'

    # This is single line comments
    print "This is in single quote, okay"
    print "This is also okay. in double quote"

    ''' This is multi line comments
    second line of the comments
    '''
    foo(5, 10)  # This is also comments, call a function

    print "Hello " * 10
    hello10 = 'Hello ' * 20
    print hello10

    print '当前目录是: ' + os.getcwd()  # utf-8的文件可以使用中文

    # 变量需要先声明, 后使用
    counter = 0
    counter += 1

    # 看看循环是怎么用的
    foods = ['苹果', '李子', '杏子', '梨']  # 列表类型
    for food in foods:  # for loop should end of :
        print 'I love ' + food

    print 'Count to 10'
    for i in range(10):
        print i


def foo(param1, param2):
    res = param1 + param2
    print '%s + %s = %s' % (param1, param2, res)
    # Let's do some if
    if param1 < 5:
        print '%s smaller than 5' % param1
    elif param1 > 7 and (param2 < 10 or res < 15):
        print "I don't know something"
    else:
        print "Papa"
    return res

if __name__ == '__main__':
    print 'main() is not main, here is the main'
    main()
    print 'This is python'
