#include <iostream>
#include <memory>
#include <pqxx/pqxx> // PostgreSQL C++ library
#include <string>

// Singleton class to manage a database connection
class DatabaseConnection {
public:
    static DatabaseConnection& getInstance() {
        static DatabaseConnection instance;
        return instance;
    }

    pqxx::connection& getConnection() {
        return *conn;
    }

private:
    DatabaseConnection() {
        conn = std::make_unique<pqxx::connection>("dbname=test user=postgres password=secret");
        if (!conn->is_open()) {
            throw std::runtime_error("Can't open database");
        }
    }

    ~DatabaseConnection() {
        conn->disconnect();
    }

    std::unique_ptr<pqxx::connection> conn;

    // Prevent copy and assignment
    DatabaseConnection(const DatabaseConnection&) = delete;
    void operator=(const DatabaseConnection&) = delete;
};

// Data Access Object (DAO) for User entity
class UserDAO {
public:
    UserDAO() = default;

    void createUser(const std::string& username, const std::string& email) {
        pqxx::work transaction(DatabaseConnection::getInstance().getConnection());

        transaction.exec0("INSERT INTO users (username, email) VALUES (" +
                          transaction.quote(username) + ", " +
                          transaction.quote(email) + ");");
        transaction.commit();
    }

    void getUser(const std::string& username) {
        pqxx::work transaction(DatabaseConnection::getInstance().getConnection());
        pqxx::result result = transaction.exec("SELECT * FROM users WHERE username = " + transaction.quote(username));

        if (result.empty()) {
            std::cout << "User not found" << std::endl;
        } else {
            std::cout << "User: " << result[0][1].c_str() << ", Email: " << result[0][2].c_str() << std::endl;
        }
        transaction.commit();
    }
};

int main() {
    UserDAO userDAO;
    
    // Create a new user
    userDAO.createUser("john_doe", "john@example.com");

    // Fetch the user
    userDAO.getUser("john_doe");

    return 0;
}
