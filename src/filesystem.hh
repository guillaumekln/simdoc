#ifndef FILESYSTEM_HH
# define FILESYSTEM_HH

# include <boost/filesystem.hpp>
# include <string>
# include <vector>

# include "data-source.hh"

class Filesystem: public DataSource
{
public:
  Filesystem(const std::string& input, bool recursive);

  virtual void fetch(TfIdf& tfidf) override;

private:
  void fetch_files(const boost::filesystem::path& dir, bool recursive);

  std::vector<boost::filesystem::path> _files;
};

# endif /* !FILESYSTEM_HH */
