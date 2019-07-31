/**
   @file schedule.c
   @author Cole Southern

   Main component for the schedule application.  For a collection of
   volunteers, it keeps a set of times when they're responsible for
   tasks.
 */

#include <stdlib.h>
#include <stdio.h>
#include "volunteer.h"

/** Maximum command length. */
#define MAX_COMMAND 7


/** Representation for the whole schedule. */
typedef struct {
  /** List of volunteers. */
  Volunteer **vlist;

  /** Number of volunteers */
  int vcount;

  /** Capacity of the volunteer list. */
  int vcap;
} Schedule;

/**
 * Dynamically acllocates a new Schedule instance, initializing
 * its fields and returning a pointer to it.
 * @return s pointer to an instance of a Schedule
 */
Schedule *makeSchedule()
{
    Schedule *s = (Schedule *)malloc(sizeof(Schedule));
    s->vcap = INITIAL_CAP;
    s->vcount = 0;
    s->vlist = (Volunteer **)malloc(s->vcap * sizeof(Volunteer *));
    return s;
}

/**
 * Frees all the memory for the given schedule, including freeing
 * volunteers in the vlist, freeing the vlist, and freeing the
 * instance of the Schedule itself.
 * @param sched pointer to Schedule instance to free
 */
void freeSchedule(Schedule *sched)
{
    for (int i = 0; i < sched->vcount; i++) {
        freeVolunteer(sched->vlist[i]);
    }
    free(sched->vlist);
    free(sched);
}

/**
 * Helper method for parseTask. Determines if the Task being added
 * is invalid or conflicts with other Tasks already given to
 * the Volunteer in question.
 * @param v const Pointer to Volunteer assigned to Task
 * @param t Task given to Volunteer
 * @return boolean value indicating whether Task is valid
 */
bool checkValidTask(Volunteer const *v, Task t) {
    int sh = t.startHour;
    int eh = t.endHour;
    if (eh < TIME_CUTOFF || (eh == TIME_CUTOFF && sh < eh)) {
        eh += MILITARY_TIME;
    }
    if (sh < TIME_CUTOFF) {
        sh += MILITARY_TIME;
    }
    if (sh > eh) {
        return false;
    }
    for (int i = 0; i < v->tcount; i++) {
        int vsh = (v->tlist + i)->startHour;
        int veh = (v->tlist + i)->endHour;
        if (vsh < TIME_CUTOFF) {
            vsh += MILITARY_TIME;
        }
        if (veh < TIME_CUTOFF) {
            veh += MILITARY_TIME;
        }
        if (sh > vsh && sh < veh) {
            return false;
        }
        if (eh > vsh && eh < veh) {
            return false;
        }
        if (eh == vsh) {
            if (t.startMinute > (v->tlist + i)->startMinute
            && t.startMinute < (v->tlist + i)->endMinute) {
                return false;
            }
            if (t.endMinute > (v->tlist + i)->startMinute) {
                if (t.endMinute < (v->tlist + i)->endMinute) {
                    return false;
                }
                if (eh != veh) {
                    return false;
                }
            }
        }
    }
    return true;
}

/**
 * Parses the rest of an "add" command given by the user, adds
 * the task to the correct Volunteer's tlist. If no Volunteer
 * with the given name, it also creates a Volunteer instance
 * with that name.
 * @param fp allows this function to read a task from a file
 * @param sched pointer to Schedule instance to add the task to
 * @return true if add command is valid, false if not
 */
bool parseTask(FILE *fp, Schedule *sched)
{
    char name[MAX_WORD + 1];
    char t[MAX_WORD + 1];
    int sh, sm, eh, em;
    fscanf(fp, "%s%s%d%*c%d%d%*c%d", name, t, &sh, &sm, &eh, &em);
    if (sm > MINUTES_IN_HOUR || em > MINUTES_IN_HOUR || (sh == eh && sm > em)) {
        printf("Invalid command\n");
        return false;
    }
    if (strlen(name) > MAX_WORD) {
        printf("Invalid command\n");
        return false;
    }
    if (strlen(t) > MAX_WORD) {
        printf("Invalid command\n");
        return false;
    }
    Task task = {};
    strcpy(task.name, t);
    task.startHour = sh;
    task.startMinute = sm;
    task.endHour = eh;
    task.endMinute = em;
    for (int i = 0; i < sched->vcount; i++) {
        if (strcmp((char *)name, sched->vlist[i]->name) == 0) {
            if (sched->vlist[i]->tcount == sched->vlist[i]->tcap) {
                sched->vlist[i]->tcap *= 2;
                sched->vlist[i]->tlist =
                    (Task *)realloc(sched->vlist[i]->tlist,
                    sched->vlist[i]->tcap * sizeof(Task));
            }
            if (!checkValidTask(sched->vlist[i], task)) {
                printf("Invalid command\n");
                return false;
            }
            sched->vlist[i]->tlist[sched->vlist[i]->tcount] = task;
            sched->vlist[i]->tcount++;
            return true;
        }
    }
    Volunteer *v = makeVolunteer((char *)name);
    v->tlist[v->tcount] = task;
    v->tcount++;
    if (sched->vcount == sched->vcap) {
        sched->vcap *= 2;
        sched->vlist = (Volunteer **)realloc(sched->vlist, sched->vcap * sizeof(Volunteer *));
    }
    sched->vlist[sched->vcount] = v;
    sched->vcount++;
    return true;
}

