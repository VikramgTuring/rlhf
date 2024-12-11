#include <iostream>
#include <string>
#include <vector>
#include <memory>

// Observer Pattern
class Subject {
public:
    using ObserverPtr = std::shared_ptr<Observer>;

    virtual void attach(ObserverPtr observer) = 0;
    virtual void notifyAll() = 0;
    virtual ~Subject() = default;
};

class Observer {
public:
    virtual ~Observer() = default;
    virtual void update() = 0;
};

// Mediator Pattern
class ChatServer : public Subject {
private:
    std::vector<ObserverPtr> clients;

public:
    void attach(ObserverPtr observer) override {
        clients.push_back(observer);
    }

    void notifyAll() override {
        for (const auto& client : clients) {
            client->update();
        }
    }

    void sendMessage(const std::string& message, const std::string& sender) {
        std::cout << "Server: Received message from " << sender << ": " << message << std::endl;
        notifyAll();
    }
};

class ChatClient : public Observer {
private:
    ChatServer& server;
    std::string username;

public:
    ChatClient(ChatServer& server, const std::string& username) : server(server), username(username) {
        server.attach(std::make_shared<ChatClient>(*this));
    }

    void update() override {
        std::cout << "Client " << username << ": Received message from another client: " << server.getLatestMessage() << std::endl;
    }

    void sendMessage(const std::string& message) {
        server.sendMessage(message, username);
    }
};

int main() {
    ChatServer server;

    ChatClient client1(server, "Alice");
    ChatClient client2(server, "Bob");

    client1.sendMessage("Hello, Bob!");
    client2.sendMessage("Hi Alice, how are you?");

    return 0;
}
