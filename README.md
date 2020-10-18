# course-graph
CS 203 Project 1 - Course Dependencies Graph

## Build using make 
Makefile already exists. Just run make.

## Build Using cmake (recommended)
To build code run `cmake .` then `make`.

## Run Code
Execure the course_graph executable by so
`./course_graph arg1 arg2 ...`

**WARNING Erroneous input files will cause undefined behavior.**

Enter commands into CLI. Valid commands include `c`, `d`, `s`, `p c`, `p d`, `p g`, and `x`.
To exit enter `x`. Others all have one argument associated with them.


### Run example code
First build the code. Then run


`./course_graph input/ex-department-math.txt input/ex-degree-bscs.txt input/ex-department-cs.txt input/ex-degree-abcs
.txt input/degree-asia.txt input/degree-afs.txt input/department-asia.txt input/department-afs.txt`

## REPORT
* Implemented all functionality requested. 
* Used `void *` pointers to enable generics. 
* Generic ArrayList and LinkedList created.
* Course names were stored in LinkedList.
* Degree is a LinkedList of LinkedLists. The 2D LinkedLists were disjuncts, 1D are the conjuncts.
* Department is an ArrayList of courses. Courses have LinkedList of prereqs (strings of their names).
* Comparator functions were used to find objects in linked lists.
* Memory freeing was done 'recursively' in the sense that each data type had a special destructor and parents called
 children's destructors 