#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> splitString(string str, char splitter)
{
    vector<int> result;
    string current = "";

    for (int i = 0; i < str.size(); i++)
    {
        if(str[i] == splitter)
        {
            if(current != "")
            {
                result.push_back(stoi(current));
                current = "";
            }

            continue;
        }

        current += str[i];
    }

    if (current.size() != 0)
        result.push_back(stoi(current));

    return result;
}


int main ()
{
    string input;
    ifstream myfile ("input.txt");

    int finalPaperArea = 0;
    int finalRibbonArea = 0;

    if (myfile.is_open())
    {
        while(getline(myfile, input))
        {
            vector<int> dimensions = splitString(input, 'x');
            sort(dimensions.begin(), dimensions.end());

            int paperArea = 2*(dimensions[0]*dimensions[1] + dimensions[1]*dimensions[2] + dimensions[0]*dimensions[2]) + dimensions[0]*dimensions[1];

            finalPaperArea += paperArea;

            //calculate Ribbon
            finalRibbonArea += (2*dimensions[0] + 2*dimensions[1]) + (dimensions[0]*dimensions[1]*dimensions[2]);
        }
    }

    cout << "Final paper area is " << finalPaperArea << endl;
    cout << "Final ribbon area is " << finalRibbonArea << endl; //PART 2

    return 0;
}