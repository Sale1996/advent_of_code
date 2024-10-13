#include <iostream>
#include <string>
#include <regex>

int main()
{
  unsigned short all_chars_summ = 0;
  unsigned short with_escaped_ch_summ = 0;

  for (std::string line; std::getline(std::cin, line);) {

    all_chars_summ += line.size();

    std::string matcher = "";

    for (auto c : line.substr(1, line.size()-2))
    {
        with_escaped_ch_summ++;
        matcher += c;

        if(matcher.size() == 2)
        {
            if(matcher == "\\x")
            {
                continue;
            }
            else if(matcher == "\\\\" || matcher == "\\\"")
            {
                with_escaped_ch_summ -= 1; //Since "\\" escaped is "\"
                matcher = "";
            }
            else
            {
                matcher = c;
            }
        }

        if(matcher.size() == 4)
        {
            const char *re = "^(.{2})([0-9a-fA-F]{2})$";
            
            std::smatch m;

            if (std::regex_search(matcher, m, std::regex(re))) 
            {
                with_escaped_ch_summ -= 3;
            }

            matcher = c;
        }

    }
  }

  std::cout << "Final lenght of strings is: " << all_chars_summ << std::endl;
  std::cout << "Final length of escaped strings: " << with_escaped_ch_summ << std::endl;

  std::cout << "Difference is: " << all_chars_summ - with_escaped_ch_summ << std::endl;

  return 0;
}