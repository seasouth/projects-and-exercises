schedule: schedule.o volunteer.o
	gcc schedule.o volunteer.o -o schedule
schedule.o: schedule.c volunteer.h
	gcc -Wall -std=c99 -g -c schedule.c
volunteer.o: volunteer.c volunteer.h
	gcc -Wall -std=c99 -g -c volunteer.c
clean:
	-rm -f schedule.o volunteer.o
	-rm -f schedule
	-rm -f output.txt