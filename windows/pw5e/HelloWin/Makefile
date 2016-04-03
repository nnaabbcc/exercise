
target=HelloWin
postext=.exe

CC86=i686-w64-mingw32-gcc
CC64=x86_64-w64-mingw32-gcc
LINK86=i686-w64-mingw32-gcc
LINK64=x86_64-w64-mingw32-gcc

CFLAGS=-mwindows -Wall -O2 -g
LIBFLAGS=-lwinmm

#SRC := ${wildcard *.c *.cpp *.cxx *.C *.CPP *.CXX}
SRC := ${wildcard *.c}
OBJ := ${patsubst %.c, %.o, $(SRC)}
X86OBJ := ${addprefix obj/x86/, $(OBJ)}
X64OBJ := ${addprefix obj/x64/, $(OBJ)}

all: $(OBJ)

#.PHONY : all 
	$(LINK86) $(CFLAGS) -o $(target).x86$(postext) $(X86OBJ) $(LIBFLAGS) 
	$(LINK64) $(CFLAGS) -o $(target).x64$(postext) $(X64OBJ) $(LIBFLAGS)


$(OBJ) : %.o : %.c
	@mkdir -p obj/x86
	@mkdir -p obj/x64
	$(CC86) $(CFLAGS) $(INCLUDE) -o obj/x86/$@ -c $< 
	$(CC64) $(CFLAGS) $(INCLUDE) -o obj/x64/$@ -c $< 

clean: cleanobj 
	rm -rf $(target).x86$(postext) $(target).x64$(postext)

cleanobj:
	rm -rf obj 
  
