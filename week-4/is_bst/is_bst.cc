#include <algorithm>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

struct Node {
  int key;
  int left;
  int right;
  Node() : key(0), left(-1), right(-1) {}
  Node(int key_, int left_, int right_) : key(key_), left(left_), right(right_) {}
};

bool is_bst(const vector<Node>& tree,int cur) {
  if(tree.empty()) return true;
  
  Node cur_nd = tree[cur];
  
  if(cur_nd.left >=0  && !(tree[cur_nd.left].key < tree[cur].key))
    return false;
  
  if(cur_nd.right >=0  && !(tree[cur_nd.right].key >= tree[cur].key))
    return false;
  
  if(cur_nd.left >= 0 && !is_bst(tree,cur_nd.left))
     return false;
     
  if(cur_nd.right >= 0 && !is_bst(tree,cur_nd.right))
     return false;
  
  return true;
}

int main() {
  int nodes;
  cin >> nodes;
  vector<Node> tree;
  for (int i = 0; i < nodes; ++i) {
    int key, left, right;
    cin >> key >> left >> right;
    tree.push_back(Node(key, left, right));
  }
  const char* bst_msg[] = {"INCORRECT","CORRECT" };
  cout<< bst_msg[is_bst(tree,0)] <<endl; 
  return 0;
}
