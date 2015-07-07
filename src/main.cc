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
  if (argc != 4)
  {
    std::cerr << "usage: " << argv[0] << "count /path/to/doc /path/to/repository" << std::endl;
    return 1;
  }

  TfIdf tfidf;

  {
    std::cerr << "Reading repository at " << argv[3] << "..." << std::endl;
    Timer timer;

    Filesystem fs(argv[3], true);
    fs.fetch(tfidf);

    tfidf.compute_tfidf();
  }

  std::vector<ResultDocument> ranked;
  size_t count = std::stoul(argv[1], 0, 10);

  {
    std::cerr << "Search for " << argv[1] << " similar documents..." << std::endl;
    Timer timer;

    std::ifstream ifs(argv[2]);
    std::string content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));

    ranked = std::move(tfidf.ranked_similarity(content, count));
  }

  std::cout << '[';
  for (const ResultDocument& res: ranked)
  {
    std::cout << res;
    if (--count > 0)
      std::cout << ',';
  }
  std::cout << ']' << std::endl;

  return 0;
}
