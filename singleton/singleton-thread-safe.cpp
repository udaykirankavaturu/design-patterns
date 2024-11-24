#include <iostream>
#include <string>
#include <mutex>
#include <thread>
#include <chrono>
using namespace std;

class Logger {
private:
    static Logger* instance;
    static int instanceCount; 
    static mutex mtx;

    Logger() {
        instanceCount++;
        cout <<endl<< "Instance count: " << instanceCount << endl; 
    }  // Private constructor
    
    // Prevent copying and assignment
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

public:
    static Logger* getInstance() {
        if(instance == nullptr){
            mtx.lock();// remove lock to see thread race conditions
            if (instance == nullptr) {
                instance = new Logger();
            }
            mtx.unlock(); 
        }
        return instance;
        
    }

    void log(const string& message) {
        cout << "Log message: " << message << endl;
    }
};

// Initialize the static members
Logger* Logger::instance = nullptr;
int Logger::instanceCount = 0;  
mutex Logger::mtx;

// for thread safety demo
void getLoggerInstance() {
    Logger* logger = Logger::getInstance();
}

int main() {
   
     // Create threads
    thread firstThread(getLoggerInstance);
    thread secondThread(getLoggerInstance);
    thread thirdThread(getLoggerInstance);

    // Join threads
    firstThread.join();
    secondThread.join();
    thirdThread.join();

    
    return 0;
}