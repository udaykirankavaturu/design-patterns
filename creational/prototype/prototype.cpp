#include <iostream>
#include <memory>
#include <vector>
#include <string>
using namespace std;

// Base class for Soldiers
class Soldier {
public:
    virtual unique_ptr<Soldier> clone() const = 0;
    virtual void display() const = 0;
    virtual ~Soldier() = default;
};

// Basic Soldier class
class BasicSoldier : public Soldier {
private:
    int exp = 10; 
    vector<string> weapons = {"knife", "blade"};
    int health = 100;

public:
    unique_ptr<Soldier> clone() const override {
        return make_unique<BasicSoldier>(*this);
    }

    void display() const override {
        cout << "Basic Soldier - Health: " << health << ", Exp: " << exp << endl;
    }
};

// Advanced Soldier class
class AdvancedSoldier : public Soldier {
private:
    int exp = 20;
    vector<string> weapons = {"knife", "blade", "double-sword", "grenade"};
    int health = 150;
    int armor = 50;

public:
    unique_ptr<Soldier> clone() const override {
        return make_unique<AdvancedSoldier>(*this);
    }

    void display() const override {
        cout << "Advanced Soldier - Health: " << health << ", Exp: " << exp << ", Armor: " << armor << endl;
    }
};

// Base Army class
class Army {
public:
    virtual unique_ptr<Army> clone() const = 0;
    virtual void addSoldier(unique_ptr<Soldier> soldier) = 0;
    virtual void display() const = 0;
    virtual ~Army() = default;
};

// Basic Army class
class BasicArmy : public Army {
private:
    vector<unique_ptr<Soldier>> soldiers;

public:
    unique_ptr<Army> clone() const override {
        auto newArmy = make_unique<BasicArmy>();
        for (const auto& soldier : soldiers) {
            newArmy->addSoldier(soldier->clone());
        }
        return newArmy;
    }

    void addSoldier(unique_ptr<Soldier> soldier) override {
        soldiers.push_back(std::move(soldier));
    }

    void display() const override {
        cout << "Basic Army:" << endl;
        for (const auto& soldier : soldiers) {
            soldier->display();
        }
    }
};

// Main function
int main() {
    // Create soldiers
    unique_ptr<Soldier> bs1 = make_unique<BasicSoldier>();
    unique_ptr<Soldier> as1 = make_unique<AdvancedSoldier>();

    // Create and populate Basic Army
    BasicArmy ba1;
    ba1.addSoldier(bs1->clone());
    ba1.addSoldier(bs1->clone());
    ba1.addSoldier(bs1->clone());

    // Clone the army
    unique_ptr<Army> ba2 = ba1.clone();

    ba1.addSoldier(bs1->clone());

    // Display both armies
    cout << "Original Basic Army:" << endl;
    ba1.display();

    cout << "\nCloned Basic Army:" << endl;
    ba2->display();


    return 0;
}
