#include <iostream>
#include <fstream>
#include <string>
#include <boost/filesystem.hpp>

char findCommonItem(std::string string1, std::string string2);
char findCommonItemThree(std::string string1, std::string string2, std::string string3);
int getPointsFromItem(char c);

int main(int argc, char const *argv[])
{
    /* Part 1 */ 
    boost::filesystem::path inputPath = boost::filesystem::complete("input.txt");
    std::ifstream inputFile (inputPath.string());
    std::string line;

    int totalPoints = 0;    
    for (int i = 0; std::getline(inputFile, line); i++) 
    {
        int compSize = line.length() / 2;
        std::string firstComp = line.substr(0, compSize);
        std::string secondComp = line.substr(compSize, line.length());

        char commonItem = findCommonItem(firstComp, secondComp);
        totalPoints += getPointsFromItem(commonItem);
    }
    std::cout << "Part 1 total priority points: " << totalPoints << std::endl;


    /* Part 2 */ 
    inputFile.clear();
    inputFile.seekg(0);

    totalPoints = 0;    
    std::string ruck1;
    std::string ruck2;
    std::string ruck3;

    while(std::getline(inputFile, ruck1) && std::getline(inputFile, ruck2) && std::getline(inputFile, ruck3))
    {
        char badge = findCommonItemThree(ruck1, ruck2, ruck3);
        totalPoints += getPointsFromItem(badge);
    }

    std::cout << "Part 2 total priority points: " << totalPoints << std::endl;
}

char findCommonItem(std::string string1, std::string string2) 
{
    // std::cout << string1 << " " << string2 << std::endl;
    for (char& c1 : string1)
    {
        for (char& c2 : string2)
        {
            if (c1 == c2) 
            {
                return c1;
            }
        }
    }
    return '1';
}

char findCommonItemThree(std::string string1, std::string string2, std::string string3) 
{
    for (char& c1 : string1)
    {
        for (char& c2 : string2)
        {
            for (char& c3 : string3)
            {
                if (c1 == c2 && c2 == c3) 
                {
                    return c1;
                }
            }
        }
    }
    return '1';
}


int getPointsFromItem(char c)
{
    if (64 < c && c < 91)
    {
        return c - 38;
    }
    if (96 < c && c < 123)
    {
        return c - 96;
    }
    return -1;
}