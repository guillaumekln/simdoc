#include "document-frequency.hh"

#include "text-processor.hh"

DocumentFrequency::DocumentFrequency(const std::string& identifier,
                                     const std::string& content,
                                     FrequencyTable& idf)
  : _identifier(identifier)
  , _word_count(0)
{
  // Process content.
  TextProcessor::parse(content,
                       [&] (const std::string& word)
                       {
                         _tf.update(word);
                         _word_count++;
                       });

  // Normalize frequencies and increment word appearance in dataset.
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
