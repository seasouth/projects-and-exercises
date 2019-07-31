chop: chop.o edit.o text.o
	gcc chop.o edit.o text.o -o chop
chop.o: chop.c edit.h text.h
	gcc -Wall -std=c99 -g -c chop.c
edit.o: edit.c edit.h text.h
	gcc -Wall -std=c99 -g -c edit.c
text.o: text.c edit.h text.h
	gcc -Wall -std=c99 -g -c text.c
clean:
	rm -f chop.o edit.o text.o
	rm -f chop
	rm -f output.txt