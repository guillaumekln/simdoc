#include "frequency-table.hh"

void FrequencyTable::update(const std::string& word)
{
  _table[word]++;
}

void FrequencyTable::map(std::function<double(const std::string&, double)> f)
{
  for (auto it = _table.begin(); it != _table.end(); ++it)
  {
    it->second = f(it->first, it->second);
  }
}

void FrequencyTable::dump(std::ostream& os) const
{
  for (auto it = _table.cbegin(); it != _table.cend(); ++it)
  {
    os << it->first << ": " << it->second << std::endl;
  }
}
