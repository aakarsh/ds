#include <stack>
#include <algorithm>
#include <utility>
#include <iostream>
#include <cassert>
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
  int min = -1;
  int max = -1;
  Node() : key(0), left(-1), right(-1) {}
  Node(long long key_, int left_, int right_) : key(key_),min(key_),max(key_), left(left_), right(right_) {}
};

typedef pair<long long,long long> range;

bool is_bst(vector<Node> & tree, int idx) {
  
  if(tree.empty()) return true;
  
  for(auto &n : tree)
    n.visited = false;
  
  stack<Node> s;
  Node cur = tree[idx];
  s.push(cur);
  
  while(!s.empty()) {
    
    cur = s.top(); s.pop();
    
    while(cur.left != -1 && !(tree[cur.left].visited)  ) { // go-left son 
      s.push(tree[cur.pos]);
      cur = tree[cur.left];
    }
    
    
    if( cur.right != -1 && !(tree[cur.right].visited)) { // has a right child
      s.push(tree[cur.pos]); // keep on stack till right is processed.
      cur = tree[cur.right];
      s.push(tree[cur.pos]);
      continue;
    }
    
    if((cur.left == -1  || tree[cur.left].visited) &&
       (cur.right == -1  || tree[cur.right].visited)){

      if(cur.left!=-1)
        tree[cur.pos].min = tree[cur.left].max;
      if(cur.right!=-1)
        tree[cur.pos].max = tree[cur.right].min;
      
      // Exhausted left sub tree, visit current
      tree[cur.pos].visited = true;
      if(cur.left!=-1 && cur.key <= tree[cur.pos].min )
        return false;
      if(cur.right!=-1 && cur.key > tree[cur.pos].max )
        return false;
    }
    
  }
  
  for(auto &n : tree)
    n.visited = false;
  
  return true;
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
  const char* bst_msg[] = {"INCORRECT","CORRECT" };
  cout<< bst_msg[is_bst(tree,0)] <<endl; 
  return 0;
}
