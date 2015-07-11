#include "document-frequency.hh"

#include "text-processor.hh"
#include "word-cache.hh"

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
                         size_t id = WordCache::get_instance().add(word);
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

double DocumentFrequency::similarity(const DocumentFrequency& doc) const
{
  return _tf.cosine_similarity(doc._tf);
}

const std::string& DocumentFrequency::identifier() const
{
  return _identifier;
}

bool DocumentFrequency::operator==(const DocumentFrequency& doc) const
{
  return _identifier == doc._identifier;
}

bool DocumentFrequency::operator!=(const DocumentFrequency& doc) const
{
  return !(*this == doc);
}
