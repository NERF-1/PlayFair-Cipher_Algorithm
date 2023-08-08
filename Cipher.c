
//This progrm is using playfire algorithm to encrypt the data
//This program has written using c language

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct
{
    char *letter1;
    char *letter2;

} Letters;

// Define a node structure for the linked list
typedef struct node {
    char* word; // The word stored in the node
    struct node* next; // The pointer to the next node
} node;


node *head;
const int sizeOfArrayLetters = 5;
Letters **letters; // this is Array struct, where we will store our english letters
char word[500]; // the words that it will get encrypted
int wordSize;
char inputText[1000]; //
int inputSize;
char key[25]; // it is the key that the user will enter
Letters *sepLitters; // this is will separated the word to Duets
int input; // this is the input senario it should be either 0 or 1

//.................................................................................
// The Encryption methods are here
void encrypt(char **node); // this will handel the whole encryption process, Using the following methods
void encryptRow (char first, char second); // encrypt the letters if they are in the same row accourding to play fire algorithm row case
void encryptColumn (char first, char second); // encrypt the letters if they are in the same column accourding to play fire algorithm column case
void encryptSquare (char first, char second); // encypt the lettrers if they are not in same column or row accourding to play fire algorithm third case
bool updateLetter (char letter, char oldLetter, char newLetter); // this method will update the lettrs from the plain text to the ciphre text, accourding to the cases above

//.................................................................................
// These are global methods works for the Ecryption and Decryption
void allocateMemory (void); // this method to dynamicly allocate a memory for array letters
void fillTheArrayLetters(void); // this mehtod will fill the 5*5 array AKA (letters) with the english litters
void fillTheArrayKey(void);  // filling the array with the key and re arrange it
bool checkMatchRow (char first, char second); // checking if the coupels of the letters are in the same row in the array
bool checkMatchColumn (char first, char second);// checking if the first and second letters are in the same column
int separateText(void); //separate the (plane text, cihper text) in the text array struct , as couple and prevent the duplication and return the TextSize of the Text Array
void getPlaces(char first, char second,  int *IdxFcol, int *IdxFrow, int *IdxScol, int *IdxSrow); //as you read it will get the give you Indexes form letters for a specific letters
bool* hasSeen(void); // this array will check the key letters in letters array as seen in array bool and return that array to use it in fillTheArrayLetters method
void findEmptyPlace(int *row, int *col); // this method will find an empty place in letters array
bool hasDuplicateLetters(void); // to check if we have a duplicated letter in the key
//LinkedList to that store the whole plain text word by word
node* create_node(char* bufferWord);
node* append_node(node* new_node);
void print_list(void);
void free_list(void);
void distributeInNodes (void);
// .....................................................................................
//The decryption methods are here
void decrypt (char **node); // it will handel the whole of the decryption process
void decryptRow (char first, char second, int Idx);
void decryptColumn(char first, char second, int Idx);
void decryptSquare(char first, char second, int Idx);
char* remove_extra(char* decrypted, char pad); //it will remove any extra padding letters

//......................................................................................
void senario (void); // this will handel the running senario if it going to be encyption or decryption and print the result of the process



int main(void)
{
    // taking the key from the user
    do{
        printf("Enter The Key:\n");
        scanf("%s", key);
        printf("\n");

    } while(hasDuplicateLetters());

    senario();
}

