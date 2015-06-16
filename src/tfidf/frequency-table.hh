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

  void dump(std::ostream& os) const;

private:
  std::unordered_map<std::string, double> _table;
};

# endif /* !FREQUENCY_TABEL_HH */
