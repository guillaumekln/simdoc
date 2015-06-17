#include "frequency-table.hh"

void FrequencyTable::update(size_t index)
{
  _table[index]++;
}

void FrequencyTable::map(std::function<double(size_t, double)> f)
{
  for (auto it = _table.begin(); it != _table.end(); ++it)
  {
    it->second = f(it->first, it->second);
  }
}

void FrequencyTable::iter(std::function<void(size_t, double)> f) const
{
  for (auto it = _table.cbegin(); it != _table.cend(); ++it)
  {
    f(it->first, it->second);
  }
}

void FrequencyTable::dump(std::ostream& os) const
{
  iter([&] (size_t id, double freq) { os << id << ": " << freq << std::endl; });
}
