#include "Test.h"


void testLinkedListDouble() {
    printf("testLinkedListDouble\n");
    double *a, *b, *c;
    a = (double *) malloc(sizeof(double)), b = (double *) malloc(sizeof(double)), c = (double *) malloc(sizeof(double));
    *a = 3.232;
    *b = 20.121;
    *c = 1.314;

    LinkedList *list = malloc(sizeof(LinkedList));
    LinkedList_init(list);
    LinkedList_push(list, a);
    LinkedList_push(list, b);
    for (int i = 0; i < 10; i++) {
        LinkedList_push(list, c);
    }
    LinkedList_print(list, double_toString);
    LinkedList_delete(list, b, double_compare, data_free);
    LinkedList_print(list, double_toString);

    LinkedList_free(list, data_free);
}


void testLinkedListString() {
    printf("testLinkedListString\n");
    char *a = "1232", *b = " avbsdfb", *c = "23rvjkne";
    LinkedList *list = malloc(sizeof(LinkedList));
    LinkedList_init(list);
    LinkedList_push(list, a);
    LinkedList_push(list, b);
    for (int i = 0; i < 10; i++) {
        LinkedList_push(list, c);
    }
    LinkedList_print(list, string_toString);
    LinkedList_delete(list, b, (int (*)(const void *, const void *)) strcmp);
    LinkedList_print(list, string_toString);
    LinkedList_free(list, dont_free);
}

void testArrayListString() {
    printf("testArrayListString\n");
    char *a = "1232", *b = " avbsdfb", *c = "23rvjkne";
    ArrayList *list = malloc(sizeof(ArrayList));
    ArrayList_init(list);
    ArrayList_push(list, a);
    ArrayList_push(list, b);
    ArrayList_push(list, c);

    ArrayList_print(list, string_toString);
    ArrayList_free(list, dont_free);
}


void testArrayListDouble() {
    printf("testArrayListDouble\n");
    double *a, *b, *c;
    a = (double *) malloc(sizeof(double)), b = (double *) malloc(sizeof(double)), c = (double *) malloc(sizeof(double));
    *a = 3.232;
    *b = 20.121;
    *c = 1.314;

    ArrayList *list = malloc(sizeof(ArrayList));
    ArrayList_init(list);
    ArrayList_push(list, a);
    ArrayList_push(list, b);
    ArrayList_push(list, c);
    ArrayList_print(list, double_toString);
    ArrayList_free(list, data_free);
}

void testDegree() {
    char line1[] = "OR CS 104, CS 105, CS 106", line2[] = "CS 150", line3[] = "OR MATH 186, MATH 286, MATH 336";
    Degree *d = malloc(sizeof(Degree));
    Degree_init(d, "BA Computer Science");
    Degree_parseLine(d, line1);
    Degree_parseLine(d, line2);
    Degree_parseLine(d, line3);
//    char *degreeStr = malloc(strlen(line1) + strlen(line2) + strlen(line3));
//    Degree_toString(d, degreeStr);
//    printf("%s\n", degreeStr);
    Degree_free(d);
//    free(degreeStr);
}
