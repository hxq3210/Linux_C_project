seqstack:seqstack.o main.o
	gcc $^ -o $@ -g
seqstack.o:seqstack.c
	gcc -c $< -o $@ -g
main.o:main.c
	gcc -c $< -o $@ -g
clean:
	rm -rf *.o seqstack
