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
