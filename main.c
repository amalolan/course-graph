#include "Test.h"

int main(int argc, char *argv[]) {
    testArrayListDouble();
    testArrayListString();
    testLinkedListDouble();
    testLinkedListString();
    testDegree();
    testCourse();
    if (argc > 1) {
        readDegree(argv[1]);
    }
//    }
    return 0;
}
