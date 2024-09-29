#include<iostream>
#include<map>
#include<string>
#include <algorithm>
#include <set>
#include <sstream>


const std::string TURN_ON {"turn on"};
const std::string TURN_OFF {"turn off"};
const std::string TOGGLE {"toggle"};

struct MapCommand
{
    MapCommand(std::string const &s) noexcept 
    {
        std::size_t position1 = 0;
        std::size_t position2 = 0;

        /*
            EXTRACT COMMAND
        */
        if (s.find(TURN_ON) != std::string::npos)
        {
            command = TURN_ON;
            position1 += TURN_ON.size();
        }
        else if (s.find(TURN_OFF) != std::string::npos)
        {
            command = TURN_OFF;
            position1 += TURN_OFF.size();
        }
        else
        {
            command = TOGGLE;
            position1 += TOGGLE.size();
        }
        std::cout<< "Command is" << command << std::endl;


        /*
            EXTRACT NUMBERS
        */

        position1++; //first space
        auto s2 = s.substr(position1);
        position1 = 0;
        std::cout<< "s2 is" << s2 << std::endl;

        //start_cell_x
        position2 = s2.find(',');
        auto start_cell_x_str = s2.substr(position1, (position2 - position1));
        std::cout<< "start_cell_x is" << start_cell_x_str << std::endl;
        start_cell_x = std::stoul(start_cell_x_str);

        // start_cell_y
        position1 = position2 + 1; //moved
        position2 = s2.find(' ');
        auto start_cell_y_str = s2.substr(position1, (position2 - position1));
        std::cout<< "start_cell_y is" << start_cell_y_str << std::endl;
        start_cell_y = std::stoul(start_cell_y_str);

        //move to the second number
        position1 = position2 + 1; // second space
        s2 = s2.substr(position1);
        position1 = s2.find(' ') + 1; //plus space

        //end_cell_x
        position2 = s2.find(',');
        auto end_cell_x_str = s2.substr(position1, (position2 - position1));
        std::cout<< "end_cell_x is" << end_cell_x_str << std::endl;
        end_cell_x = std::stoul(end_cell_x_str);

        // end_cell_y
        position2++;
        s2 = s2.substr(position2);
        std::cout<< "end_cell_y is" << s2 << std::endl;
        end_cell_y = std::stoul(s2);
    }
    
    std::string command;
    unsigned long start_cell_x;
    unsigned long start_cell_y;
    unsigned long end_cell_x;
    unsigned long end_cell_y;
};

int main()
{
    std::set<std::string> turned_on;
    for (std::string line; std::getline(std::cin, line);) {
        MapCommand command(line);

        for (int i = command.start_cell_x; i <= command.end_cell_x; i++)
        {
            for (int j = command.start_cell_y; j <= command.end_cell_y; j++)
            {
                std::stringstream sstr;
                sstr << "x" << i << "y" << j;

                std::string s = sstr.str();

                if (command.command == TURN_ON)
                    turned_on.insert(s);
                else if (command.command == TURN_OFF)
                    turned_on.erase(s);
                else if (command.command == TOGGLE)
                {
                    if (turned_on.find(s) != turned_on.end())
                        turned_on.erase(s); //TURN OFF
                    else
                        turned_on.insert(s); // TURN ON
                }
            }
        }

        
    }

    std::cout << "Number of turned on lights: " << turned_on.size() << std::endl;

    return 0;
}