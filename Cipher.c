#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char *encrypt();                             // this method will encrypt our plan text accourding to the key
void fillTheArray();                         // this mehtod will fill the 5*5 array with the english litters
bool checkMatchRow(char first, char second); // checking if the coupels of the letters are in the same row or column in the array
void encryptRaw(Letters *text, int plainTextSize); 

// in this structure we will handel the whole english letters
typedef struct
{
    char *letter1;
    char *letter2;
} Letters;

const int sizeOfArrayLetters = 5;
Letters **letters; // this is Array struct, where we will store our english letters
char plainText[500];
char key[25];

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

char *encrypt()
{

    int keyNum = strlen(key);
    int keyCount = 0;
    int plainTextSize = strlen(plainText);
    Letters *text[plainTextSize]; // this is will superate the text to Duets
    fillTheArray();
    // filling the array with the key and re arrange it
    for (int i = 0; i < sizeOfArrayLetters; i++)
    {
        for (int j = 0; j < sizeOfArrayLetters; j++)
        {
            if (keyCount < keyNum)
            {
                letters[i][j].letter1[0] = key[keyCount];
                keyCount++;
            }        }
    }

//suprate the plane text in the text struct , as couple and prevent the duplication 

    int i = 0;
    while (i < plainTextSize)
    {
        if (plainText[i] == plainText[i + 1])
        {
            text[i]->letter1[0] = plainText[i];
            text[i]->letter2[0] = 'x';
            i++;
        }
        else
        {
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
   
}

void fillTheArray()
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
                    letters[i][j].letter1[0] = 'i';
                    letters[i][j].letter2[0] = 'j';
                    englishLittersCount++;
                }
                else
                {
                    letters[i][j].letter1[0] = engilshLitters[englishLittersCount];
                    englishLittersCount++;
                }
            }
        }
    }
}

bool checkMatchRow(char first, char second)
{
    char first = first;
    char second = second;
    bool matched = false;
    for (int r = 0; r < sizeOfArrayLetters; r++)
    {
        for (int c = 0; c < sizeOfArrayLetters; c++)
        {
            if (first == letters[r][c].letter1 || letters[r][c].letter2)
            {
                for (int i = c; i < sizeOfArrayLetters; i++)
                {
                    if (second == letters[r][i].letter1 || letters[r][i].letter2)
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

void encryptRaw(Letters *text[], int plainTextSize)
{
    int n = 0;
    int sizeOfText = plainTextSize;
    while (n < sizeOfText)
    {
        char first = text[n]->letter1[0];
        char second = text[n]->letter2[0];
        bool matched = checkMatchRow(first, second);

        if (matched == true)
        {
            for (int i = 0; i < sizeOfArrayLetters; i++)
            {
                for (int j = 0; j < sizeOfArrayLetters; j++)
                {   
                    
                    if (letters[i][j].letter1[0] == text[n]->letter1[0])
                    { // check the mode later for case 4%4 == 0
                        if (j % 4 == 0)
                        {
                            text[n]->letter1[0] = letters[i][j % 4].letter1[0];
                        }
                        else
                        {
                            text[n]->letter1[0] = letters[i][j + 1].letter1[0];
                        }
                    }
                    else if (letters[i][j].letter2[0] == text[n]->letter1[0])
                    {
                         if (j % 4 == 0)
                        {
                            text[n]->letter1[0] = letters[i][j % 4].letter1[0];
                        }
                        else
                        {
                            text[n]->letter1[0] = letters[i][j + 1].letter1[0];
                        }
                    }
                   
                    if (letters[i][j].letter1[0] == text[n]->letter2[0])
                    {
                        if (j % 4 == 0)
                        {
                            text[n]->letter2[0] = letters[i][j % 4].letter2;
                        }
                        else
                        {
                            text[n]->letter2[0] = letters[i][j % 4 + 1].letter2[0];
                        }
                    }
                 
                    else if (letters[i][j].letter2[0] == text[n]->letter2[0])
                    {
                        if (j % 4 == 0)
                        {
                            text[n]->letter2[0] = letters[i][j % 4].letter2;
                        }
                        else
                        {
                            text[n]->letter2[0] = letters[i][j % 4 + 1].letter2[0];
                        }
                    }
                }
            }
        }
    }
}
