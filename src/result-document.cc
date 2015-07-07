#include "result-document.hh"

ResultDocument::ResultDocument(const std::string& document, double score)
  : _document(document)
  , _score(score)
{
}

bool ResultDocument::operator<(const ResultDocument& rd) const
{
  return _score > rd._score || (_score == rd._score && _document < rd._document);
}

std::ostream& operator<<(std::ostream& os, const ResultDocument& rd)
{
  os << "{\"score\":" << rd._score
     << ",\"file\":\"" << rd._document << "\"}";
  return os;
}
