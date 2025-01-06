#include <iostream>
using namespace std;

// Abstract base class for all expressions
class Expression {
public:
    virtual int interpret() = 0;
    virtual ~Expression() = default;
};

// Handles simple numbers
class NumberExpression : public Expression {
private:
    int number;

public:
    NumberExpression(int value) : number(value) {}
    
    int interpret() override {
        return number;
    }
};

// Handles addition of two expressions
class AddExpression : public Expression {
private:
    Expression* left;
    Expression* right;

public:
    AddExpression(Expression* l, Expression* r) : left(l), right(r) {}
    
    int interpret() override {
        return left->interpret() + right->interpret();
    }

    ~AddExpression() {
        delete left;
        delete right;
    }
};

// Handles subtraction of two expressions
class SubtractExpression : public Expression {
private:
    Expression* left;
    Expression* right;

public:
    SubtractExpression(Expression* l, Expression* r) : left(l), right(r) {}
    
    int interpret() override {
        return left->interpret() - right->interpret();
    }

    ~SubtractExpression() {
        delete left;
        delete right;
    }
};

int main() {
    // Creating the expression: 5 + (10 - 3)
    NumberExpression* five = new NumberExpression(5);
    NumberExpression* ten = new NumberExpression(10);
    NumberExpression* three = new NumberExpression(3); 
    
    SubtractExpression* subtraction = new SubtractExpression(ten, three);
    AddExpression* addition = new AddExpression(five, subtraction);
    
    int result = addition->interpret();
    cout << "Result: " << result << endl;  // Outputs: 12
    
    delete addition; 
    return 0;
}