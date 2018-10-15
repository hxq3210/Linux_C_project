linklist:linklist.o main,o
	gcc $^ -o $@ -g
linklist.o:linklist.c
	gcc -c $< -o $@ -g
main.o:main.c
	gcc -c $< -o $@ -g
clean:
	rm -rf *.o linklist
