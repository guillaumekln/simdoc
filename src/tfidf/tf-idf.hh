#ifndef TF_IDF_HH
# define TF_IDF_HH

# include <vector>
# include <string>

# include "document-frequency.hh"
# include "frequency-table.hh"
# include "result-document.hh"
# include "word-cache.hh"

class TfIdf
{
public:
  void add(const std::string& identifier, const std::string& document);
  void compute_tfidf();

  std::vector<ResultDocument> ranked_similarity(const std::string& document, size_t max_result);

  void dump(std::ostream& os) const;

private:
  std::vector<DocumentFrequency> _documents;
  WordCache _cache;
  FrequencyTable _idf;
};

# endif /* !TF_IDF_HH */
