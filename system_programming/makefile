gd = gcc -ansi -pedantic-errors -Wall -Wextra -g
#gc = gcc -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3

vsa.out : vsa.o vsa_test.o
	$(gd) -o vsa.out vsa.o vsa_test.o

objects = vsa.out vsa.o vsa_test.o 

vsa.o : src/vsa.c include/vsa.h
	$(gd) -c src/vsa.c include/vsa.h -I include/
	
vsa_test.o : test/vsa_test.c include/tests.h include/vsa.h
	$(gd) -c test/vsa_test.c include/tests.h include/vsa.h -I include/
	
clean :
	rm -f $(objects)
	

