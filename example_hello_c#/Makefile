all:
	# copy the qmlbindings module (must be in the main exe directory)
	cp ../lib/qmlbindings.netmodule . &&\
	mcs -addmodule:qmlbindings.netmodule main.cs 
run:
	DYLD_LIBRARY_PATH=../lib mono main.exe
