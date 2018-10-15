all: s  c

s: server_bak.c
	gcc $< -o $@ 
c: client_cut.c
	gcc $< -o $@ 
clean:
	rm -rf s c div.txt
	rm -rf 部分*
