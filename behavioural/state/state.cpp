#include <iostream>
#include <string>
using namespace std;

// Forward declare Ticket for use in TicketState class
class Ticket;

// Base State class
class TicketState {
protected:
    Ticket* ticket;
public:
    virtual ~TicketState() = default;
    void setTicket(Ticket* t) { ticket = t; }
    virtual string getStateName() = 0;
    virtual void startProgress() {
        cout << "Operation not allowed in " << getStateName() << " state\n";
    }
    virtual void resolve() {
        cout << "Operation not allowed in " << getStateName() << " state\n";
    }
    virtual void reopen() {
        cout << "Operation not allowed in " << getStateName() << " state\n";
    }
};

// Declare concrete states BEFORE Ticket class
class TodoState : public TicketState {
public:
    string getStateName() override { return "Todo"; }
    void startProgress() override;  // Define this after Ticket class
};

class InProgressState : public TicketState {
public:
    string getStateName() override { return "In Progress"; }
    void resolve() override;  // Define this after Ticket class
};

class DoneState : public TicketState {
public:
    string getStateName() override { return "Done"; }
    void reopen() override;  // Define this after Ticket class
};

// The Ticket class (Context)
class Ticket {
private:
    TicketState* currentState;
    string title;
    string assignee;
public:
    Ticket(const string& title) : title(title) {
        currentState = new TodoState();
        currentState->setTicket(this);
    }
    
    ~Ticket() {
        delete currentState;
    }

    void setState(TicketState* newState) {
        delete currentState;
        currentState = newState;
        currentState->setTicket(this);
    }

    void startProgress() {
        currentState->startProgress();
    }

    void resolve() {
        currentState->resolve();
    }

    void reopen() {
        currentState->reopen();
    }

    string getStateName() {
        return currentState->getStateName();
    }

    string getTitle() {
        return title;
    }
};

// Define the state transitions after both Ticket and State classes are known
void TodoState::startProgress() {
    cout << "Moving ticket to In Progress\n";
    ticket->setState(new InProgressState());
}

void InProgressState::resolve() {
    cout << "Resolving ticket\n";
    ticket->setState(new DoneState());
}

void DoneState::reopen() {
    cout << "Reopening ticket\n";
    ticket->setState(new TodoState());
}

int main() {
    // Create a new ticket
    Ticket ticket("Fix login bug");
    
    // Show initial state
    cout << "\nTicket: " << ticket.getTitle() << endl;
    cout << "Current State: " << ticket.getStateName() << endl;
    
    // Try all transitions
    cout << "\n1. Starting Progress:" << endl;
    ticket.startProgress();
    cout << "Current State: " << ticket.getStateName() << endl;
    
    cout << "\n2. Resolving Ticket:" << endl;
    ticket.resolve();
    cout << "Current State: " << ticket.getStateName() << endl;
    
    cout << "\n3. Trying to resolve again (should fail):" << endl;
    ticket.resolve();
    
    cout << "\n4. Reopening Ticket:" << endl;
    ticket.reopen();
    cout << "Current State: " << ticket.getStateName() << endl;
    
    return 0;
}