// GAP Heuristic

#include <stdio.h>
#include <stdlib.h>
#include <map>

#define  MAX_LINE_LENGTH 999 

int Gap(state_t state,int size){
	int counter = 0;

	for(int i=0; i < size-1; i++){
		if( abs(state.vars[i]-state.vars[i+1]) > 1 ) counter++;
	}

	if(abs(state.vars[size-1]-size) > 1) counter++;

	return counter;
}

int main(int argc, char const *argv[]) {
	state_t state;
	char str[MAX_LINE_LENGTH + 1];
	int size = atoi(argv[1]);

	// READ A LINE OF INPUT FROM stdin
	if( fgets(str, sizeof str, stdin) == NULL ) {
		printf("Error: empty input line.\n");
		return 0; 
	}
	// CONVERT THE LINE TO A STATE
	read_state(str, &state);

	printf("gap %d", Gap(state,size));

	return 0;
};