#include <stdio.h>

// Programmer: Omaima Siddique
// Roll no.: 26K-2517
// Class: BDS-1A
// Desc: Bakery Festival Sales Management System


int getValidDays(void)
{
    int d;
    do {
        printf("Number of days (1-7): ");
        scanf("%d", &d);
        if (d < 1 || d > 7)
            printf("Invalid! Enter a value between 1 and 7.\n");
    } while (d < 1 || d > 7);
    return d;
}

float calculateDailySales(int dayNumber)
{
    int orders, i;
    float amount, total = 0, highest = 0;

    do {
        printf("Day %d - Number of orders: ", dayNumber);
        scanf("%d", &orders);
        if (orders < 1) printf("There must be at least one order.\n");
    } while (orders < 1);

    printf("Order amounts: ");
    for (i = 0; i < orders; i++) {
        scanf("%f", &amount);
        while (amount <= 0) {
            printf("Invalid amount! Re-enter order %d: ", i + 1);
            scanf("%f", &amount);
        }
        total += amount;
        if (amount > highest) highest = amount;
    }

    printf("Total sales: Rs. %.2f\n", total);
    printf("Average order: Rs. %.2f\n", total / orders);
    printf("Highest order: Rs. %.2f\n\n", highest);
    return total;
}

int findHighestSalesDay(float dailySales[], int numberOfDays)
{
    int i, best = 0;
    for (i = 1; i < numberOfDays; i++)
        if (dailySales[i] > dailySales[best]) best = i;
    return best + 1;
}

void displayBarChart(float dailySales[], int numberOfDays)
{
    int i, j, stars;
    printf("\n===== DAILY SALES BAR CHART =====\n");
    for (i = 0; i < numberOfDays; i++) {
        stars = (int)(dailySales[i] / 100);
        printf("Day %d: ", i + 1);
        for (j = 0; j < stars; j++) printf("*");
        printf(" (Rs. %.2f)\n", dailySales[i]);
    }
}

int main(void)
{
    float dailySales[7], festivalTotal = 0;
    int days, i, best;

    days = getValidDays();
    for (i = 0; i < days; i++) {
        dailySales[i] = calculateDailySales(i + 1);
        festivalTotal += dailySales[i];
    }

    best = findHighestSalesDay(dailySales, days);
    printf("===== FESTIVAL SUMMARY =====\n");
    printf("Total festival sales: Rs. %.2f\n", festivalTotal);
    printf("Day with highest sales: Day %d\n", best);
    printf("Highest daily sales: Rs. %.2f\n", dailySales[best - 1]);

    displayBarChart(dailySales, days);
    return 0;
}
