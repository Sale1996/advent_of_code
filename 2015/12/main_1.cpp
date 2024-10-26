#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

int calculate_sum(const std::string& s)
{
    int sum = 0;

    std::stringstream found_number("");
    bool negative_number = false;

    for(std::string::size_type i = 0; i < s.size(); i++)
    {
        if(s[i] >= '0' && s[i] <= '9')
        {
            found_number << s[i];
        }
        else if(found_number.str().size() != 0)
        {
            if (negative_number)
              sum = sum - std::stoi(found_number.str());
            else
              sum = sum + std::stoi(found_number.str());

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
    }

    return sum;
}

int main ()
{
    int sum = 0; 

    std::string input;
    std::ifstream myfile ("input.txt", std::ios::in);

    if(myfile.is_open())
    {
      getline(myfile, input);
    }

    sum += calculate_sum(input);

    std::cout << "Sum is: " << sum << std::endl;
    
    return 0;
}