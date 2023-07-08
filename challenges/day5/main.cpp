#include <boost/filesystem.hpp>
#include <fstream>
#include <iostream>
#include <stack>
#include <string>
#include <regex>

// std::stack<char> *getArrangement(std::string lines[5]);
void getArrangement(std::string lines[8], std::stack<char> outArray[9]);

int main(int argc, char const *argv[])
{
    boost::filesystem::path inputPath = boost::filesystem::complete("input.txt");
    std::ifstream inputFile(inputPath.string());
    std::string headerLines[8];

    for (int i = 0; i < 8; i++)
    {
        std::getline(inputFile, headerLines[i]);
    }

    std::stack<char> arrangement[9];
    getArrangement(headerLines, arrangement);

    std::string line;
    std::getline(inputFile, line);
    std::getline(inputFile, line);

    std::regex expression("\\d+");
    std::string basic = "$1";
    std::smatch match;

    while (std::getline(inputFile, line)) {

        int numbers[3] = {0};
        int idx = 0;
        while (std::regex_search(line, match, expression))
        {
            numbers[idx] = std::stoi(match.str());
            line = match.suffix();
            idx++;
        }

        int count = numbers[0];
        size_t origin = numbers[1];
        size_t destination = numbers[2];

        /* Part 1*/
        // for (int i = 0; i < count; i++)
        // {
        //     if (arrangement[origin - 1].empty())
        //     {
        //         std::cout << "Stack " << origin << " is empty!" << std::endl;
        //     }
        //     char item = arrangement[origin - 1].top();
        //     // std::cout << item << std::endl;
        //     arrangement[origin - 1].pop();
        //     arrangement[destination - 1].push(item);
        // }
        
        /* Part 2 */
        char movedItems[count];
        for (int i = 0; i < count; i++)
        {
            if (arrangement[origin - 1].empty())
            {
                std::cout << "Stack " << origin << " is empty!" << std::endl;
            }
            char item = arrangement[origin - 1].top();
            arrangement[origin - 1].pop();
            movedItems[i] = item;
        }

        for (int i = count-1; i >= 0; i--)
        {
            arrangement[destination - 1].push(movedItems[i]);
        }
    }

    std::cout << "Final top items: ";
    for (int i = 0; i < 9; i++) {
        std::cout << arrangement[i].top();
    }
    std::cout << std::endl;
}

void getArrangement(std::string lines[8], std::stack<char> outArray[9])
{
    for (int i = 7; i >= 0; i--)
    {
        int stack_idx = 0;
        int counter = 0;
        for (char &c : lines[i])
        {
            if (65 <= c && c <= 90)
            {
                outArray[stack_idx].push(c);
                stack_idx++;
                counter = 0;
            }
            // Ugly as hell
            else if (counter == 4) {
                stack_idx++;
                counter = 0;
            }
            counter++;
        }
    }
}
