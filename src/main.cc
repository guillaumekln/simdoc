#include <algorithm>
#include <iostream>
#include <string>

#include <boost/program_options.hpp>
#include <tbb/task_scheduler_init.h>

#include "filesystem.hh"
#include "scoped-timer.hh"

namespace po = boost::program_options;

int main(int argc, char* argv[])
{
  po::options_description desc("Allowed options");

  desc.add_options()
    ("help,h", "Display this help")
    ("threads,t", po::value<unsigned>()->default_value(4), "Set the number of threads to use")
    ("count,c", po::value<unsigned>()->default_value(5), "Set the number of similar documents to list")
    ("input,i", po::value<std::string>(), "Set the input: directory or text file with one file per line")
    ("recursive,r", po::bool_switch()->default_value(false), "Enable a recursive directory traversal")
    ("with-times", po::bool_switch()->default_value(false), "Display execution times")
    ;

  po::positional_options_description p;
  p.add("input", -1);

  po::variables_map vm;
  po::store(po::command_line_parser(argc, argv).options(desc).positional(p).run(), vm);
  po::notify(vm);

  if (vm.count("help"))
  {
    std::cerr << "Usage: " << argv[0] << " [options] input" << std::endl
              << desc;
    return 0;
  }

  if (!vm.count("input"))
  {
    std::cerr << "error: missing input to process." << std::endl;
    return 1;
  }
  else if (!boost::filesystem::exists(vm["input"].as<std::string>()))
  {
    std::cerr << "error: input does not exist." << std::endl;
    return 1;
  }

  Filesystem fs(vm["input"].as<std::string>(), vm["recursive"].as<bool>());
  tbb::task_scheduler_init init(vm["threads"].as<unsigned>());
  bool with_time = vm["with-times"].as<bool>();

  std::vector<ResultDocument> res;
  TfIdf tfidf;

  {
    ScopedTimer timer(with_time ? "Process documents" : "");
    fs.fetch(tfidf);
  }

  {
    ScopedTimer timer(with_time ? "Compute TF-IDF" : "");
    tfidf.compute_tfidf();
  }

  {
    ScopedTimer timer(with_time ? "Compute similarity" : "");
    tfidf.compute_similarity(res, vm["count"].as<unsigned>());
  }

  std::cout << res << std::endl;

  return 0;
}
