#include "document-frequency.hh"

#include <boost/tokenizer.hpp>
#include <algorithm>

DocumentFrequency::DocumentFrequency(const std::string& identifier,
                                     const std::string& content,
                                     FrequencyTable& idf)
  : _identifier(identifier)
  , _word_count(0)
{
  boost::tokenizer<> tokens(content);

  for (auto it = tokens.begin(); it != tokens.end(); ++it)
  {
    std::string word(*it);
    std::transform(word.begin(), word.end(), word.begin(), ::tolower);
    _tf.update(word);
    _word_count++;
  }

  _tf.map([&] (const std::string& word, double freq)
          {
            idf.update(word);
            return freq / _word_count;
          });
}

void DocumentFrequency::dump(std::ostream& os) const
{
  os << _identifier << std::endl;
  _tf.dump(os);
  os << std::endl;
}
