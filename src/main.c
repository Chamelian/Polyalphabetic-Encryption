#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

const int SIZE_OF_ALPHABET = 96;
const int ALPHABET_COUNT = 5;
const char alphabet[] = {
    'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
    'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
    '0','1','2','3','4','5','6','7','8','9','!','@','#','$','%','^','&','*','(',')','-','_','=','+','[','{',
    ']','}',';',':','\'','"',',','<','.','>','/','?','\\','|','`','~',' ','\n'
};

// I use '\000' instead of NULL since the compiler complains even though I think it's fine


char* _genRandomAlphabet(char alphabet[SIZE_OF_ALPHABET], char returnAlphabet[SIZE_OF_ALPHABET]) {
    char tempAlphabet[SIZE_OF_ALPHABET];
    int currentAlphabetSize = SIZE_OF_ALPHABET;

    memcpy(tempAlphabet, alphabet, sizeof(tempAlphabet));

    for (int i = 0; i < SIZE_OF_ALPHABET; i++) {
        char workingAlphabet[currentAlphabetSize];
        int randInt = rand() % currentAlphabetSize;

        // Copys all Non-Null characters into the working array and set the selected random character as null in the temp array.
        // This is to prevent repetitions.
        for (int j = 0, k = 0; k < currentAlphabetSize; j++, k++) {
            if (tempAlphabet[j] != '\000') {
                workingAlphabet[k] = tempAlphabet[j];
            } else {
                k -= 1;
            }
        }
        for (int j = 0; j < SIZE_OF_ALPHABET; j++) {
            if (tempAlphabet[j] == workingAlphabet[randInt]) {
                tempAlphabet[j] = '\000';
                break;
            }
        }

        returnAlphabet[i] = workingAlphabet[randInt];

        currentAlphabetSize -= 1;
    }

    return (char*) returnAlphabet;
}

char* _stringEncoder(char message[]) {

}

char* _stringDecoder(char message[]) {

}

FILE* __initFile(char filePath[], char* mode) {
    FILE* file;
    file = fopen(filePath, mode);
    if (file == NULL) {
        printf("\nERROR: File Not Found\n");
        return NULL;
    }
    return file;
}

void _fileEncoder(
    char readFilePath[],
    char writeFilePath[],
    char alphabet[SIZE_OF_ALPHABET],
    char lemon[ALPHABET_COUNT][SIZE_OF_ALPHABET],
    char alphabetOrderKey[]
) {
    FILE* fileToEncode = __initFile(readFilePath, "r");
    FILE* outputFile = __initFile(writeFilePath, "w");

    int currentAlphabet = 0;

    while (true) {
        char character = (char) fgetc(fileToEncode);
        if (character == EOF || character == '\000') {
            break;
        }

        for (int i = 0; i < SIZE_OF_ALPHABET; i++) {
            if (character == alphabet[i]) {
                // This is kinda convoluted. Casting char to int returns the ascii code rather than the
                // actual value in the string, so I have to subtract 48 (The ascii code of '0') in order
                // to get the correct value.
                fprintf(outputFile, "%c", lemon[((int)alphabetOrderKey[currentAlphabet]-(int)'0')-1][i]);
                break;
            }
        }

        if (currentAlphabet >= ALPHABET_COUNT - 1) {
            currentAlphabet -= ALPHABET_COUNT - 1;
        } else {
            currentAlphabet += 1;
        }
    }

    fclose(fileToEncode);
    fclose(outputFile);
}

void _fileDecoder(
    char readFilePath[],
    char writeFilePath[],
    char alphabet[SIZE_OF_ALPHABET],
    char lemon[ALPHABET_COUNT][SIZE_OF_ALPHABET],
    char alphabetOrderKey[]
) {
    FILE* fileToDecode = __initFile(readFilePath, "r");
    FILE* outputFile = __initFile(writeFilePath, "w");

    int currentAlphabet = 0;

    while (true) {
        char character = (char) fgetc(fileToDecode);
        if (character == EOF || character == '\000') {
            break;
        }

        for (int i = 0; i < SIZE_OF_ALPHABET; i++) {
            if (character == lemon[((int)alphabetOrderKey[currentAlphabet]-(int)'0')-1][i]) {
                fprintf(outputFile, "%c", alphabet[i]);
                break;
            }
        }

        if (currentAlphabet >= ALPHABET_COUNT - 1) {
            currentAlphabet -= ALPHABET_COUNT - 1;
        } else {
            currentAlphabet += 1;
        }
    }

    fclose(fileToDecode);
    fclose(outputFile);
}




void main() {
    // Time is kinda shit for randomness and I can't think of a better way to generate the seed.
    // Keyboard mashing the primary key :3 (same for secondary key. Just choose a good number idk)
    int seed = 1; // Primary Key
    // Determines the order the alphabets are used in. Only supports the value of ALPHABET_COUNT right now
    // I'll probably program it so that it can be of any length. It should be as simple as "sizeof(alphabetOrderKey) - 1"
    char alphabetOrderKey[] = "11111"; // Secondary Key ("12345", "41325", "11111", etc.)
    printf("Seed (Primary Key): %d\n", seed);
    srand(seed);



    char lemon[ALPHABET_COUNT][SIZE_OF_ALPHABET];

    for (int i = 0; i < ALPHABET_COUNT; i++) {
        char returnedAlphabet[SIZE_OF_ALPHABET];
        memcpy(lemon[i], _genRandomAlphabet(alphabet, returnedAlphabet), sizeof(alphabet));
    }

    // Need to program interactive sessions (terminal input / output)

    // _fileEncoder(
    //     "/absolute/path/to/input(Decoded)/file.txt",
    //     "/absolute/path/to/output(Encoded)/file.txt",
    //     alphabet,
    //     lemon,
    //     alphabetOrderKey
    // );
    // _fileDecoder(
    //     "/absolute/path/to/input(Encoded)/file.txt",
    //     "/absolute/path/to/output(Decoded)/file.txt",
    //     alphabet,
    //     lemon,
    //     alphabetOrderKey
    // );
}