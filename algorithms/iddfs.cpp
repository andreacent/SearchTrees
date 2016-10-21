#include <iostream>
#include <ctime>
#include <csignal>
using namespace std;

#define  MAX_LINE_LENGTH 999 

bool goal;
unsigned nodes=0;
int cost=0;
		
//  Función que implementa la llamada recursiva del iddfs
//	En caso de encontrarse en la profundidad deseada o con el estado 
//  goal, se retorna

void bounded_search(unsigned d, unsigned bound,state_t state,int hist){
	int ruleid,child_hist;
	state_t child;
	ruleid_iterator_t iter;

	if (d>bound) return;

	if(is_goal(&state)) {
		goal = true;
		nodes++;
		return;
	}

	init_fwd_iter(&iter, &state);   
	while( (ruleid = next_ruleid(&iter)) >= 0) {

		if (!fwd_rule_valid_for_history(hist,ruleid)) continue;
		child_hist = next_fwd_history(hist,ruleid);

		apply_fwd_rule(ruleid, &state, &child);
		bounded_search(d+1,bound,child,child_hist);

		if(goal){
			cost += get_fwd_rule_cost(ruleid);
			break;
		}else nodes++;
	};
};

//  Función que implementa el algoritmo de búsqueda en profundidad iterativa
//	Adicionalemente se imprimen los resultados. 

void iddfs(state_t state){
	std::clock_t start;
	double t_final;
	unsigned bound = 0;
	int hist = init_history;

	start = std::clock();

	while(true) {
		nodes ++;
		bounded_search(0, bound,state,hist);
		if(goal) break;				
		bound++;
	};

	t_final = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;

	printf("%d, %u, %f, %.10e\n",cost,nodes,t_final,nodes/t_final);			
};

// Obtiene el nombre del archivo que se esta ejecutando
string SplitFilename (const std::string& str){
  size_t found = str.find_last_of(".");
  string filename = str.substr(0,found);
  found = filename.find_last_of("/");
  return filename.substr(found+1);
}

// Funcion que mata el programa cuando recibe una senal
void signalHandler( int )
{
	fprintf(stderr, "%s\n", "Falló por tiempo.");
	printf("na, na, na, na\n");	
	exit(1);
}

int main(int argc, char const *argv[]) {
	state_t state;
	char str[MAX_LINE_LENGTH + 1];

	signal( SIGINT, &signalHandler );

	//obtengo el nombre del archivo
	string s = argv[0];
	string filename = SplitFilename(s);	

	// READ A LINE OF INPUT FROM stdin
	if( fgets(str, sizeof str, stdin) == NULL ) {
		printf("Error: empty input line.\n");
		return 0; 
	}
	// CONVERT THE LINE TO A STATE
	read_state(str, &state);
	printf("X, dfid, %s, \"%s\", ",filename.c_str(),str);

	//ejecuta iddfs
	iddfs(state);

	return 0;
};
