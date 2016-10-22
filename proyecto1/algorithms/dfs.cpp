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

void bounded_search(unsigned d,unsigned bound,int hist,state_t state){
	int id,child_hist;
	state_t child;
	ruleid_iterator_t iter;

	if (d>bound) return;

	init_fwd_iter(&iter, &state);   
	while( (id = next_ruleid(&iter)) >= 0 ) {

		if (!fwd_rule_valid_for_history(hist,id)) continue;
		child_hist = next_fwd_history(hist,id);

		apply_fwd_rule(id, &state, &child);
		bounded_search(d+1,bound,child_hist,child);
		d_nodes[d+1]++;
	};
};

void dfs(state_t state,unsigned cota){
	int hist = init_history; 

	printf("%s \n","Depth\tNodos\t\tFactor");
	printf("%u\t%u\t\t",0, 1);

	d_nodes[0]=1;
	bounded_search(0,cota,hist,state);	

	for(int i=1; i<=(int)cota;i++){
		bf_nodes[i-1] = (float)d_nodes[i] / (float)d_nodes[i-1];
		printf("%f\n%u\t%u\t\t",bf_nodes[i-1],i, d_nodes[i]); 	
	}
};

int main(int argc, char const *argv[]) {
    char str[MAX_LINE_LENGTH + 1];
    ssize_t nchars;
	state_t state;
	unsigned cota = atoi(argv[1]);

	for(int i=1; i<=(int)cota;i++){
		d_nodes[i] =0;
	}

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

	dfs(state,cota);

	printf("\nNúmero de estados (NdE): %u\n", num_fwd_rules);
	for(int i=0; i<=(int)cota;i++){
		if(num_fwd_rules < d_nodes[i]) {
			printf("Profundidad para la cual el número de nodos supera el NdE: %u\n", i);
			break;
		}	
	}

	return 0;
};
