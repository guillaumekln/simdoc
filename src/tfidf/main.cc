#include <iostream>

#include "filesystem.hh"

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    return 1;
  }

  TfIdf tfidf;
  Filesystem fs(argv[1], true);
  fs.fetch(tfidf);
  tfidf.compute_tfidf();

  for (const ResultDocument& res: tfidf.ranked_similarity("life learning", 5))
    std::cout << res << std::endl;

  return 0;
}
