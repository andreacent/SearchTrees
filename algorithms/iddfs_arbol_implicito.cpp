#include <map>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

#define  MAX_LINE_LENGTH 999 

map<int, unsigned> d_nodes; //numero de nodos por profundidad
map<int, float> bf_nodes; //factor de ramificacion por profundidad
unsigned counter = 0;

/*  Función que implementa la llamada recursiva del iddfs
	En caso de encontrarse en la profundidad deseada se retorna 1 ya que
	corresponde a la presencia de un nodo en esa profundidad. 
	En caso contrario, retorna 0.*/

int bounded_search(unsigned d,unsigned bound,int hist,state_t state){
	int id,child_hist;
	state_t child;
	ruleid_iterator_t iter;

	if (d>=bound) {
		return 1;
	}

	init_fwd_iter(&iter, &state);   
	while( (id = next_ruleid(&iter)) >= 0 ) {

		if (!fwd_rule_valid_for_history(hist,id)) continue;
		child_hist = next_fwd_history(hist,id);

		apply_fwd_rule(id, &state, &child);
		counter += bounded_search(d+1,bound,child_hist,child);
	};
	return 0;
};

void iddfs(state_t state,unsigned cota){
	int hist = init_history; 
	unsigned bound = 1;
	printf("%s \n","Depth\tNodos\t\tFactor");

	printf("%u\t%u\t\t",0, 1);
	d_nodes[0] = 1;

	//Profundidad > 0
	while (bound <= cota) {
		bounded_search(0, bound,hist,state);

		//Imprime numero de nodos y factor de ramificacion
		bf_nodes[bound-1] = (float)counter / (float)d_nodes[bound-1];
		printf("%f\n%u\t%u\t\t",bf_nodes[bound-1],bound, counter);  
		d_nodes[bound] = counter;
		
		bound++;
		counter = 0;
	};
};

int main(int argc, char const *argv[]) {
    char str[MAX_LINE_LENGTH + 1];
    ssize_t nchars;
	state_t state;
	unsigned cota = atoi(argv[1]);

	// READ A LINE OF INPUT FROM stdin
	printf("Please enter a state followed by ENTER: ");
	if( fgets(str, sizeof str, stdin) == NULL ) {
		printf("Error: empty input line.\n");
		return 0; 
	}
	// CONVERT THE STRING TO A STATE
	nchars = read_state(str, &state);
	if( nchars <= 0 ) {
		printf("Error: invalid state entered.\n");
		return 0; 
	}
	printf("The state you entered is: ");
	print_state(stdout, &state);
	printf("\n");

	iddfs(state,cota);

	printf("\nNúmero de estados (NdE): %u\n", num_fwd_rules);
	for(int i=0; i<=(int)cota;i++){
		if(num_fwd_rules < d_nodes[i]) {
			printf("Profundidad para la cual el número de nodos supera el NdE: %u\n", i);
			break;
		}
			
	}

	return 0;
};
