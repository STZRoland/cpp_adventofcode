#include <iostream>
#include <fstream>
#include <string>
#include <boost/filesystem.hpp>
#include <algorithm>

int main(int argc, char const *argv[])
{
    boost::filesystem::path input_path = boost::filesystem::complete("input.txt");
    std::ifstream input_file (input_path.string());

    std::string line;
    std::list<int> elf_list;

    int lowest_max_calories = 0;
    int max_idxs[3] = {0};
    int max_calories[3] = {0};

    int array_size = sizeof(max_idxs) / sizeof(max_idxs[0]);
    // std::cout << array_size << std::endl;

    if (input_file.is_open())
    {
        int current_idx = 0;
        int cal_sum = 0;
        while (std::getline(input_file, line))
        {
            if (line.empty())
            {
                elf_list.push_back(cal_sum);


                if (cal_sum > lowest_max_calories)
                {
                    // find lowest entry in max calories array
                    int* min_element = std::min_element(max_calories, max_calories + array_size);
                    int idx_min_element = std::distance(max_calories, min_element);

                    max_calories[idx_min_element] = cal_sum;
                    max_idxs[idx_min_element] = current_idx;
                    lowest_max_calories = *std::min_element(max_calories, max_calories + array_size);
                }

                current_idx ++;
                cal_sum = 0;
            }
            else
            {
                cal_sum += std::stoi(line);
            }
        }
    }
    else 
    {
        std::cout << "Unable to open file: " << input_path.string() << std::endl;
        return -1;
    }

    int total_calories = 0;
    std::cout << "Top three elves:";
    for (int i = 0; i < array_size; i++) 
    {
        std::cout << max_idxs[i] + 1 << " c:";
        std::cout << max_calories[i] << " ";
        total_calories += max_calories[i];
    }
    std::cout << std::endl;

    std::cout << "Total calories carrie by them: " << total_calories << std::endl;
}
