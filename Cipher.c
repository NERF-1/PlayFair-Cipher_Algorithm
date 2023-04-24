//Greatings, This program created by Abdulqadir Solayman Ali Alzway 
//ID = 5046
// I started working on it in march of 2023
//This is progrma is using playfair algorithm to encrypt the data 
//This program has written in c language 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
typedef struct
{
    char *letter1;
    char *letter2;
} Letters;

const int sizeOfArrayLetters = 5;
Letters **letters; // this is Array struct, where we will store our english letters
char plainText[500];
char key[25];


char *encrypt(void);                             // this method will encrypt our plan text accourding to the key
void fillTheArray(void);                         // this mehtod will fill the 5*5 array with the english litters
bool checkMatchRow(char first, char second); // checking if the coupels of the letters are in the same row or column in the array
bool checkMatchColumn(char first, char second); 
void encryptRaw(Letters *text[], int plainTextSize); 
void encryptColumn(Letters *text[], int plainTextSize); 
char *makeCipherText(Letters *text[]); 
void updateLetter(char* letter, char oldLetter, char newLetter); 

// in this structure we will handel the whole english letters

int main(void)
{
    // taking the planText from the user
    printf("Inter the text that you want to encrypt\n");
    scanf("%s", plainText);
    // taking the key from the user
    printf("Inter the key\n");
    scanf("%s", key);

    char *cipher = encrypt();
    printf("%s", cipher);
}

char *encrypt(void)
{

    int keyNum = strlen(key);
    int keyCount = 0;
    int plainTextSize = strlen(plainText);
    Letters *text[plainTextSize]; // this is will superate the text to Duets
    fillTheArray();
    
    // filling the array with the key and re arrange it
    // and allocating memory for struct in the text
    for (int i = 0; i < plainTextSize; i++) 
    {
        text[i] = malloc(sizeof(Letters));
    }

    for (int i = 0; i < sizeOfArrayLetters; i++)
    {
        for (int j = 0; j < sizeOfArrayLetters; j++)
        {
            if (keyCount < keyNum)
            {
                letters[i][j].letter1[0] = key[keyCount];
                keyCount++;
            }        
        }
    }

//suprate the plane text in the text struct , as couple and prevent the duplication 

    int i = 0;
    while (i < plainTextSize)
    {
       if (plainText[i] == plainText[i + 1])
        {
            text[i]->letter1 = malloc(sizeof(char));
            text[i]->letter2 = malloc(sizeof(char));
            text[i]->letter1[0] = plainText[i];
            text[i]->letter2[0] = 'x';
            i++;
        }
        else
        {
            text[i]->letter1 = malloc(sizeof(char));
            text[i]->letter2 = malloc(sizeof(char));
            text[i]->letter1[0] = plainText[i];
            if (i + 1 < plainTextSize)
            {
                text[i]->letter2[0] = plainText[i + 1];
                i += 2;
            }
        }
    }
    if (text[i - 1]->letter2 == NULL)
    {
        text[i - 1]->letter2[0] = 'z';
    }

    // encrypting the text
    encryptColumn(text, plainTextSize); 
    encryptRaw(text, plainTextSize); 
    makeCipherText(text); 

    return makeCipherText(text); 
   
}

void fillTheArray(void)
{
    letters = malloc(sizeof(Letters) * 5);

    for (int i = 0; i < 5; i++)
    {
        Letters *lett = malloc(sizeof(Letters) * 5);
        letters[i] = lett;
    }

    char *engilshLitters = "abcdefghijklmnopqrstuvwxyz";
    int englishLittersCount = 0;

    for (int i = 0; i < sizeOfArrayLetters; i++)
    {
        for (int j = 0; j < sizeOfArrayLetters; j++)
        {
            if (englishLittersCount < 26)
            {
                if (engilshLitters[englishLittersCount] == 'i')
                {   
                    letters[i][j].letter1 = malloc(sizeof(char)); 
                    letters[i][j].letter2 = malloc(sizeof(char)); 
                    letters[i][j].letter1[0] = 'i';
                    letters[i][j].letter2[0] = 'j';
                    englishLittersCount++;
                }
                else
                {   
                    letters[i][j].letter1 = malloc(sizeof(char)); 
                    letters[i][j].letter1[0] = engilshLitters[englishLittersCount];
                    englishLittersCount++;
                }
            }
        }
    }
}

