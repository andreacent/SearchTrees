#include <queue>
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
float peso;

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

        int heuristica(int n){
            if (n == 1){
                return this->gap();
            } else if (n == 2){
                return this->manhattan();
            } else {
                std::cout<<"Ingrese 1 para usar heuristica gap, 2 para usar manhattan \n";
                exit(1);
            }
        };

        // Funcion que calcula la heuristica gap del paper.
        // NOTA: El warning se genera porque se usan estados de 15-puzzle pero
        // para estos casos se usarian la heuristicas correspondientes.
        float gap(){
            float numero = 0;

            for (int i = 0; i < 27; ++i){
                if (this->state.vars[i] != this->state.vars[i+1]-1 && this->state.vars[i] != this->state.vars[i+1]+1){
                    numero++;
                }
            };
            if(this->state.vars[27]!=27){numero++;};
            return this->g + peso*numero;
        };

        int manhattan(){
            float h = 0;
            for(int i = 0; i < 16; i++){
                h += tabla[this->state.vars[i]][i];
            }
            return this->g + h*peso;
        };
        
        bool operator<(Node const& p1) const {
            // return "true" if "p1" is ordered before "p2", for example:
            return this->cmash > p1.cmash;
        };

        std::pair<float,int> a_estrella(int idh){
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
            int h0 = this->heuristica(idh);
            start = std::clock();

            std::cout<<start<<"\n";
            //exit(1);
            cola.push(*this);
            while(!cola.empty()){
               if ( ((std::clock() - start)/CLOCKS_PER_SEC) == 600) {
                   std::cout<<"entre aca \n";
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
                        std:: cout <<  std::clock() - start << "\n";
                        t_final = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;

                        std::cout<<respuesta.first<<"\t"<<h0<<"\t"<<respuesta.second<<"\t"<<t_final<<"\t"<<respuesta.second/t_final;
                        return respuesta;       
                    }
                    init_fwd_iter(&iter, &n.state);

                    while((id = next_ruleid(&iter)) > -1){
                        Node aux;
                        apply_fwd_rule(id, &n.state, &child);
                        contador++;
                        aux = n.make_node(child, id,0);
                        aux.cmash = aux.heuristica(idh);
                        cola.push(aux);
                    }
                }
            i++;    
        };
        t_final = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
        std::cout<<"na"<<"\t"<<h0<<"\t"<<respuesta.second<<"\t"<<t_final<<"\t"<<respuesta.second/t_final;
        respuesta.first = -1;
        respuesta.second = -1;
        return respuesta;
        };

        state_t get_state(){
            return this->state;
        };
};

#define  MAX_LINE_LENGTH 999 

int main(int argc, char const *argv[]) {

    char str[MAX_LINE_LENGTH + 1];
    state_t state;
    std::pair<float,int> respuesta;
    //signal( SIGINT, &signalHandler );
    int idh = atoi(argv[2]);
    peso = atof(argv[3]);
    std::fstream fd;
    std::string linea;
    
    printf("%s \n","grupo,\t algorithm,\t heuristic,\t domain,\t instance,\t cost,\t h0,\t generated,\t time,\t gen_per_sec" );
    fd.open(argv[1]);
    if (fd.is_open()) {
        while(getline (fd,linea)){
            // CONVERT THE STRING TO A STATE
            read_state(linea.c_str(), &state);
            Node raiz;
            raiz = raiz.make_root_node(state);
            printf("%s \n",linea.c_str());
            respuesta = raiz.a_estrella(idh);
        }
    }

    /*
    };
    printf("The state you entered is: ");
    print_state(stdout, &state);
    printf("\n");
    
    // READ A LINE OF INPUT FROM stdin
    printf("Please enter a state followed by ENTER: ");
    if( fgets(str, sizeof str, stdin) == NULL ) {
        printf("Error: empty input line.\n");
        return 0; 
    };

    read_state(str, &state);

    
    Node raiz;
    raiz = raiz.make_root_node(state);
    respuesta = raiz.a_estrella(idh);

    printf("%s\n", "Costo al goal:");
    printf("%u\n",respuesta.first);
    printf("%u\n",respuesta.second);
*/
    
    return 0;
}