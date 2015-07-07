#include <iostream>
#include <fstream>

#include "filesystem.hh"

int main(int argc, char* argv[])
{
  if (argc != 3)
  {
    std::cerr << "usage: " << argv[0] << " /path/to/doc /path/to/repository" << std::endl;
    return 1;
  }

  TfIdf tfidf;
  Filesystem fs(argv[2], true);
  fs.fetch(tfidf);
  tfidf.compute_tfidf();

  std::ifstream ifs(argv[1]);
  std::string content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));

  for (const ResultDocument& res: tfidf.ranked_similarity(content, 5))
    std::cout << res << std::endl;

  return 0;
}
