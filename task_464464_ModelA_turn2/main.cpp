#include <iostream>
#include <bitset>

using namespace std;

// Define transaction status flags using bitwise
enum TransactionFlags {
    NONE      = 0b0000,    // No flags
    PENDING   = 0b0001,    // Transaction is pending
    COMPLETED = 0b0010,    // Transaction is completed
    FAILED    = 0b0100,    // Transaction has failed
    REFUNDED  = 0b1000     // Transaction has been refunded
};

// Function to set a transaction flag
void setFlag(int &flags, TransactionFlags flag) {
    flags |= flag; // Set the flag using bitwise OR
}

// Function to clear a transaction flag
void clearFlag(int &flags, TransactionFlags flag) {
    flags &= ~flag; // Clear the flag using bitwise AND
}

// Function to check if a transaction flag is set
bool isFlagSet(int flags, TransactionFlags flag) {
    return (flags & flag) != 0; // Check if the flag is set using bitwise AND
}

int main() {
    int transactionStatus = TransactionFlags::NONE; // Initially no flags

    // Set some flags
    setFlag(transactionStatus, TransactionFlags::PENDING);
    cout << "Transaction Status: " << bitset<4>(transactionStatus) << endl; // 0001

    setFlag(transactionStatus, TransactionFlags::COMPLETED);
    cout << "Transaction Status: " << bitset<4>(transactionStatus) << endl; // 0011

    // Check flags
    cout << "Is Pending? " << (isFlagSet(transactionStatus, TransactionFlags::PENDING) ? "Yes" : "No") << endl; // Yes
    cout << "Is Failed? " << (isFlagSet(transactionStatus, TransactionFlags::FAILED) ? "Yes" : "No") << endl; // No

    // Clear a flag
    clearFlag(transactionStatus, TransactionFlags::PENDING);
    cout << "Transaction Status after clearing PENDING: " << bitset<4>(transactionStatus) << endl; // 0010

    return 0;
}
