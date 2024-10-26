#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <map>

#define NOT_SET -1
#define OBJECT true
#define ARRAY false

int calculate_sum(const std::string& s)
{
    std::stringstream found_number("");
    bool negative_number = false;
    
    // Addition.
    std::map<int, int> object_lvl_sum;
    std::map<int, bool> object_lvl_type;
    int current_lvl = -1;
    int red_keyword_lvl = NOT_SET;

    for(std::string::size_type i = 0; i < s.size(); i++)
    {
        // Handle begin of object/array
        if(s[i] == '{' || s[i] == '[')
        {
            current_lvl++;
            object_lvl_sum[current_lvl] = 0;

            if (s[i] == '{') 
                object_lvl_type[current_lvl] = OBJECT;
            else
                object_lvl_type[current_lvl] = ARRAY;
        }

        // Handle "red" keyword
        if(s[i] == 'r' && i < (s.size() - 2) && object_lvl_type[current_lvl] == OBJECT)
        {
            if(s[i+1] == 'e' && s[i+2] == 'd' && red_keyword_lvl == NOT_SET)
            {
                red_keyword_lvl = current_lvl;
            }
        }
        else if(s[i] >= '0' && s[i] <= '9')
        {
            found_number << s[i];
        }
        else if(found_number.str().size() != 0)
        {
            if (negative_number)
              object_lvl_sum[current_lvl] = object_lvl_sum[current_lvl] - std::stoi(found_number.str());
            else
              object_lvl_sum[current_lvl] = object_lvl_sum[current_lvl] + std::stoi(found_number.str());

            negative_number = false;
            found_number.str("");
        }
        else if(s[i] == '-' && i < (s.size() - 1))
        {
            if (s[i+1] >= '0' && s[i+1] <= '9')
            {
                negative_number = true;
            }
        }

        // Handle end of object/array
        if(s[i] == '}' || s[i] == ']')
        {
            if(red_keyword_lvl == NOT_SET)
            {
                if (current_lvl > 0)
                {
                    // Add summ to parent object/array sum
                    object_lvl_sum[current_lvl - 1] = object_lvl_sum[current_lvl - 1] + object_lvl_sum[current_lvl];
                    object_lvl_sum[current_lvl] = 0;      
                }        
            }
            else if(current_lvl >= red_keyword_lvl && red_keyword_lvl != NOT_SET)
            {
                object_lvl_sum[current_lvl] = 0;

                if(current_lvl == red_keyword_lvl)
                    red_keyword_lvl = NOT_SET;
            }

            object_lvl_type[current_lvl] = false; // Default value
            current_lvl--;
        }
    }

    return object_lvl_sum[0];
}

int main ()
{
    std::string input;
    std::ifstream myfile ("input.txt", std::ios::in);

    if(myfile.is_open())
    {
      getline(myfile, input);
    }

    int sum = calculate_sum(input);

    std::cout << "Sum is: " << sum << std::endl;
    
    return 0;
}