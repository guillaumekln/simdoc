#ifndef RESULT_DOCUMENT_HH
# define RESULT_DOCUMENT_HH

# include <string>
# include <vector>
# include <ostream>

class ResultDocument
{
public:
  class SimilarDocument
  {
  public:
    SimilarDocument(const std::string& document, double score);
    bool operator<(const SimilarDocument& rd) const;
    friend std::ostream& operator<<(std::ostream& os, const SimilarDocument& rd);

  private:
    std::string _document;
    double _score;
  };

  ResultDocument();
  ResultDocument(const std::string& document, size_t max_size);

  void add_similar_doc(const std::string& document, double score);
  void sort_similar_doc(size_t max_results);

  bool operator<(const ResultDocument& rd) const;
  friend std::ostream& operator<<(std::ostream& os, const ResultDocument& rd);

private:
  std::string _document;
  std::vector<SimilarDocument> _similarTo;
};

# endif /* !RESULT_DOCUMENT_HH */
