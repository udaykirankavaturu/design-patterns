#include <iostream>
using namespace std;

// interface
class PaymentProcessor{
    public:
    virtual void processPayment() = 0;
    virtual ~PaymentProcessor() = default; // destructor
};

class NetBankingProcessor : public PaymentProcessor {
    public:
    void processPayment() override {
        cout<<"processing net banking payment"<<endl;
    }
};

class UPIProcessor : public PaymentProcessor{
    public:
    void processPayment() override {
        cout<<"processing upi payment"<<endl;
    }
};

// abstract class or interface depending on need
class PaymentProcessorFactory {
    public:
    virtual PaymentProcessor* createPaymentProcessor() = 0;
    virtual ~PaymentProcessorFactory() = default; // destructor
};

class NetBankingFactory : public PaymentProcessorFactory {
    public:
    PaymentProcessor* createPaymentProcessor() override {
        return new NetBankingProcessor();
    }
};

class UPIFactory : public PaymentProcessorFactory {
    public:
    PaymentProcessor* createPaymentProcessor() override {
        return new UPIProcessor();
    }
};

int main(){

    int input;
    cout << "Choose payment method: 1 -> Net Banking or 2 -> UPI" << endl;
    cin >> input;

    switch(input) {
        case 1: {
            NetBankingFactory netBankingFactory;
            PaymentProcessor* processor = netBankingFactory.createPaymentProcessor();
            processor->processPayment();
            delete processor;
            break;
        }
        case 2: {
            UPIFactory upiFactory;
            PaymentProcessor* processor = upiFactory.createPaymentProcessor();
            processor->processPayment();
            delete processor;
            break;
        }
        default: {
            cout << "Invalid input" << endl;
            break;
        }
    }
}