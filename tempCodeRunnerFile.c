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