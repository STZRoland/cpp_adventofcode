#include <boost/filesystem.hpp>
#include <boost/graph/graph_as_tree.hpp>
#include <fstream>
#include <iostream>
#include <regex>
#include <stack>
#include <string>

class File;
class Folder;

const int totalSize = 70000000;
const int requiredSize = 30000000;

// Super ugly but well
Folder *smallestPossibleFolder;
int currentSmallestSize = 1000000000;

class File {
  public:
    int size;
    std::string name;
    Folder *parent;

    File(std::string name, Folder *parent, int size)
        : name(name), parent(parent), size(size) {}

    int getSize() { return size; }
    void setParent(Folder *parent) { parent = parent; }
    Folder *getParent() { return parent; }
};

class Folder {
  public:
    std::vector<Folder> subFolder;
    std::vector<File> subFiles;
    std::string name;
    Folder *parent;

    Folder(std::string name, Folder *parent) : name(name), parent(parent) {
        subFolder = std::vector<Folder>();
        subFiles = std::vector<File>();
    }

    int getSize() {
        int size = 0;
        for (Folder &folder : subFolder) {
            size += folder.getSize();
        }
        for (File &file : subFiles) {
            size += file.getSize();
        }
        return size;
    }

    void setParent(Folder *parent) { parent = parent; }
    Folder *getParent() { return parent; }

    void printContent() {
        for (File &file : subFiles) {
            std::cout << "f " << file.name << std::endl;
        }
        for (Folder &folder : subFolder) {
            std::cout << "D " << folder.name << std::endl;
        }
    }

    int partOne() {
        int size = getSize();
        int returnSize = 0;
        if (size <= 100000) {
            returnSize = size;
        }
        for (Folder &folder : subFolder) {
            returnSize += folder.partOne();
        }
        return returnSize;
    }

    void partTwo(int minSize) {
        int size = getSize();

        if (size >= minSize && size <= currentSmallestSize) {
            smallestPossibleFolder = this;
            currentSmallestSize = size;
        }

        for (Folder &folder : subFolder) {
            folder.partTwo(minSize);
        }
    }

    void addSubFolder(Folder folder) { subFolder.push_back(folder); }
    void addFile(File file) { subFiles.push_back(file); }

    Folder *getFolder(std::string name) {
        for (Folder &folder : subFolder) {
            if (folder.name == name) {
                return &folder;
            }
        }
        return nullptr;
    }
    File *getFile(std::string name) {
        for (File &file : subFiles) {
            if (file.name == name) {
                return &file;
            }
        }
        return nullptr;
    }
};

int main(int argc, char const *argv[]) {
    boost::filesystem::path inputPath =
        boost::filesystem::absolute("input.txt");
    std::ifstream inputFile(inputPath.string());
    std::string line;
    std::getline(inputFile, line);

    Folder root{"root", nullptr};
    root.parent = &root;
    Folder *currentRoot = &root;

    while (std::getline(inputFile, line)) {
        char firstChar = line.at(0);

        if (firstChar == '$') {
            // cd
            if (line.at(2) == 'c') {
                std::string folderName = line.substr(5);
                if (folderName == "..") {
                    currentRoot = currentRoot->getParent();
                    // currentRoot
                    continue;
                }

                Folder *foundFolder = currentRoot->getFolder(folderName);
                if (foundFolder) {
                    currentRoot = *&foundFolder;
                } else {
                    std::cout << "Error, folder with name " << folderName
                              << " does not exist in dir " << currentRoot->name
                              << std::endl;
                }
            }
            continue;
        }

        if (line.at(0) == 'd') {
            std::string folderName = line.substr(4);
            Folder *foundFolder = currentRoot->getFolder(folderName);
            if (!foundFolder) {
                Folder newFolder = *new Folder(folderName, currentRoot);
                currentRoot->addSubFolder(newFolder);
            }
        } else {
            std::size_t spacePos = line.find(' ');
            std::string numberString = line.substr(0, spacePos);
            int size = std::stoi(numberString);

            std::string fileName = line.substr(spacePos + 1);

            File *foundFile = currentRoot->getFile(fileName);
            if (!foundFile) {
                File newFile(fileName, currentRoot, size);
                // File newFile = *new File(fileName, currentRoot, size);
                currentRoot->addFile(newFile);
            }
        }
    }

    int occupiedSize = root.getSize();
    std::cout << "Occupied size: " << occupiedSize << std::endl;
    std::cout << "Part one result: " << root.partOne() << std::endl;

    int freeSize = totalSize - occupiedSize;
    int deleteSize = requiredSize - freeSize;

    std::cout << "The size required to delete is " << deleteSize << std::endl;
    smallestPossibleFolder = &root;
    root.partTwo(deleteSize);
    std::cout << "Smallest possible Folder " << smallestPossibleFolder->name
              << " with size " << smallestPossibleFolder->getSize()
              << std::endl;
}
