#include <iostream>
#include <string>

// Implementation interface
class DatabaseEngine {
public:
    virtual ~DatabaseEngine() = default;
    virtual void connect(const std::string& connectionString) = 0;
    virtual void disconnect() = 0;
    virtual void executeQuery(const std::string& query) = 0;
};

// Concrete implementations
class MySQLEngine : public DatabaseEngine {
public:
    void connect(const std::string& connectionString) override {
        std::cout << "MySQL: Connecting to " << connectionString << std::endl;
    }

    void disconnect() override {
        std::cout << "MySQL: Disconnecting from database" << std::endl;
    }

    void executeQuery(const std::string& query) override {
        std::cout << "MySQL executing: " << query << std::endl;
    }
};

class MongoDBEngine : public DatabaseEngine {
public:
    void connect(const std::string& connectionString) override {
        std::cout << "MongoDB: Connecting to " << connectionString << std::endl;
    }

    void disconnect() override {
        std::cout << "MongoDB: Disconnecting from database" << std::endl;
    }

    void executeQuery(const std::string& query) override {
        std::cout << "MongoDB executing: " << query << std::endl;
    }
};

// Abstraction
class QueryBuilder {
protected:
    DatabaseEngine* engine;
    std::string query;

public:
    QueryBuilder(DatabaseEngine* dbEngine) : engine(dbEngine), query("") {}
    virtual ~QueryBuilder() = default;

    virtual void connect(const std::string& connectionString) {
        engine->connect(connectionString);
    }

    virtual void disconnect() {
        engine->disconnect();
    }

    virtual QueryBuilder& select(const std::string& fields) {
        query = "SELECT " + fields;
        return *this;
    }

    virtual QueryBuilder& from(const std::string& table) {
        query += " FROM " + table;
        return *this;
    }

    virtual QueryBuilder& where(const std::string& condition) {
        query += " WHERE " + condition;
        return *this;
    }

    virtual void execute() {
        engine->executeQuery(query);
        query.clear();
    }
};

// Refined Abstractions
class SQLQueryBuilder : public QueryBuilder {
public:
    SQLQueryBuilder(DatabaseEngine* dbEngine) : QueryBuilder(dbEngine) {}

    // Add SQL-specific query methods
    QueryBuilder& join(const std::string& table, const std::string& condition) {
        query += " JOIN " + table + " ON " + condition;
        return *this;
    }
};

class NoSQLQueryBuilder : public QueryBuilder {
public:
    NoSQLQueryBuilder(DatabaseEngine* dbEngine) : QueryBuilder(dbEngine) {}

    // Override select for MongoDB-style queries
    QueryBuilder& select(const std::string& fields) override {
        query = "db.collection.find({}, {" + fields + "})";
        return *this;
    }

    // Override where for MongoDB-style queries
    QueryBuilder& where(const std::string& condition) override {
        query = "db.collection.find({" + condition + "})";
        return *this;
    }
};

// Example usage
int main() {
    // Create database engines
    DatabaseEngine* mysqlEngine = new MySQLEngine();
    DatabaseEngine* mongoEngine = new MongoDBEngine();

    // Create query builders
    SQLQueryBuilder sqlBuilder(mysqlEngine);
    NoSQLQueryBuilder noSqlBuilder(mongoEngine);

    // Use SQL builder
    std::cout << "\n=== SQL Query Example ===\n";
    sqlBuilder.connect("mysql://localhost:3306/mydb");
    
    sqlBuilder
        .select("name, age")
        .from("users")
        .where("age > 25")
        .execute();
    
    sqlBuilder
        .select("*")
        .from("users")
        .where("orders.amount > 1000")
        .execute();
    
    sqlBuilder.disconnect();

    // Use NoSQL builder
    std::cout << "\n=== MongoDB Query Example ===\n";
    noSqlBuilder.connect("mongodb://localhost:27017/mydb");
    
    noSqlBuilder
        .select("name: 1, age: 1")
        .execute();
    
    noSqlBuilder
        .where("age: {$gt: 25}")
        .execute();
    
    noSqlBuilder.disconnect();

    // Clean up
    delete mysqlEngine;
    delete mongoEngine;

    return 0;
}