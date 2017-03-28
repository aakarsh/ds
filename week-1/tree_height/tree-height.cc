#include <utility> 
#include <stack> 
#include <cassert>
#include <algorithm>
#include <iostream>
#include <vector>
#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif

#ifdef DEBUG
const bool debug = true;
#else
const bool debug = false;
#endif

using  std::pair;

class Node;

class Node {
public:
  int key;
  Node *parent;
  std::vector<Node *> children;

  Node() {
    this->parent = NULL;
  }

  void setParent(Node *theParent) {
    parent = theParent;
    parent->children.push_back(this);
  }
  bool is_leaf() { return this->children.empty(); }
};


int main_with_large_stack_space() {
  
  std::ios_base::sync_with_stdio(0);
  int n;
  std::cin >> n;


  // vector of nodes - represent each leaf 
  std::vector<Node> nodes;
  nodes.resize(n);
  int root;
  // iterating through every node
  for (int child_index = 0; child_index < n; child_index++) {
    // for current child node read parent index
    int parent_index;
    std::cin >> parent_index;
    // set node<child_index>'s parent to be read value
    // -1 will have no parent since it is the root
    if (parent_index >= 0)
      nodes[child_index].setParent(&nodes[parent_index]);
    else
      root = child_index;
    
    nodes[child_index].key = child_index;
  }
  
  long maxHeight = 0;
  
  /**
   * Instead we can start from root and do a depth first traversal and
   * find compute height.
   */
  std::stack<pair<long,Node*>> stacked;
  stacked.push(std::make_pair(0,&nodes[root]));

  while( !stacked.empty() ) {
    // need reference to top to modify processed child index 
    pair<long,Node*> *cur  = &(stacked.top());
    Node* node = cur->second;
    long child_position = cur->first;

    if (node->is_leaf()) {
      maxHeight = std::max((long)stacked.size() , maxHeight);
      if(debug)
        std::cerr<<"height : "<<maxHeight<<" stack "<<stacked.size()<<std::endl;
      
    } else {
      // better off with node child iterator? 
      if( child_position < node->children.size() ) {
        Node* child = node->children[child_position];
        stacked.push(std::make_pair(0,child));
        
        if(debug) std::cerr<<"pushing "<<child->key <<std::endl;
        
        // increment child position,ugly! 
        cur->first+=1;
        // continue to process newly pushed child 
        continue;
      }
    }
    stacked.pop();
  }
  std::cout << maxHeight << std::endl;
  return 0;
}

int main (int argc, char **argv)
{
#if defined(__unix__) || defined(__APPLE__)
  // Allow larger stack space
  const rlim_t kStackSize = 16 * 1024 * 1024;   // min stack size = 16 MB
  struct rlimit rl;
  int result;

  result = getrlimit(RLIMIT_STACK, &rl);
  if (result == 0)
    {
      if (rl.rlim_cur < kStackSize)
        {
          rl.rlim_cur = kStackSize;
          result = setrlimit(RLIMIT_STACK, &rl);
          if (result != 0)
            {
              std::cerr << "setrlimit returned result = " << result << std::endl;
            }
        }
    }

#endif
  return main_with_large_stack_space();
}
