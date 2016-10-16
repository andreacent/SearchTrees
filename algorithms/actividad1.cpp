#include <map>
using namespace std;

map<int, unsigned> d_nodes;
map<int, float> bf_nodes;
bool gtbf = false; // true cuando el counter es mayor que el factor de ramificacion
unsigned dgtbf;
unsigned counter = 1;

class Node {
	state_t state;
	Node* father;
	int ruleid;
	unsigned g;

	public:
		// Constructuores de Nodos.
		Node(){};

		Node(state_t s, Node* p, int action, unsigned gcost): state(s), father(p), ruleid(action), g(gcost){};

		Node make_node(state_t state, int action){
			return Node(state, this, action, g + get_fwd_rule_cost(action));
		};

		// Función que implementa el algoritmo de búsqueda en profundidad iterativa
		// Adicionalemente se imprime la tabla de resultados. 

		void iddfs(unsigned cota){
			//ruleid_iterator_t iter;
			int hist = init_history; 
			unsigned bound = 0;
			printf("%s \n","Depth\tNodos\t\tFactor");

			//init_fwd_iter(&iter, &this->state);

			while (bound <= cota) {
				this->bounded_search(0, bound,hist);
				if(bound > 0){
					bf_nodes[bound-1] = (float)counter / (float)d_nodes[bound-1];
					printf("%f\n%u\t%u\t\t",bf_nodes[bound-1],bound, counter);
				}else{
					printf("%u\t%u\t\t",bound, counter);
				}				
				d_nodes[bound] = counter;
				if(num_fwd_rules < counter && !gtbf){
					dgtbf=bound;
					gtbf = true;
				}
				bound++;
				counter = 0;
			};
		};
		
		/* Función que implementa la llamada recursiva del iddfs
		 	En caso de encontrarse en la profundidad deseada se retorna 1 ya que
			corresponde a la presencia de un nodo en esa profundidad. 
			En caso contrario, retorna 0.*/

		int bounded_search(unsigned d, unsigned bound,int hist){
			state_t child;
	    	int id,child_hist;
	
			if (d>=bound) {
				return 1;
			}

			ruleid_iterator_t iter;
			init_fwd_iter(&iter, &this->state);
			
			while( (id = next_ruleid(&iter)) >= 0 ) {

				if (!fwd_rule_valid_for_history(hist,id)) continue;
				child_hist = next_fwd_history(hist,id);

	        	apply_fwd_rule(id, &this->state, &child);
	        	Node aux = make_node(child,id);	 
	        	counter += aux.bounded_search(d+1,bound,child_hist);
			};
			return 0;
		};

		Node make_root_node (state_t state){
			return Node(state, NULL, -1, 0);
		};

		state_t get_state(){
			return this->state;
		};

};

// imprime cantidad de nodos y factor de ramificacion
/*
void print_d_nodes(int bound){
    printf("Depth\tNodes\t\tFactor\n");     
    for(int i=0; i<=bound; i++ ){
        printf("%d\t%u\t\t%f\n",i,d_nodes[i],bf_nodes[i]);
    } 
}
*/

int main(int argc, char const *argv[]) {

	unsigned cota = atoi(argv[1]);
	Node raiz;
	state_t state;
	ruleid_iterator_t iter;
	init_fwd_iter(&iter, &state);
	raiz = raiz.make_root_node(state);
	raiz.iddfs(cota);

	printf("\nProfundidad para la cual el número de nodos supera el número de estados: %u\n", dgtbf);

	//branching factor 
	/*
    for(int i=0; i<(int)cota; i++ ){
        bf_nodes[i] = d_nodes[i+1] / d_nodes[i];
    }
    bf_nodes[(int)cota] = bf_nodes[(int)cota-1];
    print_d_nodes((int)cota);
    */

	return 0;
};
	