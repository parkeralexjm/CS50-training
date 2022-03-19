#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    // search for name in array called candidates[] then candidate[i] = candidate[i].vote + 1;
    for (int i = 0; i <= candidate_count - 1; i++)
    {
        if (strcmp(candidates[i].name, name) == 0)
        {
            candidates[i].votes++;
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // do a bubble sort on the candidates according to candidates[].vote
    int j = 0;
    for (int i = 0; i <= candidate_count - 1; i++)
    {
        if (candidates[j].votes < candidates[i].votes)
        {
            j = i;
        }
    }

    printf("%s\n", candidates[j].name);
    for (int k = 0; k < candidate_count; k++)
        if (candidates[j].votes == candidates[k].votes)
        {
            if (strcmp(candidates[j].name, candidates[k].name) != 0)
            {
                printf("%s\n", candidates[k].name);
            }
        }
    return;
}