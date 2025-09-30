#include "wordle.h"

int num_greens(char answer[], char guess[]){
	int greens;
	for (int i = 0; i <= 5; i++){
		if (guess[i] == answer[i]) greens++;
	}
	return greens;
}

int num_yellows(char answer[], char guess[]){
	int yellows;
	for (int i = 0; i <= 5; i++){
		if (guess[i] == answer[i])
        {guess[i] = '*';
		answer[i] = '*';}
	}
	for (int i = 0; i <= 5; i++){
		if (guess[i] != '*'){
			for (int j = 0; j < 5; j++){
				if (answer[j] != '*' && guess[i] == answer[j]){
					yellows++;
					answer[j] = '*';
					break;
				}
			}
		}
	}
	return yellows;
}

void test(void){
}
