#include <stdio.h>

long long factorial(long long n);

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
        nCk = factorial(n) / (factorial(k) * factorial(n - k));
        fprintf(output, "%lld\n", nCk);
    }

    // Close files
    fclose(input);
    fclose(output);

    return 0;
}

long long factorial(long long n)
{
    if (n == 0)
        return 1;
    return n * factorial(n - 1);
}
