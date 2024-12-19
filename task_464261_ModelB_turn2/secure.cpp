#include <cstring>

struct Configuration {
    char username[16];
    char password[16];
};

void loadConfiguration(Configuration* config, const char* username, const char* password) {
    strncpy(config->username, username, sizeof(config->username) - 1);
    strncpy(config->password, password, sizeof(config->password) - 1);

    config->username[sizeof(config->username) - 1] = '\0';
    config->password[sizeof(config->password) - 1] = '\0';
}

int main() {
    Configuration config;
    const char* username = "myLongUsername";
    const char* password = "verySecretPassword123";

    loadConfiguration(&config, username, password);

    size_t usernameLen = strnlen(config.username, sizeof(config.username));
    size_t passwordLen = strnlen(config.password, sizeof(config.password));

    printf("Username: %.*s (Length: %zu)\n", (int)usernameLen, config.username, usernameLen);
    printf("Password: %.*s (Length: %zu)\n", (int)passwordLen, config.password, passwordLen);

    return 0;
}
