
@ECHO OFF

::SET FILEPATH=C:\zhaoyl\file1.7z
::SET FILEPATH=C:\zhaoyl\file2.wim
SET FILEPATH = Z:__IMAGE_PATH_

::SET FILEPATH=C:\zhaoyl\file3.zip

:: IF NOT EXIST %FILEPATH% (
::   GOTO:EOF
:: )

:: Get the extension name
SET EXT2=%FILEPATH:~-2%
SET EXT3=%FILEPATH:~-3%
:: make the extension name upper case
CALL :UpCase EXT2
CALL :UpCase EXT3

:: Get the file type
IF "%EXT2%" EQU "7Z" (
  :: Is 7z File
  CALL :Do7Z %FILEPATH%
) ELSE (
  IF "%EXT3%" EQU "ZIP" (
    :: Is Zip File
    CALL :DoZip %FILEPATH%
  ) ELSE IF "%EXT3%" EQU "WIM" (
    :: Is Wim File
    CALL :DoWIM %FILEPATH%
  )
)
:: End of the main
GOTO:EOF 

:: Functions
:UpCaseFILEPATH
FOR %%i IN ("a=A" "b=B" "c=C" "d=D" "e=E" "f=F" "g=G" "h=H" "i=I" "j=J" "k=K" "l=L" "m=M" "n=N" "o=O" "p=P" "q=Q" "r=R" "s=S" "t=T" "u=U" "v=V" "w=W" "x=X" "y=Y" "z=Z") DO CALL SET "%1=%%%1:%%~i%%"
GOTO:EOF

:Do7Z
:: Subroutine to Do actions for 7z file
SET FILEPATH=%1
ECHO %FILEPATH% is 7z file
GOTO:EOF

:DoZip
:: Subroutine to Do actions for Zip file
SET FILEPATH=%1
ECHO %FILEPATH% is zip file
GOTO:EOF

:DoWIM
:: Subroutine to Do actions for WIM file
SET FILEPATH=%1
ECHO %FILEPATH% is wim file
ECHO %FILEPATH:~-3% is extension name
ECHO %FILEPATH:~0,-4% is without extension name
GOTO:EOF