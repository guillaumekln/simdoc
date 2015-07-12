#include "result-document.hh"

#include <algorithm>

ResultDocument::ResultDocument()
{
}

ResultDocument::ResultDocument(const std::string& document, size_t max_size)
  : _document(document)
{
  _similarTo.reserve(max_size);
}

void ResultDocument::add_similar_doc(const std::string& document, double score)
{
  _similarTo.emplace_back(document, score);
}

void ResultDocument::sort_similar_doc(size_t max_results)
{
  std::sort(_similarTo.begin(), _similarTo.end());

  if (max_results < _similarTo.size())
    _similarTo.erase(_similarTo.begin() + max_results, _similarTo.end());
}

bool ResultDocument::operator<(const ResultDocument& rd) const
{
  return _document < rd._document;
}

std::ostream& operator<<(std::ostream& os, const ResultDocument& rd)
{
  os << "{\"file\":\"" << rd._document
     << "\",\"similarTo\":[";

  for (auto it = rd._similarTo.begin(); it != rd._similarTo.end(); it++)
  {
    if (it != rd._similarTo.begin())
      os << ',';
    os << *it;
  }

  os << "]}";
  return os;
}

std::ostream& operator<<(std::ostream& os, const std::vector<ResultDocument>& rds)
{
  os << '[';
  for (auto it = rds.cbegin(); it != rds.cend(); it++)
  {
    if (it != rds.cbegin())
      os << ',';
    os << *it;
  }
  os << ']';

  return os;
}


ResultDocument::SimilarDocument::SimilarDocument(const std::string& document, double score)
  : _document(document)
  , _score(score)
{
}

bool ResultDocument::SimilarDocument::operator<(const SimilarDocument& sd) const
{
  return _score > sd._score || (_score == sd._score && _document < sd._document);
}

std::ostream& operator<<(std::ostream& os, const ResultDocument::SimilarDocument& sd)
{
  os << "{\"score\":" << sd._score
     << ",\"file\":\"" << sd._document << "\"}";
  return os;
}
