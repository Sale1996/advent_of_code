#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main()
{
    string input;
    ifstream myfile ("input.txt");

    if(myfile.is_open())
    {
        getline(myfile, input);
    }

    int floor = 0;
    int found_index = -1;

    for(int i = 0; i < input.length(); i++)
    {
        if(input[i] == '(')
            floor++;
        else if (input[i] == ')')
            floor--;
        
        if(floor == -1 && found_index == -1)
            found_index = i + 1;
    }

    cout<<"Final floor is:" << floor << endl;
    cout<<"Index of first arrival at -1 floor: " << found_index << endl; // PART 2 

    return 0;
}
