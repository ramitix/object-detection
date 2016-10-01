########################################
##
## Makefile
## LINUX compilation 
##
##############################################





#FLAGS
C++FLAG = -g -std=c++11

MATH_LIBS = -lm

EXEC_DIR=.


.cc.o:
	g++ $(C++FLAG) $(INCLUDES)  -c $< -o $@


#Including
INCLUDES=  -I. 

#-->All libraries (without LEDA)
LIBS_ALL =  -L/usr/lib -L/usr/local/lib 


#First Program (ListTest)

Cpp_OBJ_1=image.o  p1.o
PROGRAM_NAME_1=p1
$(PROGRAM_NAME_1): $(Cpp_OBJ_1)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(Cpp_OBJ_1) $(INCLUDES) $(LIBS_ALL)

Cpp_OBJ_2= image.o p2.o DisjSets.o 
PROGRAM_NAME_2=p2
$(PROGRAM_NAME_2): $(Cpp_OBJ_2)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(Cpp_OBJ_2) $(INCLUDES) $(LIBS_ALL)

Cpp_OBJ_3= image.o p3.o 
PROGRAM_NAME_3=p3
$(PROGRAM_NAME_3): $(Cpp_OBJ_3)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(Cpp_OBJ_3) $(INCLUDES) $(LIBS_ALL)

Cpp_OBJ_4= image.o p4.o 
PROGRAM_NAME_4=p4
$(PROGRAM_NAME_4): $(Cpp_OBJ_4)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(Cpp_OBJ_4) $(INCLUDES) $(LIBS_ALL)

all: 
	make $(PROGRAM_NAME_1)
	make $(PROGRAM_NAME_2)
	make $(PROGRAM_NAME_3) 
	make $(PROGRAM_NAME_4) 


runp1_2:	
		./$(PROGRAM_NAME_1) two_objects.pgm 130 p1_output.pgm

runp1_m1: 	
		./$(PROGRAM_NAME_1) many_objects_1.pgm 130 p1_output.pgm

runp1_m2:    	
		./$(PROGRAM_NAME_1) many_objects_2.pgm 130 p1_output.pgm

runp2: 	     	
		./$(PROGRAM_NAME_2) p1_output.pgm labeled.pgm

runp3:        	
		./$(PROGRAM_NAME_3) labeled.pgm database.txt p3_output.pgm

runp4:		
		./$(PROGRAM_NAME_4) labeled.pgm database.txt p4_output.pgm

clean:
	(rm -f *.o;)

(:
