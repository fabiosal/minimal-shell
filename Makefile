.DEFAULT_GOAL := run

msh: msh.c
	gcc msh.c -o msh

clean:
	rm msh

run: msh
	./msh

