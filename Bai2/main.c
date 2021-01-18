#include <stdio.h>

typedef struct
{
    char n;
    int g;
    int v;
    double vpg;
    int count;
}
type;

int main(void)
{
    int W, N;

    // Open BAG.INP
    FILE *input = fopen("BAG.INP", "r");
    if (input == NULL)
        return 1;

    // Read BAG.INP
    fscanf(input, "%d %d\n", &N, &W);
    type types[N], *order[N];
    for (int i = 0; fscanf(input, "%d %d %c\n", &types[i].g, &types[i].v, &types[i].n) != EOF; i++)
    {
        types[i].vpg = (double) types[i].v / types[i].g;
        types[i].count = 0;
        order[i] = &types[i];
    }

    // Sort order[N] by vpg
    type *tmp;
    for (int i = 0; i < N - 1; i++)
    {
        for (int j = i + 1; j < N; j++)
        {
            if ((*order[i]).vpg < (*order[j]).vpg)
            {
                tmp = order[i];
                order[i] = order[j];
                order[j] = tmp;
            }
        }
    }

    // Greedy algorithm
    int max = 0;
    for (int i = 0; i < N; i++)
    {
        if (W > (*order[i]).g)
        {
            (*order[i]).count = W / (*order[i]).g;
            W %= (*order[i]).g;
            max += (*order[i]).v * (*order[i]).count;
        }
    }

    // Print out result
    printf("%d\n", max);
    for (int i = 0; i < N; i++)
    {
        if (types[i].count != 0)
            printf("%c %d\n", types[i].n, types[i].count);
    }

    // Close BAG.INP
    fclose(input);

    return 0;
}
