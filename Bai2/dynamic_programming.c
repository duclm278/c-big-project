#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    char n;
    int g;
    int v;
}
item;

int knapsack(int capacity, int N, item items[], int itemsSelected[]);

int main(void)
{
    int W, N;

    // Open BAG.INP
    FILE *input = fopen("BAG.INP", "r");
    if (input == NULL)
        return 1;

    // Read BAG.INP
    fscanf(input, "%d %d\n", &N, &W);
    item items[N];
    for (int i = 0; i < N; i++)
    {
        fscanf(input, "%d %d %c\n", &items[i].g, &items[i].v, &items[i].n);
    }

    // Print out result
    int itemsSelected[N];
    printf("%d\n", knapsack(W, N, items, itemsSelected));
    for (int i = 0; i < N; i++)
    {
        if (itemsSelected[i] != 0)
            printf("%c %d\n", items[i].n, itemsSelected[i]);
    }

    // Close BAG.INP
    fclose(input);

    return 0;
}

int knapsack(int capacity, int N, item items[], int itemsSelected[])
{
    if (capacity < 0 || N == 0)
        exit(1);

    // Initialize a table where individual rows represent items
    // and columns represent the weight of the knapsack
    int DP[N + 1][capacity + 1];
    for (int i = 0; i <= N; i++)
    {
        for (int sz = 0; sz <= capacity; sz++)
        {
            if (i == 0)
            {
                DP[i][sz] = 0;
                continue;
            }

            // Get the value and weight of the item
            int w = items[i - 1].g;
            int v = items[i - 1].v;

            // Consider not picking this element
            DP[i][sz] = DP[i - 1][sz];

            // Consider including the current element and
            // see if this would be more profitable
            if (sz >= w && DP[i][sz - w] + v > DP[i][sz])
                DP[i][sz] = DP[i][sz - w] + v;
        }
    }

    int sz = capacity;
    for (int i = N; i > 0; i--)
    {
        // Get the value and weight of the item
        int w = items[i - 1].g;
        int v = items[i - 1].v;

        // Using the information inside the table we can backtrack and determine
        // which items were selected during the dynamic programming phase. The idea
        // is that if DP[i][sz] != DP[i-1][sz] then the item was selected. Subtract
        // sz by w, increment count and repeat until DP[i][sz] == DP[i-1][sz]
        int count = 0;
        while (DP[i][sz] != DP[i - 1][sz])
        {
            count++;
            sz -= w;
        }
        int itemIndex = i - 1;
        itemsSelected[itemIndex] = count;
    }

    return DP[N][capacity];
}
