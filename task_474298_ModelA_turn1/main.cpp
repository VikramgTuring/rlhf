#include <iostream>
#include <string>

class PaymentService {
public:
    void processPayment(const std::string &userId, double amount) {
        printf("[PaymentService] Processing payment of $%.2f for user %s...\n", amount, userId.c_str());
        // Simulate some processing logic
        if (amount > 1000) {
            printf("[PaymentService] Warning: High-value payment detected!\n");
        }
    }
};

class FraudDetectionService {
public:
    bool checkFraud(const std::string &userId, double amount) {
        printf("[FraudDetectionService] Checking fraud for user %s on amount $%.2f...\n", userId.c_str(), amount);
        // Simplified fraud detection logic
        return amount > 1000; // Simulating a fraud condition
    }
};

class NotificationService {
public:
    void sendNotification(const std::string &userId, const std::string &message) {
        printf("[NotificationService] Notifying user %s: %s\n", userId.c_str(), message.c_str());
    }
};

class DigitalPaymentSystem {
private:
    PaymentService paymentService;
    FraudDetectionService fraudService;
    NotificationService notificationService;

public:
    void makePayment(const std::string &userId, double amount) {
        paymentService.processPayment(userId, amount);

        if (fraudService.checkFraud(userId, amount)) {
            notificationService.sendNotification(userId, "Fraud detected! Payment has been blocked.");
            printf("[DigitalPaymentSystem] Payment blocked due to potential fraud for user %s.\n", userId.c_str());
        } else {
            notificationService.sendNotification(userId, "Payment processed successfully.");
            printf("[DigitalPaymentSystem] Payment of $%.2f successful for user %s.\n", amount, userId.c_str());
        }
    }
};

int main() {
    DigitalPaymentSystem system;
    system.makePayment("user123", 500);  // Normal payment
    system.makePayment("user123", 1500); // Potential fraud payment

    return 0;
}
