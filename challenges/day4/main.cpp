#include <iostream>
#include <fstream>
#include <string>
#include <boost/filesystem.hpp>

std::vector<std::string> splitString(std::string inputString, char delimiter);

int main(int argc, char const *argv[])
{
    /* Part 1 */ 
    boost::filesystem::path inputPath = boost::filesystem::complete("input.txt");
    std::ifstream inputFile (inputPath.string());
    std::string line;

    int fullContainments = 0;
    int overlaps = 0;

    while (std::getline(inputFile, line))
    {
        std::vector<std::string> assignments = splitString(line, ',');
        // std::cout << assignments[0] << " " << assignments[1] << std::endl;

        std::vector<std::string> sections1 = splitString(assignments[0], '-');
        std::vector<std::string> sections2 = splitString(assignments[1], '-');

        int start1 = std::stoi(sections1[0]);
        int end1 = std::stoi(sections1[1]);
        int start2 = std::stoi(sections2[0]);
        int end2 = std::stoi(sections2[1]);

        /* Part 1 */
        if (start1 <= start2 && end1 >= end2) {
            fullContainments ++;
        }
        else if (start2 <= start1 && end2 >= end1) {
            fullContainments ++;
        }

        /* Part 2 */
        if (end1 < start2 || end2 < start1) continue;
        else overlaps++;
    }

    std::cout << "Number of containments: " << fullContainments << std::endl;
    std::cout << "Number of overlaps: " << overlaps << std::endl;
}

std::vector<std::string> splitString(std::string inputString, char delimiter)
{
    
    int length = inputString.length();
    int i;
    for (i = 0; i < length; i++) 
    {
        if (inputString[i] == delimiter)
        {
            break;
        }
    }

    return std::vector<std::string> {inputString.substr(0, i), inputString.substr(i+1, length)};
}
