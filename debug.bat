rmdir /s /q out
%GDK_WIN%\bin\make -f %GDK_WIN%\makefile.gen debug
.\tool\Fusion\Fusion.exe out\rom.bin