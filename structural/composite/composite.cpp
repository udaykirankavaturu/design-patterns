#include <iostream>
#include <vector>
#include <memory> // For smart pointers

// Abstract Base Component
class FileSystemComponent {
public:
    virtual void showDetails(int depth = 0) const = 0; // Pure virtual function
    virtual ~FileSystemComponent() = default; // Virtual destructor
};

// Leaf: Represents a File
class File : public FileSystemComponent {
private:
    std::string name;

public:
    File(const std::string& fileName) : name(fileName) {}

    void showDetails(int depth = 0) const override {
        std::cout << std::string(depth, '-') << "File: " << name << std::endl;
    }
};

// Composite: Represents a Folder
class Folder : public FileSystemComponent {
private:
    std::string name;
    std::vector<std::shared_ptr<FileSystemComponent>> children;

public:
    Folder(const std::string& folderName) : name(folderName) {}

    void add(const std::shared_ptr<FileSystemComponent>& component) {
        children.push_back(component);
    }

    void remove(const std::shared_ptr<FileSystemComponent>& component) {
        children.erase(std::remove(children.begin(), children.end(), component), children.end());
    }

    void showDetails(int depth = 0) const override {
        std::cout << std::string(depth, '-') << "Folder: " << name << std::endl;
        for (const auto& child : children) {
            child->showDetails(depth + 2);
        }
    }
};

// Main Function
int main() {
    // Create Files
    auto file1 = std::make_shared<File>("File1.txt");
    auto file2 = std::make_shared<File>("File2.txt");
    auto file3 = std::make_shared<File>("File3.txt");

    // Create Folders
    auto folder1 = std::make_shared<Folder>("Folder1");
    auto folder2 = std::make_shared<Folder>("Folder2");

    // Add Files to Folders
    folder1->add(file1);
    folder1->add(file2);

    folder2->add(file3);
    folder2->add(folder1); // Adding folder1 to folder2 (composite within a composite)

    // Display Structure
    std::cout << "File System Structure:" << std::endl;
    folder2->showDetails();

    return 0;
}
