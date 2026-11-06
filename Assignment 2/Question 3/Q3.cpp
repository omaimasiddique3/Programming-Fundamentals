#include <stdio.h>

#define MAXS 50
#define MAXH 100

// Programmer: Omaima Siddique
// Roll no.: 26K-2517
// Class: BDS-1A
// Desc: Greenhouse Temperature Monitoring System

void inputReadings(int temps[][MAXH], int sensors, int hours)
{
    int s, h;
    for (s = 0; s < sensors; s++) {
        printf("Sensor %d readings: ", s + 1);
        for (h = 0; h < hours; h++)
            scanf("%d", &temps[s][h]);
    }
}

void analyzeSensor(int readings[], int n, int *total, float *avg, int *max,
                   int *min, int *critical, int *warning, int *streak)
{
    int i, run = 0;
    *total = 0;
    *max = readings[0];
    *min = readings[0];
    *critical = 0;
    *warning = 0;
    *streak = 0;

    for (i = 0; i < n; i++) {
        *total += readings[i];
        if (readings[i] > *max) *max = readings[i];
        if (readings[i] < *min) *min = readings[i];

        if (readings[i] >= 40) (*critical)++;
        else if (readings[i] >= 35) (*warning)++;

        if (readings[i] >= 35) {
            run++;
            if (run > *streak) *streak = run;
        } else {
            run = 0;
        }
    }
    *avg = (float)(*total) / n;
}

int findHighestAverage(int temps[][MAXH], int sensors, int hours)
{
    int s, h, best = 0, sum, bestSum = 0;
    for (h = 0; h < hours; h++) bestSum += temps[0][h];
    for (s = 1; s < sensors; s++) {
        sum = 0;
        for (h = 0; h < hours; h++) sum += temps[s][h];
        if (sum > bestSum) {
            bestSum = sum;
            best = s;
        }
    }
    return best;
}

int main(void)
{
    int temps[MAXS][MAXH];
    int sensors, hours, s, best;
    int total, max, min, critical, warning, streak;
    float avg, bestAvg = 0;

    printf("Enter number of sensors: ");
    scanf("%d", &sensors);
    printf("Enter number of hourly readings: ");
    scanf("%d", &hours);

    inputReadings(temps, sensors, hours);

    printf("\n");
    for (s = 0; s < sensors; s++) {
        analyzeSensor(temps[s], hours, &total, &avg, &max, &min,
                      &critical, &warning, &streak);
        printf("Sensor %d: Total=%d  Avg=%.2f  Max=%d  Min=%d\n",
               s + 1, total, avg, max, min);
        printf("          Critical=%d  Warning=%d  Longest hot streak=%d\n",
               critical, warning, streak);
    }

    best = findHighestAverage(temps, sensors, hours);
    analyzeSensor(temps[best], hours, &total, &bestAvg, &max, &min,
                  &critical, &warning, &streak);
    printf("\nHighest average: Sensor %d (%.2f)\n", best + 1, bestAvg);
    return 0;
}
