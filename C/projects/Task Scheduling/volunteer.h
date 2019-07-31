/**
   @file volunteer.h
   @author Cole Southern

   Header for the volunteer component, defining part of the schedule
   representation.
 */
#include <string.h>
#include <stdbool.h>

/** Maximum length of a volunteer or a task name. */
#define MAX_WORD 20

/** Initial capacity for resizable arrays. */
#define INITIAL_CAP 3

#define TIME_CUTOFF 8
#define MINUTES_IN_HOUR 60
#define MILITARY_TIME 12

/** Representation ofr a task that a volunteer is responsible for. */
typedef struct {
  /** Name of the task (e.g. an attraction name) where the volunteer is
      working. */
  char name[ MAX_WORD + 1 ];

  /** Start time of the task. */
  int startHour;
  int startMinute;
  
  /** End time of the task. */
  int endHour;
  int endMinute;
} Task;

/** Representation for a volunteer, with a resizable array holding a set
    of tasks. */
typedef struct {
  /** Name of the volunteer. */
  char name[ MAX_WORD + 1 ];

  /** List of tasks for this volunteer. */
  Task *tlist;

  /** Number of tasks on tlist. */
  int tcount;

  /** Capacity of the task list. */
  int tcap;
} Volunteer;

/**
 * Dynamically allocates a new instance of the Volunteer struct,
 * using the given name to copy into it, and sets up its resizable
 * array of tasks.
 * @param name char pointer to be used as Volunteer's name
 * @return Returns a pointer to a Volunteer instance with given name
 */
extern Volunteer *makeVolunteer(char *name);

/**
 * Frees all the dynamically allocated memory for the Volunteer
 * that was passed in as a parameter, including the Volunteer
 * struct itself and the task list inside it.
 * @param v pointer to Volunteer struct to be freed
 */
extern void freeVolunteer(Volunteer *v);

/**
 * Sorts the tasks associated with the given Volunteer in
 * chronological order, uses qsort to do so.
 * @param v pointer to Volunteer to sort the tasks for
 */
extern void sortTasks(Volunteer *v);

/**
 * Prints out a report for a single Volunteer, used by the
 * report command given by the user.
 * @param v pointer to Volunteer to report status
 */
extern void reportVolunteer(Volunteer *v);
