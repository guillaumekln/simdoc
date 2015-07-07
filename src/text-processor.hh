#ifndef TEXT_PROCESSOR_HH
# define TEXT_PROCESSOR_HH

# include <functional>
# include <string>

class TextProcessor
{
public:
  static void parse(const std::string& text,
                    std::function<void(const std::string& word)> onWord);

private:
};

# endif /* !TEXT_PROCESSOR_HH */
