#include <iostream>
#include <string>
#include <regex>

int main()
{
  unsigned short all_chars_summ = 0;
  unsigned short all_chars_encoded_summ = 0;

  for (std::string line; std::getline(std::cin, line);) {

    all_chars_summ += line.size();

    all_chars_encoded_summ += 2; // for the " at the start and at the beggining

    for (auto c : line)
    {
        all_chars_encoded_summ++;

        if ( c == '\"' || c == '\\')
            all_chars_encoded_summ++;

        std::cout << "character is: " << c << std::endl;
    }
    
  }

  std::cout << "Final lenght of strings is: " << all_chars_summ << std::endl;
  std::cout << "Final length of encoded strings: " << all_chars_encoded_summ << std::endl;

  std::cout << "Difference is: " << all_chars_encoded_summ - all_chars_summ << std::endl;

  return 0;
}