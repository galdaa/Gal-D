gd = gcc -ansi -pedantic-errors -Wall -Wextra -g

sort.out : sort.o sort_test.o 
	$(gd) -o sort.out sort.o sort_test.o 

objects = sort.out sort.o sort_test.o 

sort.o : src/sort.c include/sort.h
	$(gd) -c src/sort.c include/sort.h -I include/

sort_test.o : test/sort_test.c include/sort.h
	$(gd) -c test/sort_test.c include/sort.h -I include/
	
clean :
	rm -f $(objects)
	

