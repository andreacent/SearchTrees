# to make a PDB starting from foo.psvn  type the command:     make pdb ss=foo
# if $(absname).txt exists it will be used as the input (abstraction commands) to build the abstraction,
#   otherwise the user will enter the abstraction commands interactively.

ACTDIR = act_4
CC = gcc
CXX = g++
OPT = -g -Wall -O3 -Wno-unused-function -Wno-unused-variable

PSVNOPT0 = --state_map --no_backwards_moves --fwd_history_len=0 --keep_duplicate_rules
PSVNOPT1 = --state_map --no_backwards_moves --fwd_history_len=1 --remove_duplicate_rules
PSVNOPT2 = --state_map --no_backwards_moves --fwd_history_len=2 --remove_duplicate_rules

psvn2c_core.c:
	cp ../../src/psvn2c_core.c ./psvn2c_core.c

psvn2c_state_map.c:
	cp ../../src/psvn2c_state_map.c ./psvn2c_state_map.c

psvn2c_abstraction.c:
	cp ../../src/psvn2c_abstraction.c ./psvn2c_abstraction.c

%.c: %.psvn psvn2c_core.c psvn2c_state_map.c psvn2c_abstraction.c
	../../bin/psvn2c $(PSVNOPT0) --name=$(*F) < $< > $@
	rm -f ./psvn2c_core.c ./psvn2c_state_map.c ./psvn2c_abstraction.c

%n1: %.psvn psvn2c_core.c psvn2c_state_map.c psvn2c_abstraction.c
	../../bin/psvn2c $(PSVNOPT1) --name=$(*F) < $< > $@
	rm -f ./psvn2c_core.c ./psvn2c_state_map.c ./psvn2c_abstraction.c

%n2: %.psvn psvn2c_core.c psvn2c_state_map.c psvn2c_abstraction.c
	../../bin/psvn2c $(PSVNOPT2) --name=$(*F) < $< > $@
	rm -f ./psvn2c_core.c ./psvn2c_state_map.c ./psvn2c_abstraction.c

.PRECIOUS: %.c

%.actividad1: %.c ../algorithms/actividad1.cpp
	$(CXX) $(OPT) ../algorithms/actividad1.cpp -std=gnu++0x -include $< -o $@
	rm -f $*.c
%.a_estrella: %.c ../algorithms/a_estrella.cpp
	$(CXX) $(OPT) ../algorithms/a_estrella.cpp -std=gnu++0x -include $< -o $@
	rm -f $*.c
%.a_est: %.c ../algorithms/a_estrella_b.cpp
	$(CXX) $(OPT) ../algorithms/a_estrella_b.cpp -std=gnu++0x -include $< -o $@
	rm -f $*.c
%.ida_estrella: %.c ../algorithms/ida_estrella.cpp
	$(CXX) $(OPT) ../algorithms/ida_estrella.cpp -std=gnu++0x -include $< -o $@
	rm -f $*.c

# N = 0
%.act0: %.c ../algorithms/actividad1.cpp
	$(CXX) $(OPT) ../algorithms/actividad1.cpp -std=gnu++0x -include $< -o $@
	rm -f $*.c
# N = 1
%.act1: %n1 ../algorithms/actividad1.cpp
	$(CXX) $(OPT) ../algorithms/actividad1.cpp -std=gnu++0x -include $< -o $@
	rm -f $*.c
# N = 2
%.act2: %n2 ../algorithms/actividad1.cpp
	$(CXX) $(OPT) ../algorithms/actividad1.cpp -std=gnu++0x -include $< -o $@
	rm -f $*.c


%.iddfs: %.c ../algorithms/dfs.cpp
	$(CXX) $(OPT) ../algorithms/dfs.cpp -std=gnu++0x -include $< -o $@
	rm -f $*.c
# N = 0
%.iddfs0: %.c ../algorithms/dfs.cpp
	$(CXX) $(OPT) ../algorithms/dfs.cpp -std=gnu++0x -include $< -o $@
	rm -f $*.c
# N = 1
%.iddfs1: %n1 ../algorithms/dfs.cpp
	$(CXX) $(OPT) ../algorithms/dfs.cpp -std=gnu++0x -include $< -o $@
	rm -f $*.c
# N = 2
%.iddfs2: %n2 ../algorithms/dfs.cpp
	$(CXX) $(OPT) ../algorithms/dfs.cpp -std=gnu++0x -include $< -o $@
	rm -f $*.c


%.ida_g: %n2 ../algorithms/ida_gap.cpp
	$(CXX) $(OPT) ../algorithms/ida_gap.cpp -std=gnu++0x -include $< -o $@
	rm -f $*.c

# N = 0
%.gap: %.c ../algorithms/gap.cpp
	$(CXX) $(OPT) ../algorithms/gap.cpp -std=gnu++0x -include $< -o $@
	rm -f $*.c

.PHONY: clean
clean:
	rm -fr *.succ *.iddfs* *.act* *.dist_pdb psvn2c_core.c psvn2c_state_map.c *.dSYM *.o *~ *.a_est* *.ida*
