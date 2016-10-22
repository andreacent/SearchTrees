/* Se le pasa como primer argumento el archivo de instancias, de segundo el
tipo de heuristica y como tercer argumento el peso deseado
*/
#include <queue>
#include <iostream>
#include <cstdio>
#include <ctime>
#include <csignal>
#include <fstream>
#include <string>
#include <stdio.h>

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
state_map_t *mapa1;
state_map_t *mapa2;
state_map_t *mapa3;
abstraction_t *abs1;
abstraction_t *abs2;
abstraction_t *abs3;
state_t estado_abs1, estado_abs2, estado_abs3;

unsigned* tabla[16] = {tabla0,tabla1,tabla2,tabla3,tabla4,tabla5,tabla6,tabla7,tabla8,tabla9,tabla10,tabla11,tabla12,tabla13,tabla14,tabla15};

class Node {
    state_t state;
    Node* father;
    int ruleid;
    float g;
    float cmash;

    public:
        // Constructores de Nodos.
        Node(){};

        Node(state_t s, Node* p, int action, float gcost, float f): state(s), father(p), ruleid(action), g(gcost), cmash(f){};

        Node make_node(state_t state, int action, float f){
            return Node(state, this, action, this->g + get_fwd_rule_cost(action), f);
        };
        Node make_root_node (state_t state){
            return Node(state, NULL, -1, 0.0, 0.0);
        };

        int manhattan(){
            float h = 0;
            for(int i = 0; i < 16; i++){
                h += tabla[this->state.vars[i]][i];
            }
            return this->g + h;
        };
        
        bool operator<(Node const& p1) const {
            // return "true" if "p1" is ordered before "p2", for example:
            return this->cmash > p1.cmash;
        };

        std::pair<float,int> a_estrella(){
            std::clock_t start;
            double t_final;
            std::priority_queue<Node, std::vector<Node>> cola;
            state_map_t mapa = *new_state_map();
            Node n, aux, auxi;
            int id;
            int contador = 0;
            int* mejorCosto;
            int i = 0;
            state_t child;
            ruleid_iterator_t iter;
            std::pair<float,int> respuesta;
            int h0 = this->manhattan();
            start = std::clock();
            cola.push(*this);
            while(!cola.empty()){
               if ( ((std::clock() - start)/CLOCKS_PER_SEC) == 600) {
                   break; 
                }
                Node n;
                n = cola.top();
                cola.pop();
                mejorCosto = state_map_get(&mapa, &n.state);
                if (!mejorCosto || (n.g < *mejorCosto) ){
                    state_map_add(&mapa, &n.state, n.g);
                    
                    if (is_goal(&n.state)){
                        respuesta.first = n.g;
                        respuesta.second = contador;
                        t_final = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;

                        std::cout<<respuesta.first<<"\t"<<h0<<"\t"<<respuesta.second<<"\t"<<t_final<<"\t"<<respuesta.second/t_final<<"\n";
                        return respuesta;       
                    }
                    init_fwd_iter(&iter, &n.state);

                    while((id = next_ruleid(&iter)) > -1){
                        Node aux;
                        apply_fwd_rule(id, &n.state, &child);
                        contador++;
                        aux = n.make_node(child, id,0);
                        aux.cmash = aux.manhattan();
                        cola.push(aux);
                    }
                }
            i++;    
        };
        t_final = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
        std::cout<<"na"<<"\t"<<h0<<"\t"<<respuesta.second<<"\t"<<t_final<<"\t"<<respuesta.second/t_final<<"\n";
        respuesta.first = -1;
        respuesta.second = -1;
        return respuesta;
        };

        state_t get_state(){
            return this->state;
        };
};

// Funcion que mata el programa cuando recibe una senal
void signalHandler( int )
{
    fprintf(stderr, "%s\n", "Falló por tiempo o espacio.");
    printf("na, na, na, na, na\n"); 
    exit(1);
}

#define  MAX_LINE_LENGTH 999 

int main(int argc, char const *argv[]) {
    state_t state;
    char str[MAX_LINE_LENGTH + 1];
    std::pair<float,int> respuesta;
  
    signal( SIGKILL, &signalHandler );

    // READ A LINE OF INPUT FROM stdin
    if( fgets(str, sizeof str, stdin) == NULL ) {
        printf("Error: empty input line.\n");
        return 0; 
    }
    // CONVERT THE LINE TO A STATE
    read_state(str, &state);

    printf("X, a*, manhattan, 15Puzzle, \"%s\", ",str );

    Node raiz;
    raiz = raiz.make_root_node(state);
    respuesta = raiz.a_estrella();
    
    return 0;
}