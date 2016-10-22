#include <map>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

map<int, unsigned> d_nodes; //numero de nodos por profundidad
map<int, float> bf_nodes; //factor de ramificacion por profundidad
unsigned counter = 0;

class Node {
	state_t state;
	Node* father;
	int ruleid;
	unsigned g;

	public:
		// Constructores de Nodos.
		Node(){};

		Node(state_t s, Node* p, int action, unsigned gcost): state(s), father(p), ruleid(action), g(gcost){};

		Node make_node(state_t state, int action){
			return Node(state, this, action, g + get_fwd_rule_cost(action));
		};

		/*  Función que implementa el algoritmo de búsqueda en profundidad iterativa
			Adicionalemente se imprime la tabla de resultados. */

		Node iddfs(state_t state,unsigned cota){
			int hist = init_history; 
			unsigned bound = 1;
			printf("%s \n","Depth\tNodos\t\tFactor");
	
			//Inicializo la raiz
			//state_t st;
			//ruleid_iterator_t iter; 
			//init_fwd_iter(&iter, &st);
			//Nodo raiz - profundidad 0

			Node root = Node(state, NULL, -1, 0);
			printf("%u\t%u\t\t",0, 1);
			d_nodes[0] = 1;

			//Profundidad > 0
			while (bound <= cota) {
				root.bounded_search(0, bound,hist);

				//Imprime numero de nodos y factor de ramificacion
				bf_nodes[bound-1] = (float)counter / (float)d_nodes[bound-1];
				printf("%f\n%u\t%u\t\t",bf_nodes[bound-1],bound, counter);  
				d_nodes[bound] = counter;
				
				bound++;
				counter = 0;
			};

			return root;
		};
		
		/*  Función que implementa la llamada recursiva del iddfs
			En caso de encontrarse en la profundidad deseada se retorna 1 ya que
			corresponde a la presencia de un nodo en esa profundidad. 
			En caso contrario, retorna 0.*/

		int bounded_search(unsigned d, unsigned bound,int hist){
			int id,child_hist;
			state_t child;
			ruleid_iterator_t iter;
	
			if (d>=bound) {
				return 1;
			}
	
			init_fwd_iter(&iter, &state);   

			/*
			if(is_goal(&st)) {
				printf("Goal a profundidad: %u\n",bound);
				printf("cost: %d  ",g);
				printf("state: \n\n");
				print_state(stdout,&st);
				return 1;
			} */

			while( (id = next_ruleid(&iter)) >= 0 ) {

				if (!fwd_rule_valid_for_history(hist,id)) continue;
				child_hist = next_fwd_history(hist,id);

				apply_fwd_rule(id, &state, &child);
				Node aux = make_node(child,id);  
				counter += aux.bounded_search(d+1,bound,child_hist);
			};
			return 0;
		};

		Node make_root_node (){
			ruleid_iterator_t iter;
			state_t st;
			init_fwd_iter(&iter, &st);
			return Node(st, NULL, -1, 0);
		};

		state_t get_state(){
			return this->state;
		};

};

#define  MAX_LINE_LENGTH 999 

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

	Node raiz;
	raiz = raiz.iddfs(state,cota);

	printf("\nNúmero de estados (NdE): %u\n", num_fwd_rules);
	for(int i=0; i<=(int)cota;i++){
		if(num_fwd_rules < d_nodes[i]) {
			printf("Profundidad para la cual el número de nodos supera el NdE: %u\n", i);
			break;
		}
			
	}

	return 0;
};
