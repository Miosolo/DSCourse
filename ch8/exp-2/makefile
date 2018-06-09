exp8-2:  graph.o travsal.o exp8-2.o
	g++ -o exp8-2 graph.o travsal.o exp8-2.o

graph.o: graph.cpp graph.h
	g++ -c graph.cpp

exp8-2.o: exp8-2.cpp graph.h
	g++ -c exp8-2.cpp

travsal.o: travsal.cpp graph.h
	g++ -c travsal.cpp
