#ifndef DATA_SOURCE_HH
# define DATA_SOURCE_HH

# include <mutex>

# include "tf-idf.hh"

class DataSource
{
public:
  virtual void fetch(TfIdf& tfidf) = 0;

protected:
  void safe_merge(TfIdf& main, const TfIdf& aux);

private:
  std::mutex _mutex;
};

# endif /* !DATA_SOURCE_HH */
