build:
	g++ -std=c++17 -stdlib=libc++ utils.cpp Token.cpp main.cpp -o compiler
compile:
	./compiler program.heph > hello.S
	as -o hello.o hello.s 
	ld -macosx_version_min 13.0.0 -o hello hello.o -lSystem -syslibroot `xcrun -sdk macosx --show-sdk-path` -e _start -arch arm64
run:
	./hello
uprun:
	as -o hello.o hello.s 
	ld -macosx_version_min 13.0.0 -o hello hello.o -lSystem -syslibroot `xcrun -sdk macosx --show-sdk-path` -e _start -arch arm64
	./hello
test:
	./compiler program.heph > hello.S
clean:
	rm hello hello.S hello.o
cleanall:
	rm hello hello.S hello.o compiler