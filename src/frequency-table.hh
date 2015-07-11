#ifndef FREQUENCY_TABLE_HH
# define FREQUENCY_TABLE_HH

# include <unordered_map>
# include <functional>
# include <ostream>
# include <string>

class FrequencyTable
{
public:
  void update(const std::string& word);
  void map(std::function<double(const std::string&, double)> f);
  void iter(std::function<void(const std::string&, double)> f) const;

  void multiply_by(const FrequencyTable& ft);

  double norm() const;
  double norm(const FrequencyTable& ft) const;
  double dot(const FrequencyTable& ft) const;

  double cosine_similarity(const FrequencyTable& ft) const;

  void merge(const FrequencyTable& ft);

private:
  std::unordered_map<std::string, double> _table;
};

# endif /* !FREQUENCY_TABEL_HH */
