//Greatings, This program created by Abdulqadir Solayman Ali Alzway
//ID = 5046
// I started working on it in march of 2023
//This progrm is using playfire algorithm to encrypt the data
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


int plainTextSize;
const int sizeOfArrayLetters = 5;
Letters **letters; // this is Array struct, where we will store our english letters
char plainText[500]; // the plain text that the user will enter
char key[25]; // it is the key that the user will enter
Letters *text; // this is will superate the text to Duets
char cipherText[500]; // this is the encrypted Text

// in this structure we will handle the whole english letters:

bool hasDuplicateLetters(void); // to check if we have a duplicated letter in the key
void findEmptyPlace(int *row, int *col); // this method will find an empty place in letters array
bool* hasSeen(void); // this array will check the key letters in letters array as seen in array bool and return that array to use it in fillTheArrayLetters method
void allocateMemory (void); // this method to dynamicly allocate a memory for array letters
void encrypt(void); // this will handel the whole encryption process, Using the following methods
void fillTheArrayLetters(void); // this mehtod will fill the 5*5 array AKA (letters) with the english litters
void fillTheArrayKey(void);  // filling the array with the key and re arrange it
int separatePlaneText(void); //separate the plane text in the text array struct , as couple and prevent the duplication and return the TextSize of the Text Array
bool checkMatchRow (char first, char second); // checking if the coupels of the letters are in the same row in the array
bool checkMatchColumn (char first, char second);// checking if the first and second letters are in the same column
void encryptRow (char first, char second); // encrypt the letters if they are in the same row accourding to play fire algorithm row case
void encryptColumn (char first, char second); // encrypt the letters if they are in the same column accourding to play fire algorithm column case
void encryptSquare (char first, char second); // encypt the lettrers if they are not in same column or row accourding to play fire algorithm third case
bool updateLetter (char letter, char oldLetter, char newLetter); // this method will update the lettrs from the plain text to the ciphre text, accourding to the cases above


int main(void)
{
    // taking the planText from the user
    printf("Enter The Text That You Want To Encrypt:\n");
    scanf("%s", plainText);
    // calculate the size of plainText
    plainTextSize = strlen(plainText);
    printf("your text size =  %i\n\n", plainTextSize);
    // taking the key from the user
    do{
        printf("Now Enter The Key:\n");
        scanf("%s", key);
        printf("\n");

    } while(hasDuplicateLetters());

    encrypt(); // this will encrypt and do everything for us

    printf("Your Cipher Text Is: \n%s\n", cipherText); // this is our cipherText

}

void encrypt(void)
{
    allocateMemory();
    fillTheArrayKey();
    fillTheArrayLetters();

    memset(cipherText,'\0', 500);

    int TextSize = separatePlaneText();

    const int rows = sizeOfArrayLetters;
    const int cols = sizeOfArrayLetters;

    for (int Idx = 0; Idx < TextSize; Idx++)
    {
        char first = text[Idx].letter1[0];
        char second = text[Idx].letter2[0];

        bool matchedColumn = checkMatchColumn (first, second);
        bool matchedRaw = checkMatchRow (first, second);

        if(matchedColumn)
        {
            encryptColumn (first, second);
            continue;
        }
        else if (matchedRaw)
        {
            encryptRow (first, second);
            continue;
        }
        else
        {
            encryptSquare (first, second);
        }

    }

    printf("\n:");
}


void fillTheArrayLetters (void)
{
    char *englishLetters = "abcdefghijklmnopqrstuvwxyz";
    int englishLettersCount = 0;
    bool *seen = hasSeen(); // this will check the key letters in array letters and set the seen letters of them
    int seenIdx = 0;

    for (int i = 0; i < sizeOfArrayLetters; i++)
    {
        for (int j = 0; j < sizeOfArrayLetters; j++)
        {
            if (englishLettersCount < 26)
            {
                seenIdx = englishLetters[englishLettersCount] - 'a';

                 if(seen[seenIdx])
                {
                    englishLettersCount++;
                    continue;
                }

                int row = 0;
                int col = 0;
                findEmptyPlace(&row, &col);

                if (englishLetters[englishLettersCount] == 'i')
                {
                    letters[row][col].letter1[0] = 'i';
                    letters[row][col].letter2[0] = 'j';
                    englishLettersCount += 2;
                }
                else
                {
                    letters[row][col].letter1[0] = englishLetters[englishLettersCount];
                    englishLettersCount++;
                }
            }
        }
    }

    for(int i = 0; i<5; i++)
    {
        for(int j = 0; j<5; j++)
        {
            printf("%c ",letters[i][j].letter1[0]);
        }
        printf("\n");
    }

}

