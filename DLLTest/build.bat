set PATH=D:\Programs\mingw-w64\mingw32\bin;%PATH%
g++ -c -DBUILD_DLL nDll.cpp
g++ -shared -o nDll.dll nDll.o -Wl,--out-implib,libnDll.a
pause