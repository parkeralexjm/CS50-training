#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Get input words from both players and convert to lowercase
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // Print the winner
    if (score1 > score2)
    {
        printf("Player 1 wins!");
    }
    else if (score2 > score1)
    {
        printf("Player 2 wins!");
    }
    else
    {
        printf("Tie!");
    }
}

int compute_score(string word)
{

    // Compute and return score for string

    // create a variable for the score
    int j = 0;
    // for the length of the word, put each letter through the loop
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        //check if alpha char
        if (isalpha(word[i]))
        {
            // if lowercase then subtract a and change the points
            if (islower(word[i]))
            {
                j += POINTS[word[i] - 'a' ];
            }
            // if uppercase then subtract A and change the points
            else if (isupper(word[i]))
            {
                j += POINTS[word[i] - 'A'];
            }
        }
    }
    // return points to the function compute_score
    return j;
}

