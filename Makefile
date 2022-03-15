CXXFLAGS = 

main.exe: main.o negative_size_error.o
	g++ main.o negative_size_error.o -o main.exe --std=c++0x

main.o: main.cpp
	g++ -c main.cpp -o main.o --std=c++0x

negative_size_error.o: negative_size_error.cpp
	g++ -c negative_size_error.cpp -o negative_size_error.o 

.PHONY:
clean:
	rm *.exe *.o
