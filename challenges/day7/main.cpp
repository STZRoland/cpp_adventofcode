#include <boost/filesystem.hpp>
#include <boost/graph/graph_as_tree.hpp>
#include <fstream>
#include <iostream>
#include <regex>
#include <stack>
#include <string>

class Node {
  public:
    std::string name;

    Node *parent;

    Node(std::string name, Node *parent) : name(name), parent(parent) {}
    virtual int getSize() = 0;
};

class File : public Node {
  public:
    int size;

    File(std::string name, Node *parent, int size)
        : Node(name, parent), size(size) {}

    int getSize() { return size; }
};

class Folder : public Node {
  public:
    std::vector<Folder *> subFolder;
    std::vector<File *> subFiles;
    Folder *parent;

    Folder(std::string name, Folder *parent) : Node(name, parent) {
        subFolder = std::vector<Folder *>();
        subFiles = std::vector<File *>();
    }

    int getSize() {
        int size = 0;
        for (Folder *folder : subFolder) {
            size += folder->getSize();
        }
        for (File *file : subFiles) {
            size += file->getSize();
        }
        return size;
    }

    void printContent() {
        for (File *file : subFiles) {
            std::cout << "f " << file->name << std::endl;
        }
        for (Folder *folder : subFolder) {
            std::cout << "D " << folder->name << std::endl;
        }
    }

    int partOne() {
        std::cout << "FOLDER: " << name << ", size: " << getSize() << std::endl;
        int size = getSize();
        int returnSize = 0;
        if (size <= 100000) {
            returnSize = size;
        }
        for (Folder *folder : subFolder) {
            returnSize += folder->partOne();
        }
        // std::cout << "Return size " << returnSize << std::endl;
        // std::cout << "Size " << size << std::endl;
        printContent();
        return returnSize;
    }

    void addSubFolder(Folder *folder) {
        this->subFolder.push_back(folder);
        // std::cout << "Added folder " << folder->name << std::endl;
    }
    void addFile(File *file) { this->subFiles.push_back(file); }

    Folder *getFolder(std::string name) {
        for (Folder *folder : subFolder) {
            if (folder->name == name) {
                return folder;
            }
        }
        return nullptr;
    }
    File *getFile(std::string name) {
        for (File *file : subFiles) {
            if (file->name == name) {
                return file;
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
    Folder *currentRoot = &root;

    while (std::getline(inputFile, line)) {
        char firstChar = line.at(0);
        std::cout << std::endl;
        std::cout << line << std::endl;
        std::cout << "Current root " << currentRoot->name << std::endl;

        if (firstChar == '$') {
            // cd
            if (line.at(2) == 'c') {
                std::string folderName = line.substr(5);
                if (folderName == "..") {
                    std::cout << "cd .. from " << currentRoot->name << " to "
                              << currentRoot->parent->name << std::endl;
                    currentRoot = currentRoot->parent;
                    continue;
                }

                Folder *foundFolder = currentRoot->getFolder(folderName);
                if (foundFolder) {
                    std::cout << "cd from " << currentRoot->name << " to "
                              << foundFolder->name << std::endl;
                    currentRoot = foundFolder;
                } else {
                    // Folder newFolder(folderName, currentRoot);
                    // std::cout << "mkdir " << newFolder.name << std::endl;
                    // // Folder newFolder = *new Folder(folderName,
                    // currentRoot); currentRoot->addSubFolder(&newFolder);
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
            if (foundFolder) {
                currentRoot = foundFolder;
                std::cout << "Listing folder " << folderName << std::endl;
            } else {
                Folder newFolder(folderName, currentRoot);
                // Folder newFolder = *new Folder(folderName, currentRoot);
                std::cout << "Creating folder " << folderName << std::endl;
                currentRoot->addSubFolder(&newFolder);
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
                currentRoot->addFile(&newFile);
            }
        }
    }

    std::cout << "Complete size: " << root.getSize() << std::endl;
    std::cout << "Part one result: " << root.partOne() << std::endl;
}
