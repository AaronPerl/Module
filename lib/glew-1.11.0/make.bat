gcc -m64 -DGLEW_NO_GLU -O2 -Wall -W -Iinclude  -DGLEW_BUILD -o src/glew.o -c src/glew.c
gcc -m64 -shared -Wl,-soname,libglew32.dll -Wl,--out-implib,lib/libglew32.dll.a    -o lib/glew32.dll src/glew.o -L/mingw/lib -lglu32 -lopengl32 -lgdi32 -luser32 -lkernel32

ar cr lib/libglew32.a src/glew.o

gcc -m64 -DGLEW_NO_GLU -DGLEW_MX -O2 -Wall -W -Iinclude  -DGLEW_BUILD -o src/glew.mx.o -c src/glew.c
gcc -m64 -shared -Wl,-soname,libglew32mx.dll -Wl,--out-implib,lib/libglew32mx.dll.a -o lib/glew32mx.dll src/glew.mx.o -L/mingw/lib -lglu32 -lopengl32 -lgdi32 -luser32 -lkernel32

ar cr lib/libglew32mx.a src/glew.mx.o

gcc -m64 -c -O2 -Wall -W -Iinclude  -o src/glewinfo.o src/glewinfo.c
gcc -m64 -O2 -Wall -W -Iinclude  -o bin/glewinfo.exe src/glewinfo.o -Llib  -lglew32 -L/mingw/lib -lglu32 -lopengl32 -lgdi32 -luser32 -lkernel32
gcc -m64 -c -O2 -Wall -W -Iinclude  -o src/visualinfo.o src/visualinfo.c
gcc -m64 -O2 -Wall -W -Iinclude  -o bin/visualinfo.exe src/visualinfo.o -Llib  -lglew32 -L/mingw/lib -lglu32 -lopengl32 -lgdi32 -luser32 -lkernel32