INC += -I/usr/local/pgsql/include
LNK += -L/usr/local/pgsql/lib -lpq

nectrf : main.o
	g++ -o nectrf main.o $(LNK)

main.o : main.cpp main.h
	g++ -c $(INC) main.cpp

clean :
	rm nectrf main.o main
