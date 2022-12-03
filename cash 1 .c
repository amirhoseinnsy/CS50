
int main(void)
{
    float dollars;
    dollars = get_float("Change owed: ");
    if (dollars < 0)
    {
        dollars = get_float("Change owed: ");
    }
    int cents = round(dollars * 100);
    int total = 0;
    for (int i = cents; i >= 25; i -= 25)
    {
        total++;
        cents -= 25;
    }
    for (int l = cents; l >= 10; l -= 10)
    {
        total++;
        cents -= 10;
    }
    for (int k = cents; k >= 5; k -= 5)
    {
        total++;
        cents -= 5;
    }
    for (int p = cents; p >= 1; p -= 1)
    {
        total++;
        cents -= 1;
    }
    printf("%i\n", total);
}