bool checkMatchRow (char fir, char sec)
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
                for (int i = 0; i < sizeOfArrayLetters; i++)
                {
                    if (second == letters[r][i].letter1[0] || second == letters[r][i].letter2[0])
                    {
                        matched = true;
                        return matched;
                    }
                }
            }
        }
    }

    return matched;
}

void encryptRow (char first, char second)
{
    const int rows = sizeOfArrayLetters;
    const int cols = sizeOfArrayLetters;

    bool first1 = false;
    bool first2 = false;
    bool second1 = false;
    bool second2 = false;

    for (int col = 0; col < cols; col++) // this algorithm is not efficient, it is butter to use hash table, I was just busy to do it
    {   // another thing dont focuse in the name of col and row int he implementation , it might makes you lost , so instade focuse in the place of the index
        for (int row = 0; row < rows; row++)
        {
          first1 = updateLetter(first, letters[col][row].letter1[0], letters[col][row % 4].letter1[0]);

          if(!first1)
          {
            if(row + 1 < rows)
            {
                first2 = updateLetter(first, letters[col][row].letter1[0], letters[col][row + 1].letter1[0]);
            }
          }

          second1 = updateLetter(second, letters[col][row].letter1[0], letters[col][row % 4].letter1[0]);

          if(!second1)
          {
            if(row + 1 < rows)
            {
                second2 = updateLetter(second, letters[col][row].letter1[0], letters[col][row + 1].letter1[0]);
            }
          }

          if((first1 && second1 == true) || (first1 && second2 == true) || (first2 && second1 == true) || (first && second2 == true)) // this is just to add more efficiency although it has a bad desgin
            {return;}

        }

     }

}

bool checkMatchColumn (char fir, char sec)
{
    char first = fir;
    char second = sec;
    bool matched = false;

    for (int r = 0; r < sizeOfArrayLetters; r++)
    {
        for (int c = 0; c < sizeOfArrayLetters; c++)
        {
            if (first == letters[c][r].letter1[0] || first == letters[c][r].letter2[0])
            {
                for (int i = 0; i < sizeOfArrayLetters; i++)
                {
                    if (second == letters[i][r].letter1[0] || second == letters[i][r].letter2[0])
                    {
                        matched = true;
                        return matched;
                    }
                 }
             }
        }
    }

    return matched;
}

void encryptColumn (char first, char second)
{
    const int rows = sizeOfArrayLetters;
    const int cols = sizeOfArrayLetters;

    bool first1 = false;
    bool first2 = false;
    bool second1 = false;
    bool second2 = false;

    for (int col = 0; col < cols; col++) // this algorithm is not efficient, it is butter to use hash table, I was just busy to do it
    {
        for (int row = 0; row < rows; row++)
        {
            first1 = updateLetter(first, letters[row][col].letter1[0], letters[row % 4][col].letter1[0]);

            if(!first1)
            {
                if(row + 1 < rows)
                {
                    first2 = updateLetter(first, letters[row][col].letter1[0], letters[row + 1][col].letter1[0]);
                }
            }

            second1 = updateLetter(second, letters[row][col].letter1[0], letters[row % 4][col].letter1[0]);

            if(!second1)
            {
                if(row + 1 < rows)
                {
                    second2 = updateLetter(second, letters[row][col].letter1[0], letters[row + 1][col].letter1[0]);
                }
            }

            if((first1 && second1 == true) || (first1 && second2 == true) || (first2 && second1 == true) || (first && second2 == true)) // this is just to add more efficiency although it has a bad desgin
                {return;}

        }

     }

}


