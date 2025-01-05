#include <iostream>
using namespace std;
#include <string>

// Forward declarations
class GuestUser;
class RegisteredUser;

// Visitor interface
class Visitor {
public:
    virtual void visitGuestUser(GuestUser* user) = 0;
    virtual void visitRegisteredUser(RegisteredUser* user) = 0;
    virtual ~Visitor() = default;
};

// Base User class
class User {
public:
    virtual void accept(Visitor* v) = 0;
    virtual ~User() = default;
};

// Concrete User classes
class GuestUser : public User {
public:
    void accept(Visitor* v) override {
        v->visitGuestUser(this);
    }
};

class RegisteredUser : public User {
    string username;
public:
    RegisteredUser(const string& name) : username(name) {}
    
    string getUsername() const { return username; }
    
    void accept(Visitor* v) override {
        v->visitRegisteredUser(this);
    }
};

// Concrete Visitors
class Newsletters : public Visitor {
public:
    void visitGuestUser(GuestUser* user) override {
        cout << "Sending guest newsletter with registration benefits\n";
    }
    
    void visitRegisteredUser(RegisteredUser* user) override {
        cout << "Sending personalized newsletter to " << user->getUsername() << "\n";
    }
};

class Audits : public Visitor {
public:
    void visitGuestUser(GuestUser* user) override {
        cout << "Logging guest user activity\n";
    }
    
    void visitRegisteredUser(RegisteredUser* user) override {
        cout << "Auditing registered user " << user->getUsername() << "'s actions\n";
    }
};

int main() {
    // Create users
    GuestUser guest;
    RegisteredUser registered("uday kiran kavaturu");
    
    // Create visitors
    Newsletters newsletterVisitor;
    Audits auditVisitor;
    
    // Use visitors
    cout << "Newsletter operations:\n";
    guest.accept(&newsletterVisitor);
    registered.accept(&newsletterVisitor);
    
    cout << "\nAudit operations:\n";
    guest.accept(&auditVisitor);
    registered.accept(&auditVisitor);
    
    return 0;
}