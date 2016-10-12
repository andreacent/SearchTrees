//Iterative deepening depth_first search

#include <vector>
#include <cstdlib>
#include <map>
#include "node.cpp"
using namespace std;

map<int, int> d_nodes;

Node* bounded_dfs_visit(Node n, 
						unsigned int d, 
						unsigned int bound,
						ruleid_iterator_t iter){

	state_t child;
	int ruleid;

	/*
	if(d > bound){ 
		return nullptr; //prune branch by depth bound
	}
	*/

	if(is_goal(&n.state)==1) {
		printf("Goal: \n");
		printf("cost: %d  ",n.g);
	    print_state(stdout,&n.state);
	    printf("state: \n\n");
		Node* aux = &n;
		return aux;
	} //goal is found, return
	
	//expansion and recursion
	while( (ruleid = next_ruleid(&iter) ) >= 0 ) {
		d_nodes[d] += 1;
		apply_fwd_rule(ruleid, &n.state, &child);
		Node* m = bounded_dfs_visit(n.make_node(child,ruleid,get_fwd_rule_cost(ruleid)),
									d+1,
									bound,
									iter);
		if(m > nullptr) return m;
	}

	return nullptr; //failure: there is no path from node n to goal
}

Node* iterative_deepening_depth_first_search(int bound){
	state_t state;
	ruleid_iterator_t iter;

	init_fwd_iter(&iter, &state);

	Node root = make_root_node(state); 
	d_nodes[0] += 1;

	//perform depth_bounded searches with increasing depth bounds
	Node* n = bounded_dfs_visit(root,1,bound,iter);
	if(n > nullptr) return n;

	return nullptr;
}

int main(int argc, char **argv) {	
	int bound = atoi(argv[1]);

	//initialize number of nodes
	for(int i=0; i<=bound; i++ ){
		d_nodes[i] = 0;
	}

	//execute id dfs
	Node* goal =iterative_deepening_depth_first_search(bound);
	if(goal == nullptr) fprintf(stderr, "No goal reached\n\n");

	//show number of nodes created
	fprintf(stderr, "depth 	nodes\n");     
	for(int i=0; i<=bound; i++ ){
		fprintf(stderr, "%d 	%d\n",i,d_nodes[i]);
	} 
	fprintf(stderr, "\n"); 

	return 0;
}

