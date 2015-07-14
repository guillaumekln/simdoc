#ifndef FILESYSTEM_HH
# define FILESYSTEM_HH

# include "files-list.hh"

class Filesystem: public FilesList
{
public:
  Filesystem(const std::string& directory, bool recursive = false);

private:
  void fetch_files(const boost::filesystem::path& dir, bool recursive);
};

# endif /* !FILESYSTEM_HH */
