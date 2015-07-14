#include "files-list.hh"

#include <fstream>

#include <tbb/parallel_for.h>
#include <tbb/blocked_range.h>

void FilesList::fetch(TfIdf& tfidf)
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
