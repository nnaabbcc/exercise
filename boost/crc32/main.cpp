
#include <boost/crc.hpp>
#include <stdio.h>
#include <errno.h>

using namespace boost;

void crc32sum(const char* fileName)
{
  crc_32_type crc32;

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
    crc32.process_bytes(buf, count);
  }

  printf("%08x  %s\n", crc32.checksum(), fileName);


  fclose(file);
}

int main(int argc, char* argv[])
{
  for (int i = 1; i < argc; i++)
  {
    crc32sum(argv[i]);
  }
  return 0;
}
