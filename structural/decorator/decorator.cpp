#include <iostream>
using namespace std;
#include <memory>
#include <string>

// Component Interface
class Coffee {
public:
    virtual ~Coffee() = default;
    virtual double getCost() = 0;
    virtual string getDescription() = 0;
};

// Concrete Component
class SimpleCoffee : public Coffee {
public:
    double getCost() override {
        return 5.0;
    }
    
    string getDescription() override {
        return "Basic Coffee";
    }
};

// Base Decorator
class CoffeeDecorator : public Coffee {
protected:
    unique_ptr<Coffee> decoratedCoffee;

public:
    explicit CoffeeDecorator(unique_ptr<Coffee> coffee) 
        : decoratedCoffee(std::move(coffee)) {}

    double getCost() override {
        return decoratedCoffee->getCost();
    }

    string getDescription() override {
        return decoratedCoffee->getDescription();
    }
};

// Concrete Decorators
class MilkDecorator : public CoffeeDecorator {
public:
    explicit MilkDecorator(unique_ptr<Coffee> coffee) 
        : CoffeeDecorator(std::move(coffee)) {}

    double getCost() override {
        return decoratedCoffee->getCost() + 2.0;
    }

    string getDescription() override {
        return decoratedCoffee->getDescription() + ", Milk";
    }
};

class CaramelDecorator : public CoffeeDecorator {
public:
    explicit CaramelDecorator(unique_ptr<Coffee> coffee) 
        : CoffeeDecorator(std::move(coffee)) {}

    double getCost() override {
        return decoratedCoffee->getCost() + 1.5;
    }

    string getDescription() override {
        return decoratedCoffee->getDescription() + ", Caramel";
    }
};

int main() {
    // Create a basic coffee
    unique_ptr<Coffee> coffee = make_unique<SimpleCoffee>();
    cout << "Base Coffee: " 
              << coffee->getDescription() 
              << " - $" << coffee->getCost() << endl;

    // Add milk decorator
    coffee = make_unique<MilkDecorator>(std::move(coffee));
    cout << "Coffee with Milk: " 
              << coffee->getDescription() 
              << " - $" << coffee->getCost() << endl;

    // Add caramel decorator
    coffee = make_unique<CaramelDecorator>(std::move(coffee));
    cout << "Coffee with Milk and Caramel: " 
              << coffee->getDescription() 
              << " - $" << coffee->getCost() << endl;

    return 0;
}