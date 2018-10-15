student:student.o main.o
	gcc $^ -o $@ -g
student.o:student.c
	gcc -c $< -o $@ -g
main.o:main.c
	gcc -c $< -o $@ -g
clean:
	rm -rf *.o student
