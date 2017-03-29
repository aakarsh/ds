#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <utility>

using std::pair;
using std::priority_queue;
using std::vector;
using std::cin;
using std::cout;

class JobQueue {

 private:
  
  int num_workers_;
  vector<int> jobs_;

  vector<int> assigned_workers_;
  vector<long long> start_times_;

  void WriteResponse() const {
    for (int i = 0; i < jobs_.size(); ++i) {
      cout << assigned_workers_[i] << " " << start_times_[i] << "\n";
    }
  }

  void ReadData() {
    int m;
    cin >> num_workers_ >> m;
    jobs_.resize(m);
    for(int i = 0; i < m; ++i)
      cin >> jobs_[i];
  }

  class pair_compare {
  public:
     bool operator()(const pair<long,long> & w1 , const pair<long,long> & w2 ) {
       return w1.second == w2.second ? w1.first > w2.first : w1.second > w2.second;
    }
  };

  void AssignJobs() {
    
    assigned_workers_.resize(jobs_.size());
    start_times_.resize(jobs_.size());
    
    vector<long long> next_free_time(num_workers_, 0);
    
    typedef std::priority_queue<pair<long,long>,vector<pair<long,long>>,pair_compare> heap_t;
    heap_t worker_queue;
    
    int dawn_of_time = 0;
    for(long i = 0; i < num_workers_; i++){
      worker_queue.push(std::make_pair(i,dawn_of_time));
    }
    
    /**
     * Using a priority queue:
     *
     * 1. Find workers with minimum next_free_time
     * 2. Assign the new worker to this job. 
     * 3. Add job duration to worker finish time add back to the priority queue.
     */
    for(long i = 0; i < jobs_.size(); i++) {
      int duration = jobs_[i];
      
      pair<long,long> worker = worker_queue.top(); worker_queue.pop();
      
      long worker_id = worker.first;
      long worker_finish_time = worker.second;
     
      assigned_workers_[i] = worker_id;
      
      // start time for this job will be when the worker that
      // was assigned to it finishes.
      start_times_[i] = worker_finish_time;

      worker_finish_time += duration;
      
      // enqueue the worker back to the queue.
      pair<long,long> updated_worker = std::make_pair(worker.first,worker_finish_time);
      worker_queue.push(updated_worker);
    }
    
  }

 public:
  
  void Solve() {
    ReadData();
    AssignJobs();
    WriteResponse();
  }
  
};

int main() {
  std::ios_base::sync_with_stdio(false);
  JobQueue job_queue;
  job_queue.Solve();
  return 0;
}
