#include <iostream>

using namespace std;

int secure_bitwise_and(int alice_secret, int bob_secret) {
    // Alice and Bob share the result of XORing their secrets
    int shared_xor = alice_secret ^ bob_secret;

    // Alice calculates (A AND B) = (A XOR (A XOR B))
    int alice_part = alice_secret ^ shared_xor;

    // Bob calculates (A AND B) = (B XOR (A XOR B))
    int bob_part = bob_secret ^ shared_xor;

    // Now, both Alice and Bob have the result of (A AND B)
    return alice_part;
}

int main() {
    int alice_secret = 13; // Alice's secret: 1101 in binary
    int bob_secret = 7;    // Bob's secret:  0111 in binary

    cout << "Alice's secret: " << alice_secret << " (binary: " << bitset<4>(alice_secret) << ")" << endl;
    cout << "Bob's secret:   " << bob_secret << " (binary: " << bitset<4>(bob_secret) << ")" << endl;

    int result = secure_bitwise_and(alice_secret, bob_secret);

    cout << "Result of (Alice's secret AND Bob's secret): " << result << " (binary: " << bitset<4>(result) << ")" << endl;

    return 0;
}
