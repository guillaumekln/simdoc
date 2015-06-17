#include "document-frequency.hh"

#include "text-processor.hh"

DocumentFrequency::DocumentFrequency(const std::string& identifier,
                                     const std::string& content,
                                     FrequencyTable& idf,
                                     WordCache& cache)
  : _identifier(identifier)
  , _word_count(0)
{
  // Process content.
  TextProcessor::parse(content,
                       [&] (const std::string& word)
                       {
                         size_t id = cache.add(word);
                         _tf.update(id);
                         _word_count++;
                       });

  // Normalize frequencies and increment word appearance in dataset.
  _tf.map([&] (size_t index, double freq)
          {
            idf.update(index);
            return freq / _word_count;
          });
}

void DocumentFrequency::compute_tfidf(const FrequencyTable& idf)
{
  _tf.multiply_by(idf);
}

void DocumentFrequency::dump(std::ostream& os, const WordCache& cache) const
{
  os << _identifier << std::endl;
  _tf.dump(os, cache);
  os << std::endl;
}
