#ifndef FILES_LIST_HH
# define FILES_LIST_HH

# include <boost/filesystem.hpp>
# include <string>
# include <vector>

# include "data-source.hh"

class FilesList: public DataSource
{
public:
  virtual void fetch(TfIdf& tfidf) override;

protected:
  std::vector<boost::filesystem::path> _files;
};

# endif /* !FILES_LIST_HH */
