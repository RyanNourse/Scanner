main:
	g++ main.cpp Scanner.cpp -o myScannerExecutable

run: main
	./myScannerExecutable example.txt

