#include <iostream>
#include <string>
#include <fstream>
#include <ctime>

#include "filesystem.hh"

class Timer
{
public:
  Timer()
    : _start(std::clock())
  {
  }

  ~Timer()
  {
    std::cerr << "(done in "
              << (std::clock() - _start) / (double)(CLOCKS_PER_SEC / 1000) << " ms)"
              << std::endl;
  }
private:
  std::clock_t _start;
};

int main(int argc, char* argv[])
{
  if (argc != 3)
  {
    std::cerr << "usage: " << argv[0] << " count /path/to/repository" << std::endl;
    return 1;
  }

  TfIdf tfidf;
  Filesystem fs(argv[2], true);
  std::cerr << "Compute TF-IDF..." << std::endl;

  {
    Timer timer;
    fs.fetch(tfidf);
    tfidf.compute_tfidf();
  }

  size_t count = std::stoul(argv[1], 0, 10);
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
