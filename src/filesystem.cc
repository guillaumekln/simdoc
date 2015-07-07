#include "filesystem.hh"

#include <iostream>
#include <stdexcept>
#include <fstream>

Filesystem::Filesystem(const std::string& directory, bool recursive)
  : _directory(directory)
  , _recursive(recursive)
{
  if (!boost::filesystem::exists(_directory))
  {
    throw std::invalid_argument(directory + " directory does not exist");
  }
}

void Filesystem::fetch_rec(const boost::filesystem::path& dir, TfIdf& tfidf)
{
  boost::filesystem::directory_iterator end_it;

  for (boost::filesystem::directory_iterator it(dir); it != end_it; ++it)
  {
    if (_recursive && boost::filesystem::is_directory(it->status()))
    {
      fetch_rec(it->path(), tfidf);
    }
    else if (boost::filesystem::is_regular_file(it->status()))
    {
      std::string path = it->path().native();
      std::string filename = it->path().filename().native();

      std::ifstream ifs(path);
      std::string content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
      tfidf.add(filename, content);
    }
  }
}

void Filesystem::fetch(TfIdf& tfidf)
{
  fetch_rec(_directory, tfidf);
}
