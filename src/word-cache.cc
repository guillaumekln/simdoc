#include "word-cache.hh"

#include <stdexcept>

WordCache& WordCache::get_instance()
{
  static WordCache cache;
  return cache;
}

size_t WordCache::add(const std::string& word)
{
  std::lock_guard<std::mutex> lock(_mutex);
  auto right_iter = _cache.right.find(word);

  if (right_iter == _cache.right.end())
  {
    size_t id = _cache.size();
    _cache.right.insert(boost::bimap<size_t, std::string>::right_value_type(word, id));
    return id;
  }
  else
  {
    return right_iter->second;
  }
}

const std::string& WordCache::get(size_t id) const
{
  auto left_iter = _cache.left.find(id);

  if (left_iter == _cache.left.end())
    throw std::invalid_argument("id does not exist");

  return left_iter->second;
}
