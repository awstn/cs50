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

bool noCycle(int edgeWinner, int edgeLoser);
int getWeakestWinner(int lastIndex);

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
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO

    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (i < j)
            {
                preferences[ranks[i]][ranks[j]]++;
            }
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    int counter = 1;
    for (int x = 0; x < pair_count; x++)
    {
        pair greatestPairTemp = pairs[x];
        int greatestDiffTemp = preferences[pairs[x].winner][pairs[x].loser] -
                               preferences[pairs[x].loser][pairs[x].winner];
        int greatestIndex = x;
        for (int y = counter; y < pair_count; y++)
        {
            int currentDiffTemp = preferences[pairs[y].winner][pairs[y].loser] -
                                  preferences[pairs[y].loser][pairs[y].winner];
            if (greatestDiffTemp < currentDiffTemp)
            {
                greatestDiffTemp = currentDiffTemp;
                greatestPairTemp = pairs[y];
                greatestIndex = y;
            }
        }
        pairs[greatestIndex] = pairs[x];
        pairs[x] = greatestPairTemp;
        counter++;
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    for (int i = 0; i < pair_count; i++)
    {
        pair edgeCandidate = pairs[i];

        if (noCycle(edgeCandidate.winner, edgeCandidate.loser))
        {
            locked[edgeCandidate.winner][edgeCandidate.loser] = true;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // Go through pairs, find the lowest strength of victory that has an edge
    // Iterate through to find the source.
    int winner = -1;
    bool isWinner = false;

    for (int x = 0; x < candidate_count; x++)
    {
        isWinner = true;
        for (int y = 0; y < candidate_count; y++)
        {
            if (locked[y][x])
                isWinner = false;
        }
        if (isWinner)
        {
            winner = x;
            break;
        }
    }

    if (winner == -1)
    {
        printf("No winner!");
        return;
    }

    printf("%s\n", candidates[winner]);
}

bool noCycle(int edgeWinner, int edgeLoser)
{
    bool visitedArray[candidate_count];

    for (int x = 0; x < candidate_count; x++)
        visitedArray[x] = false;

    if (edgeWinner == edgeLoser)
        return false;

    for (int i = 0; i < candidate_count; i++)
    {
        if (visitedArray[i])
            continue;

        if (locked[edgeLoser][i])
        {
            visitedArray[i] = true;
            if (!noCycle(edgeWinner, i))
                return false;
        }
    }

    return true;
}

int getWeakestWinner(int lastIndex)
{
    if (lastIndex < 0)
        return -1;

    pair candidate = pairs[lastIndex];

    if (locked[candidate.winner][candidate.loser])
        return lastIndex;

    return getWeakestWinner(lastIndex - 1);
}