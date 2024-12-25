#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// Interface for Observer
class Observer {
public:
    virtual void update(const string& message) = 0;
    virtual ~Observer() = default;
};

// Concrete Observer: WeatherTVDisplay
class WeatherTVDisplay : public Observer {
private:
    string name;

public:
    WeatherTVDisplay(const string& displayName) : name(displayName) {}

    void update(const string& message) override {
        cout << name << " received update - Current weather: " 
                 << message << endl;
    }
};

// Concrete Observer: WeatherApp
class WeatherApp : public Observer {
private:
    string username;

public:
    WeatherApp(const string& username) : username(username) {}

    void update(const string& message) override {
        cout << "Weather App User: " <<username << " received update - Current weather: " 
                 << message << endl;
    }
};

// Interface for Subject (Observable)
class Subject {
public:
    virtual void attach(Observer* observer) = 0;
    virtual void detach(Observer* observer) = 0;
    virtual void notify() = 0;
    virtual ~Subject() = default;
};

// Concrete Subject: WeatherStation
class WeatherStation : public Subject {
private:
    vector<Observer*> observers;
    string currentWeather;

public:
    void attach(Observer* observer) override {
        observers.push_back(observer);
    }

    void detach(Observer* observer) override {
        observers.erase(
            remove(observers.begin(), observers.end(), observer),
            observers.end()
        );
    }

    void notify() override {
        for (Observer* observer : observers) {
            observer->update(currentWeather);
        }
    }

    // Method to change weather and notify observers
    void setWeather(const string& weather) {
        currentWeather = weather;
        notify();
    }
};



// Example usage
int main() {
    // Create the subject (WeatherStation)
    WeatherStation weatherStation;

    // Create observers (displays)
    WeatherTVDisplay display1("Living Room Display");
    WeatherTVDisplay display2("Office Display");
    WeatherTVDisplay display3("Kitchen Display");

    // Create observers (app users)
    WeatherApp user1("user 1");
    WeatherApp user2("user 2");
    WeatherApp user3("user 3");

    // Register observers to the subject
    weatherStation.attach(&display1);
    weatherStation.attach(&display2);
    weatherStation.attach(&display3);
    weatherStation.attach(&user1);
    weatherStation.attach(&user2);
    weatherStation.attach(&user3);

    // Change weather - all displays will be updated
    cout << "Weather changing to Sunny:\n";
    weatherStation.setWeather("Sunny");

    cout << "\nRemoving Office Display...\n";
    weatherStation.detach(&display2);

    // Change weather again - now only two displays will be updated
    cout << "\nWeather changing to Rainy:\n";
    weatherStation.setWeather("Rainy");

    return 0;
}