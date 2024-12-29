#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MICROSERVICE_NAME_MAX_LEN 32

struct Transaction {
    char request_id[256];
    char source_account[64];
    char destination_account[64];
    double amount;
};

void log_api_call(char* microservice_name, const struct Transaction* transaction) {
    if (microservice_name == NULL || transaction == NULL) {
        fprintf(stderr, "Error: log_api_call: Invalid argument\n");
        return;
    }

    // Ensure microservice name doesn't overflow the buffer
    if (strlen(microservice_name) >= MICROSERVICE_NAME_MAX_LEN) {
        fprintf(stderr, "Error: log_api_call: Microservice name too long\n");
        return;
    }

    fprintf(stderr, "[%s] API CALL: %s \n", microservice_name, transaction->request_id);
    fprintf(stderr, "[%s] Source Account: [************]%s\n", microservice_name,
        transaction->source_account + strlen(transaction->source_account) - 4);
    fprintf(stderr, "[%s] Destination Account: [************]%s\n", microservice_name,
        transaction->destination_account + strlen(transaction->destination_account) - 4);
    fprintf(stderr, "[%s] Transaction Amount: %.2lf\n\n", microservice_name, transaction->amount);
}

int main() {
    struct Transaction transaction = {
        .request_id = "REQ1234567890ABCDEF",
        .source_account = "ACC12345678901234567",
        .destination_account = "ACC98765432109876543",
        .amount = 100.00
    };

    log_api_call("payment-service", &transaction);
    log_api_call("authorization-service", &transaction);

    return 0;
}

