#include <iostream>
#include <string>

// Subject Interface
class Image {
public:
    virtual void display() = 0;
    virtual ~Image() = default;
};

// Real Subject: Actual Image Loader
class RealImage : public Image {
private:
    std::string filename;

    void loadImageFromDisk() {
        std::cout << "Loading image: " << filename << std::endl;
    }

public:
    RealImage(const std::string& filename) : filename(filename) {}

    void display() override {
        loadImageFromDisk();
        std::cout << "Displaying: " << filename << std::endl;
    }
};

// Proxy: Lazy Loading Image Proxy
class ImageProxy : public Image {
private:
    std::string filename;
    RealImage* realImage;

public:
    ImageProxy(const std::string& filename) : filename(filename), realImage(nullptr) {}

    ~ImageProxy() {
        delete realImage;
    }

    void display() override {
        // Lazy initialization
        if (realImage == nullptr) {
            realImage = new RealImage(filename);
        }
        realImage->display();
    }
};

int main() {
    // Using proxy to manage image loading
    Image* image1 = new ImageProxy("landscape.jpg");
    
    // Image is not loaded yet
    std::cout << "Image proxy created, not loaded" << std::endl;

    // First display triggers image loading
    image1->display();

    // Next displays use already loaded image
    image1->display();

    // Call destructor
    delete image1;

    return 0;
}