void encrypt(char **node)
{
    memset(word, '\0', 500);
    strcpy(word, *node);

    allocateMemory();
    fillTheArrayKey();
    fillTheArrayLetters();

    int seperatedTextSize = separateText();
    // setting the word to NUL so we can store the word after encryption on it
    memset(word, '\0', 500);

    for (int Idx = 0; Idx < seperatedTextSize; Idx++)
    {
        char first = sepLitters[Idx].letter1[0];
        char second = sepLitters[Idx].letter2[0];

        bool matchedColumn = checkMatchColumn (first, second);
        bool matchedRow = checkMatchRow (first, second);

        if(matchedColumn)
        {
            encryptColumn (first, second);
            continue;
        }
        else if (matchedRow)
        {
            encryptRow (first, second);
            continue;
        }
        else
        {
            encryptSquare (first, second);
        }

    }
     //realloc memory for our node
    char *new_str = strdup(word); // allocate and copy word in one function
    if (new_str == NULL)
    {
        // handle allocation failure
        printf("faild in memory allocation");
    }
    else
    {   // update the value that node points to with the new memory
        *node = new_str;
    }

    printf("\n");

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
    int IdxFcol = 0;
    int IdxFrow = 0;
    int IdxScol = 0;
    int IdxSrow = 0;

    getPlaces(first, second, &IdxFcol, &IdxFrow, &IdxScol, &IdxSrow);


    if(IdxFrow + 1 < sizeOfArrayLetters)
    {
        updateLetter (first, letters[IdxFcol][IdxFrow].letter1[0], letters[IdxFcol][IdxFrow + 1].letter1[0]);
    }
    else
    {
        updateLetter (first, letters[IdxFcol ][IdxFrow].letter1[0], letters[IdxFcol][IdxFrow % 4].letter1[0]);
    }
    if(IdxSrow + 1 < sizeOfArrayLetters)
    {
        updateLetter (second, letters[IdxScol][IdxSrow].letter1[0], letters[IdxScol][IdxSrow + 1].letter1[0]);
    }
    else
    {
        updateLetter (second, letters[IdxScol][IdxSrow].letter1[0], letters[IdxScol][IdxSrow % 4].letter1[0]);
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

    int IdxFcol = 0;
    int IdxFrow = 0;
    int IdxScol = 0;
    int IdxSrow = 0;

    getPlaces(first, second, &IdxFcol, &IdxFrow, &IdxScol, &IdxSrow);


    if(IdxFcol + 1 < sizeOfArrayLetters)
    {
        updateLetter (first, letters[IdxFcol][IdxFrow].letter1[0], letters[IdxFcol + 1][IdxFrow].letter1[0]);
    }
    else
    {
        updateLetter (first, letters[IdxFcol ][IdxFrow].letter1[0], letters[IdxFcol % 4][IdxFrow].letter1[0]);
    }
    if(IdxScol + 1 < sizeOfArrayLetters)
    {
        updateLetter (second, letters[IdxScol][IdxSrow].letter1[0], letters[IdxScol + 1][IdxSrow].letter1[0]);
    }
    else
    {
        updateLetter (second, letters[IdxScol][IdxSrow].letter1[0], letters[IdxScol % 4][IdxSrow].letter1[0]);
    }

}


bool updateLetter (char letter, char oldLetter, char newLetter)
{

    if (letter == oldLetter && letter != newLetter )
    {
        for (int i = 0; i < 500; i++) // this way is not efficient it is butter to make it in linked list, but I was busy to do it
        {
            if(word[i] == '\0') {word[i] = newLetter; printf("%c -> %c\n",letter, word[i]); return true; }
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


int separateText (void)
{
    int i = 0;
    int j = 0;

    while (i < wordSize)
    {
        sepLitters[j].letter1[0] = word[i];

        if (i + 1 != wordSize && word[i] == word[i + 1])
        {
            sepLitters[j].letter2[0] = 'x';
            i++;
        }
        else if (i + 1 == wordSize)
        {
            sepLitters[j].letter2[0] = 'x';
            i++;
        }
        else
        {
            sepLitters[j].letter2[0] = word[i + 1];
            i += 2;
        }

        j++;
    }
    // to avoid the segmentation fault we should know the size of our superatedTextArray array
    int seperatedTextSize = j ;
    return seperatedTextSize;
}


void encryptSquare (char first, char second)
{

    int IdxFcol = 0; // Idex for col in the first letter The same way of reading for the the others
    int IdxScol = 0; //
    int IdxFrow = 0; //
    int IdxSrow = 0; //

    getPlaces(first, second, &IdxFcol, &IdxFrow, &IdxScol, &IdxSrow);

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
    wordSize = strlen(word);
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
    sepLitters = malloc(wordSize * sizeof(Letters));
    for (int i = 0; i < wordSize; i++)
    {
        for (int j = 0; j < wordSize; j++)
        {
            sepLitters[j].letter1 = malloc(sizeof(char));
            sepLitters[j].letter2 = malloc(sizeof(char));
            sepLitters[j].letter1[0] = '\0';
            sepLitters[j].letter2[0] = '\0';
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


void decrypt (char **node)
{

    memset(word, '\0', 500);
    strcpy(word, *node);

    allocateMemory();
    fillTheArrayKey();
    fillTheArrayLetters();

    int superatedTextSize = separateText();
    //setting the word to NUL to store the new word
    memset(word, '\0', 500);

     for (int Idx = 0; Idx < superatedTextSize; Idx++)
     {
        char first = sepLitters[Idx].letter1[0];
        char second = sepLitters[Idx].letter2[0];

        bool matchedColumn = checkMatchColumn (first, second);
        bool matchedRow = checkMatchRow (first, second);

        if(matchedColumn)
        {
            decryptColumn(first, second, Idx);
        }
        else if(matchedRow)
        {
            decryptRow(first, second, Idx);
        }
        else decryptSquare(first, second, Idx);
    }
    for (int i = 0, j = 0; i <= wordSize; i += 2)
    {
        word[i] = sepLitters[j].letter1[0];
        word[i + 1] = sepLitters[j].letter2[0];
        j++;
    }
    // remove the extra letters in word
    char *finalWord = remove_extra(word,'x');
    //realloc memory for our node
    char *new_str = strdup(finalWord); // allocate and copy word in one function
    if (new_str == NULL)
    {
        // handle allocation failure
        printf("faild in memory allocation");
    }
    else
    {   // update the value that node points to with the new memory
        *node = new_str;
    }

    printf("\n");



}



void decryptColumn(char first, char second, int Idx)
{
    int IdxFcol = 0;
    int IdxFrow = 0;
    int IdxScol = 0;
    int IdxSrow = 0;

    getPlaces(first, second, &IdxFcol, &IdxFrow, &IdxScol, &IdxSrow);

    if(IdxFcol == 0)
    {
        sepLitters[Idx].letter1[0] = letters[sizeOfArrayLetters - 1][IdxFrow].letter1[0];
        printf("%c -> %c\n", first, letters[sizeOfArrayLetters - 1][IdxFrow].letter1[0]);
    }
    else
    {
        sepLitters[Idx].letter1[0] = letters[IdxFcol - 1 ][IdxFrow].letter1[0];
        printf("%c -> %c\n", first, letters[IdxFcol - 1][IdxFrow].letter1[0]);
    }

    if(IdxScol == 0)
    {
        sepLitters[Idx].letter2[0] = letters[sizeOfArrayLetters - 1][IdxSrow].letter1[0];
        printf("%c -> %c\n", second, letters[sizeOfArrayLetters - 1][IdxSrow].letter1[0]);
    }
    else
    {
        sepLitters[Idx].letter2[0] = letters[IdxScol - 1][IdxSrow].letter1[0];
        printf("%c -> %c\n", second, letters[IdxScol - 1][IdxSrow].letter1[0]);
    }
}




void decryptRow (char first, char second, int Idx)
{
    int IdxFcol = 0; // col of the first letter
    int IdxFrow = 0; // row of the first letter
    int IdxScol = 0;
    int IdxSrow = 0;

    getPlaces(first, second, &IdxFcol, &IdxFrow, &IdxScol, &IdxSrow);


    if(IdxFrow == 0)
    {
        sepLitters[Idx].letter1[0] = letters[IdxFcol][sizeOfArrayLetters - 1].letter1[0];
        printf("%c -> %c\n",first, letters[IdxFcol][sizeOfArrayLetters - 1].letter1[0]);
    }
    else
    {
        sepLitters[Idx].letter1[0] = letters[IdxFcol ][IdxFrow - 1].letter1[0];
        printf("%c -> %c\n",first, letters[IdxFcol][IdxFrow - 1].letter1[0]);
    }


    if(IdxSrow == 0)
    {
        sepLitters[Idx].letter2[0] = letters[IdxScol][sizeOfArrayLetters - 1].letter1[0];
        printf("%c -> %c\n",second, letters[IdxScol][sizeOfArrayLetters - 1].letter1[0]);
    }
    else
    {
        sepLitters[Idx].letter2[0] = letters[IdxScol][IdxSrow - 1].letter1[0];
        printf("%c -> %c\n",second, letters[IdxScol][IdxSrow - 1].letter1[0]);
    }
}




void decryptSquare(char first, char second, int Idx)
{
    int IdxFcol = 0;
    int IdxFrow = 0;
    int IdxScol = 0;
    int IdxSrow = 0;
    getPlaces(first, second, &IdxFcol, &IdxFrow, &IdxScol, &IdxSrow);

    sepLitters[Idx].letter1[0] = letters[IdxFcol][IdxSrow].letter1[0];
    sepLitters[Idx].letter2[0] = letters[IdxScol][IdxFrow].letter1[0];
    printf("%c -> %c\n",first,letters[IdxFcol][IdxSrow].letter1[0]);
    printf("%c -> %c\n",second,letters[IdxScol][IdxFrow].letter1[0]);

}


void senario(void)
{
    do
    {
        printf("[0]:Encrytion\n[1]:Decryption\nChoose 0 for Encryption and 1 for Decryption.\n");
        scanf("%i", &input);
        int c; // declare an int variable to store the input character
        while ((c = getchar()) != '\n' && c != EOF); // read and discard characters until \n or EOF

    } while (input != 0 && input != 1);

    switch(input)
    {
        case 0:
            // taking the planText from the user
            printf("Enter The Text That You Want To Encrypt:\n");
            fgets(inputText, 1000, stdin);
                // calculate the size of plainText
            inputSize = strlen(inputText);
            printf("Your Text Size + Spaces =  %i\n\n", inputSize - 1);
            // start the encrypting
            head = NULL;
            distributeInNodes();
            // iterate over the list
            node *current1 = head;
            while (current1 != NULL)
            {
                encrypt(&current1->word);
                current1 = current1->next;
            }
            // finally we can print our cipher text which is inside the list
            printf("Your CipherText Is: \n");
            print_list();
            free_list();
            break;
        case 1:
            // taking the planText from the user
            printf("Enter The Text That You Want To Decrypt:\n");
            fgets(inputText, 1000, stdin);
            // calculate the size of cipherText
            inputSize = strlen(inputText);
            printf("Your Text Size + Spaces =  %i\n\n", inputSize - 1);
            // start the decrypting
            head = NULL;
            distributeInNodes();
            // iterate over the list
            node *current2 = head;
            while (current2 != NULL)
            {
                decrypt(&current2->word);
                current2 = current2->next;
            }
            // finally we can print our plainText which is inside the list
            printf("Your PlainText Is: \n");
            print_list();
            free_list();
            break;
    }
}

void getPlaces (char first, char second,  int *IdxFcol, int *IdxFrow, int *IdxScol, int *IdxSrow)
{
    const int rows = sizeOfArrayLetters;
    const int cols = sizeOfArrayLetters;

    for (int col = 0; col < cols; col++) // this algorithm is not efficient, it is butter to use hash table, I was just busy to do it
    {   // another thing dont focuse in the name of col and row int he implementation , it might makes you lost , so instade focuse in the place of the index
        for (int row = 0; row < rows; row++)
        {
            if(first == letters[col][row].letter1[0] || first == letters[col][row].letter2[0])
            {
                *IdxFcol = col;
                *IdxFrow = row;
            }
            if(second == letters[col][row].letter1[0] || second == letters[col][row].letter2[0])
            {
                *IdxScol = col;
                *IdxSrow = row;
            }
        }
    }
}

// A function to remove extra letters after decryption
char* remove_extra(char* decrypted, char pad)
{
    // Allocate memory for the original text
    char* original = (char*)malloc(strlen(decrypted));
    // Initialize a counter for the original text
    int i = 0;
    // Loop through the decrypted text
    for (int j = 0; j < strlen(decrypted); j++)
    {
        // If the current character is the padding letter
        if (decrypted[j] == pad)
        {
            // Check the next character
            if (j < strlen(decrypted) - 1)
            {
                // If the next character is also the padding letter
                if (decrypted[j + 1] == pad)
                {
                    // Keep only one of them and skip the other
                    original[i] = pad;
                    i++;
                    j++;
                }
                // If the next character is different from the padding letter
                else
                {
                    // Drop the current character and keep the next one
                    original[i] = decrypted[j + 1];
                    i++;
                    j++;
                }
            }
            // If there is no next character, drop the current character
            else {
                break;
            }
        }
        // If the current character is not the padding letter, keep it as it is
        else {
            original[i] = decrypted[j];
            i++;
        }
    }
    // Add a null terminator to the original text
    original[i] = '\0';
    // Return the original text
    return original;
}

// Create a new node with a given word and return its pointer
node* create_node(char* bufferWord)
{
    // Allocate memory for the node
    node* new_node = malloc(sizeof(node));
    if (new_node == NULL)
    {
        printf("Memory allocation failed\n");
        exit(1);
    }

    // Allocate memory for the word and copy it
    new_node->word = malloc(strlen(bufferWord) + 1);
    if (new_node->word == NULL)
    {
        printf("Memory allocation failed\n");
        exit(1);
    }
    strcpy(new_node->word, bufferWord);

    // Set the next pointer to NULL
    new_node->next = NULL;

    // Return the node pointer
    return new_node;
}

// Append a node to the end of a linked list and return its pointer
node* append_node(node* new_node)
{
    // If the list is empty, return the new node as the head
    if (head == NULL)
    {
        return new_node;
    }

    // Find the last node of the list
    node* current = head;
    while (current->next != NULL)
    {
        current = current->next;
    }

    // Link the new node to the last node
    current->next = new_node;

    // Return the head of the list
    return head;
}

// Print the words in a linked list
void print_list()
{
    // Loop through the list and print each word
    node* current = head;
    while (current != NULL)
    {
        printf("%s ", current->word); // Print the word
        current = current->next; // Move to the next node
    }
    printf("\n");
}

// Free the memory allocated for a linked list
void free_list()
{
    // Loop through the list and free each node
    node* current = head;
    while (current != NULL)
    {
        node* next = current->next; // Save the next pointer
        free(current->word); // Free the word
        free(current); // Free the node
        current = next; // Move to the next node
    }
}

void distributeInNodes (void)
{
    int count = 0;
    int countWord = 0;
    char bufferWord[78] = {'\0'};
    bool inWord = false;

    while (count < inputSize)
    {
        while (!isspace(inputText[count]) && countWord < 78)
        {
            bufferWord[countWord] = inputText[count];
            count++;
            countWord++;
            inWord = true;
        }

        if (inWord)
        {
            head = append_node(create_node(bufferWord));
            memset(bufferWord,'\0', 78);
            countWord = 0;
            inWord = false;
        }
        count++;
    }

    if (inWord) // if there is still a word in the buffer
    {
        append_node(create_node(bufferWord)); // create and append a node
    }
}

