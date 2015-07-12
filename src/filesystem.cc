#include "filesystem.hh"

#include <iostream>
#include <stdexcept>
#include <fstream>

#include <tbb/parallel_for.h>
#include <tbb/blocked_range.h>

Filesystem::Filesystem(const std::string& directory, bool recursive)
  : _directory(directory)
  , _recursive(recursive)
{
  if (!boost::filesystem::exists(_directory))
  {
    throw std::invalid_argument(directory + " directory does not exist");
  }
}

void Filesystem::fetch_rec(const boost::filesystem::path& dir)
{
  boost::filesystem::directory_iterator end_it;

  for (boost::filesystem::directory_iterator it(dir); it != end_it; ++it)
  {
    if (_recursive && boost::filesystem::is_directory(it->status()))
    {
      fetch_rec(it->path());
    }
    else if (boost::filesystem::is_regular_file(it->status()))
    {
      _files.push_back(it->path());
    }
  }
}

void Filesystem::merge(TfIdf& main, const TfIdf& aux)
{
  std::lock_guard<std::mutex> lock(_mutex);
  main.merge(aux);
}

void Filesystem::fetch(TfIdf& tfidf)
{
  fetch_rec(_directory);

  tbb::parallel_for(tbb::blocked_range<size_t>(0, _files.size()),
                    [&](const tbb::blocked_range<size_t>& r)
                    {
                      TfIdf aux;

                      for (size_t i = r.begin(); i != r.end(); ++i)
                      {
                        std::string path = _files[i].native();
                        std::string filename = _files[i].filename().native();

                        std::ifstream ifs(path);
                        std::string content((std::istreambuf_iterator<char>(ifs)),
                                            (std::istreambuf_iterator<char>()));

                        aux.add(filename, content);
                      }

                      merge(tfidf, aux);
                    });
}
