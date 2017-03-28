#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::cin;
using std::cout;
using std::swap;
using std::pair;
using std::make_pair;

class HeapBuilder {
 private:
  vector<int> data_;
  vector< pair<int, int> > swaps_;

  void WriteResponse() const {
    cout << swaps_.size() << "\n";
    for (int i = 0; i < swaps_.size(); ++i) {
      cout << swaps_[i].first << " " << swaps_[i].second << "\n";
    }
  }

  void ReadData() {
    int n;
    cin >> n;
    data_.resize(n);
    for(int i = 0; i < n; ++i)
      cin >> data_[i];
  }

  void sift_down(int i,vector<pair<int,int>> & swaps) {
    int min_index = i;
    int size = this->data_.size();
    int left  = 2*i+1;
    if(left < size && this->data_[left]  < this->data_[min_index]){
      min_index = left;
    }
      
    int right = left+1;
    if(right < size && this->data_[right]  < this->data_[min_index]){
      min_index = right;
    }
    
    if(i != min_index) {
      std::swap(data_[min_index],data_[i]);
      swaps.push_back(make_pair(min_index,i));
      sift_down(min_index,swaps);
    }
  }
  

  void GenerateSwaps() {
    swaps_.clear();

    int n = data_.size();
    for(int i = n/2 ; i >=0 ; i--){
      sift_down(i,swaps_);
    }
  }

 public:
  void Solve() {
    ReadData();
    GenerateSwaps();
    WriteResponse();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  HeapBuilder heap_builder;
  heap_builder.Solve();
  return 0;
}
