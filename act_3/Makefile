# to make a PDB starting from foo.psvn  type the command:     make pdb ss=foo
# if $(absname).txt exists it will be used as the input (abstraction commands) to build the abstraction,
#   otherwise the user will enter the abstraction commands interactively.

ACTDIR = act_1
CC = gcc
CXX = g++
OPT = -g -Wall -O3 -Wno-unused-function -Wno-unused-variable

PSVNOPT0 = --state_map --no_backwards_moves --fwd_history_len=0 --keep_duplicate_rules

psvn2c_core.c:
	cp ../src/psvn2c_core.c ./psvn2c_core.c

psvn2c_state_map.c:
	cp ../src/psvn2c_state_map.c ./psvn2c_state_map.c

psvn2c_abstraction.c:
	cp ../src/psvn2c_abstraction.c ./psvn2c_abstraction.c

%.c: %.psvn psvn2c_core.c psvn2c_state_map.c psvn2c_abstraction.c
	../bin/psvn2c $(PSVNOPT0) --name=$(*F) < $< > $@
	rm -f ./psvn2c_core.c ./psvn2c_state_map.c ./psvn2c_abstraction.c

.PRECIOUS: %.c

#actividad 3
%.act3: %.c ../algorithms/actividad3.cpp
	$(CXX) $(OPT) ../algorithms/actividad3.cpp -std=gnu++0x -include $< -o $@
	rm -f $*.c

#actividad 1_2
%.act1: %.c ../algorithms/actividad1.cpp
	$(CXX) $(OPT) ../algorithms/actividad1.cpp -std=gnu++0x -include $< -o $@
	rm -f $*.c

.PHONY: clean
clean:
	rm -fr *.succ *.iddfs* *.act* *.dist_pdb psvn2c_core.c psvn2c_state_map.c *.dSYM *.o *~
