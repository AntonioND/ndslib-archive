@echo off

if "%DEVDIR%"=="" set DEVDIR=C:\devkitARM
echo Using %DEVDIR% as devkit directory.

echo Building the library...
make clean
make

echo Building devkit ARM update and copying files...
cd startup
make clean
make

echo *************************
echo *       WARNING         *
echo *************************
echo Copy crt files and linkerscript to devkit ARM library directory now?

if not "%UNATTENDED%"=="" goto yes
set /p CHOICE="yes or no?"
if (%CHOICE%==yes) goto yes
if (%CHOICE%==y) goto yes
goto end
:yes

copy *.o %DEVDIR%\arm-elf\lib\
copy *.ld %DEVDIR%\arm-elf\lib\
copy *.specs %DEVDIR%\arm-elf\lib\
copy thumb\*.o %DEVDIR%\arm-elf\lib\thumb\
copy interwork\*.o %DEVDIR%\arm-elf\lib\interwork\
copy thumb\interwork\*.o %DEVDIR%\arm-elf\lib\thumb\interwork\

if "%UNATTENDED%"=="" pause

:end

cd ..
