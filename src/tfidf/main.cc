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

  tfidf.dump(std::cout);

  return 0;
}
