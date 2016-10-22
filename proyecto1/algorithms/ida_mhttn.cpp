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

unsigned tabla0[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
unsigned tabla1[16] = {1,0,1,2,2,1,2,3,3,2,3,4,4,3,4,5};
unsigned tabla2[16] = {2,1,0,1,3,2,1,2,4,3,2,3,5,4,3,4};
unsigned tabla3[16] = {3,2,1,0,4,3,2,1,5,4,3,2,6,5,4,3};
unsigned tabla4[16] = {1,2,3,4,0,1,2,3,1,2,3,4,2,3,4,5};
unsigned tabla5[16] = {2,1,2,3,1,0,1,2,2,1,2,3,3,2,3,4};
unsigned tabla6[16] = {3,2,1,2,2,1,0,1,3,2,1,2,4,3,2,3};
unsigned tabla7[16] = {4,3,2,1,3,2,1,0,4,3,2,1,5,4,3,2};
unsigned tabla8[16] = {2,3,4,5,1,2,3,4,0,1,2,3,1,2,3,4};
unsigned tabla9[16] = {3,2,3,4,2,1,2,3,1,0,1,2,2,1,2,3};
unsigned tabla10[16] = {4,3,2,3,3,2,1,2,2,1,0,1,3,2,1,2};
unsigned tabla11[16] = {5,4,3,2,4,3,2,1,3,2,1,0,4,3,2,1};
unsigned tabla12[16] = {3,4,5,6,2,3,4,5,1,2,3,4,0,1,2,3};
unsigned tabla13[16] = {4,3,4,5,3,2,3,4,2,1,2,3,1,0,1,2};
unsigned tabla14[16] = {5,4,3,4,4,3,2,3,3,2,1,2,2,1,0,1};
unsigned tabla15[16] = {6,5,4,3,5,4,3,2,4,3,2,1,3,2,1,0};

unsigned* tabla[16] = {tabla0,tabla1,tabla2,tabla3,tabla4,tabla5,tabla6,tabla7,tabla8,tabla9,tabla10,tabla11,tabla12,tabla13,tabla14,tabla15};

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

/*// Funcion que calcula la heuristica gap del paper.
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
};*/

int manhattan(Node n){
    float h = 0;
    for(int i = 0; i < 16; i++){
        h += tabla[n.state.vars[i]][i];
    }
    return n.g + h;
};

/*  Función que implementa la llamada recursiva del iddfs
	En caso de encontrarse en la profundidad deseada se retorna 1 ya que
	corresponde a la presencia de un nodo en esa profundidad. 
	En caso contrario, retorna 0.*/

int bounded_search(Node n, unsigned bound,int hist){
	int id,child_hist,f,h;
	state_t child;
	ruleid_iterator_t iter;

	h = manhattan(n) * peso;
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
	h0 = manhattan(root);

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

    printf("X, ida, manhattan, 15-puzzle, \"%s\", ",str );

    ida(state);

    return 0;
};
