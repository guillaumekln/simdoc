#include <iostream>
#include <string>
#include <fstream>
#include <chrono>

#include <tbb/task_scheduler_init.h>

#include "filesystem.hh"

class Timer
{
public:
  Timer()
    : _t0(std::chrono::steady_clock::now())
  {
  }

  ~Timer()
  {
    auto diff = std::chrono::steady_clock::now() - _t0;
    double ms = std::chrono::duration_cast<std::chrono::milliseconds>(diff).count();
    std::cerr << "Done in " << ms / 1000.0 << " seconds." << std::endl;
  }

private:
  std::chrono::steady_clock::time_point _t0;
};

int main(int argc, char* argv[])
{
  if (argc != 4)
  {
    std::cerr << "usage: " << argv[0] << " nthreads count /path/to/repository" << std::endl;
    return 1;
  }

  tbb::task_scheduler_init init(std::stoul(argv[1], 0, 10));

  TfIdf tfidf;
  Filesystem fs(argv[3], true);
  std::cerr << "Compute TF-IDF..." << std::endl;

  {
    Timer timer;
    fs.fetch(tfidf);
    tfidf.compute_tfidf();
  }

  size_t count = std::stoul(argv[2], 0, 10);
  std::vector<ResultDocument> res;
  std::cerr << "Compute similarity..." << std::endl;

  {
    Timer timer;
    tfidf.compute_similarity(res, count);
  }

  std::cout << '[';
  for (auto it = res.cbegin(); it != res.cend(); it++)
  {
    if (it != res.cbegin())
      std::cout << ',';
    std::cout << *it;
  }
  std::cout << ']' << std::endl;

  return 0;
}