bool checkMatchRow(char fir, char sec)
{
    char first = fir;
    char second = sec;
    bool matched = false;
    for (int r = 0; r < sizeOfArrayLetters; r++)
    {
        for (int c = 0; c < sizeOfArrayLetters; c++)
        {
            if (first == letters[r][c].letter1[0] || first == letters[r][c].letter2[0])
            {
                for (int i = c; i < sizeOfArrayLetters; i++)
                {
                    if (second == letters[r][i].letter1[0] || second == letters[r][i].letter2[0])
                    {
                        matched = true;
                        break;
                    }
                }
            }
        }
    }

    return matched;
}

void encryptRaw(Letters* text[], int plainTextSize)
{
    int n = 0;
    int sizeOfText = plainTextSize;

    while (n < sizeOfText)
    {
        char first = text[n]->letter1[0];
        char second = text[n]->letter2[0];
        bool matched = checkMatchRow(first, second);

        if (matched)
        {
            for (int i = 0; i < sizeOfArrayLetters; i++)
            {
                for (int j = 0; j < sizeOfArrayLetters; j++)
                {
                    updateLetter(&text[n]->letter1[0], letters[i][j].letter1[0], letters[i][j % 4].letter1[0]);
                    updateLetter(&text[n]->letter1[0], letters[i][j].letter2[0], letters[i][j + 1].letter1[0]);
                    updateLetter(&text[n]->letter2[0], letters[i][j].letter1[0], letters[i][j % 4].letter2[0]);
                    updateLetter(&text[n]->letter2[0], letters[i][j].letter2[0], letters[i][j + 1].letter2[0]);
                }
            }
            n++;
        }
        else
        {
            n += 2;
        }
    }
}

bool checkMatchColumn(char fir, char sec)
{
    char first = fir;
    char second = sec;
    bool matched = false;

    for (int c = 0; c < sizeOfArrayLetters; c++)
    {
        for (int r = 0; r < sizeOfArrayLetters; r++)
        {
            if (first == letters[c][r].letter1[0] || first == letters[c][r].letter2[0])
            {
                for (int i = c; i < sizeOfArrayLetters; i++)
                {
                    if (second == letters[r][i].letter1[0] || second == letters[r][i].letter2[0])
                    {
                        matched = true;
                        break;
                    }
                }
            }
        }
    }

    return matched;
}

void encryptColumn(Letters *text[], int plainTextSize)
{
    if (plainTextSize % 2 != 0) {
        // plaintext size must be even
        return;
    }

    const int rows = 4;
    const int cols = 4;

    for (int pairIdx = 0; pairIdx < plainTextSize; pairIdx += 2)
    {
        char first = text[pairIdx]->letter1[0];
        char second = text[pairIdx]->letter2[0];
        bool matched = checkMatchColumn(first, second);

        if (matched)
        {
            for (int row = 0; row < rows; row++)
            {
                for (int col = 0; col < cols; col++)
                {
                    if (letters[row][col].letter1[0] == first)
                    {
                        if (col % 4 == 0)
                        {
                            text[pairIdx]->letter1[0] = letters[row % 4][col].letter1[0];
                        }
                        else
                        {
                            text[pairIdx]->letter1[0] = letters[row + 1][col].letter1[0];
                        }
                    }
                    else if (letters[row][col].letter2[0] == first)
                    {
                        if (col % 4 == 0)
                        {
                            text[pairIdx]->letter1[0] = letters[row % 4][col].letter1[0];
                        }
                        else
                        {
                            text[pairIdx]->letter1[0] = letters[row + 1][col].letter1[0];
                        }
                    }

                    if (letters[row][col].letter1[0] == second)
                    {
                        if (col % 4 == 0)
                        {
                            text[pairIdx + 1]->letter2[0] = letters[row % 4][col].letter2[0];
                        }
                        else
                        {
                            text[pairIdx + 1]->letter2[0] = letters[row + 1][col].letter2[0];
                        }
                    }
                    else if (letters[row][col].letter2[0] == second)
                    {
                        if (col % 4 == 0)
                        {
                            text[pairIdx + 1]->letter2[0] = letters[row % 4][col].letter2[0];
                        }
                        else
                        {
                            text[pairIdx + 1]->letter2[0] = letters[row + 1][col].letter2[0];
                        }
                    }
                }
            }
        }
    }
}


char *makeCipherText(Letters *text[])
{
    char *cipehrText = malloc(sizeof(char)*500); 
    int LengthOfText = strlen(plainText); 

    for(int i = 0; i < LengthOfText; i++)
    {
        cipehrText[i] = text[i]->letter1[0]; 
    }

    return cipehrText; 
}

void updateLetter(char* letter, char oldLetter, char newLetter)
{
    if (*letter == oldLetter)
    {
        *letter = newLetter;
    }
}