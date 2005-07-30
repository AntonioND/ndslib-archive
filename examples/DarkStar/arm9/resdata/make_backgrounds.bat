@echo off

gfx2gba -D -t8 -c16 -pfont.pal font.bmp
gfx2gba -D -t8 -c16 -pbuttons.pal buttons.bmp
rem gfx2gba -D -x -c32k DarkStar2.bmp
gfx2gba -D -x -t8 -c16 menu.bmp
gfx2gba -D -x -t8 -c16 icons.bmp
gfx2gba -D -x -t8 -c16 mines.bmp
gfx2gba -D -x -t8 -c16 mines2.bmp
gfx2gba -D -x -t8 -c16 ttt.bmp
gfx2gba -D -x -t8 -c16 default.bmp

mv -f *.pal ../resources/
mv -f *.raw ../resources/

pause
