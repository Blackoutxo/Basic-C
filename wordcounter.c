#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define LINE_LENGTH 1024

int main() {
    FILE *filePointer = fopen("repeated.txt", "r");

    if (filePointer == NULL)
    {
        perror("ERROR");
    }

    char buffer[LINE_LENGTH];
    char currentWord[LINE_LENGTH];
    char longestWord[LINE_LENGTH];
    int lines = 0, words = 0;
    int maxLen = 0, currentLen = 0;
    char lastChar = ' ';
    

    while(fgets(buffer, sizeof(buffer), filePointer) != NULL) {
        lines++;

        for(size_t i = 0; buffer[i] != '\0'; i++) {
            const char current = buffer[i];

            if (isalpha(buffer[i])) {
                currentWord[currentLen] = buffer[i];
                currentLen++;
            } else {
                words++;
                currentWord[currentLen] = '\0';

                if (currentLen > maxLen) {
                    maxLen = currentLen;
                    strcpy(longestWord, currentWord);
                }
                currentLen = 0;                
            }
        }

    }

    printf("Words : %d\n", words);
    printf("Longest word: %s", longestWord);

    return 0;
}