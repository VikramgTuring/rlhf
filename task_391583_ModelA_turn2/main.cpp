#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <stdexcept>

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

// Connection Pool Class
class ConnectionPool {
public:
    ConnectionPool(const std::string& dbType, size_t poolSize) : dbType(dbType) {
        for (size_t i = 0; i < poolSize; ++i) {
            if (dbType == "MySQL") {
                connections.push(std::make_unique<MySQLConnection>());
            } else if (dbType == "PostgreSQL") {
                connections.push(std::make_unique<PostgreSQLConnection>());
            } else {
                throw std::runtime_error("Invalid database type");
            }
        }
    }

    std::unique_ptr<IDatabaseConnection> acquire() {
        std::unique_lock<std::mutex> lock(mutex);
        condVar.wait(lock, [this] { return !connections.empty(); });
        auto connection = std::move(connections.front());
        connections.pop();
        return connection;
    }

    void release(std::unique_ptr<IDatabaseConnection> connection) {
        std::unique_lock<std::mutex> lock(mutex);
        connections.push(std::move(connection));
        condVar.notify_one();
    }

private:
    std::string dbType;
    std::queue<std::unique_ptr<IDatabaseConnection>> connections;
    std::mutex mutex;
    std::condition_variable condVar;
};

// Usage Example
int main() {
    const std::string dbType = "PostgreSQL";
    ConnectionPool pool(dbType, 5); // Create a pool of 5 connections

    // Simulate a request handling logic:
    for (int i = 0; i < 10; ++i) {
        try {
            auto connection = pool.acquire();
            std::cout << connection->executeQuery("SELECT * FROM users") << std::endl;
            pool.release(std::move(connection)); // Release after use
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    return 0;
}
