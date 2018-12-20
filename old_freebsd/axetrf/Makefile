INC += -I/usr/local/pgsql/include
LNK += -L/usr/local/pgsql/lib -lpq

axetrf : main.o
	g++ -o axetrf  main.o $(LNK)

main.o : main.cpp main.h
	g++ -c $(INC) main.cpp

clean :
	rm axetrf main.o main
