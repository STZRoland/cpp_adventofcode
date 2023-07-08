#include <boost/filesystem.hpp>
#include <fstream>
#include <iostream>
#include <regex>
#include <stack>
#include <string>

bool hasDuplicates(char *array, int size);

const int n_start_packet = 4;
const int n_start_message = 14;

int main(int argc, char const *argv[])
{
    boost::filesystem::path inputPath = boost::filesystem::complete("input.txt");
    std::ifstream inputFile(inputPath.string());
    std::string line;
    
    std::cout << inputPath.string() << std::endl;

    std::getline(inputFile, line);

    if (line.length() < 1) 
    {
        std::cout << "Read input is empty, aborting!" << std::endl;
        return 0;
    }

    bool foundPacket = false;
    int packetStart;
    bool foundMessage = false;
    int messageStart;
    for (int i = 0; i < line.length() - n_start_message; i++)
    {
        // Wild error! Because i initially did not declare the array size +1 it probably wrote the
        // end of array character into i ...
        char packetArray[n_start_packet + 1];
        char messageArray[n_start_message + 1];

        // Could have also been done with the string directly
        std::strcpy(packetArray, line.substr(i, n_start_packet).c_str());
        std::sort(packetArray, packetArray + n_start_packet);

        std::strcpy(messageArray, line.substr(i, n_start_message).c_str());
        std::sort(messageArray, messageArray + n_start_message);

        if (!hasDuplicates(packetArray, n_start_packet) && !foundPacket)
        {
            foundPacket = true;
            packetStart = i + n_start_packet;
            // break;
        }

        if (!hasDuplicates(messageArray, n_start_message) && !foundMessage)
        {
            foundMessage = true;
            messageStart = i + n_start_message;
            break;
        }
    }

    if (!foundPacket)
        std::cout << "Error, no start-of-packet marker found" << std::endl;
    if (!foundMessage)
        std::cout << "Error, no start-of-message marker found" << std::endl;

    std::cout << "First packet marker after " << packetStart << std::endl;
    std::cout << "First message marker after " << messageStart << std::endl;
}

bool hasDuplicates(char *array, int size)
{
    for (int j = 0; j < size; j++)
    {
        if (array[j] == array[j + 1])
        {
            return true;
        }
    }
    return false;
}
