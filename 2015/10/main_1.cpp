#include <iostream>
#include <string>
#include <sstream>


std::string look_and_say(std::string s)
{
    int char_counter = 0;
    char last_char = ' ';
    std::stringstream said_string;

    if(s.size() == 1)
    {
        return "1" + s;
    }

    for (char c : s)
    {
        if(last_char == ' ')
        {
            char_counter = 1;
            last_char = c;
        }
        else if(last_char == c)
        {
            char_counter++;
        }
        else
        {
            said_string << char_counter;
            said_string << last_char;
            char_counter = 1;
            last_char = c;
        }
    }

    said_string << char_counter;
    said_string << last_char;

    return said_string.str();
}

int main ()
{
    std::cout << "Enter start digit: ";

    std::string digit = "";
    std::cin >> digit;

    std::string l_n_say = digit;

    for(int counter = 0; counter < 50; counter ++)
    {
        l_n_say = look_and_say(l_n_say); 
        std::cout << "Look and say on counter " << counter << " is " << l_n_say << " ! " << std::endl;
    }

    std::cout << "Final size of string is " << l_n_say.size() << std::endl;

    return 0;
}