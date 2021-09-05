hashes: hash_main.c hash_func.c 
	gcc hash_main.c hash_func.c -o hashes -lm

hash_main.o: hash_main.c hash.h
	gcc -c hash_main.c -o hash_main.o 

hash_func.o: hash_func.c hash.h
	gcc -c hash_func.c -o hash_main.o 