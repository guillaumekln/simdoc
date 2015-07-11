#ifndef DOCUMENT_FREQUENCY_HH
# define DOCUMENT_FREQUENCY_HH

# include <ostream>
# include <string>

# include "frequency-table.hh"

class DocumentFrequency
{
public:
  DocumentFrequency(const std::string& identifier,
                    const std::string& content,
                    FrequencyTable& idf);

  void compute_tfidf(const FrequencyTable& idf);
  double similarity(const DocumentFrequency& doc) const;

  const std::string& identifier() const;

  bool operator==(const DocumentFrequency& doc) const;
  bool operator!=(const DocumentFrequency& doc) const;

private:
  FrequencyTable _tf;
  std::string _identifier;
  size_t _word_count;
};

# endif /* !DOCUMENT_FREQUENCY_HH */
