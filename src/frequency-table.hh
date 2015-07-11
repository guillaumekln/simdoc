#ifndef FREQUENCY_TABLE_HH
# define FREQUENCY_TABLE_HH

# include <unordered_map>
# include <functional>
# include <ostream>
# include <string>

class FrequencyTable
{
public:
  void update(size_t index);
  void map(std::function<double(size_t, double)> f);
  void iter(std::function<void(size_t, double)> f) const;

  void multiply_by(const FrequencyTable& ft);

  double norm() const;
  double norm(const FrequencyTable& ft) const;
  double dot(const FrequencyTable& ft) const;

  double cosine_similarity(const FrequencyTable& ft) const;

private:
  std::unordered_map<size_t, double> _table;
};

# endif /* !FREQUENCY_TABEL_HH */
