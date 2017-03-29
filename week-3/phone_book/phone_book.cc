#include <iostream>
#include <vector>
#include <string>

using std::string;
using std::vector;
using std::cin;

/**
 * Represents a user query -{ add, del, find } 
 */
struct Query {
  string type;
  string  name;
  int number;
};

vector<Query> read_queries() {
  int n;
  cin >> n;
  vector<Query> queries(n);
  for (int i = 0; i < n; ++i) {
    cin >> queries[i].type;
    if (queries[i].type == "add")
      cin >> queries[i].number >> queries[i].name;
    else
      cin >> queries[i].number;
  }
  return queries;
}

void write_responses(const vector<string>& result) {
  for (size_t i = 0; i < result.size(); ++i)
    std::cout << result[i] << "\n";
}

vector<string> process_queries(const vector<Query>& queries) {
  
  vector<string> result;
  
  long long max_number = 0;
  for(int i = 0; i < queries.size(); i++) {
    if(queries[i].number > max_number)
      max_number = queries[i].number;
  }
  
  vector<string> names(max_number+1,"");
  
  vector<Query> contacts;
  
  // Iterate through the user queries 
  for (size_t i = 0; i < queries.size(); ++i)
    if (queries[i].type == "add") {
     names[queries[i].number] = queries[i].name; 
    } else if (queries[i].type == "del") {
      names[queries[i].number]  = "";
    } else {
      
      string response = "not found";
      if(names[queries[i].number] != "") {
        response = names[queries[i].number];
      }
      
      result.push_back(response);
    }
  return result;
}

int main() {
  write_responses(process_queries(read_queries()));
  return 0;
}
