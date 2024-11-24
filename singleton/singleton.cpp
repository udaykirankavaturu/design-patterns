#include <iostream>
#include <string>
using namespace std;

class Logger {
private:
    static Logger* instance;  
    Logger() {}              // Private constructor

public:
    static Logger* getInstance() {
        if (instance == nullptr) {  
            instance = new Logger();
            cout<<"new instance created"<<endl;
        }
        return instance;
    }

    void log(const string& message) {  
        cout << "Log message: " << message << endl;
    }
};

// Initialize the static member
Logger* Logger::instance = nullptr;

int main() {
    Logger* loggerInstance = Logger::getInstance();  
    loggerInstance->log("hello1");  

    // Can't call constructor
    // Logger* logger = new Logger();

    // Logger* loggerInstance2 = Logger::getInstance();   
    // loggerInstance2->log("hello2");  
    // Logger* loggerInstance3 = Logger::getInstance(); 
    // loggerInstance3->log("hello3");  
    // Logger* loggerInstance4 = Logger::getInstance();
    // loggerInstance4->log("hello4");  
    
    return 0;
}