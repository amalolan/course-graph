course_graph.exe: main.o ArrayList.o Course.o BinaryTree.o Requirements.o Student.o Degree.o Department.o Graph.o InputHandler.o LinkedList.o Test.o Util.o
	gcc -Wall -g main.o ArrayList.o Course.o BinaryTree.o Requirements.o Student.o Degree.o Department.o Graph.o InputHandler.o LinkedList.o Test.o Util.o -o course_graph

main.o: main.c
	gcc -Wall -g -c  main.c

ArrayList.o: ArrayList.h ArrayList.c
	gcc -Wall -g -c ArrayList.c

Course.o: Course.h Course.c
	gcc -Wall -g -c Course.c

BinaryTree.o: BinaryTree.h BinaryTree.c
	gcc -Wall -g -c BinaryTree.c

Requirements.o: Requirements.h Requirements.c
	gcc -Wall -g -c Requirements.c
	
Student.o: Student.h Student.c
	gcc -Wall -g -c Student.c

Degree.o: Degree.h Degree.c
	gcc -Wall -g -c Degree.c

Department.o: Department.h Department.c
	gcc -Wall -g -c Department.c

InputHandler.o: InputHandler.h InputHandler.c
	gcc -Wall -g -c InputHandler.c  
Graph.o: Graph.h Graph.c
	gcc -Wall -g -c Graph.c  
LinkedList.o: LinkedList.h LinkedList.c
	gcc -Wall -g -c LinkedList.c
Test.o: Test.h Test.c
	gcc -Wall -g -c Test.c
Util.o: Util.h Util.c
	gcc -Wall -g -c Util.c