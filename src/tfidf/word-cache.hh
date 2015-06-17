#ifndef WORD_CACHE_HH
# define WORD_CACHE_HH

# include <boost/bimap.hpp>
# include <string>

class WordCache
{
public:
  size_t add(const std::string& word);
  const std::string& get(size_t id) const;

private:
  boost::bimap<size_t, std::string> _cache;
};

# endif /* !WORD_CACHE_HH */
