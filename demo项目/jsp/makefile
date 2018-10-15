.PHONY: clean install uninstall

jsq: add.o sub.o mul.o chu.o main.o
	gcc $^ -o $@

add.o: add.c
	gcc -c $< -o $@
sub.o: sub.c
	gcc -c $< -o $@
mul.o: mul.c
	gcc -c $< -o $@
chu.o: chu.c
	gcc -c $< -o $@
	
clean:
	rm -rf *.o jsq

install:
	cp jsq /usr/sbin/
uninstall:
	rm  /usr/sbin/jsq
