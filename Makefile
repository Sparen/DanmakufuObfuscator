# USAGE:
#
# // to compile:
# make
# // remove compilation output files:
# make clean

# make variables let us avoid pasting these options in multiple places
CC = g++ 
CCFLAGS = -std=c++11 -Wall -Wextra -pedantic -O
#CCFLAGS = -std=c++11 -Wall -Wextra -pedantic -g -O

bin: dnhobf

dnhobf_fxn.o: dnhobf_fxn.cc dnhobf_fxn.h
	$(CC) $(CCFLAGS) -c dnhobf_fxn.cc

dnhobf.o: dnhobf.cc dnhobf_fxn.h
	$(CC) $(CCFLAGS) -c dnhobf.cc

dnhobf: dnhobf.o dnhobf_fxn.o
	$(CC) $(CCFLAGS) -o dnhobf dnhobf.o dnhobf_fxn.o

clean: 
	rm -f *.o dnhobf *# *~ *.exe *.gcov *.gcda *.gcno tmp/*
