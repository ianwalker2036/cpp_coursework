tube: main.o tube.o
	g++ -Wall -g main.o tube.o -o tube

main.o: main.cpp tube.h
	g++ -c -g main.cpp

tube.o: tube.cpp tube.h
	g++ -c -g tube.cpp

clean: 
	rm -f *.o tube
