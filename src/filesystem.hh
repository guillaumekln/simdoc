#ifndef FILESYSTEM_HH
# define FILESYSTEM_HH

# include <boost/filesystem.hpp>
# include <string>
# include <vector>
# include <mutex>

# include "data-source.hh"

class Filesystem: public DataSource
{
public:
  Filesystem(const std::string& directory, bool recursive = false);
  void merge(TfIdf& main, const TfIdf& aux);

  virtual void fetch(TfIdf& tfidf) override;

private:
  void fetch_rec(const boost::filesystem::path& dir);

  std::vector<boost::filesystem::path> _files;
  std::mutex _mutex;
  boost::filesystem::path _directory;
  bool _recursive;
};

# endif /* !FILESYSTEM_HH */
