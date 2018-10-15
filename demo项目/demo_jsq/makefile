jsq:jsq.o main.o
	gcc $^ -o $@
jsq.o:jsq.c
	gcc -c $< -o $@
main.o:main.c
	gcc -c $< -o $@
clean:
	rm -rf *.o jsq
