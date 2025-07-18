#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Constants
#define MAX_LETTERS 31
#define MAX_NUM 12
#define MAX_ITEMS 5
#define MAX_ENTRIES 50

// Typedefs
typedef char StringName[MAX_LETTERS];
typedef char StringNum[MAX_NUM];

typedef struct {
    int MinPrice;
    int MaxPrice;
} PriceRange;

typedef struct {
    StringName Name;
    StringName Location;
    StringNum ContactNum;
    StringName ServingMode;
    StringName PaymentOpt;
    StringName FoodCateg;
    PriceRange Price;
    int numPopularItems;
    StringName popularItems[MAX_ITEMS];
} EstablishmentDetails;

typedef struct {
    EstablishmentDetails entry[MAX_ENTRIES];
    int numEntries;
} Directory;

// ----- Main Menu and Modes -----
void MainMenu(Directory *directory, char filename[]);
void AdminMode(Directory *directory);
void UserMode(Directory *directory);

// ----- CRUD Operations -----
void addEstablishment(Directory *directory);
void editEstablishment(Directory *directory);
void deleteEstablishment(Directory *directory);

// ----- Search and Filters -----
void Search(Directory *directory);
void SingleFilter(Directory *directory);
void MultipleFilter(Directory *directory);

// ----- Display -----
void DisplayTable(EstablishmentDetails entries[], int numEntries);

// ----- File Handling -----
void saveToFile(Directory *directory, char filename[]);
void loadFromFile(Directory *directory, char filename[]);

// ----- Helper Functions (Optional) -----
void handleSave(Directory *directory, char filename[]);
void stripNewline(char *str);
void toLowerCase(const char *src, char *dest); // Converts string to lowercase (used for case-insensitive match)
int filterMatch(EstablishmentDetails *e,
                const char *location,
                const char *category,
                const char *payment,
                const char *serving,
                int userMin,
                int userMax); // Matches a single entry against all filters (AND logic)

void printFilterHints(Directory *directory); // Displays available filter values (no duplicates)

void promptFilters(char *location,
                   char *category,
                   char *payment,
                   char *serving,
                   int *min,
                   int *max); // Prompts the user for all filters at once


#endif