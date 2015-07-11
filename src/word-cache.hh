#ifndef WORD_CACHE_HH
# define WORD_CACHE_HH

# include <boost/bimap.hpp>
# include <string>
# include <mutex>

class WordCache
{
public:
  static WordCache& get_instance();

  size_t add(const std::string& word);
  const std::string& get(size_t id) const;

private:
  WordCache() {};
  WordCache(const WordCache&) = delete;
  void operator=(const WordCache&) = delete;

  std::mutex _mutex;
  boost::bimap<size_t, std::string> _cache;
};

# endif /* !WORD_CACHE_HH */
