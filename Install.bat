SET DEVDIR=C:\devkitARM

@echo off
echo building the library
make clean

make

echo building devkit arm update and copying files
cd startup
make clean

make

echo *************************
echo *                       *
echo *       WARNING         *
echo *                       *
echo *************************

echo copy crt files and linkerscript 
echo to devkit arm lib directory? 
echo (must be done manualy if not)

set /p choice=yes or no?

if not (%choice%==yes or %choice%==y)exit

copy *.o %DEVDIR%\arm-elf\lib\
copy *.ld %DEVDIR%\arm-elf\lib\
copy *.specs %DEVDIR%\arm-elf\lib\
copy thumb\*.o %DEVDIR%\arm-elf\lib\thumb\
copy interwork\*.o %DEVDIR%\arm-elf\lib\interwork\
copy thumb\interwork\*.o %DEVDIR%\arm-elf\lib\thumb\interwork\

pause