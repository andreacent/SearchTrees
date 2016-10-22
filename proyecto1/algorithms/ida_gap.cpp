// Si no le pasan argumento, el tomara el peso 1 por default. 

#include <map>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <cstdio>
#include <ctime>
#include <csignal>
#include <fstream>
#include <string>

using namespace std;

#define  MAX_LINE_LENGTH 999 

class Node {
	public:
		state_t state; //pointer to state represented by node
		Node* parent; //parent of node (NULL if root)
		int action; //action mapping state to node (-1 if root)
		unsigned g;

		Node(state_t, Node*, int, unsigned);	
		Node make_node(state_t, int, unsigned);
		//void extract_path(std::vector<ruleid_iterator_t>);
};
Node::Node(state_t st, Node* n, int act, unsigned gcost){
	state = st;
	parent = n;
	action=act;
	g= gcost;
}
Node Node::make_node(state_t st, int act, unsigned gcost){
	Node node(st, this, act, gcost + g);
	return node;
}


unsigned counter = 0;
int h0;
Node* goal;
float peso=1; 

// Funcion que calcula la heuristica gap del paper.
// NOTA: El warning se genera porque se usan estados de 15-puzzle pero
// para estos casos se usarian la heuristicas correspondientes.
int gap(state_t state,int size){
    int numero = 0;

    for (int i = 0; i < size; ++i){
        if (state.vars[i] != state.vars[i+1]-1 && state.vars[i] != state.vars[i+1]+1){
            numero++;
        }
    };
    if(state.vars[size]!=size){numero++;};

    return numero; //+g
};

/*  Función que implementa la llamada recursiva del iddfs
	En caso de encontrarse en la profundidad deseada se retorna 1 ya que
	corresponde a la presencia de un nodo en esa profundidad. 
	En caso contrario, retorna 0.*/

int bounded_search(Node n, unsigned bound,int hist){
	int id,child_hist,f,h;
	state_t child;
	ruleid_iterator_t iter;

	h = gap(n.state,27) * peso;
	f = (int)n.g + h;

	if (f > (int)bound) return f;  
	if(is_goal(&n.state)) {
		goal = &n;
		return (int)n.g;
	}

	int t = INT_MAX;
	init_fwd_iter(&iter, &n.state); 
	while( (id = next_ruleid(&iter)) >= 0 ) {

		if (!fwd_rule_valid_for_history(hist,id)) continue;
		child_hist = next_fwd_history(hist,id);

		apply_fwd_rule(id, &n.state, &child);
		Node m = n.make_node(child, id, get_fwd_rule_cost(id));
		counter++;

		int p = bounded_search(m,bound,child_hist);

		if (goal != nullptr) return p; 

		t = min(t,p);
	};

	return t;
};

/*  Función que implementa el algoritmo de búsqueda en profundidad iterativa
	Adicionalemente se imprime la tabla de resultados. */

void ida(state_t state){
	int hist = init_history; 
	unsigned bound = 1;	

    std::clock_t start;
    double t_final;

    start = std::clock();

	Node root = Node(state, NULL, -1, 0);
	h0 = gap(state,27);

	//Profundidad > 0
	while (true) {
		counter++;
		unsigned p = bounded_search(root,bound,hist);
		if (goal != nullptr) {
			t_final = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
			printf("%u, %d, %u, %f, %.10e\n",goal->g,h0,counter,t_final,counter/t_final);	
			return; 
		}
		bound = (int)p;				
	};
};


// Funcion que mata el programa cuando recibe una senal
void signalHandler( int )
{
    fprintf(stderr, "%s\n", "Falló por tiempo o espacio.");
    printf("na, na, na, na, na\n"); 
    exit(1);
}

int main(int argc, char const *argv[]) {
    state_t state;
    char str[MAX_LINE_LENGTH + 1];

    if ( argc > 1 ) {
    	peso = atoi(argv[1]);
    }

    signal( SIGKILL, &signalHandler );

    // READ A LINE OF INPUT FROM stdin
    if( fgets(str, sizeof str, stdin) == NULL ) {
        printf("Error: empty input line.\n");
        return 0; 
    }
    // CONVERT THE LINE TO A STATE
    read_state(str, &state);

    printf("X, ida, gap, pancake28, \"%s\", ",str );

    ida(state);

    return 0;
};
