all:
	gcc main.c -o example_hello_c -I../src -L../lib -lqmlbindings
run:
	DYLD_LIBRARY_PATH=../lib ./example_hello_c