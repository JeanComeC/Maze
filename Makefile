all : maze.exe

rdfs_generator.o: src/rdfs_generator.c src/rdfs_generator.h
	gcc -c src/rdfs_generator.c

resolver_breadthfirstsearch.o: src/resolver_breadthfirstsearch.c src/resolver_breadthfirstsearch.h
	gcc -c src/resolver_breadthfirstsearch.c

resolver_djikstra.o: src/resolver_djikstra.c src/resolver_djikstra.h
	gcc -c src/resolver_djikstra.c

resolver_a.o: src/resolver_a.c src/resolver_a.h
	gcc -c src/resolver_a.c

main.o: src/main.c src/rdfs_generator.h src/resolver_breadthfirstsearch.h src/resolver_djikstra.h src/resolver_a.h
	gcc -c src/main.c

maze.exe: resolver_a.o resolver_djikstra.o resolver_breadthfirstsearch.o rdfs_generator.o main.o
	gcc -o maze.exe resolver_a.o resolver_djikstra.o resolver_breadthfirstsearch.o rdfs_generator.o main.o

.PHONY: clean
clean:
	rm -f *.o maze.exe

# NE PAS OUBLIER DE RAJOUTER LES BIBLIOTHEQUES SPECIALES	!!!
#-lssl -lcrypto -lncurses