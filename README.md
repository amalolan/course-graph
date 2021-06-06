# course-graph
CS 203 Semester Project: A C Program that handles a course database. Given information about the various degrees offered in different departments of a college/university, and information about courses and their requirements, the program can keep track of different individuals' progress towards their degree and display the relevant courses they would need to take to complete their degrees.

## Build using make 
Makefile already exists. Just run make.

## Build Using cmake (recommended)
To build code run `cmake .` then `make`.

## Run Code
Execute the course_graph executable by so
`./course_graph arg1 arg2 ...`

**WARNING Erroneous input files will cause undefined behavior.**

Enter commands into CLI. Valid commands include `c`, `d`, `s`, `a`, `m`, `n`, `q`, `r`, `p c`, `p d`, `p g`, `p s` and
 `x`.
To exit enter `x`. All others have one argument associated with them.


### Run example code
First build the code. Then run


`./course_graph input/ex-department-math.txt input/ex-degree-bscs.txt input/ex-department-cs.txt input/ex-degree-abcs.txt input/degree-asia.txt input/degree-afs.txt input/department-asia.txt input/department-afs.txt input/ex-student1.txt input/ex-student2.txt input/ex-student3.txt input/ex-student4.txt input/ex-student5.txt`
 
