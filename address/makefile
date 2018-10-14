address:address.o main.o
	gcc $^ -o $@ -g
address.o:address.c
	gcc -c $< -o $@ -g
mian.o:main.c
	gcc -c $< -o $@ -g
clean:
	rm -rf *.o address
