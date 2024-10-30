#include <iostream>
#include <map>
#include <set>
#include <string>
#include <regex>
#include <cassert>

struct Reindeer
{
    Reindeer(std::string s)
    {
        
        const char *re = "(\\w+) can fly (\\w+) km/s for (\\w+) seconds, but then must rest for (\\w+) seconds.";
        std::smatch m;

        if (!std::regex_search(s, m, std::regex(re))) {
            std::cerr << "Unable to interpret:" << s << "\n";
            assert(false);
        }

        _name = m.str(1);
        _speed = std::stoul(m.str(2));
        _fly_seconds = std::stoul(m.str(3));
        _rest_seconds = std::stoul(m.str(4));
    }

    std::string _name;
    unsigned short _speed;
    unsigned short _fly_seconds;
    unsigned short _rest_seconds;
};

int main () 
{
    std::vector<Reindeer> reindeers; 
    std::map<std::string, int> reindeer_distance;
    std::map<std::string, int> reindeer_points;

    for (std::string line; std::getline(std::cin, line);) {
        Reindeer reindeer(line);

        reindeers.push_back(reindeer); 
        reindeer_points[reindeer._name] = 0;
        reindeer_distance[reindeer._name] = 0;
    };

    int race_time = 2503;

    for (int i = 0; i < race_time; i++)
    {
        std::vector<Reindeer> winningReindeers;

        for (Reindeer reindeer : reindeers)
        {
            int current_interval_time = i % (reindeer._fly_seconds + reindeer._rest_seconds);
            bool is_flying_second = (current_interval_time < reindeer._fly_seconds) ? true : false;
            int passed_distance = is_flying_second ? reindeer._speed : 0;

            reindeer_distance[reindeer._name] += passed_distance;

            if(winningReindeers.empty())
            {
                winningReindeers.push_back(reindeer);
            }
            else if(reindeer_distance[reindeer._name] > reindeer_distance[winningReindeers.at(0)._name])
            {
                winningReindeers.clear();
                winningReindeers.push_back(reindeer);
            }
            else if(reindeer_distance[reindeer._name] == reindeer_distance[winningReindeers.at(0)._name])
            {
                winningReindeers.push_back(reindeer);
            }
        }

        if(winningReindeers.empty())
        {
            // Not single reindeer changed distance in meantime
            for (auto points : reindeer_points)
            {
                points.second = points.second + 1;
            }
        }
        else
        {
            for(Reindeer reindeer: winningReindeers)
            {
                reindeer_points[reindeer._name] += 1;
            }
        }

        winningReindeers.clear();
    }

    int maximum_points = 0;

    for (auto points : reindeer_points)
    {
        std::cout << "Reindeer [" << points.first << "] has points: " << points.second << std::endl; 
        if(points.second > maximum_points)
            maximum_points = points.second;
    }

    std::cout << "\nMaximum points is: " << maximum_points << std::endl;

    return 0;
}