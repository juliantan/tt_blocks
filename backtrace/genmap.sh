gcc -g -rdynamic add.c -fPIC -shared -o libadd.so -Wl,-Map,add.map
