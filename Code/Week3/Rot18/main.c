#include "rot18.h"

void rot(char str[]);
void test(void);
void your_tests(void);

int main(void){
    test();
    return 0;
}

void test(void){
    char str[100];
    strcpy(str, "Hello, World!");
    rot(str);
    assert(strcmp(str, "Uryyb, Jbeyq!") == 0);
    rot(str);
    assert(strcmp(str, "Hello, World!") == 0);
    strcpy(str, "1325");
    rot(str);
    assert(strcmp(str, "6870") == 0);

    your_tests();

}
