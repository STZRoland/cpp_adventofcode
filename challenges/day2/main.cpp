#include <iostream>
#include <fstream>
#include <string>
#include <boost/filesystem.hpp>
// #include <map>


int evaluateRound(char opponentShape, char yourShape);
char getDesiredShape(char opponentShape, char desiredOutcome);
void partOne();
void partTwo();

int main(int argc, char const *argv[])
{
    partOne();
    partTwo();
}


void partTwo()
{
    boost::filesystem::path inputPath = boost::filesystem::complete("input.txt");
    std::ifstream inputFile (inputPath.string());
    std::string line;

    int totalPoints = 0;    
    for (int i = 0; std::getline(inputFile,line); i++) 
    {
        char opponentMove = line[0];
        char desiredOutcome = line[2];

        char yourMove = getDesiredShape(opponentMove, desiredOutcome);
        // std::cout << evaluateRound(opponentMove, yourMove) << std::endl;
        totalPoints += evaluateRound(opponentMove, yourMove);
    }

    std::cout << "Total points: " << totalPoints << std::endl;

}

char getDesiredShape(char opponentShape, char desiredOutcome)
{
    switch (opponentShape) 
    {
        // Rock
        case 'A':
            switch (desiredOutcome) {
                case 'X':
                    return 'Z'; // Scissors
                case 'Y':
                    return 'X'; // Rock
                case 'Z':
                    return 'Y'; // Scissors
            }
            break;
        // Paper
        case 'B':
            switch (desiredOutcome) {
                case 'X':
                    return 'X';
                case 'Y':
                    return 'Y';
                case 'Z':
                    return 'Z';
            }
            break;
        case 'C':
            switch (desiredOutcome) {
                case 'X':
                    return 'Y';
                case 'Y':
                    return 'Z';
                case 'Z':
                    return 'X';
            }
            break;
    }
    return '0';
}


void partOne()
{
    boost::filesystem::path inputPath = boost::filesystem::complete("input.txt");
    std::ifstream inputFile (inputPath.string());
    std::string line;

    int totalPoints = 0;    
    for (int i = 0; std::getline(inputFile,line); i++) 
    {
        char opponentMove = line[0];
        char yourMove = line[2];
        
        totalPoints += evaluateRound(opponentMove, yourMove);
    }

    std::cout << "Total points: " << totalPoints << std::endl;
}

int evaluateRound(char opponentShape, char yourShape)
{
    int points = 0;

    switch (yourShape) 
    {
        // Rock
        case 'X':
            points += 1;
            switch (opponentShape) {
                case 'A':
                    points += 3;
                    break;
                case 'C':
                    points += 6;
                    break;
            }
            break;
        // Paper
        case 'Y':
            points += 2;
            switch (opponentShape) {
                case 'A':
                    points += 6;
                    break;
                case 'B':
                    points += 3;
                    break;
            }
            break;
        // Scissors
        case 'Z':
            points += 3;
            switch (opponentShape) {
                case 'B':
                    points += 6;
                    break;
                case 'C':
                    points += 3;
                    break;
            }
            break;
    }
    return points;
}

