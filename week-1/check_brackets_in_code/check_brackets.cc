#include <iostream>
#include <stack>
#include <string>

struct Bracket {
  Bracket(char type, int position):
    type(type),
    position(position)
  {}

  bool match(char c) {
    if (type == '[' && c == ']')
      return true;
    if (type == '{' && c == '}')
      return true;
    if (type == '(' && c == ')')
      return true;
    return false;
  }

  char type;
  int position;
};


int main() {
  std::string text;
  getline(std::cin, text);

  std::stack <Bracket> opening_brackets_stack;
  
  for (int position = 0; position < text.length(); ++position) {
    char next = text[position];

    if (next == '(' || next == '[' || next == '{') {
      opening_brackets_stack.push(Bracket(next,position)); 
    } else if (next == ')' || next == ']' || next == '}') {
      if(opening_brackets_stack.empty()) {
        std::cout<<position+1<<std::endl;
        return 0;
      } else {
        if(opening_brackets_stack.top().match(next)) {
          opening_brackets_stack.pop();
        }
      }
    }
  }

  if(opening_brackets_stack.empty()) {
    std::cout<<"Success"<<std::endl;
  } else {
    Bracket br = opening_brackets_stack.top();
    std::cout<<br.position+1<<std::endl;
  }
  
  return 0;
}
