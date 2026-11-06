#include <stdio.h>

// Programmer: Omaima Siddique
// Roll no.: 26K-2517
// Class: BDS-1A
// Desc: Cinema Hall Seat Booking Management System


int main(void)
{
    int seats[50][50], freeRow[50];
    int rows, cols, r, c, k, total = 0;
    int mid, d, t, cand, count, found = 0, foundRow = -1, foundStart = -1;

    do {
        printf("Enter number of rows (1-50): ");
        scanf("%d", &rows);
    } while (rows < 1 || rows > 50);
    do {
        printf("Enter number of seats per row (1-50): ");
        scanf("%d", &cols);
    } while (cols < 1 || cols > 50);

    printf("Enter seating status (0 = available, 1 = booked):\n");
    for (r = 0; r < rows; r++)
        for (c = 0; c < cols; c++){
        scanf(" %1d", &seats[r][c]);   
        while (seats[r][c] != 0 && seats[r][c] != 1) {
            printf("Invalid! Enter only 0 or 1 for Row %d, Seat %d: ", r, c);
            scanf(" %1d", &seats[r][c]);
        }
    }
          

    for (r = 0; r < rows; r++) {
        freeRow[r] = 0;
        for (c = 0; c < cols; c++)
            if (seats[r][c] == 0) freeRow[r]++;
        total += freeRow[r];
    }

    printf("\n    ");
    for (c = 0; c < cols; c++) printf("%d ", c);
    printf("\n");
    for (r = 0; r < rows; r++) {
        printf("R%-2d ", r);
        for (c = 0; c < cols; c++)
            printf("%c ", seats[r][c] == 0 ? '_' : 'X');
        printf("\n");
    }
    printf("\nFree seats per row: ");
    for (r = 0; r < rows; r++) printf("%d ", freeRow[r]);
    printf("  Total free: %d\n", total);

    printf("\nEnter group size k: ");
    scanf("%d", &k);
    if (k <= 0 || k > cols) {
        printf("Invalid group size. Must be between 1 and %d.\n", cols);
        return 0;
    }

    mid = rows / 2;
    for (d = 0; d < rows && !found; d++) {
        for (t = 0; t < 2 && !found; t++) {
            if (t == 0) cand = mid - d;
            else {
                if (d == 0) continue;
                cand = mid + d;
            }
            if (cand < 0 || cand >= rows) continue;

            count = 0;
            for (c = 0; c < cols && !found; c++) {
                if (seats[cand][c] == 0) {
                    count++;
                    if (count == k) {
                        found = 1;
                        foundRow = cand;
                        foundStart = c - k + 1;
                    }
                } else {
                    count = 0;
                }
            }
        }
    }

    if (found) {
        for (c = foundStart; c < foundStart + k; c++) seats[foundRow][c] = 1;
        freeRow[foundRow] -= k;
        total -= k;
        printf("\nGroup of %d seated in Row %d, Seats %d to %d\n",
               k, foundRow, foundStart, foundStart + k - 1);

        printf("\n    ");
        for (c = 0; c < cols; c++) printf("%d ", c);
        printf("\n");
        for (r = 0; r < rows; r++) {
            printf("R%-2d ", r);
            for (c = 0; c < cols; c++)
                printf("%c ", seats[r][c] == 0 ? '_' : 'X');
            printf("\n");
        }
        printf("\nRemaining available seats: %d\n", total);
    } else {
        printf("\nSorry, no row has %d consecutive available seats. Plan unchanged.\n", k);
    }
    return 0;
}
