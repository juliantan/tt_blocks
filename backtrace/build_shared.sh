gcc -g -rdynamic add.c -fPIC -shared -o libadd.so
gcc -g -rdynamic backtrace.c dump.c -L. -ladd -Wl,-rpath=. -o backtrace
