#include "frequency-table.hh"

#include <cmath>

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

void FrequencyTable::iter(std::function<void(const std::string&, double)> f) const
{
  for (auto it = _table.cbegin(); it != _table.cend(); ++it)
  {
    f(it->first, it->second);
  }
}

void FrequencyTable::multiply_by(const FrequencyTable& ft)
{
  map([&] (const std::string& word, double freq)
      {
        auto iter = ft._table.find(word);
        if (iter != ft._table.end())
          return freq * iter->second;
        return freq;
      });
}

double FrequencyTable::norm() const
{
  double norm = 0;
  iter([&] (const std::string&, double freq) { norm += freq * freq; });
  return sqrt(norm);
}

double FrequencyTable::norm(const FrequencyTable& ft) const
{
  double norm = 0;
  iter([&] (const std::string& word, double freq)
       {
         auto iter = ft._table.find(word);
         if (iter != ft._table.end())
           norm += freq * freq;
       });
  return sqrt(norm);
}

double FrequencyTable::dot(const FrequencyTable& ft) const
{
  double sum = 0;
  iter([&] (const std::string& word, double freq)
       {
         auto iter = ft._table.find(word);
         if (iter != ft._table.end())
           sum += freq * iter->second;
       });
  return sum;
}

double FrequencyTable::cosine_similarity(const FrequencyTable& ft) const
{
  return dot(ft) / (norm() * ft.norm(*this));
}

void FrequencyTable::merge(const FrequencyTable& ft)
{
  for (auto it = ft._table.cbegin(); it != ft._table.cend(); it++)
  {
    _table[it->first] += it->second;
  }
}
