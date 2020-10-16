#include "Types.h"

int double_compare(const void *one, const void *two) {
    double *oned = (double *) one;
    double *twod = (double *) two;
    if (*oned > *twod) {
        return 1;
    } else if ((*oned - *twod) <= 0.0001 && (*oned - *twod) >= 0) {
        return 0;
    } else {
        return -1;
    }
}

void double_toString(const void *data, char* str) {
    sprintf(str, "%f",  *(double*)data);
}



void string_toString(const void *data, char* str) {
    strcpy(str, (char*)data);
}

void data_free(void *data) {
    free(data);
}

void dont_free(void *data) {

}