//Iterative deepening depth_first search

#include <map>
#include "node.cpp"
using namespace std;

#define history_len 2
map<int, int> d_nodes;

//#define fwd_history_len = 0

Node* bounded_dfs_visit(Node n, 
                        unsigned int d, 
                        unsigned int bound,
                        ruleid_iterator_t iter,
                        int hist){

    state_t child;
    int ruleid,child_hist;

    if(d > bound){ 
        return nullptr; //prune branch by depth bound
    }

    if(is_goal(&n.state)) {
        printf("Goal: \n");
        printf("cost: %d  ",n.g);
        print_state(stdout,&n.state);
        printf("state: \n\n");
        Node* aux = &n;
        return aux;
    } //goal is found, return
    
    //expansion and recursion
    while( (ruleid = next_ruleid(&iter) ) >= 0 ) {

    	if (!fwd_rule_valid_for_history(hist,ruleid)) continue;
		child_hist = next_fwd_history(hist,ruleid);
    	
        d_nodes[d] += 1;
        apply_fwd_rule(ruleid, &n.state, &child);
        Node* m = bounded_dfs_visit(n.make_node(child,ruleid,get_fwd_rule_cost(ruleid)),
                                    d+1,
                                    bound,
                                    iter,
                                    child_hist);
        if(m > nullptr) return m;
    }

    return nullptr; //failure: there is no path from node n to goal
}

Node* iterative_deepening_depth_first_search(int bound){
    state_t state;
    ruleid_iterator_t iter;

    int hist = init_history; 

    init_fwd_iter(&iter, &state);

    Node root = make_root_node(state); 
    d_nodes[0] += 1;

    //perform depth_bounded searches with increasing depth bounds
    Node* n = bounded_dfs_visit(root,1,bound,iter,hist);
    if(n > nullptr) return n;

    return nullptr;
}

void print_d_nodes(int bound){
	//unsigned long sum =0;
    //show number of nodes created
    fprintf(stderr, "depth\tnodes\n");     
    for(int i=0; i<=bound; i++ ){
    	//sum += d_nodes[i];
        fprintf(stderr, "%d\t%d\n",i,d_nodes[i]);
    } 
    //fprintf(stderr, "Total %lu\n",sum); 
}

int main(int argc, char **argv) {  

    // Error
    if( argc < 3 ) {
        fprintf(stderr, "More arguments needed.\n");
        exit(-1);
    }

    int bound = atoi(argv[1]);
    bool iterative = atoi(argv[2]);
    Node* goal;

    //initialize number of nodes
    for(int i=0; i<=bound; i++ ){
        d_nodes[i] = 0;
    }

    //execute id dfs
    if( iterative ) {
        for(int d=0; d<=bound; d++){
            goal = iterative_deepening_depth_first_search(d);
            if(goal == nullptr) fprintf(stderr, "No goal reached\n");
            print_d_nodes(d);
            fprintf(stderr, "----------------\n");
        }
    }else{
        goal = iterative_deepening_depth_first_search(bound);
        if(goal == nullptr) fprintf(stderr, "No goal reached\n");
        print_d_nodes(bound);
    }

    return 0;
}

