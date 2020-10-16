#include "Course.h"

void Course_init(Course *c, char *title, char *name, LinkedList *prereqs) {
    strcpy(c->name, name);
    strcpy(c->title, title);
    prereqs = prereqs;
}
