#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

long count_letters(string text);
long count_words(string text);
long count_sentences(string text);

int main(void)
{
    string text = get_string("Text: ");
    long letters = count_letters(text);
    long words = count_words(text);
    long sentences = count_sentences(text);
    double average_words = 100. / words; 
    float L = average_words * letters * 0.0588;
    float S = average_words * sentences * 0.296;
    int index = round(L - S - 15.8);
    //printf("%s\n", text);
    //printf("%li letters\n", letters);
    //printf("%li words\n", words);
    //printf("%li sentences\n", sentences);
    if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}

long count_letters(string text)
{
    int i = 0; // var for alpha
    int j = 0; // var for non alpha
    while (text[i] != '\0')
    {
        // check each char to see if it is an alpha character, increase i for yes, both for no
        if (isalpha(text[i]))
        {
            i++;
        }
        else
        {
            i++;
            j++;
        }
    }
    // calculate alpha characters minus non alpha
    return i - j;
}

long count_words(string text)
{
    int i;
    int spaces = 0;
    int n;
    // for each char check if it is a space, increase spaces for each one and add 1 for the first word.
    // assumes each word starts with a space (adding 1 for the first word)
    for (i = 0, n = strlen(text); i < n; i++)
        if (isspace(text[i]))
        {
            spaces++;
        }
    return spaces + 1;
}

long count_sentences(string text)
{
    int i;
    int j = 0;
    int n;
    // for each char check if it is a ? or ! or . and increase j for each one
    // assumes every sentence ends in a punctuation
    for (i = 0, n = strlen(text); i < n; i++)
        if (text[i] - '?' == 0 || text[i] - '!' == 0 || text[i] - '.' == 0)
        {
            j++;
        }

    return j;
}