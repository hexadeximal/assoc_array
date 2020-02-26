all:
	gcc main.c -o assoc -Wall -Wextra -pedantic -g -O2 -Werror=format-security -Wl,-z,defs -Wl,-z,now -Wl,-z,relro
