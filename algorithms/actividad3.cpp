#include <ctime>
#include <sstream>
#include <string>
#include <fstream>
using namespace std;

#define  MAX_LINE_LENGTH 999 

bool goal;
double t_final;
unsigned nodes=0;
int cost=0;

/*
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

		//  Función que implementa el algoritmo de búsqueda en profundidad iterativa
		//	Adicionalemente se imprime la tabla de resultados. 

		Node iddfs(state_t state){
			std::clock_t start;
			unsigned bound = 0;

			start = std::clock();

			Node root = Node(state, NULL, -1, 0);

			//Profundidad > 0
			while(!goal) {
				root.bounded_search(0, bound);				
				bound++;
				//nodes=0;
			};

			t_final = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
			printf("%d, %d, %f, %.10e\n",cost,nodes,t_final,nodes/t_final);			

			return root;
		};
		
		//  Función que implementa la llamada recursiva del iddfs
		//	En caso de encontrarse en la profundidad deseada se retorna 1 ya que
		//	corresponde a la presencia de un nodo en esa profundidad. 
		//	En caso contrario, retorna 0.

		void bounded_search(unsigned d, unsigned bound){
			int ruleid;
			state_t child;
			ruleid_iterator_t iter;

			if(is_goal(&state)) {
				goal = true;
				nodes++;
				return;
			} 

			if (d>=bound){ 
				nodes++;
				return;
			}
	
			init_fwd_iter(&iter, &state);   
			while( (ruleid = next_ruleid(&iter)) >= 0 && !goal) {
				apply_fwd_rule(ruleid, &state, &child);
				Node aux = make_node(child,ruleid);  
				aux.bounded_search(d+1,bound);
				if(goal) cost += get_fwd_rule_cost(ruleid);
			};
		};

		state_t get_state(){
			return this->state;
		};
};
*/
		
//  Función que implementa la llamada recursiva del iddfs
//	En caso de encontrarse en la profundidad deseada se retorna 1 ya que
//	corresponde a la presencia de un nodo en esa profundidad. 
//	En caso contrario, retorna 0.

void bounded_search(unsigned d, unsigned bound,state_t state){
	int ruleid;
	state_t child;
	ruleid_iterator_t iter;

	if(is_goal(&state)) {
		goal = true;
		nodes++;
		return;
	} 

	if (d>=bound){ 
		nodes++;
		return;
	}

	init_fwd_iter(&iter, &state);   
	while( (ruleid = next_ruleid(&iter)) >= 0 && !goal) {
		apply_fwd_rule(ruleid, &state, &child);
		bounded_search(d+1,bound,child);
		if(goal) cost += get_fwd_rule_cost(ruleid);
	};
};

//  Función que implementa el algoritmo de búsqueda en profundidad iterativa
//	Adicionalemente se imprime la tabla de resultados. 

void iddfs(state_t state){
	std::clock_t start;
	unsigned bound = 0;

	start = std::clock();

	//Profundidad > 0
	while(!goal) {
		bounded_search(0, bound,state);				
		bound++;
	
	};

	t_final = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
	printf("%d, %d, %f, %.10e\n",cost,nodes,t_final,nodes/t_final);			
};

int main(int argc, char const *argv[]) {
	state_t state;

	stringstream ss;
	ss << "../instances/" << argv[1] <<".txt";
	ifstream myfile(ss.str());

	printf("grupo, algorithm, domain, instance, cost, generated, time, gen_per_sec\n");
	printf("X, dfid, %s, \"",argv[1]);

	for( string line; getline( myfile, line ); ){
    	// CONVERT THE LINE TO A STATE
		read_state(line.c_str(), &state);
		print_state(stdout, &state);
		printf("\", ");
		iddfs(state);
		goal = false;
		nodes=0;
		cost=0;

		break; 
	}

	return 0;
};
