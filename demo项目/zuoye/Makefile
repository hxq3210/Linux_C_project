linklist:main.o linklist.o
	gcc $^ -o $@ -g
main.o:main.c
	gcc -c $< -o $@ -g
linklist.o:linklist.c
	gcc -c $< -o $@ -g
clean:
	rm -rf *.o linklist
