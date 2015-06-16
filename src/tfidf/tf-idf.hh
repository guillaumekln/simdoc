#ifndef TF_IDF_HH
# define TF_IDF_HH

# include <vector>
# include <string>

# include "document-frequency.hh"
# include "frequency-table.hh"

class TfIdf
{
public:
  void add(const std::string& identifier, const std::string& document);
  void compute_idf();

  void dump(std::ostream& os) const;

private:
  std::vector<DocumentFrequency> _documents;
  FrequencyTable _idf;
};

# endif /* !TF_IDF_HH */
