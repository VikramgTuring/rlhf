#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_LEN 100

typedef struct {
    char payment_id[MAX_LEN];
    char user_id[MAX_LEN];
    double amount;
    char status[MAX_LEN];
} payment_t;

// User Authentication Microservice
payment_t* authenticate_user(const char* user_id, const char* password) {
    srand(time(NULL));
    int random_num = rand() % 100;

    if (random_num < 70) {
        printf("[Authentication] User %s authenticated successfully.\n", user_id);
        payment_t* payment = malloc(sizeof(payment_t));
        strcpy(payment->user_id, user_id);
        strcpy(payment->payment_id, "PAY123456");
        payment->amount = 0;
        strcpy(payment->status, "Pending");
        return payment;
    } else {
        printf("[Authentication] User %s authentication failed.\n", user_id);
        return NULL;
    }
}

// Payment Processing Microservice
void process_payment(payment_t* payment) {
    if (payment) {
        printf("[Payment Processing] Processing payment %s for user %s...\n", payment->payment_id, payment->user_id);
        srand(time(NULL));
        int random_num = rand() % 100;

        if (random_num < 90) {
            payment->amount = 100.00;
            strcpy(payment->status, "Successful");
            printf("[Payment Processing] Payment %s of $%.2f successful.\n", payment->payment_id, payment->amount);
        } else {
            strcpy(payment->status, "Failed");
            printf("[Payment Processing] Payment %s failed.\n", payment->payment_id);
        }
    } else {
        printf("[Payment Processing] Payment request failed: Invalid payment details.\n");
    }
}

// Notification Microservice
void send_notification(payment_t* payment) {
    if (payment) {
        printf("[Notification] Sending notification for payment %s: Status - %s\n", payment->payment_id, payment->status);
    } else {
        printf("[Notification] Notification failed: Invalid payment details.\n");
    }
}

int main() {
    const char* user_id = "user456";
    const char* password = "password";

    payment_t* payment = authenticate_user(user_id, password);

    if (payment) {
        process_payment(payment);
        send_notification(payment);

        printf("[System] Payment %s for user %s completed. Status: %s\n", payment->payment_id, payment->user_id, payment->status);

        free(payment);
    }

    return 0;
}

