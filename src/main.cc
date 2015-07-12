#include <algorithm>
#include <iostream>
#include <string>

#include <boost/program_options.hpp>
#include <tbb/task_scheduler_init.h>

#include "filesystem.hh"
#include "timer.hh"

namespace po = boost::program_options;

int main(int argc, char* argv[])
{
  po::options_description desc("Allowed options");

  desc.add_options()
    ("help,h", "Display this help")
    ("threads,t", po::value<unsigned>()->default_value(4), "Set the number of threads to use")
    ("count,c", po::value<unsigned>()->default_value(5), "Set the number of similar documents to list")
    ("dir,d", po::value<std::string>(), "Set the directory to process")
    ("recursive,r", po::bool_switch()->default_value(false), "Enable a recursive directory traversal")
    ;

  po::positional_options_description p;
  p.add("dir", -1);

  po::variables_map vm;
  po::store(po::command_line_parser(argc, argv).options(desc).positional(p).run(), vm);
  po::notify(vm);

  if (vm.count("help"))
  {
    std::cerr << "Usage: " << argv[0] << " [options] directory" << std::endl
              << desc;
    return 0;
  }

  if (!vm.count("dir"))
  {
    std::cerr << "error: missing directory to process." << std::endl;
    return 1;
  }

  tbb::task_scheduler_init init(vm["threads"].as<unsigned>());
  std::vector<ResultDocument> res;
  TfIdf tfidf;

  try
  {
    Filesystem fs(vm["dir"].as<std::string>(), vm["recursive"].as<bool>());

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
    tfidf.compute_similarity(res, vm["count"].as<unsigned>());
  }

  std::cout << res << std::endl;

  return 0;
}
