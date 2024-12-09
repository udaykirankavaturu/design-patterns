#include <iostream>
#include <string>
using namespace std;

class LegacyOracleDB {
public:
    bool connectToOracleDB(string hostname, string port, string username, string password) {
        // connection logic goes here
        cout << "Connected to Oracle database" << endl;
        return true;
    }
};

class DatabaseConnection {
public:
    virtual bool connect(string connectionString) = 0;
    virtual ~DatabaseConnection() {} 
};

class OracleDBAdapter : public DatabaseConnection {
private:
    LegacyOracleDB legacyOracleDB;

public:
    OracleDBAdapter(LegacyOracleDB legacyDB) {
        legacyOracleDB = legacyDB; 
    }

    bool connect(string connectionString) override {
        // parse connection string
        string hostname = "localhost";
        string port = "3067";
        string username = "admin";
        string password = "sdf8723$@";
        return legacyOracleDB.connectToOracleDB(hostname, port, username, password);
    }
};

int main() {
    LegacyOracleDB legacyDB; // Create an instance of LegacyOracleDB
    OracleDBAdapter oda(legacyDB); // Pass the instance to the adapter
    oda.connect("localhost:3067@admin:sdf8723$@");

    return 0; 
}