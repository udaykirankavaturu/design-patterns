#include <iostream>
using namespace std;
#include <string>

// Abstract base class that defines the template method
class Beverage {
protected:
    // These are the "primitive" operations that can be overridden
    virtual void boilWater() {
        cout << "Boiling water" << endl;
    }
    
    virtual void brew() = 0;  // Pure virtual - must be implemented by subclasses
    
    virtual void pourInCup() {
        cout << "Pouring into cup" << endl;
    }
    
    virtual void addCondiments() = 0;  // Pure virtual - must be implemented by subclasses

public:
    // This is the template method
    void prepareBeverage() {
        boilWater();
        brew();
        pourInCup();
        addCondiments();
        cout << "Your beverage is ready!" << endl;
    }
    
    // Virtual destructor is important for inheritance
    virtual ~Beverage() {}
};

// Concrete class for making coffee
class Coffee : public Beverage {
protected:
    void brew() override {
        cout << "Brewing coffee grounds" << endl;
    }
    
    void addCondiments() override {
        cout << "Adding sugar and milk" << endl;
    }
};

// Concrete class for making tea
class Tea : public Beverage {
protected:
    void brew() override {
        cout << "Steeping the tea" << endl;
    }
    
    void addCondiments() override {
        cout << "Adding lemon" << endl;
    }
};

int main() {
    cout << "Making coffee:" << endl;
    Coffee coffee;
    coffee.prepareBeverage();
    
    cout << "\nMaking tea:" << endl;
    Tea tea;
    tea.prepareBeverage();
    
    return 0;
}