#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

int main()
{
    string input;
    ifstream myfile ("input.txt");

    if(myfile.is_open())
    {
        getline(myfile, input);
    }

    int santa_y_axis = 0;
    int santa_x_axis = 0;

    int robo_santa_y_axis = 0;
    int robo_santa_x_axis = 0;

    map<string,int> houses;

    houses[to_string(santa_y_axis) + "_" + to_string(santa_x_axis)] = 1; //first house

    for (int i = 0; i < input.length(); i++)
    {
        if (input[i] == '^')
            i % 2 == 0 ? santa_y_axis++ : robo_santa_y_axis++;
        else if (input[i] == 'v')
            i % 2 == 0 ? santa_y_axis-- : robo_santa_y_axis--;
        else if (input[i] == '>')
            i % 2 == 0 ? santa_x_axis++ : robo_santa_x_axis++;
        else if (input[i] == '<')
            i % 2 == 0 ? santa_x_axis-- : robo_santa_x_axis--;

        string house_cord = "";

        if (i % 2 == 0)        
            house_cord = (to_string(santa_y_axis) + "_" + to_string(santa_x_axis));
        else
            house_cord = (to_string(robo_santa_y_axis) + "_" + to_string(robo_santa_x_axis));

        cout << "House cord " << house_cord << endl;

        if (houses.find(house_cord) == houses.end())
        {
            houses[house_cord] = 1;
            cout << "Inserting into map " << house_cord << endl;
        }
        else
        {
            houses[house_cord] = houses[house_cord] + 1;
            cout << "Appending into map " << house_cord << endl;
        }
    }

    cout << "Number of houses with at least one gift is: " << houses.size() << endl;

    return 0;
}
