#include <iostream>
#include <string>
#include <memory>

// Interface for Database Connection
class IDatabaseConnection {
public:
    virtual ~IDatabaseConnection() = default;
    virtual std::string executeQuery(const std::string& query) = 0;
};

// Concrete Database Connection Classes
class MySQLConnection : public IDatabaseConnection {
public:
    std::string executeQuery(const std::string& query) override {
        return "MySQL: Executing " + query;
    }
};

class PostgreSQLConnection : public IDatabaseConnection {
public:
    std::string executeQuery(const std::string& query) override {
        return "PostgreSQL: Executing " + query;
    }
};

// Factory Method class
class DatabaseConnectionFactory {
public:
    static std::unique_ptr<IDatabaseConnection> createConnection(const std::string& dbType) {
        if (dbType == "MySQL") {
            return std::make_unique<MySQLConnection>();
        } else if (dbType == "PostgreSQL") {
            return std::make_unique<PostgreSQLConnection>();
        }
        throw std::runtime_error("Invalid database type");
    }
};

int main() {
    try {
        std::string dbType1 = "MySQL";
        std::unique_ptr<IDatabaseConnection> conn1 = DatabaseConnectionFactory::createConnection(dbType1);
        std::cout << conn1->executeQuery("SELECT * FROM users") << std::endl;

        std::string dbType2 = "PostgreSQL";
        std::unique_ptr<IDatabaseConnection> conn2 = DatabaseConnectionFactory::createConnection(dbType2);
        std::cout << conn2->executeQuery("SELECT * FROM users") << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
