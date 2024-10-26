#include <iostream>
#include <string>


std::string return_new_password(const std::string& old_password)
{
    std::string password = old_password;
    
    while (true)
    {
        // Reseting requirement booleans
        bool first_requirement = false;
        bool third_requirement = false;
        
        // Dealing with second requirement
        bool found_confusing_letter = false;

        for(std::string::size_type i = 0; i < password.size(); ++i)
        {
            if (found_confusing_letter)
            {
                password[i] = 'a';
            }     
            else if (password[i] == 'i' || password[i] == 'o' || password[i] == 'l' )
            {
                password[i] = password[i] + 1;
                found_confusing_letter = true;
            }
        }

        // Checking requirements
        int number_of_pairs = 0;
        char first_pair_letter = ' ';

        for(std::string::size_type i = 0; i < password.size(); ++i)
        {
            // Checking first requirement
            if (i < password.size() - 2 && first_requirement == false)
            {
                if ((password[i]+1) == password[i+1] && (password[i]+2) == password[i+2])
                {
                    first_requirement = true;
                }
            }
            
            // Checking third requirement
            if (number_of_pairs >= 2)
            {
                third_requirement = true;
            }
            else if (password[i] == password[i+1] && password[i] != first_pair_letter && third_requirement == false)
            {
                number_of_pairs++;
                first_pair_letter = password[i];
            }

        }

        if(first_requirement && third_requirement && password != old_password)
            return password;

        // Requirements are not met. Increment password.
        for(std::string::size_type i = password.size() - 1; i >= 0; i--)
        {
            if(password[i] == 'z')
            {
                password[i] = 'a';
            }
            else
            {
                password[i] = password[i] + 1;
                break;
            }
        }
    }
}

int main () 
{
    std::string input_password;

    std::cout << "Insert old password: ";
    std::cin >> input_password;

    std::string new_pass = return_new_password(input_password);

    std::cout << std::endl << "New string is: " << new_pass << std::endl;

    return 0;
}