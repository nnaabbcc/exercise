
CC86=i686-w64-mingw32-gcc
CC64=x86_64-w64-mingw32-gcc

CFLAGS=-mwindows

all : scrnsize.x86.exe scrnsize.x64.exe

scrnsize.x86.exe : scrnsize.c
	$(CC86) $(CFLAGS) -o $@ $< 

scrnsize.x64.exe : scrnsize.c
	$(CC64) $(CFLAGS) -o $@ $< 

clean:
	rm -f scrnsize.x86.exe scrnsize.x64.exe
