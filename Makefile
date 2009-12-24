all: 
	@echo please "'make bundle'" for mac or "'make shared'" for linux and others

bundle: sqlitearpa.c
	gcc -bundle -fPIC -Isqlite3 -o sqlitearpa.sqlext sqlitearpa.c 
	
shared: sqlitearpa.c
	gcc -shared -fPIC -Isqlite3 -o sqlitearpa.sqlext sqlitearpa.c

clean:
	rm -f sqlitearpa.sqlext