#include "text-processor.hh"

#include <stemming/english_stem.h>
#include <boost/tokenizer.hpp>
#include <algorithm>

void TextProcessor::parse(const std::string& text,
                          std::function<void(const std::string& word)> onWord)
{
  boost::tokenizer<> tokens(text);
  stemming::english_stem<> StemEnglish;

  for (auto it = tokens.begin(); it != tokens.end(); ++it)
  {
    std::string word(*it);
    std::transform(word.begin(), word.end(), word.begin(), ::tolower);

    // Temporary wstring.
    std::wstring wword(word.begin(), word.end());
    StemEnglish(wword);
    word = std::string(wword.begin(), wword.end());

    onWord(word);
  }
}
