#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <algorithm>

using std::list;
using std::string;
using std::vector;
using std::cin;

struct Query {
  string type;
  string s;
  size_t ind;
};

class QueryProcessor {
  
  int bucket_count;
  
  // hash table as a vector of linked lists 
  vector<list<string>> * table;
  
  /**
   * (sum  [0..|S|-1] of (S[i] * x^i) mod prime) mod bucket_count
   *
   * Hash will automatically adjust to the bucket size.
   *
   * Magic constants of x = 263 and prime = 1000000007, fix the family
   * of hash function
   *
   * s[i] is based off the i'th character of string
   */
  size_t hash_func(const string& s) const {
    static const size_t multiplier = 263;
    static const size_t prime = 1000000007;
    
    unsigned long long hash = 0;
    
    for (int i = static_cast<int> (s.size()) - 1; i >= 0; --i)
      hash = (hash * multiplier + s[i]) % prime;
    
    return hash % bucket_count;
  }

  
public:
  
  explicit QueryProcessor(int bucket_count):
    bucket_count(bucket_count) {
    table = new vector<list<string>>(bucket_count,list<string>());
  }
  
  ~QueryProcessor(){
    delete table;
  }
  
  Query readQuery() const {
    Query query;
    cin >> query.type;
    if (query.type != "check")
      cin >> query.s;
    else
      cin >> query.ind;
    return query;
  }

  inline void writeSearchResult(bool was_found) const {
    std::cout << (was_found ? "yes" : "no")<<std::endl;;
  }
  
  /**
   * Add str to the hash table. if table is insufficient size.
   * resize it.
   */
  void add_string(const string & str) {
    vector<list<string>>& hash_table = *table; 
    long long id = idx(str);
    
    if(id > bucket_count)
      resize(id);
    
    hash_table[id].push_front(str);
  }

  void resize(long long sz) {
    vector<list<string>>& hash_table = *table; 
    
    while(bucket_count < sz) bucket_count *= 2;
    
    vector<list<string>>* new_table = new vector<list<string>>(bucket_count,list<string>());
    
    for(auto const & chain : hash_table) {
      for(auto const & e  : chain) {
        (*new_table)[idx(e)].push_front(e); 
      }
    }
    
    delete table;
    this->table = new_table;
  }

  inline long long idx(const string & str) {
    return static_cast<long long>(hash_func(str));
  }
  
  inline bool find(const string & str) {
    vector<list<string>>& hash_table = *table; 
    list<string>& chain = hash_table[idx(str)];
    for(auto const & elem : chain)
      if(elem == str) return true;
    return false;
  }
  
  void processQuery(const Query& query) {
    vector<list<string>>& hash_table = *table; 
    
    if (query.type == "check") { // space seperated chain mapped to same key 
      list<string>& chain = hash_table[query.ind];
      for(auto const & elem : chain)
        std::cout<<elem<<" ";
      std::cout <<std::endl;
    } else {
      
      if (query.type == "find") {
        writeSearchResult(find(query.s));
      } else if (query.type == "add") {
        add_string(query.s);
      } else if (query.type == "del") {
        list<string>& chain = hash_table[idx(query.s)];
        for(auto it = chain.begin(); it!=chain.end();){
          (query.s == *it) ? chain.erase(it++) : it++;
        }
 
      }
    }
  }

  void processQueries() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i)
      processQuery(readQuery());
  }
  
};

int main() {
  std::ios_base::sync_with_stdio(false);
  int bucket_count;
  cin >> bucket_count;
  QueryProcessor proc(bucket_count);
  proc.processQueries();
  return 0;
}
