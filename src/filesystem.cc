#include "filesystem.hh"

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
