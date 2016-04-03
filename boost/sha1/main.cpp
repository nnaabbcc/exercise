
#include <boost/uuid/sha1.hpp>
#include <stdio.h>
#include <errno.h>

using namespace boost::uuids::detail;

void sha1sum(const char* fileName)
{
  sha1 sha;

  FILE * file = fopen(fileName, "rb");
  if (NULL == file)
  {
    fprintf(stderr, "Could not open file %s, errno(%d)\n", fileName, errno);
    return;
  }

  unsigned char buf[256];
  while(!feof(file))
  {
    int count = fread(buf, sizeof(unsigned char), 256, file);
    sha.process_bytes(buf, count);
  }

  unsigned int digest[5];
  sha.get_digest(digest);

  for (int i = 0; i < 5 ; i++)
  {
    printf("%08x", digest[i]);
  }

  printf("  %s\n", fileName);


  fclose(file);
}

int main(int argc, char* argv[])
{
  for (int i = 1; i < argc; i++)
  {
    sha1sum(argv[i]);
  }
  return 0;
}
