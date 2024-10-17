#include <iostream>
#include <map>
#include <set>
#include <string>
#include <regex>
#include <cassert>

struct Route
{
    Route(std::string s)
    {
        const char *re = "(\\w+)\\sto\\s(\\w+)\\s=\\s(\\w+)";
        std::smatch m;

        if (!std::regex_search(s, m, std::regex(re))) {
            std::cerr << "Unable to interpret:" << s << "\n";
            assert(false);
        }

        _city1 = m.str(1);
        _city2 = m.str(2);
        _distance = std::stoul(m.str(3));
    }

    std::string _city1;
    std::string _city2;
    unsigned short _distance;
};

int calculate_max_distance(std::string root_city, std::set<std::string> cities, const std::map<std::string, int>& distances)
{
    if(cities.size() == 2)
    {
        auto it = cities.begin();

        std::string city1 = *it;
        std::string city2 = *(++it);

        return distances.at(city1 + "," + city2);
    }
    else
    {
        cities.erase(root_city);
        int minimal_distance = -1;

        for (std::string city : cities)
        {            
            int distance = distances.at(root_city + "," + city) + calculate_max_distance(city, cities, distances);

            if(minimal_distance == -1 || distance > minimal_distance)
                minimal_distance = distance;
        }

        return minimal_distance;
    }
}

int main () 
{
    std::set<std::string> cities; 
    std::map<std::string, int> distances;

    for (std::string line; std::getline(std::cin, line);) {
        Route route(line);

        cities.insert(route._city1);
        cities.insert(route._city2);

        distances[route._city1 + "," + route._city2] = route._distance;
        distances[route._city2 + "," + route._city1] = route._distance;     
    }

    int minimal_distance = -1;

    for (std::string city : cities)
    {
        int distance = calculate_max_distance(city, cities, distances);

        if (minimal_distance == -1 || distance > minimal_distance)
            minimal_distance = distance;
    }

    std::cout << "Maximal  distance is s [" << minimal_distance << "]" << std::endl;

    return 0;
}