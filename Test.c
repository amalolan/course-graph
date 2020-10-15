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
    LinkedList_delete(list, b, double_compare);
    LinkedList_print(list, double_toString);

    free(a);
    free(b);
    free(c);
    LinkedList_free(list);
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
    LinkedList_delete(list, b, (int(*)(const void*, const void*)) strcmp);
    LinkedList_print(list, string_toString);
//    free(a);
//    free(b);
//    free(c);
    LinkedList_free(list);
}

void testArrayListString() {
    printf("testArrayListString\n");
    char *a = "1232", *b = " avbsdfb", *c = "23rvjkne";
    ArrayList *list = malloc(sizeof(ArrayList));
    ArrayList_init(list);
    ArrayList_push(list, a);
    ArrayList_push(list, b);
    for (int i = 0; i < 10; i++) {
        ArrayList_push(list, c);
    }
    ArrayList_print(list, string_toString);
//    LinkedList_delete(list, b, (int(*)(const void*, const void*)) strcmp);
//    LinkedList_print(list, string_toString);
//    free(a);
//    free(b);
//    free(c);
    ArrayList_free(list);
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
    for (int i = 0; i < 10; i++) {
        ArrayList_push(list, c);
    }
    ArrayList_print(list, double_toString);
    free(a);
    free(b);
    free(c);
    free(list);
}
