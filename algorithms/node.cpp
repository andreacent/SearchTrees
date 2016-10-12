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

Node make_root_node(state_t state){
	Node node(state, NULL, -1, 0);
	return node;
}