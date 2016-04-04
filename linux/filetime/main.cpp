
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

#include <string.h>
#include <stdio.h>
#include <errno.h>

#define BUFSIZE 256

void copyfile(const char* fileName)
{
  FILE *fIn = fopen(fileName, "rb");
  if (NULL == fIn)
  {
    fprintf(stderr, "Could not open file %s, errno(%d)\n", fileName, errno);
    return;
  }

  size_t nFileLen = strlen(fileName);
  char * dstFile = new char[nFileLen + 10];
  memset(dstFile, 0, nFileLen + 10);

  strcpy(dstFile, fileName);
  strcat(dstFile, ".new");

  FILE *fOut = fopen(dstFile, "wb");
  if (NULL == fOut)
  {
    fprintf(stderr, "Could not open file %s, errno(%d)\n", dstFile, errno);
    delete[] dstFile;
    fclose(fIn);
    return;
  }

  // Copy file contents
  unsigned char buf[BUFSIZE];
  while (!feof(fIn))
  {
    int count = fread(buf, sizeof(unsigned char), BUFSIZE, fIn);
    fwrite(buf, sizeof(unsigned char), count, fOut);
  }

  fclose(fIn);
  fclose(fOut);

  // read the attributes of src file
  struct stat sb;
  stat(fileName, &sb);
  printf("fileName: %s\n", fileName);
  printf("Last status change:      %s", ctime(&sb.st_ctime));
  printf("Last file access:        %s", ctime(&sb.st_atime));
  printf("Last file modification:  %s", ctime(&sb.st_mtime));
  printf("\n");
  // set the attributes of new file
  int fd = open(dstFile, O_WRONLY);
  if (fd < 0)
  {
    fprintf(stderr, "Could not Open %s, errno(%d)\n", dstFile, errno);
    return;
  }

  struct timespec ts[2];
  memcpy(&(ts[0]), (&sb.st_atime), sizeof(struct timespec));
  memcpy(&(ts[1]), (&sb.st_mtime), sizeof(struct timespec));

  if (futimens(fd, ts) == -1)
  {
    fprintf(stderr, "Set time for %s error, errno(%d)\n", dstFile, errno);
  }

  close(fd);
  delete[] dstFile;
}

int main(int argc, char* argv[])
{
  for (int i = 1; i < argc; i++)
  {
    copyfile(argv[i]);
  }
  return 0;
}
