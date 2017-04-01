#include <algorithm>
#include <utility>
#include <iostream>
#include <vector>

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
  int key;
  int left;
  int right;
  Node() : key(0), left(-1), right(-1) {}
  Node(int key_, int left_, int right_) : key(key_), left(left_), right(right_) {}
};

typedef pair<int,int> range;

/**
 * Return rightmost child as well as if it is tree.
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
    tree.push_back(Node(key, left, right));
  }
  const char* bst_msg[] = {"INCORRECT","CORRECT" };
  cout<< bst_msg[is_bst(tree,0).first] <<endl; 
  return 0;
}
