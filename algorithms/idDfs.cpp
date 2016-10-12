//Iterative deepening depth_first search

#include <vector>
#include <cstdlib>
#include <map>
#include "../global/priority_queue.hpp"
using namespace std;

map<int, char> d_nodes;
state_t state, child;
ruleid_iterator_t iter;

class Node {
	public:
		state_t state; //pointer to state represented by node
		Node* parent; //parent of node (NULL if root)
		int action; //action mapping state to node (-1 if root)
		unsigned int g;

		Node(state_t, Node*, int, unsigned int);	
		Node make_node(state_t, int, unsigned int);
		//void extract_path(std::vector<ruleid_iterator_t>);
};
Node::Node(state_t st, Node* n, int act, unsigned int gcost){
	state = st;
	parent = n;
	action=act;
	g= gcost;
}
/*
void Node::extract_path(std::vector<ruleid_iterator_t> &reversed_path) {
	Node node = this;
	while(node /= NULL && node.parent /= NULL){
		reversed_path.push_back(node.action);
		node = node.parent;	
	}
}*/
Node Node::make_node(state_t st, int act, unsigned int gcost){
	Node node(st, this, act, gcost + g);
	return node;
}

Node make_root_node(){
	Node node(state, NULL, -1, 0);
	return node;
}


Node* bounded_dfs_visit(Node n, 
						unsigned int d, 
						unsigned int bound){

	print_state(stdout,&n.state);
	fprintf(stderr, "b = %d\n",d);

	int ruleid;
	//base cases
	if(d > bound){ 
		return nullptr; //prune branch by depth bound
	}
	if(is_goal(&n.state)==1) {
		Node* aux = &n;
		return aux;
		fprintf(stderr, "is goal\n");
	} //goal is found, return
	
	//expansion and recursion
	while( (ruleid = next_ruleid(&iter) ) >= 0 ) {
		d_nodes[d] += 1;
		apply_fwd_rule(ruleid, &n.state, &child);
		Node* m = bounded_dfs_visit(n.make_node(child,ruleid,get_fwd_rule_cost(ruleid)),
									d+1,
									bound);
		if(m > nullptr) return m;
	}

	return nullptr; //failure: there is no path from node n to goal
}

Node iterative_deepening_depth_first_search(int depth){
	Node root = make_root_node(); 

	init_fwd_iter(&iter, &state);

	root.state = state;

	printf("iterador y estado: \n");
	print_state(stdout,&state);
	printf(" \n");

	//perform depth_bounded searches with increasing depth bounds
	Node* n = bounded_dfs_visit(root, 0, depth);
	if(n > nullptr) return *n;
	return root;
}

int main(int argc, char **argv) {	
	int depth = atoi(argv[1]);

	/*
	//initialize state
	int d; //distance
	PriorityQueue<state_t> open; // used for the states we have generated but not yet expanded (the OPEN list)
	// add goal states
	first_goal_state(&state, &d);
	do {
		open.Add(0, 0, state);
	} while( next_goal_state(&state, &d) );
	// remove top state from priority state
    state = open.Top();
    open.Pop();
    */

    printf("estado inicial: \n");
    print_state(stdout,&state);
    printf(" \n");

	//initialize number of nodes
	for(int i=0; i<=depth; i++ ){
		d_nodes[i] = 0;
	}

	//execute id dfs
	iterative_deepening_depth_first_search(atoi(argv[1]));

	//show number of nodes created
	fprintf(stderr, "depth 	nodes\n");     
	for(int i=0; i<=depth; i++ ){
		fprintf(stderr, "%d 	%d\n",i,d_nodes[i]);
	} 
	fprintf(stderr, "\n"); 

	return 0;
}

