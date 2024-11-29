#include <iostream>
using namespace std;

class CPU {
public:
    virtual void operation() = 0;
    virtual ~CPU() = default;
};

class IntelCPU : public CPU {
public:
    void operation() override {
        cout << "This is from Intel CPU" << endl;
    }
};

class AppleCPU : public CPU {
public:
    void operation() override {
        cout << "This is from Apple CPU" << endl;
    }
};

class OperatingSystem {
public:
    virtual void operation() = 0;
    virtual ~OperatingSystem() = default;
};

class WindowsOS : public OperatingSystem {
public:
    void operation() override {
        cout << "Welcome to Windows" << endl;
    }
};

class MacOS : public OperatingSystem {
public:
    void operation() override {
        cout << "Welcome to macOS" << endl;
    }
};

class Computer {
public:
    CPU* cpu;
    OperatingSystem* os;

    Computer(CPU* cpu, OperatingSystem* os) {
        this->cpu = cpu;
        this->os = os;
    }

    ~Computer() {
        delete cpu;
        delete os;
    }
};

class ComputerFactory {

    protected:
    virtual CPU* createCPU() = 0;
    virtual OperatingSystem* createOS() = 0;

    public:
    Computer* assemble() {
        CPU* cpu = createCPU();
        OperatingSystem* os = createOS(); 
        return new Computer(cpu, os);
    }

    virtual ~ComputerFactory() = default;
};

class DellFactory : public ComputerFactory {
public:
    CPU* createCPU() override {
        return new IntelCPU();
    }
    OperatingSystem* createOS() override {
        return new WindowsOS();
    }
};

class AppleFactory : public ComputerFactory {
public:
    CPU* createCPU() override {
        return new AppleCPU();
    }
    OperatingSystem* createOS() override {
        return new MacOS();
    }
};

int main() {
    ComputerFactory* appleFactory = new AppleFactory();
    Computer* appleComputer = appleFactory->assemble();
    appleComputer->cpu->operation();
    appleComputer->os->operation();

    ComputerFactory* dellFactory = new DellFactory();
    Computer* dellComputer = dellFactory->assemble();
    dellComputer->cpu->operation();
    dellComputer->os->operation();
 
    // Cleanup
    delete appleComputer;
    delete dellComputer;
    delete appleFactory;
    delete dellFactory;

    return 0;
}
