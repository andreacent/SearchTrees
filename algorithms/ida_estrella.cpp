#include <map>
#include <stdlib.h>
#include <stdio.h>
#include <limits>
#include <iostream>
int contador = 0;
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
 

 /*
 Leccion 5
 make [nombre-psvn-original(sin .psvn)]/[nombre-archivo-abstractor(sin .txt)].pdb*/
 // 25 24 11 10 7 3 15 16 17 18 19 26 27 20 23 0 12 13 14 21 22 4 5 6 8 9 1 2


class Node {
    state_t state;
    Node* father;
    int ruleid;
    int g;

    public:
        // Constructores de Nodos.
        Node(){};

        Node(state_t s, Node* p, int action, unsigned gcost): state(s), father(p), ruleid(action), g(gcost){};

        Node make_node(state_t state, int action){
            return Node(state, this, action, this->g + get_fwd_rule_cost(action));
        };

        int heuristica(int n){
            if (n == 0){
                return this->gap();
            } else if (n == 1){
                return this->manhattan();
            } else {
                std::cout<<"Ingrese 1 para usar heuristica gap, 2 para usar manhattan \n";
                exit(1);
            }
        };
        // Heuristica gap para pancakes
        int gap(){
            int numero = 0;

            for (int i = 0; i < 27; ++i){
                if (this->state.vars[i] != this->state.vars[i+1]-1 && this->state.vars[i] != this->state.vars[i+1]+1){
                    numero++;
                }
            };
            if(this->state.vars[27]!=27){numero++;}
 
            return numero;
        };

        int manhattan(){
            int numero = 0;
            for(int i = 0; i < 16; i++){
                numero += tabla[this->state.vars[i]][i];
            }
            return numero;
        };    
        /*   */

        Node ida_search(state_t state, int idh){
            Node root = Node(state, NULL, -1, 0);
            int bound = root.heuristica(idh);
            std::pair<Node*,int> p;

            while (true) {
                p = root.f_bounded_dfs_visit(bound, idh);
                //std::cout << "en el while true \n";
                if (p.first) {
                	std::cout<<"Cantidad de nodos expandidos.\n";
                    std::cout<<contador<<"\n";
                    return *p.first;
                }
                bound = p.second;
                contador = 0;
                //std::cout<<p.second<<"\n";
            }
        };
        
        /* */
        std::pair <Node*, int> f_bounded_dfs_visit(int bound, int idh){
            state_t child;
            ruleid_iterator_t iter;
            int id,f,t;
            std::pair <Node*, int> respuesta;

            f = this->g + this->heuristica(idh);
            //std::cout << f << "\n";

            if (f>bound) {
                respuesta.first = nullptr;
                respuesta.second = this->g + this->heuristica(idh);
                return respuesta;
            }
            if (is_goal(&this->state)) {
                respuesta.first = this;
                respuesta.second = this->g;
                return respuesta;
            };
            //std::cout<<"algo\n";
            
            t = std::numeric_limits<int>::max();
            init_fwd_iter(&iter, &this->state);
            while( (id = next_ruleid(&iter)) >= 0 ){
                //std::cout<<get_fwd_rule_label(id)<<"\n";
                apply_fwd_rule(id, &this->state, &child);
                Node aux = make_node(child,id);
                contador++;
                respuesta = aux.f_bounded_dfs_visit(bound, idh);
                if (respuesta.first){
                     return respuesta;
                }
                t = std::min(t,respuesta.second);
            };
            respuesta.first = nullptr;
            respuesta.second = t;
            return respuesta;
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

        int get_cost(){
            return this->g;
        }

};

#define  MAX_LINE_LENGTH 999 

int main(int argc, char const *argv[]) {
    char str[MAX_LINE_LENGTH + 1];
    ssize_t nchars;
    state_t state;
    int idh = atoi(argv[1]);

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

    Node raiz,resultado;
    resultado = raiz.ida_search(state,idh);

    printf("%s\n", "Costo al goal:");
    printf("%d\n",resultado.get_cost());    
   /* Node n = Node(state, NULL, -1, 0);
    std::cout<<n.manhattan() << "\n";*/
    
    return 0;
};