/**
 * Removes the task at the given time for the volunteer with the
 * given name. If the volunteer has no remaining tasks, it also
 * removes them from the schedule.
 * @param sched pointer to Schedule containing the task to remove
 * @param name pointer to String containing the volunteer's name
 * @param startHour starting hour of the event to remove
 * @return true if command was valid, false if not
 */
bool cancel(Schedule *sched, char *name, int sh, int sm)
{
    for (int i = 0; i < sched->vcount; i++) {
        if (strcmp(name, sched->vlist[i]->name) == 0) {
            for (int j = 0; j < sched->vlist[i]->tcount; j++) {
                if ((sched->vlist[i]->tlist + j)->startHour == sh
                        && (sched->vlist[i]->tlist + j)->startMinute == sm) {
                    while (j < sched->vlist[i]->tcount - 1) {
                        sched->vlist[i]->tlist[j] = sched->vlist[i]->tlist[j + 1];
                        j++;
                    }
                    sched->vlist[i]->tcount--;
                    if (sched->vlist[i]->tcount == 0) {
                        freeVolunteer(sched->vlist[i]);
                        while (i < sched->vcount - 1) {
                            sched->vlist[i] = sched->vlist[i + 1];
                            i++;
                        }
                        sched->vcount--;
                    }
                    return true;
                }
            }
        }
    }
    printf("Invalid command\n");
    return false;
}

/**
 * Helper method for qsort found in function sortSchedule,
 * Sorts the Volunteers in lexicographic order (alphabetic
 * order).
 * @param aptr void pointer to first Volunteer
 * @param bptr void pointer to second Volunteer
 * @return int indicating order of the two Volunteers
 */
int scheduleSort(const void *aptr, const void *bptr)
{
    Volunteer const *a = aptr;
    Volunteer const *b = bptr;
    Volunteer **ap = (Volunteer **)a;
    Volunteer **bp = (Volunteer **)b;
    char aname[MAX_WORD + 1];
    char bname[MAX_WORD + 1];
    strcpy(aname, (*ap)->name);
    strcpy(bname, (*bp)->name);
    int cmp = strcmp(aname, bname);
    if (cmp < 0) {
        return -1;
    } else if (cmp > 0) {
        return 1;
    } else {
        return 0;
    }
}

/**
 * Sorts the list of Volunteers in the schedule to be listed in
 * lexicographic order, so they can be displayed that way when
 * the user requests the list of Volunteers.
 * @param sched pointer to Schedule to sort Volunteers in
 */
void sortSchedule(Schedule *sched)
{
    qsort(sched->vlist, sched->vcount, sizeof(Volunteer *), scheduleSort);
}

/**
 * Program starting point. Creates an instance of a schedule,
 * keeps track of the number of Volunteers in the schedule for
 * the ability to traverse the Volunteers in the schedule, reads
 * from standard input to interpret commands by the user, and
 * delegates those commands appropriately.
 * @return returns exit status.
 */
int main()
{
    Schedule *schedule = makeSchedule();
    char c[MAX_COMMAND];
    while (scanf("%s", c) != EOF) {
        if (strcmp(c, "add") == 0) {
            parseTask(stdin, schedule);
        } else if (strcmp(c, "report") == 0) {
            bool isThere = false;
            Volunteer *r;
            char name[MAX_WORD + 1];
            scanf("%s", name);
            for (int i = 0; i < schedule->vcount; i++) {
                if (strcmp(name, schedule->vlist[i]->name) == 0) {
                    isThere = true;
                    r = schedule->vlist[i];
                    reportVolunteer(r);
                }
            }
            if (!isThere) {
                printf("Invalid command\n");
            }
        } else if (strcmp(c, "cancel") == 0) {
            char name[MAX_WORD + 1];
            int hour, minute;
            scanf("%s%d%*c%d", name, &hour, &minute);
            cancel(schedule, name, hour, minute);
        } else if (strcmp(c, "list") == 0) {
            sortSchedule(schedule);
            for (int i = 0; i < schedule->vcount; i++) {
                printf("%s\n", schedule->vlist[i]->name);
            }
        } else if (strcmp(c, "quit") == 0) {
            freeSchedule(schedule);
            return EXIT_SUCCESS;
        } else {
            char ch;
            while ((ch = getchar()) != '\n') {
                ch = getchar();
            }
            printf("Invalid command\n");
        }
    }
    if (schedule) {
      freeSchedule(schedule);
    }
    return EXIT_SUCCESS;
}
