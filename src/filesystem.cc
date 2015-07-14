#include "filesystem.hh"

#include <fstream>

#include <tbb/parallel_for.h>
#include <tbb/blocked_range.h>

Filesystem::Filesystem(const std::string& directory, bool recursive)
{
  fetch_files(directory, recursive);
}

void Filesystem::fetch_files(const boost::filesystem::path& dir, bool recursive)
{
  boost::filesystem::directory_iterator end_it;

  for (boost::filesystem::directory_iterator it(dir); it != end_it; ++it)
  {
    if (recursive && boost::filesystem::is_directory(it->status()))
    {
      fetch_files(it->path(), recursive);
    }
    else if (boost::filesystem::is_regular_file(it->status()))
    {
      _files.push_back(it->path());
    }
  }
}

void Filesystem::fetch(TfIdf& tfidf)
{
  tbb::parallel_for(tbb::blocked_range<size_t>(0, _files.size()),
                    [&](const tbb::blocked_range<size_t>& r)
                    {
                      TfIdf aux;

                      for (size_t i = r.begin(); i != r.end(); ++i)
                      {
                        std::string path(_files[i].native());
                        std::string filename(_files[i].filename().native());

                        std::ifstream ifs(path);
                        std::string content((std::istreambuf_iterator<char>(ifs)),
                                            (std::istreambuf_iterator<char>()));

                        aux.add(filename, content);
                      }

                      safe_merge(tfidf, aux);
                    });
}
