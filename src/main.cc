#include <iostream>
#include <string>
#include <fstream>

#include "filesystem.hh"

int main(int argc, char* argv[])
{
  if (argc != 4)
  {
    std::cerr << "usage: " << argv[0] << "count /path/to/doc /path/to/repository" << std::endl;
    return 1;
  }

  TfIdf tfidf;
  Filesystem fs(argv[3], true);
  fs.fetch(tfidf);
  tfidf.compute_tfidf();

  std::ifstream ifs(argv[2]);
  std::string content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));

  size_t count = std::stoul(argv[1], 0, 10);

  std::cout << '[';
  for (const ResultDocument& res: tfidf.ranked_similarity(content, count))
  {
    std::cout << res;
    if (--count > 0)
      std::cout << ',';
  }
  std::cout << ']' << std::endl;

  return 0;
}
