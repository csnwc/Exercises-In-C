#include "wordle.h"

int main(void) {
    char word1[6] = "HELLO";
    char word2[6] = "WORLD";

    // 'L' is green, 'O' is yellow
    assert(num_greens(word1, word2) == 1);
    assert(num_yellows(word1, word2) == 1);

    strcpy(word1, "APPLE");
    strcpy(word2, "ALLEY");

    // 'A' is green, 'L' and 'E' are yellow
    assert(num_greens(word1, word2) == 1);
    assert(num_yellows(word1, word2) == 2);

    // Should give same result if answer and guess swapped
    assert(num_greens(word2, word1) == 1);
    assert(num_yellows(word2, word1) == 2);

    test();

    return 0;
}
