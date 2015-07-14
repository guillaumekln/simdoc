#include "data-source.hh"

void DataSource::safe_merge(TfIdf& main, const TfIdf& aux)
{
  std::lock_guard<std::mutex> lock(_mutex);
  main.merge(aux);
}
