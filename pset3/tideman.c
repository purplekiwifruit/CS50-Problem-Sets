#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
} pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
int calculate_margin(int winner, int loser);
bool isCycle(int winner, int loser);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    bool isValidVote = false;
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0)
        {
            ranks[rank] = i;
            isValidVote = true;
        }
    }
    return isValidVote;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            int winner = ranks[i];
            int loser = ranks[j];
            preferences[winner][loser]++;
        }
    }
    // return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    pair_count = 0;
    // Loop preferences 2D Array
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;

                pair_count++;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;

                pair_count++;
            }
            else
            {
                continue;
            }
        }
    }
    // return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{

    // loop throgh the paris, find the strongest pair
    for (int i = 0; i < pair_count; i++)
    {
        int max_index = i;
        int max_margin = calculate_margin(pairs[i].winner, pairs[i].loser);

        // Find the strongest pair in the unsorted part of the array
        for (int j = i + 1; j < pair_count; j++)
        {
            int margin = calculate_margin(pairs[j].winner, pairs[j].loser);

            if (margin > max_margin)
            {
                max_margin = margin;
                max_index = j;
            }
        }

        // Swap if a stronger pair is found
        if (i != max_index)
        {
            pair tmp = pairs[i];
            pairs[i] = pairs[max_index];
            pairs[max_index] = tmp;
        }
    }
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        int winner = pairs[i].winner;
        int loser = pairs[i].loser;

        if (!isCycle(winner, loser))
        {
            locked[winner][loser] = true;
        }
    }
}

// Print the winner of the election
void print_winner(void)
{

    for (int j = 0; j < candidate_count; j++)
    {
        bool isWinner = true;

        // Check if any candidate has an edge pointing to candidate `j`
        for (int i = 0; i < candidate_count; i++)
        {
            if (locked[i][j])
            {
                isWinner = false;
                break;
            }
        }

        if (isWinner)
        {
            printf("%s\n", candidates[j]);
            return;
        }
    }
}

int calculate_margin(int winner, int loser)
{
    return preferences[winner][loser] - preferences[loser][winner];
}

bool isCycle(int winner, int loser)
{
    // Base case: if we reach back to the original winner, a cycle is formed
    if (loser == winner)
    {
        return true;
    }

    // Check all outgoing edges from the current loser to see if any path leads back to the winner
    // If a path exists, adding this new pair will create a cycle.
    // Example:
    // Current graph: A -> B -> C
    // New pair to add: C (winner) -> A (loser)
    // This function checks if there is a path from A (loser) back to C (winner) in the current
    // graph.
    for (int i = 0; i < candidate_count; i++)
    {
        // If there is an outgoing edge from `loser` to `i`, check recursively
        // if there is a path from `i` back to `winner`
        if (locked[loser][i] && isCycle(winner, i))
        {
            return true;
        }
    }
    // No cycle detected
    return false;
}
