#include <cassert>
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <utility>
#include <algorithm>
#include <cstdlib>

using std::list;
using std::string;
using std::vector;
using std::cin;
using std::cerr;
using std::cout;

#ifdef DEBUG
const bool debug = true;
#else
const bool debug = false;
#endif

struct Query {
  string type;
  string s;
  size_t ind;
};

class QueryProcessor {
  
  long long bucket_count = 0;

  long long num_keys = 0;
  
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
  long long hash_func(const string& s) const {
    static const long long multiplier = 263;
    static const long long prime = 1000000007;
    unsigned long long hash = 0;
    for (long long i = static_cast<long long> (s.size()) - 1; i >= 0; --i)
      hash = (hash * multiplier + s[i]) % prime;
    return hash % bucket_count;
  }

  
private:
  
  inline long long next_bucket_count(long long in){
    long long i = 1;
    for( i = 1; i < in; i *= 2);
    return i;
  }

  void resize() {
    vector<list<string>>& hash_table = *table; 
    bucket_count *= 2;
    
    if(debug)
      std::cerr<<"resizing:"<<bucket_count<<std::endl;
        
    vector<list<string>>* new_table =
      new vector<list<string>>(bucket_count,list<string>());
    
    for(const auto & chain : hash_table) 
      for(const auto & e  : chain) {
        if(debug)
          std::cerr<<"rehashing "<<e<<std::endl;
        (*new_table)[idx(e)].push_front(e); 
      }
    
    delete table;
    this->table = new_table;
  }
  
public:
  
  explicit QueryProcessor(int bucket_count): bucket_count(bucket_count) {
    bucket_count = next_bucket_count(bucket_count);
    table = new vector<list<string>>(bucket_count,list<string>());
  }
  
  ~QueryProcessor(){
    delete table;
  }
  
  inline long long idx(const string & str) {
    return static_cast<long long>(hash_func(str));
  }

  /**
   * Add str to the hash table. if table is insufficient size.
   * resize it.
   */
  void add_string(const string & str) {
    long long id = idx(str);
    double  load_factor = (num_keys*1.0)/bucket_count; 
    
    if(debug)
      std::cerr<<"load_factor:"<<load_factor<<"["<<num_keys<<","<<bucket_count<<"]"<<std::endl;
    
    if(load_factor > .9)
      resize();
    
    vector<list<string>>& hash_table = *table; 
    if(!find_string(str)) {
      hash_table[id].push_front(str);
      num_keys++;
    }
  }
  
  /**
   * true - there exists a occurance of str in hashed bucket.
   */
  inline bool find_string(const string & str) {
    vector<list<string>>& hash_table = *table; 
    list<string>& chain = hash_table[idx(str)];
    for(auto const & elem : chain)
      if(elem == str) return true;
    return false;
  }
  
  /**
   * Delete all occurances of str from hashed bucket.
   */  
  void delete_string(const string & str) {
    vector<list<string>>& hash_table = *table; 
    list<string>& chain = hash_table[idx(str)];
    for(auto it = chain.begin(); it!=chain.end();){
      if(str == *it) {
        chain.erase(it++) ;
        num_keys--;
      } else {
          it++;
      }
    }
  }
  
  Query readQuery() const {
    Query query;
    cin >> query.type;
    (query.type != "check") ? cin >> query.s : cin >> query.ind;
    return query;
  }

  inline void writeSearchResult(bool was_found) const {
    std::cout<< (was_found ? "yes" : "no")<<std::endl;;
  }
   
  void processQuery(const Query& query) {
    vector<list<string>>& hash_table = *table; 
    if (query.type == "check") { // space seperated chain mapped to same key 
      for(auto const & elem : hash_table[query.ind])
        std::cout<<elem<<" ";
      std::cout <<std::endl;
    } else if (query.type == "find") {
      writeSearchResult(find_string(query.s));
    } else if (query.type == "add") {
      add_string(query.s);
    } else if (query.type == "del") {
      delete_string(query.s);
    } // ignore unknown commands
  }

  void processQueries() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i)
      processQuery(readQuery());
  }
  
};

string random_string(int len) {
  string retval(len,' ');
  static const char char_set[] =
    "0123456789"
    "abcdefghijklmnopqrstuvwxyz"
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  for(int i = 0 ;i< len; i++)
    retval[i] = char_set[rand() % (sizeof(char_set)-1)];
  
  return retval;
}

void test() {
  
  QueryProcessor proc(10);
  std::map<string,bool> map;
  
  for(long long i = 0 ; i < 1000000; i++) {
    string r = random_string(50); 
    map[r] = true; 
    proc.add_string(r);
  }
  
  int i = 0; 
  for(const auto& entry : map) {
    if(debug)
      std::cerr<<"checking "<<i++<<" "<<entry.first<<"("<<proc.idx(entry.first)<<")"<<std::endl;
    assert(proc.find_string(entry.first));
    proc.delete_string(entry.first);
    assert(!proc.find_string(entry.first));
  }
  
}

int main() {
  std::ios_base::sync_with_stdio(false);
  if(debug) {
    test();
    return 0;
  }
  int bucket_count;
  cin >> bucket_count;
  QueryProcessor proc(bucket_count);
  proc.processQueries();
  return 0;
}
