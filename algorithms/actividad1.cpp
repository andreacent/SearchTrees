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

		void iddfs(state_t state, unsigned cota){
			ruleid_iterator_t iter;
			//Node root = make_node(state,NULL,-1,0);
			int hist = init_history; 
			unsigned bound = 0;
			printf("%s \n","Depth\tNodos");
			init_fwd_iter(&iter, &state);
			while (bound <= cota) {
				this->bounded_search(0, bound,iter,hist);
				printf("%u\t%u \n",bound, counter);
				bound++;
				counter = 0;
			};
		};
		
		/* Función que implementa la llamada recursiva del iddfs
		 	En caso de encontrarse en la profundidad deseada se retorna 1 ya que
			corresponde a la presencia de un nodo en esa profundidad. 
			En caso contrario, retorna 0.*/

		int bounded_search(unsigned d, unsigned bound,ruleid_iterator_t iter,int hist){
			state_t child;
	    	int id,child_hist;
	
			if (d>=bound) {
				return 1;
			}
			while( (id = next_ruleid(&iter)) >= 0 ) {

				if (!fwd_rule_valid_for_history(hist,id)) continue;
				child_hist = next_fwd_history(hist,id);

	        	apply_fwd_rule(id, &state, &child);
	        	Node aux = make_node(child,id);
	        	counter += aux.bounded_search(d+1,bound,iter,child_hist);
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

int main(int argc, char const *argv[]) {
	unsigned cota = atoi(argv[1]);
	Node raiz;
	state_t state;
	ruleid_iterator_t iter;
	init_fwd_iter(&iter, &state);
	raiz = raiz.make_root_node(state);
	raiz.iddfs(raiz.get_state(), cota);
	return 0;
};
	