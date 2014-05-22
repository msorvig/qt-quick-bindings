all:
	lein deps && DYLD_LIBRARY_PATH=../lib lein compile && lein uberjar
run:
	DYLD_LIBRARY_PATH=../lib lein run -m hello.core
repl:
	DYLD_LIBRARY_PATH=../lib lein repl
clean:
	# Deleting the stored copy of QtQuck.har to force a reload
	rm -r ~/.m2/repository/local/QtQuick/
deps:
	lein deps	
	