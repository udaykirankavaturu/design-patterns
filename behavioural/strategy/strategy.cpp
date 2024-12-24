#include <iostream>
#include <string>
using namespace std;

// Strategy interface - defines how all payment methods should behave
class PaymentStrategy {
public:
    virtual void pay(float amount) = 0;
    virtual ~PaymentStrategy() = default;
};

// First concrete strategy - Credit Card payment
class CreditCardPayment : public PaymentStrategy {
public:
    void pay(float amount) override {
        cout << "Paid ₹" << amount << " using Credit Card" << endl;
    }
};

// Second concrete strategy - UPI payment
class UPIPayment : public PaymentStrategy {
public:
    void pay(float amount) override {
        cout << "Paid ₹" << amount << " using UPI" << endl;
    }
};

// Context - Shopping Cart
class ShoppingCart {
private:
    PaymentStrategy* paymentMethod;
    float total;

public:
    ShoppingCart() : paymentMethod(nullptr), total(0) {}

    void setPaymentMethod(PaymentStrategy* method) {
        paymentMethod = method;
    }

    void addItem(float price) {
        total += price;
        cout << "Added item worth ₹" << price << ". Cart total: ₹" << total << endl;
    }

    void checkout() {
        if (paymentMethod != nullptr) {
            paymentMethod->pay(total);
        } else {
            cout << "Please select a payment method first!" << endl;
        }
    }
};

int main() {
    // Create our shopping cart
    ShoppingCart cart;

    // Add some items
    cart.addItem(1500.50);
    cart.addItem(750.00);

    // Create payment strategies
    CreditCardPayment creditCard;
    UPIPayment UPI; 

    // Try checkout with credit card
    cout << "\nPaying with Credit Card:" << endl;
    cart.setPaymentMethod(&creditCard);
    cart.checkout();

    // Try checkout with UPI
    cout << "\nPaying with UPI:" << endl;
    cart.setPaymentMethod(&UPI);
    cart.checkout();

    return 0;
}