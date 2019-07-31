/**
   @file volunteer.c
   @author Cole Southern

   Source file for the volunteer component, assists schedule.c in defining
   Volunteers to which to assign particular tasks and add to the schedule.
   This particular class allows the schedule program to create a Volunteer,
   free the Volunteer from the schedule, sort the tasks in the Volunteer'sbrk
   task list, and display the tasks assigned to any particular Volunteer.
 */
#include <stdlib.h>
#include <stdio.h>
#include "volunteer.h"

/** Character field width for indentation of tasks when user calls report. */
#define INDENT 24
/**
 * Preprocessor converting indentation number to string to be used as
 * a character field width in printf."
 */
#define INDENT_(x) #x
/**
 * Function to be called in printf conversion specifiers to convert the
 * indentation number to a string using the preprocessor defined above.
 */
#define INDENTATION(x) INDENT_(x)
/**
 * Special case of a Volunteer working 12 hours requires macro for the
 * number of minutes in 12 hours.
 */
#define TWELVE_HOURS 720
/**
 * Defining TEN to avoid magic numbers in program. Allows a 0 to be
 * added if the number of minutes is less than 10. e.g. 6: 9 will
 * be displayed correctly as 6:09.
 */
#define TEN 10


/**
 * Dynamically allocates a new instance of the Volunteer struct,
 * using the given name to copy into it, and sets up its resizable
 * array of tasks.
 * @param name char pointer to be used as Volunteer's name
 * @return Returns a pointer to a Volunteer instance with given name
 */
Volunteer *makeVolunteer(char *name)
{
    Volunteer *v = (Volunteer *)malloc(sizeof(Volunteer));
    strcpy(v->name, name);
    v->tcap = INITIAL_CAP;
    v->tcount = 0;
    v->tlist = (Task *)malloc(v->tcap * sizeof(Task));
    return v;
}

/**
 * Frees all the dynamically allocated memory for the Volunteer
 * that was passed in as a parameter, including the Volunteer
 * struct itself and the task list inside it.
 * @param v pointer to Volunteer struct to be freed
 */
void freeVolunteer(Volunteer *v)
{
    free(v->tlist);
    free(v);
}

/**
 * Helper method for qsort found in function sortTasks,
 * Sorts the tasks in chronological order (if one task
 * starts before another, it will be listed before the
 * other).
 * @param aptr void pointer to first Task
 * @param bptr void pointer to second Task
 * @return int indicating order of the two Tasks
 */
int taskSort(const void *aptr, const void *bptr)
{
    Task const *a = aptr;
    Task const *b = bptr;
    
    int aH = a->startHour;
    int bH = b->startHour;
    if (aH < TIME_CUTOFF) {
        aH += MILITARY_TIME;
    }
    if (bH < TIME_CUTOFF) {
        bH += MILITARY_TIME;
    }
    if (aH < bH) {
        return -1;
    } else if (aH > bH) {
        return 1;
    } else {
        if (a->startMinute < b->startMinute) {
            return -1;
        }
        if (a->startMinute > b->startMinute) {
            return 1;
        } else {
            return 0;
        }
    }
}

/**
 * Sorts the tasks associated with the given Volunteer in
 * chronological order, uses qsort to do so.
 * @param v pointer to Volunteer to sort the tasks for
 */
void sortTasks(Volunteer *v)
{
    qsort(v->tlist, v->tcount, sizeof(Task), taskSort);
}

/**
 * Prints out a report for a single Volunteer, used by the
 * report command given by the user.
 * @param v pointer to Volunteer to report status
 */
void reportVolunteer(Volunteer *v)
{
    printf("%s ", v->name);
    int minutes = 0;
    for (int i = 0; i < v->tcount; i++) {
        int vsh = (v->tlist + i)->startHour;
        int veh = (v->tlist + i)->endHour;
        if (veh < TIME_CUTOFF || (veh == TIME_CUTOFF && vsh < veh)) {
            veh += MILITARY_TIME;
        }
        if (vsh < TIME_CUTOFF) {
            vsh += MILITARY_TIME;
        }

        int add = veh - vsh;
        add *= MINUTES_IN_HOUR;
        int sub = ((v->tlist + i)->endMinute) - ((v->tlist + i)->startMinute);
        add += sub;
        minutes += add;
    }
    if (minutes == 0) {
        minutes = TWELVE_HOURS;
    }
    printf("(%d)\n", minutes);
    sortTasks(v);
    for (int i = 0; i < v->tcount; i++) {
        if ((v->tlist + i)->startMinute < TEN) {
            if ((v->tlist + i)->endMinute < TEN) {
                printf("%" INDENTATION(INDENT) "s %2d:0%d %2d:0%d\n",
                (v->tlist + i)->name, (v->tlist + i)->startHour, (v->tlist + i)->startMinute,
                (v->tlist + i)->endHour, (v->tlist + i)->endMinute);
            } else {
                printf("%" INDENTATION(INDENT) "s %2d:0%d %2d:%2d\n",
                (v->tlist + i)->name, (v->tlist + i)->startHour, (v->tlist + i)->startMinute,
                (v->tlist + i)->endHour, (v->tlist + i)->endMinute);
            }
        } else if ((v->tlist + i)->endMinute < TEN) {
            printf("%" INDENTATION(INDENT) "s %2d:%2d %2d:0%d\n",
            (v->tlist + i)->name, (v->tlist + i)->startHour, (v->tlist + i)->startMinute,
            (v->tlist + i)->endHour, (v->tlist + i)->endMinute);
        } else {
            printf("%" INDENTATION(INDENT) "s %2d:%2d %2d:%2d\n",
            (v->tlist + i)->name, (v->tlist + i)->startHour, (v->tlist + i)->startMinute,
            (v->tlist + i)->endHour, (v->tlist + i)->endMinute);
        }
    }
}
