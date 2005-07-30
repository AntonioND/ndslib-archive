@echo off

gfx2gba -D -t8 -c256 -pbackground.pal background.bmp
gfx2gba -D -t8 -c16 -pgame.pal game.bmp
gfx2gba -D -t8 -c16 -pdefault.pal default.bmp
gfx2gba -D -t8 -c16 -pcur.pal cur.bmp
gfx2gba -D -t8 -c16 -pdarkain.pal darkain.bmp
gfx2gba -D -t8 -c16 -psquare.pal square.bmp
gfx2gba -D -t8 -c16 -pbutton.pal button.bmp

rm master.pal

mv -f *.pal ../resources/
mv -f *.raw ../resources/

pause
