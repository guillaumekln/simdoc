#ifndef DOCUMENT_FREQUENCY_HH
# define DOCUMENT_FREQUENCY_HH

# include <ostream>
# include <string>

# include "frequency-table.hh"
# include "word-cache.hh"

class DocumentFrequency
{
public:
  DocumentFrequency(const std::string& identifier,
                    const std::string& content,
                    FrequencyTable& idf,
                    WordCache& cache);
  DocumentFrequency(const std::string& identifier,
                    const std::string& content,
                    WordCache& cache);

  void compute_tfidf(const FrequencyTable& idf);
  double similarity(const DocumentFrequency& doc) const;

  const std::string& identifier() const;

  void dump(std::ostream& os, const WordCache& cache) const;

private:
  FrequencyTable _tf;
  std::string _identifier;
  size_t _word_count;
};

# endif /* !DOCUMENT_FREQUENCY_HH */
