#include <stdio.h>
#include <string.h>

// Programmer: Omaima Siddique
// Roll no.: 26K-2517
// Class: BDS-1A
// Desc: University Library Management System



void displayMenu(void)
{
    printf("\n===== UNIVERSITY LIBRARY MENU =====\n");
    printf("1. Register Member\n");
    printf("2. Display Available Books\n");
    printf("3. Borrow a Book\n");
    printf("4. Return a Book\n");
    printf("5. Display Member Record\n");
    printf("6. Exit\n");
    printf("Enter choice: ");
}

void registerMember(char name[], int *studentID, int *memberType)
{
    printf("Enter name: ");
    scanf(" %49[^\n]", name);
    printf("Enter student ID: ");
    scanf("%d", studentID);
    do {
        printf("Membership type (1 = Student, 2 = Faculty): ");
        scanf("%d", memberType);
        if (*memberType != 1 && *memberType != 2)
            printf("Invalid membership type!\n");
    } while (*memberType != 1 && *memberType != 2);
    printf("Member registered successfully.\n");
}

void displayBooks(int bookIDs[], char bookTitles[][50], int availableCopies[], int totalBooks)
{
    int i;
    printf("\n%-6s %-25s %-6s\n", "ID", "Title", "Copies");
    printf("----------------------------------------\n");
    for (i = 0; i < totalBooks; i++)
        printf("%-6d %-25s %-6d\n", bookIDs[i], bookTitles[i], availableCopies[i]);
}

void borrowBook(int bookIDs[], char bookTitles[][50], int availableCopies[],
                int totalBooks, int borrowedBookIDs[], int *borrowedCount, int memberType)
{
    int id, days, i, idx = -1;

    if (*borrowedCount >= 3) {
        printf("Borrowing limit reached (maximum 3 books).\n");
        return;
    }
    printf("Enter book ID: ");
    scanf("%d", &id);
    printf("Enter number of days you intend to keep the book: ");
    scanf("%d", &days);
    if (days <= 0) {
        printf("Number of days must be positive.\n");
        return;
    }
    if (days > (memberType == 1 ? 14 : 30))
        printf("Note: this exceeds your allowed period; late fines will apply after %d days.\n",
               memberType == 1 ? 14 : 30);

    for (i = 0; i < totalBooks; i++)
        if (bookIDs[i] == id) idx = i;
    if (idx == -1) {
        printf("Invalid book ID.\n");
        return;
    }
    if (availableCopies[idx] == 0) {
        printf("Sorry, no copies of '%s' are available.\n", bookTitles[idx]);
        return;
    }
    for (i = 0; i < *borrowedCount; i++)
        if (borrowedBookIDs[i] == id) {
            printf("You have already borrowed this book.\n");
            return;
        }

    borrowedBookIDs[*borrowedCount] = id;
    (*borrowedCount)++;
    availableCopies[idx]--;
    printf("You borrowed '%s'.\n", bookTitles[idx]);
}

float returnBook(int bookIDs[], int availableCopies[], int totalBooks,
                 int borrowedBookIDs[], int *borrowedCount, int memberType, float *totalFine)
{
    int id, days, i, idx = -1, pos = -1, allowed, rate;
    float fine = 0;
    char code[30];

    printf("Enter book ID to return: ");
    scanf("%d", &id);
    printf("Enter actual number of days the book was kept: ");
    scanf("%d", &days);
    if (days <= 0) {
        printf("Number of days must be positive.\n");
        return 0;
    }
    for (i = 0; i < *borrowedCount; i++)
        if (borrowedBookIDs[i] == id) pos = i;
    if (pos == -1) {
        printf("You have not borrowed this book.\n");
        return 0;
    }
    for (i = 0; i < totalBooks; i++)
        if (bookIDs[i] == id) idx = i;

    availableCopies[idx]++;

    allowed = (memberType == 1) ? 14 : 30;
    rate = (memberType == 1) ? 20 : 10;
    if (days > allowed) fine = (float)(days - allowed) * rate;

    *totalFine += fine;

    if (fine > 0) {
        printf("Late fine: Rs. %.2f\n", fine);
        printf("Enter membership code for waiver (or any text to skip): ");
        scanf("%29s", code);
        if (strcmp(code, "LIB2026") == 0) {
            fine = fine * 0.5f;
            printf("Code accepted. 50%% waiver applied.\n");
        } else {
            printf("Incorrect code. No waiver applied.\n");
        }
    } else {
        printf("Returned on time. No fine.\n");
    }

    for (i = pos; i < *borrowedCount - 1; i++)
        borrowedBookIDs[i] = borrowedBookIDs[i + 1];
    (*borrowedCount)--;

    printf("Fine payable for this return: Rs. %.2f\n", fine);
    return fine;
}

void displayMemberRecord(char name[], int studentID, int memberType,
                         int borrowedBookIDs[], int borrowedCount,
                         float totalFine, float fineAfterWaiver)
{
    int i;
    printf("\n----- MEMBER RECORD -----\n");
    printf("Name: %s\n", name);
    printf("Student ID: %d\n", studentID);
    printf("Membership type: %s\n", memberType == 1 ? "Student" : "Faculty");
    printf("Currently borrowed books: ");
    if (borrowedCount == 0) printf("None");
    for (i = 0; i < borrowedCount; i++) printf("%d ", borrowedBookIDs[i]);
    printf("\nTotal fine before waiver: Rs. %.2f\n", totalFine);
    printf("Final fine payable after waiver: Rs. %.2f\n", fineAfterWaiver);
}

int main(void)
{
    int bookIDs[4] = {101, 102, 103, 104};
    char bookTitles[4][50] = {"Programming in C", "Data Structures",
                              "Database Systems", "Computer Networks"};
    int availableCopies[4] = {5, 3, 0, 4};
    int totalBooks = 4;

    char name[50] = "";
    int studentID = 0, memberType = 0, registered = 0;
    int borrowedBookIDs[3], borrowedCount = 0;
    float totalFine = 0, fineAfterWaiver = 0, payable;
    int choice;

    do {
        displayMenu();
       if (scanf("%d", &choice) != 1) {
    choice = 0;
    while (getchar() != '\n');
   }

        switch (choice) {
        case 1:
            registerMember(name, &studentID, &memberType);
            registered = 1;
            borrowedCount = 0;
            totalFine = 0;
            fineAfterWaiver = 0;
            break;
        case 2:
            displayBooks(bookIDs, bookTitles, availableCopies, totalBooks);
            break;
        case 3:
            if (!registered) printf("Please register a member first.\n");
            else borrowBook(bookIDs, bookTitles, availableCopies, totalBooks,
                            borrowedBookIDs, &borrowedCount, memberType);
            break;
        case 4:
            if (!registered) printf("Please register a member first.\n");
            else {
                payable = returnBook(bookIDs, availableCopies, totalBooks,
                                     borrowedBookIDs, &borrowedCount, memberType, &totalFine);
                fineAfterWaiver += payable;
            }
            break;
        case 5:
            if (!registered) printf("Please register a member first.\n");
            else displayMemberRecord(name, studentID, memberType, borrowedBookIDs,
                                     borrowedCount, totalFine, fineAfterWaiver);
            break;
        case 6:
            printf("Goodbye!\n");
            break;
        default:
            printf("Invalid choice! Try again.\n");
        }
    } while (choice != 6);

    return 0;
}
