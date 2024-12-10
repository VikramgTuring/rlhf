#include<cstdio>

#include<cstring>

int main() {

    char buf[10]; // Buffer with size 10 bytes

    printf("Enter a string: ");

    fgets(buf, sizeof(buf), stdin); // or strcpy/strncpy without bound check

    return 0;

}
