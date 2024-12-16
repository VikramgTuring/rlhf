#include <iostream>
#include <string>
#include <memory>
#include <queue>
#include <mutex>
#include <condition_variable>

// Maximum number of connections in the pool
const int MAX_CONNECTIONS = 5;

// Interface for Database Connection
class IDatabaseConnection {
public:
    virtual ~IDatabaseConnection() = default;
    virtual std::string executeQuery(const std::string& query) = 0;
};

// Concrete Database Connection Classes
class MySQLConnection : public IDatabaseConnection {
public:
    MySQLConnection() {}
    std::string executeQuery(const std::string& query) override {
        return "MySQL: Executing " + query;
    }
};

class PostgreSQLConnection : public IDatabaseConnection {
public:
    PostgreSQLConnection() {}
    std::string executeQuery(const std::string& query) override {
        return "PostgreSQL: Executing " + query;
    }
};

// Connection Pool class
class ConnectionPool {
public:
    ConnectionPool(const std::string& dbType) : dbType(dbType) {
        for (int i = 0; i < MAX_CONNECTIONS; ++i) {
            createConnectionAndAddToPool();
        }
    }

    ~ConnectionPool() {
        while (!connections.empty()) {
            std::unique_ptr<IDatabaseConnection> conn = std::move(connections.front());
            connections.pop();
        }
    }

    std::unique_ptr<IDatabaseConnection> getConnection() {
        std::unique_lock<std::mutex> lock(mutex);
        condition.wait(lock, [this] {
            return !connections.empty() || connectionCreationInProgress;
        });

        if (connectionCreationInProgress) {
            condition.wait(lock, [this] { return !connections.empty(); });
        }

        std::unique_ptr<IDatabaseConnection> connection = std::move(connections.front());
        connections.pop();
        return connection;
    }

    void returnConnection(std::unique_ptr<IDatabaseConnection> connection) {
        std::unique_lock<std::mutex> lock(mutex);
        if (connections.size() < MAX_CONNECTIONS) {
            connections.push(std::move(connection));
            condition.notify_one();
        }
    }

private:
    std::string dbType;
    std::queue<std::unique_ptr<IDatabaseConnection>> connections;
    std::mutex mutex;
    std::condition_variable condition;
    bool connectionCreationInProgress = false;

    void createConnectionAndAddToPool() {
        if (dbType == "MySQL") {
            std::unique_ptr<IDatabaseConnection> conn = std::make_unique<MySQLConnection>();
            connections.push(std::move(conn));
        } else if (dbType == "PostgreSQL") {
            std::unique_ptr<IDatabaseConnection> conn = std::make_unique<PostgreSQLConnection>();
            connections.push(std::move(conn));
        }
        condition.notify_one();
    }
};

// Factory Method class updated to use Connection Pool
class DatabaseConnectionFactory {
public:
    static std::unique_ptr<IDatabaseConnection> createConnection(const std::string& dbType) {
        static ConnectionPool pool(dbType);
        return pool.getConnection();
    }
};

int main() {
    try {
        std::string dbType = "PostgreSQL";

        std::unique_ptr<IDatabaseConnection> conn1 = DatabaseConnectionFactory::createConnection(dbType);
        std::cout << conn1->executeQuery("SELECT * FROM users") << std::endl;

        DatabaseConnectionFactory::createConnection(dbType)->executeQuery("SELECT * FROM users");
        DatabaseConnectionFactory::createConnection(dbType)->executeQuery("SELECT * FROM users");

        conn1->executeQuery("SELECT * FROM users");

        // Return connections to the pool
        DatabaseConnectionFactory::createConnection(dbType);
        DatabaseConnectionFactory::createConnection(dbType);

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}

