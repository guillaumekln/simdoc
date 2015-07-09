#include "tf-idf.hh"

#include <algorithm>
#include <cmath>

#include <tbb/parallel_for.h>
#include <tbb/blocked_range.h>

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

void TfIdf::compute_similarity(std::vector<ResultDocument>& res, size_t max_results) const
{
  res.resize(_documents.size());

  tbb::parallel_for(tbb::blocked_range<size_t>(0, _documents.size()),
                    [&](const tbb::blocked_range<size_t>& r)
                    {
                      for(size_t i = r.begin(); i != r.end(); ++i)
                      {
                        res[i] = ResultDocument(_documents[i].identifier(), _documents.size() - 1);

                        for (const DocumentFrequency& doc2: _documents)
                        {
                          if (_documents[i] == doc2)
                            continue;

                          double score = _documents[i].similarity(doc2);
                          res[i].add_similar_doc(doc2.identifier(), score);
                        }

                        res[i].sort_similar_doc(max_results);
                      }
                    });
}

void TfIdf::dump(std::ostream& os) const
{
  for (const DocumentFrequency& doc: _documents)
  {
    doc.dump(os, _cache);
  }
}
