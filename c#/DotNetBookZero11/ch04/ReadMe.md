# Use nmake for build

## Build 
nmake /f Makefile.nmake  
nmake /f Makefile.nmake all  

## Build FirstProgram seperately
nmake /f Makefile.nmake FirstProgram.exe

## Build HelloWorld.exe seperately
nmake /f Makefile.nmake HelloWorld.exe

## Disassamble FirstProgram.exe
nmake /f Makefile.nmake dasm

## Assamble FirstProgram again
nmake /f Makefile.nmake asm

## Clean all
nmake /f Makefile.nmake clean
