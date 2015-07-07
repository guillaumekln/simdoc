#ifndef DATA_SOURCE_HH
# define DATA_SOURCE_HH

# include "tf-idf.hh"

class DataSource
{
public:
  virtual void fetch(TfIdf& tfidf) = 0;
};

# endif /* !DATA_SOURCE_HH */
