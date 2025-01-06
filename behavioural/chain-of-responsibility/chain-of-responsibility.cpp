#include <iostream>
using namespace std;
#include <string>

// Base handler class
class SupportHandler {
protected:
    SupportHandler* nextHandler;
    int level;

public:
    SupportHandler() : nextHandler(nullptr) {}

    void setNext(SupportHandler* handler) {
        nextHandler = handler;
    }

    virtual void handleTicket(int ticketLevel, const string& issue) {
        if (ticketLevel <= level) {
            resolve(issue);
        } else if (nextHandler != nullptr) {
            cout << "Escalating to next level...\n";
            nextHandler->handleTicket(ticketLevel, issue);
        } else {
            cout << "No handler available for this issue.\n";
        }
    }

    virtual void resolve(const string& issue) = 0;
};

// Concrete handlers
class Level1Support : public SupportHandler {
public:
    Level1Support() {
        level = 1;
    }

    void resolve(const string& issue) override {
        cout << "Level 1 Support handling issue: " << issue << "\n";
        cout << "Performing basic troubleshooting...\n";
    }
};

class Level2Support : public SupportHandler {
public:
    Level2Support() {
        level = 2;
    }

    void resolve(const string& issue) override {
        cout << "Level 2 Support handling issue: " << issue << "\n";
        cout << "Performing advanced troubleshooting...\n";
    }
};

class Level3Support : public SupportHandler {
public:
    Level3Support() {
        level = 3;
    }

    void resolve(const string& issue) override {
        cout << "Level 3 Support handling issue: " << issue << "\n";
        cout << "Performing expert level troubleshooting...\n";
    }
};

int main() {
    // Create handlers
    Level1Support* level1 = new Level1Support();
    Level2Support* level2 = new Level2Support();
    Level3Support* level3 = new Level3Support();

    // Set up the chain
    level1->setNext(level2);
    level2->setNext(level3);

    // Test the chain with different issues
    cout << "Submitting level 1 issue:\n";
    level1->handleTicket(1, "Password reset");
    
    cout << "\nSubmitting level 2 issue:\n";
    level1->handleTicket(2, "Software configuration problem");
    
    cout << "\nSubmitting level 3 issue:\n";
    level1->handleTicket(3, "Server crash investigation");

    // Clean up
    delete level1;
    delete level2;
    delete level3;

    return 0;
}