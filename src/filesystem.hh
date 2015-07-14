#ifndef FILESYSTEM_HH
# define FILESYSTEM_HH

# include <boost/filesystem.hpp>
# include <string>
# include <vector>

# include "data-source.hh"

class Filesystem: public DataSource
{
public:
  Filesystem(const std::string& directory, bool recursive = false);

  virtual void fetch(TfIdf& tfidf) override;

private:
  void fetch_rec(const boost::filesystem::path& dir);

  std::vector<boost::filesystem::path> _files;
  boost::filesystem::path _directory;
  bool _recursive;
};

# endif /* !FILESYSTEM_HH */
