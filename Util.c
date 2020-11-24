#include "Util.h"

int string_compare(const void *one, const void *two) {
    char *onec = (char *) one;
    char *twoc = (char *) two;
    return strcmp(onec, twoc);
}

void free_data(void *data) {
    free(data);
}

void dont_free(void *data) {
    return;
}

int direct_compare(const  void *one, const void *two) {
    return one != two;
}

void string_toString(const void *data, char *str) {
    strcpy(str, (char *)data);
}

void removeNewline(char *str) {
    size_t ln = strlen(str)-1;
    if (str[ln] == '\n')
        str[ln] = '\0';
}

