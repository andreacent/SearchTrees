#include <iostream>
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

//No hay estructura nodo porque no es necesario almacenar el arbol
		
//  Función que implementa la llamada recursiva del iddfs
//	En caso de encontrarse en la profundidad deseada o con el estado 
//  goal, se retorna

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
//	Adicionalemente se imprimen los resultados. 

void iddfs(state_t state){
	std::clock_t start;
	unsigned bound = 0;

	start = std::clock();

	//Profundidad > 0
	while(!goal) {
		bounded_search(0, bound,state);				
		bound++;
		//nodes=0; no se si debe imprimir todos los nodos de todas las iteraciones o solo el de la iteracion que halla el goal
	};

	t_final = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
	printf("%d, %d, %f, %.10e\n",cost,nodes,t_final,nodes/t_final);			
};

string SplitFilename (const std::string& str){
  size_t found = str.find_last_of(".");
  string filename = str.substr(0,found);
  found = filename.find_last_of("/");
  return filename.substr(found+1);
}

int main(int argc, char const *argv[]) {
	state_t state;

	//obtengo el nombre del archivo
	string str = argv[0];
	string filename = SplitFilename(str);

	stringstream ss;
	ss << "../instances/" << filename <<".txt";
	ifstream myfile(ss.str());

	printf("grupo, algorithm, domain, instance, cost, generated, time, gen_per_sec\n");
	printf("X, dfid, %s, \"",filename.c_str());

	for( string line; getline( myfile, line ); ){
    	// CONVERT THE LINE TO A STATE
		read_state(line.c_str(), &state);
		print_state(stdout, &state);
		printf("\", ");
		//ejecuta iddfs
		iddfs(state);
		//devuelve las variables a sus estados iniciales
		goal = false;
		nodes=0;
		cost=0;

		break; //este break no va, pero hasta que no se ponga el timer de 10min no se puede quitar
	}

	return 0;
};
