#include <stack>
#include <algorithm>
#include <utility>
#include <iostream>
#include <vector>

using std::stack;
using std::pair;
using std::make_pair;
using std::cin;
using std::cout;
using std::endl;
using std::vector;

#ifdef DEBUG
const bool debug = true;
#else
const bool debug = false;
#endif

struct Node {
  long long key;
  int left;
  int right;
  bool visited = 0;
  int pos  = -1;
  Node() : key(0), left(-1), right(-1) {}
  Node(long long key_, int left_, int right_) : key(key_), left(left_), right(right_) {}
};

typedef pair<long long,long long> range;

void in_order(const vector<Node>& tree, int cur){
  if(tree.empty())
    return;
  Node n = tree[cur];
  int left = n.left;
  int right = n.right;
  
  if(left >= 0)
    in_order(tree,left);
  
  cout<<" "<<n.key<<" ";
  
  if(right>=0)
    in_order(tree,right);
  
}

void in_order_stackless( vector<Node>& tree,int idx){
  
  if(tree.empty())
    return;
  
  stack<Node*> s;
  Node root = tree[idx];
  
  s.push(&root);
  while(!s.empty()) {
    
    Node * cur_p = s.top(); s.pop();
    Node & cur = *cur_p;
    if( cur.left == -1 || tree[cur.left].visited ) { // ready process current node
      
      std::cout<<" "<<cur.key<<" ";
      cur.visited = true;
      
      if(cur.right >= 0) { // add the right child for processing. 
        s.push(&tree[cur.right]);
      }
      
    } else { // unvisited left child
      s.push(&cur); // delay processing current
      s.push(&tree[cur.left]);
    }
  }
}

void in_order_nonrecurse(vector<Node> & tree, int idx) {
  
  if(tree.empty()) return;
  
  for(auto &n : tree) n.visited = false;
  
  stack<Node> s;
  Node cur =tree[idx];
  s.push(cur);
  
  while(!s.empty()) {
    
    cur = s.top(); s.pop();
    
    while(cur.left != -1 && !(tree[cur.left].visited)  ) { // go-left son 
      s.push(tree[cur.pos]);
      cur = tree[cur.left];
    }
    
    // Exhausted left sub tree, visit current
    std::cerr<<" "<< cur.key<<" ";
    tree[cur.pos].visited = true;
    
    if(cur.right != -1 ) {// has a right child 
      cur = tree[cur.right];
      s.push(tree[cur.pos]);
    }
  }
  
  for(auto &n : tree) n.visited = false;
  
  std::cerr<<endl;
}

/**
 * Return rightmost child as well as if it is tree.
 j
 */
pair<bool,range>is_bst (const vector<Node>& tree,int cur) {
  
  range empty_range = make_pair(-1,-1);
  
  if(tree.empty())
    return make_pair(true,empty_range);
                                         
  Node cur_nd = tree[cur];
  range left_range  = make_pair(cur_nd.key,cur_nd.key);
  range right_range = make_pair(cur_nd.key,cur_nd.key);

  if(cur_nd.left >=0  && !(tree[cur_nd.left].key < cur_nd.key)) {
    
    if(debug)
      std::cerr<<"for node "<<cur_nd.key<<" left child more "<<tree[cur_nd.left].key<<std::endl;
    
    return make_pair(false,empty_range);
  }
  
  if(cur_nd.right >=0  && !(tree[cur_nd.right].key >= cur_nd.key)) {
    
    if(debug)
      std::cerr<<"for node "<<cur_nd.key<<" right child less "<<tree[cur_nd.right].key<<std::endl;
    
    return make_pair(false,empty_range);
  }
  
  if(cur_nd.left >= 0) {
    pair<bool,range> p = is_bst(tree,cur_nd.left);
    bool left_bst = p.first;
    left_range = p.second;
  
    if(!left_bst || !(left_range.second < cur_nd.key))
      return make_pair(false,empty_range);
  }
  
  if(cur_nd.right >= 0) {
    pair<bool,range> rp = is_bst(tree,cur_nd.right);
    bool right_bst = rp.first;
    right_range = rp.second;
  
    if(!right_bst || !(right_range.first >= cur_nd.key))
      return make_pair(false,empty_range);
  }
  
  range cur_range = make_pair(left_range.first,right_range.second); 
  if(debug)
    std::cerr<<"key: "<<cur_nd.key<<" range :["<<cur_range.first<<","<<cur_range.second<<"]"<<std::endl;
  
  return make_pair(true,cur_range);
}


int main() {
  int nodes;
  cin >> nodes;
  vector<Node> tree;
  for (int i = 0; i < nodes; ++i) {
    int key, left, right;
    cin >> key >> left >> right;
    Node n = Node(key, left, right);
    n.pos = i;
    n.visited = false;
    tree.push_back(n);
  }
  if(debug){ 
    in_order(tree,0);
    std::cout<<endl;
    in_order_stackless(tree,0);
    std::cout<<std::endl;
    in_order_nonrecurse(tree,0);
  }  
  const char* bst_msg[] = {"INCORRECT","CORRECT" };
  cout<< bst_msg[is_bst(tree,0).first] <<endl; 
  return 0;
}
