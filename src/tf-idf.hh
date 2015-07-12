#ifndef TF_IDF_HH
# define TF_IDF_HH

# include <vector>
# include <string>

# include "document-frequency.hh"
# include "frequency-table.hh"
# include "result-document.hh"

class TfIdf
{
public:
  void add(const std::string& identifier, const std::string& document);
  void compute_tfidf();
  void compute_similarity(std::vector<ResultDocument>& res, size_t max_result) const;

  void merge(const TfIdf& tfidf);

private:
  std::vector<DocumentFrequency> _documents;
  FrequencyTable _idf;
};

# endif /* !TF_IDF_HH */
