#include <stdio.h>

long long combanation(long long n, long long k);

int main(void)
{
    long long n, k, nCk;

    // Open files
    FILE *input = fopen("TOHOP.INP", "r");
    if (input == NULL)
        return 1;
    FILE *output = fopen("TOHOP.OUT", "w");
    if (output == NULL)
        return 1;

    // Read and write files
    while (fscanf(input, "%lld %lld\n", &n, &k) != EOF)
    {
        fprintf(output, "%lld\n", combanation(n, k));
    }

    // Close files
    fclose(input);
    fclose(output);

    return 0;
}

// https://en.wikipedia.org/wiki/Combination#Example_of_counting_combinations
long long combanation(long long n, long long k)
{
    long long nCk = 1;
    for (int i = n, j = 1; i >= n - (k - 1); i--, j++)
    {
        nCk = nCk * i / j;
    }
    return nCk;
}
