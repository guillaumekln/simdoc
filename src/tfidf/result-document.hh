#ifndef RESULT_DOCUMENT_HH
# define RESULT_DOCUMENT_HH

# include <string>
# include <ostream>

class ResultDocument
{
public:
  ResultDocument(const std::string& document, double score);

  bool operator<(const ResultDocument& rd) const;

  friend std::ostream& operator<<(std::ostream& os, const ResultDocument& rd);

private:
  std::string _document;
  double _score;
};

# endif /* !RESULT_DOCUMENT_HH */