bool updateLetter (char letter, char oldLetter, char newLetter)
{

    if (letter == oldLetter && letter != newLetter )
    {
        for(int i = 0; i < plainTextSize * 2; i++) // this way is not efficient it is butter to make it in linked list, but I was busy to do it
        {
          if(cipherText[i] == '\0') {cipherText[i] = newLetter; printf("%c -> %c\n",letter,cipherText[i]); return true; }
        }

    }

    return false;
}



void fillTheArrayKey (void)
{
    int keySize = strlen(key);
    int keyIdx = 0;

    for (int i = 0; i < sizeOfArrayLetters; i++)
    {
        for (int j = 0; j < sizeOfArrayLetters; j++)
        {
            if (keyIdx < keySize)
            {
                letters[i][j].letter1[0] = key[keyIdx];
                keyIdx++;
            }
        }
    }
}


int separatePlaneText (void)
{
    int i = 0;
    int j = 0;

    while (i < plainTextSize)
    {
        text[j].letter1[0] = plainText[i];

        if (i + 1 != plainTextSize && plainText[i] == plainText[i + 1])
        {
            text[j].letter2[0] = 'x';
            i++;
        }
        else if (i + 1 == plainTextSize)
        {
            text[j].letter2[0] = 'x';
            i++;
        }
        else
        {
            text[j].letter2[0] = plainText[i + 1];
            i += 2;
        }

        j++;
    }

    // if (text[j - 1]->letter2[0] == '\0')
    // {
    //     text[j - 1]->letter2[0] = 'z';
    // }

      // to avoid the segmentation fault we should know the size of our text array
        int TextSize = j ;
        return TextSize;
}


void encryptSquare (char first, char second)
{

    const int rows = sizeOfArrayLetters;
    const int cols = sizeOfArrayLetters;

    int IdxFcol = 0; // Idex for col in the first letter The same way of reading for the the others
    int IdxScol = 0; //
    int IdxFrow = 0; //
    int IdxSrow = 0; //

    for (int col = 0; col < cols; col++) // this algorithm is not efficient, it is butter to use hash table, I was just busy to do it
    {   // another thing dont focuse in the name of col and row int he implementation , it might makes you lost , so instade focuse in the place of the index
        for (int row = 0; row < rows; row++)
        {
            if(first == letters[col][row].letter1[0] || first == letters[col][row].letter2[0])
            {
                IdxFcol = col;
                IdxFrow = row;
            }
             if(second == letters[col][row].letter1[0] || second == letters[col][row].letter2[0])
             {
                IdxScol = col;
                IdxSrow = row;
             }
        }
     }

    updateLetter(first, letters[IdxFcol][IdxFrow].letter1[0], letters[IdxFcol][IdxSrow].letter1[0]);
    updateLetter(second, letters[IdxScol][IdxSrow].letter1[0], letters[IdxScol][IdxFrow].letter1[0]);

}

bool hasDuplicateLetters(void)
{
    bool seen[26] = {false}; // Initialize an array to keep track of seen letters
    int len = strlen(key);

    for (int i = 0; i < len; i++)
    {
        int index = key[i] - 'a';
        if (seen[index])
        {
            // If this letter has already been seen, then we have a duplicate
            printf("%c, is a duplicated letter\n",key[i]);
            return true;
        }
        else
        {
            seen[index] = true;
        }
    }
    // If we reach here, then there are no duplicates
    return false;
}

void allocateMemory (void)
{
    // allocation memory for letters
    letters = malloc(sizeof(Letters) * sizeOfArrayLetters);

    for (int i = 0; i < sizeOfArrayLetters; i++)
    {
        Letters *lett = malloc(sizeof(Letters) * 5);
        letters[i] = lett;
    }

    for(int i = 0; i < sizeOfArrayLetters; i++)
    {
        for(int j = 0; j < sizeOfArrayLetters; j++)
        {
            letters[i][j].letter1 = malloc(sizeof(char));
            letters[i][j].letter2 = malloc(sizeof(char));
            letters[i][j].letter1[0] = '\0';
            letters[i][j].letter2[0] = '\0';

        }
    }

    // allocationg memory for text
    text = malloc(plainTextSize * sizeof(Letters));
    for (int i = 0; i < plainTextSize; i++)
    {
        for (int j = 0; j < plainTextSize; j++)
        {
            text[j].letter1 = malloc(sizeof(char));
            text[j].letter2 = malloc(sizeof(char));
            text[j].letter1[0] = '0';
            text[j].letter2[0] = '0';


        }
    }
}

