axecdr : main.o axecdr.o
	g++ main.o axecdr.o -o axecdr 
axecdr.o :	
	g++ -c axecdr.cpp	
main.o : main.cpp
	g++ -c main.cpp
clean :
	del main.o axecdr.o axecdr.exe
