#include <algorithm>
#include <iostream>
#include <string>

#include <tbb/task_scheduler_init.h>

#include "filesystem.hh"
#include "timer.hh"

int main(int argc, char* argv[])
{
  if (argc != 4)
  {
    std::cerr << "usage: " << argv[0]
              << " nb_threads nb_similar_docs /path/to/repository" << std::endl;
    return 1;
  }

  unsigned long nb_threads;
  unsigned long nb_sim;

  try
  {
    nb_threads = std::stoul(argv[1], 0, 10);
  }
  catch (std::exception& e)
  {
    std::cerr << "error: invalid thread count." << std::endl;
    return 1;
  }

  try
  {
    nb_sim = std::stoul(argv[2], 0, 10);
  }
  catch (std::exception& e)
  {
    std::cerr << "error: invalid similar documents count." << std::endl;
    return 1;
  }

  tbb::task_scheduler_init init(nb_threads);
  std::vector<ResultDocument> res;
  TfIdf tfidf;

  try
  {
    Filesystem fs(argv[3], true);

    {
      Timer timer("Process documents");
      fs.fetch(tfidf);
    }
  }
  catch (std::exception& e)
  {
    std::cerr << "error: " << e.what() << std::endl;
    return 1;
  }

  {
    Timer timer("Compute TF-IDF");
    tfidf.compute_tfidf();
  }

  {
    Timer timer("Compute similarity");
    tfidf.compute_similarity(res, nb_sim);
  }

  std::sort(res.begin(), res.end());

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
