# hideProcesLinux

Source.c is an scrypt that hides a proces in Linux operating system. It will use scrypt.c. 

Compile with the following commands:

$ gcc -fPIC -shared -o library_name.so source.c -ldl

And then:

LD_PRELOAD=$(pwd)/library_name.so ps -aux