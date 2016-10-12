//Iterative deepening depth_first search

#include <vector>
#include <cstdlib>
#include <map>
using namespace std;

map<int, int> d_nodes;

int bounded_dfs_visit_states(	state_t state,
								ruleid_iterator_t iter, 
								unsigned int d, 
								unsigned int bound){

	state_t child;
	int ruleid;

	//base cases
	if(d > bound){ 
		return 0; //prune branch by depth bound
	}

	if(is_goal(&state)==1) {
		fprintf(stderr, "is goal\n");
		return 1;
	} //goal is found, return
	
	//expansion and recursion
	while( (ruleid = next_ruleid(&iter) ) >= 0 ) {
		d_nodes[d] += 1;
		apply_fwd_rule(ruleid, &state, &child);
		bounded_dfs_visit_states(child,iter,d+1,bound);
	}

	return 0;
}

int main(int argc, char **argv) {	
	int depth = atoi(argv[1]);

	//initialize number of nodes
	for(int i=0; i<=depth; i++ ){
		d_nodes[i] = 0;
	}

	state_t state;
	ruleid_iterator_t iter;

	init_fwd_iter(&iter, &state);
	//execute id dfs
	d_nodes[0] += 1;
	bounded_dfs_visit_states(state,iter, 1, depth);

	//show number of nodes created
	fprintf(stderr, "depth 	nodes\n");     
	for(int i=0; i<=depth; i++ ){
		fprintf(stderr, "%d 	%d\n",i,d_nodes[i]);
	} 
	fprintf(stderr, "\n"); 

	return 0;
}

