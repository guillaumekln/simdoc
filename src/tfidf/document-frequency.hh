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

  void dump(std::ostream& os) const;

private:
  FrequencyTable _tf;
  std::string _identifier;
  size_t _word_count;
};

# endif /* !DOCUMENT_FREQUENCY_HH */
