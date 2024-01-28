#include <iostream>
#include <bitset>

int main() {
    int x = 42;
    char* c = (char*)&x;
    printf("%d \n", c[0]);
    printf("%d \n", c[1]);
    printf("%d \n", c[2]);
    printf("%d \n", c[3]);


    return 0;
}



 