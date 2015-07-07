#include "tf-idf.hh"

#include <algorithm>
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

std::vector<ResultDocument> TfIdf::ranked_similarity(const std::string& document, size_t max_results)
{
  std::vector<ResultDocument> rank;
  rank.reserve(_documents.size());

  DocumentFrequency docfreq(document, _cache);
  docfreq.compute_tfidf(_idf);

  for (const DocumentFrequency& doc: _documents)
  {
    double d = docfreq.similarity(doc);
    rank.emplace_back(doc.identifier(), d);
  }

  std::sort(rank.begin(), rank.end());

  if (max_results < rank.size())
    rank.erase(rank.begin() + max_results, rank.end());

  return rank;
}

void TfIdf::dump(std::ostream& os) const
{
  for (const DocumentFrequency& doc: _documents)
  {
    doc.dump(os, _cache);
  }
}
