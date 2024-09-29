#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <map>

struct StringLetter
{
    StringLetter(std::string const &s) : letter_(s) {}

    bool isNice()
    {
        bool containsPairOfTwoLetters = false;
        bool containsLetterBetween = false;
        std::map<std::string,int> allLetterSyllables;

        char syllable[] = {letter_.at(0),letter_.at(0), '\0'};

        std::cout << "Letter is " << letter_ << std::endl;

        for(unsigned int i = 0; i < letter_.size(); i++)
        {
            char currentChar = letter_.at(i);

            syllable[0] = syllable[1]; //last char
            syllable[1] = currentChar;

            if( i > 0 )
            {
                if(allLetterSyllables.find(std::string(syllable)) == allLetterSyllables.end())
                {
                    std::cout << "Saving syllable: " << syllable << std::endl;
                    allLetterSyllables[std::string(syllable)] = i; //saving second location number in order to prevent saving two syllabels with sharing letter
                }
                else
                {
                    /*
                    It contains a pair of any two letters that appears at least twice in the string without overlapping,
                     like xyxy (xy) or aabcdefgaa (aa), 
                     ****but not like aaa (aa, but it overlaps).****
                    */
                    if(allLetterSyllables.at(std::string(syllable)) != (i-1))
                    {
                        std::cout << "It contains two letters already in map ! " << std::endl;
                        containsPairOfTwoLetters = true;
                    }
                }

                if(i > 1)
                {
                    if(letter_.at(i-2) == currentChar)
                    {
                        std::cout << "Is containing two letters" << letter_.substr(i-2, 3) << std::endl;

                        containsLetterBetween = true;
                    }
                }
            }     
        }
        
        return containsPairOfTwoLetters && containsLetterBetween;
    }

    std::string letter_;
};

int main()
{
    int niceStrNm = 0;
    int count_words = 0;

    std::string input;
    std::ifstream myfile("ulaz.txt");

    std::cout<<"Starting app" << std::endl;
    if(myfile.is_open())
    {
        while(std::getline(myfile, input))
        {
            StringLetter s(input);
            if(s.isNice()) niceStrNm++;
            std::cout << "Passed test on " << input << std::endl;
            count_words++;
        }

        std::cout<< "Number of nice strings is: " << niceStrNm << std::endl;
        std::cout<< "And number of all words here are: " << count_words << std::endl;
    }
    else
    {
        std::cout << "File is not open" << std::endl;
    }

    return 0;
};