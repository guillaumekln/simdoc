#include "tf-idf.hh"

#include <cmath>

void TfIdf::add(const std::string& identifier, const std::string& document)
{
  _documents.emplace_back(identifier, document, _idf, _cache);
}

void TfIdf::compute_tfidf()
{
  _idf.map([&] (size_t, double freq) { return 1 + log(_documents.size() / freq); });

  for (DocumentFrequency& doc: _documents)
  {
    doc.compute_tfidf(_idf);
  }
}

void TfIdf::dump(std::ostream& os) const
{
  for (const DocumentFrequency& doc: _documents)
  {
    doc.dump(os, _cache);
  }
}