bool* hasSeen(void)
{
    bool* seen = (bool*) malloc(26 * sizeof(bool));  // allocate memory for the array on the heap
    memset(seen, false, 26 * sizeof(bool));  // initialize all elements to false

    int idx = 0;

    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            idx = letters[i][j].letter1[0] - 'a';
            seen[idx] = true;
        }
    }

    return seen;
}

void findEmptyPlace(int *row, int *col)
{
    for(int i = 0 ; i < 5; i++)
    {
        for(int j = 0; j< 5; j++)
        {
           if(letters[i][j].letter1[0] == '\0')
           {
            *row = i ;
            *col = j ;
            return;
           }
        }
    }
}


























































// char *encrypt(void)
// {

//     int keyNum = strlen(key);
//     int keyCount = 0;
//     char cipherText[plainTextSize]; // this is the encrypted Text
//     memset(cipherText,'\0', plainTextSize);
//     fillTheArray();

//     // filling the array with the key and re arrange it
//     for (int i = 0; i < sizeOfArrayLetters; i++)
//     {
//         for (int j = 0; j < sizeOfArrayLetters; j++)
//         {
//             if (keyCount < keyNum)
//             {
//                 letters[i][j].letter1[0] = key[keyCount];
//                 keyCount++;
//             }
//         }
//     }

// //suprate the plane text in the text struct , as couple and prevent the duplication
// int i = 0;
// int j = 0;
// while (i < plainTextSize)
// {
//     text[j] = malloc(sizeof(Letters));
//     text[j]->letter1 = malloc(sizeof(char) * 1);
//     text[j]->letter2 = malloc(sizeof(char) * 1);

//     text[j]->letter1[0] = plainText[i];

//     if (i + 1 != plainTextSize || plainText[i] == plainText[i + 1])
//     {
//         text[j]->letter2[0] = plainText[i + 1];
//         i +=2;
//     }
//     else if (i + 1 == plainTextSize)
//     {
//         text[j]->letter2[0] = '\0';
//         i++;
//     }

//     j++;
// }

// if (text[j - 1]->letter2[0] == '\0')
// {
//     text[j - 1]->letter2[0] = 'z';
// }

//     // encrypting the text
//     int TextSize = j-1;

//     encryptColumn(text, TextSize, cipherText);
//     encryptRaw(text, TextSize, cipherText);

//     return makeCipherText(text, TextSize);

// }



// void encryptColumn(Letters *text[], int TextSize, char *cipherText)
// {
//     const int rows = sizeOfArrayLetters;
//     const int cols = sizeOfArrayLetters;

//     for (int Idx = 0; Idx < TextSize; Idx++)
//     {
//         char first = text[Idx]->letter1[0];
//         char second = text[Idx]->letter2[0];

//         bool matched = checkMatchColumn(first, second);

//         if (matched)
//         {
//             int tempFirst = first;
//             int tempSecond = second;
//             for (int col = 0; col < cols; col++)
//             {
//                 for (int row = 0; row < rows; row++)
//                 {
//                     updateLetter(&text[Idx]->letter1[0], letters[row][col].letter1[0], letters[row % 4][col].letter1[0], tempFirst, tempSecond, cipherText);
//                     updateLetter(&text[Idx]->letter1[0], letters[row][col].letter1[0], letters[row + 1][col].letter1[0], tempFirst, tempSecond, cipherText);
//                     updateLetter(&text[Idx]->letter2[0], letters[row][col].letter2[0], letters[row % 4][col].letter2[0], tempFirst, tempSecond, cipherText);
//                     updateLetter(&text[Idx]->letter2[0], letters[row][col].letter2[0], letters[row + 1][col].letter2[0], tempFirst, tempSecond, cipherText);

//                  }

//              }
//          }

//     }
// }
