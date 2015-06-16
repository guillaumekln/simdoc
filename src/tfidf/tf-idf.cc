#include "tf-idf.hh"

#include <cmath>

void TfIdf::add(const std::string& identifier, const std::string& document)
{
  _documents.emplace_back(identifier, document, _idf);
}

void TfIdf::compute_idf()
{
  _idf.map([&] (const std::string&, double freq) { return 1 + log(_documents.size() / freq); });
}

void TfIdf::dump(std::ostream& os) const
{
  for (const DocumentFrequency& doc: _documents)
  {
    doc.dump(os);
  }

  os << "Inverse Document Frequencies:" << std::endl;
  _idf.dump(os);
}
