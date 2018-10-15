bitree:bitree.o main.o
	gcc  $^ -o $@ -g
bitree.o:bitree.c
	gcc -c $< -o $@ -g
main.o:main.c
	gcc -c $< -o $@ -g
clean:
	rm -rf *.o bitree
