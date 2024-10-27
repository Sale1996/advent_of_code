#include <iostream>
#include <map>
#include <set>
#include <string>
#include <regex>
#include <cassert>

struct Sitting
{
    Sitting(std::string s)
    {
        const char *re = "(\\w+) would (\\w+) (\\w+) happiness units by sitting next to (\\w+).";
        std::smatch m;

        if (!std::regex_search(s, m, std::regex(re))) {
            std::cerr << "Unable to interpret:" << s << "\n";
            assert(false);
        }

        _person1 = m.str(1);
        _gain = (m.str(2) == "gain") ? true : false;
        _happines_unit = std::stoul(m.str(3));
        _person2 = m.str(4);
    }

    std::string _person1;
    std::string _person2;
    unsigned short _happines_unit;
    bool _gain;
};

int calculate_max_happines(std::set<std::string> in_persons, const std::map<std::string, int>& persons_happines)
{
        int max_score = 0;
        std::vector<std::string> persons (in_persons.begin(), in_persons.end());
        std::sort(persons.begin(), persons.end());

        do 
        {
            int current_score = 0;
            std::cout << "\r" << persons[0];
            
            for (std::size_t i = 1; i < persons.size(); ++i) {
                std::cout << " <- " << persons[i] << std::flush;
                current_score += persons_happines.at(persons[i-1] + "," + persons[i]);
            }

            // final one
            current_score += persons_happines.at(persons[0] + "," + persons[persons.size()-1]);

            if (current_score > max_score) 
            {
                max_score = current_score;
            }

        } while (std::next_permutation(persons.begin(), persons.end()));

        std::cout << "\n";

        return max_score;
}

int main () 
{
    std::set<std::string> persons; 
    std::map<std::string, int> persons_happines;

    for (std::string line; std::getline(std::cin, line);) {
        Sitting sitting(line);

        persons.insert(sitting._person1);
        persons.insert(sitting._person2);

        std::string comb1 = sitting._person1 + "," + sitting._person2;
        std::string comb2 = sitting._person2 + "," + sitting._person1;

        if(persons_happines.find(comb1) != persons_happines.end())
        {
            persons_happines[comb1] += sitting._gain ? sitting._happines_unit : (-1)*sitting._happines_unit;
            persons_happines[comb2] += sitting._gain ? sitting._happines_unit : (-1)*sitting._happines_unit;
        }
        else
        {
            persons_happines[comb1] = sitting._gain ? sitting._happines_unit : (-1)*sitting._happines_unit;
            persons_happines[comb2] = sitting._gain ? sitting._happines_unit : (-1)*sitting._happines_unit;
        }         
    }

    std::string host_person = "Host";

    // Addition of one extra person
    for(std::string person : persons)
    {
        persons_happines[person + "," + host_person] = 0;
        persons_happines[host_person + "," + person] = 0;
    }

    persons.insert(host_person);

    int max_happines = calculate_max_happines(persons, persons_happines);

    std::cout << "Maximum happines is: " << max_happines << std::endl;

    return 0;
}