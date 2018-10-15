all: s  c

s: server.c
	gcc $< -o $@ -l sqlite3
c: client.c
	gcc $< -o $@
clean:
	rm -rf s c
