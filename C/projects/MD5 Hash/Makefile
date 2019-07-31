hash: hash.o md5.o buffer.o
	gcc hash.o md5.o buffer.o -o hash
testdriver: testdriver.o hash.o md5.o buffer.o
	gcc -Wall -std=c99 -g -DTESTABLE testdriver.c md5.c buffer.c -o testdriver
hash.o: hash.c md5.h buffer.h
	gcc -Wall -std=c99 -g -c hash.c
buffer.o: buffer.c buffer.h md5.h
	gcc -Wall -std=c99 -g -c buffer.c
md5.o: md5.c md5.h buffer.h
	gcc -Wall -std=c99 -g -c md5.c
clean:
	-rm -f hash.o
	-rm -f md5.o
	-rm -f buffer.o
	-rm -f hash
	-rm -f output.txt
	-rm -f stderr.txt
