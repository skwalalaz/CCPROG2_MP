#include "header.h"
#include <ctype.h>

void stripNewline(char *str) {
    int len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

// Converts string to lowercase (used for case-insensitive match)
void toLowerCase(const char *src, char *dest) {
    while (*src) {
        *dest = tolower(*src);
        src++;
        dest++;
    }
    *dest = '\0';
}

int stringAlreadyExists(StringName list[], int count, const char *value) {
    for (int i = 0; i < count; i++) {
        if (strcmp(list[i], value) == 0) {
            return 1;  // found
        }
    }
    return 0;  // not found
}

void findPriceRange(const Directory *directory, int *min, int *max) {
    if (directory->numEntries == 0) {
        *min = *max = -1;
        return;
    }

    *min = directory->entry[0].Price.MinPrice;
    *max = directory->entry[0].Price.MaxPrice;

    for (int i = 1; i < directory->numEntries; i++) {
        int curMin = directory->entry[i].Price.MinPrice;
        int curMax = directory->entry[i].Price.MaxPrice;

        if (curMin < *min) *min = curMin;
        if (curMax > *max) *max = curMax;
    }
} 

// ----- CRUD Operation Helpers -----

void userInputText(const char *label, char *dest, int maxLen) {
    printf("%s: ", label);
    fgets(dest, maxLen, stdin);
    stripNewline(dest);

    if (strlen(dest) == 0) {
        printf("Input cannot be empty.\n");
    }
}

int userInputNum(const char *label) {
    char buffer[20];
    printf("%s: ", label);
    fgets(buffer, sizeof(buffer), stdin);
    stripNewline(buffer);

    if (strlen(buffer) == 0) return -1;

    return atoi(buffer);
}

void promptPriceRange(PriceRange *price) {
    int min, max;

    do {
        min = userInputNum("Min Price");
        max = userInputNum("Max Price");

        if (min < 0 || max < 0 || max < min) {
            printf("Invalid price range. Please try again.\n");
        }
    } while (min < 0 || max < 0 || max < min);

    price->MinPrice = min;
    price->MaxPrice = max;
}

void promptPopularItems(int *count, StringName items[]) {
    int n = userInputNum("How many popular items? (max 5)");

    if (n < 0 || n > MAX_ITEMS) {
        printf("Invalid number of items.\n");
        *count = 0;
        return;
    }

    *count = n;

    for (int i = 0; i < n; i++) {
        char label[40];
        sprintf(label, "Item %d", i + 1);
        userInputText(label, items[i], MAX_LETTERS);
    }
}

// Matches a single entry against all filters (AND logic)
int filterMatch(EstablishmentDetails *e, const char *location, const char *category, const char *payment, const char *serving, int userMin, int userMax){
    char loc1[MAX_LETTERS], loc2[MAX_LETTERS];
    char cat1[MAX_LETTERS], cat2[MAX_LETTERS];
    char pay1[MAX_LETTERS], pay2[MAX_LETTERS];
    char serve1[MAX_LETTERS], serve2[MAX_LETTERS];

    // Case-insensitive comparison
    toLowerCase(e->Location, loc1); toLowerCase(location, loc2);
    toLowerCase(e->FoodCateg, cat1); toLowerCase(category, cat2);
    toLowerCase(e->PaymentOpt, pay1); toLowerCase(payment, pay2);
    toLowerCase(e->ServingMode, serve1); toLowerCase(serving, serve2);

    if (strlen(location) > 0 && strcmp(loc1, loc2) != 0) return 0;
    if (strlen(category) > 0 && strcmp(cat1, cat2) != 0) return 0;
    if (strlen(payment) > 0 && strcmp(pay1, pay2) != 0) return 0;
    if (strlen(serving) > 0 && strcmp(serve1, serve2) != 0) return 0;

    int isValid = 1;

    if (userMin != -1) {
    if (e->Price.MinPrice >= userMin) {
        // OK
    } else {
        isValid = 0;
    }
    }

    if (userMax != -1) {
    if (e->Price.MaxPrice <= userMax) {
        // OK
    } else {
        isValid = 0;
    }
    }

    if (!isValid) return 0;


    return 1;  // All filters matched
}

// Displays available filter values (no duplicates)
void printFilterHints(Directory *directory) {
    char locations[MAX_ENTRIES][MAX_LETTERS];
    char categories[MAX_ENTRIES][MAX_LETTERS];
    char payments[MAX_ENTRIES][MAX_LETTERS];
    char servings[MAX_ENTRIES][MAX_LETTERS];
    int locCount = 0, catCount = 0, payCount = 0, serveCount = 0;

    int minPrice = -1, maxPrice = -1;

    for (int i = 0; i < directory->numEntries; i++) {
        EstablishmentDetails *e = &directory->entry[i];

        if (!stringAlreadyExists(locations, locCount, e->Location)) {
            strcpy(locations[locCount++], e->Location);
        }

        if (!stringAlreadyExists(categories, catCount, e->FoodCateg)) {
            strcpy(categories[catCount++], e->FoodCateg);
        }

        if (!stringAlreadyExists(payments, payCount, e->PaymentOpt)) {
            strcpy(payments[payCount++], e->PaymentOpt);
        }

        if (!stringAlreadyExists(servings, serveCount, e->ServingMode)) {
            strcpy(servings[serveCount++], e->ServingMode);
        }

        if (e->Price.MinPrice > 0 && e->Price.MaxPrice > 0) {
            if (minPrice == -1 || e->Price.MinPrice < minPrice) {
                minPrice = e->Price.MinPrice;
            }
            if (maxPrice == -1 || e->Price.MaxPrice > maxPrice) {
                maxPrice = e->Price.MaxPrice;
            }
        }
    }

    int maxCount = locCount;
    if (catCount > maxCount) maxCount = catCount;
    if (payCount > maxCount) maxCount = payCount;
    if (serveCount > maxCount) maxCount = serveCount;

    printf("\n=================== FILTER HINTS ===================\n\n");
    printf("+------------------------+------------------------+------------------------+------------------------+\n");
    printf("| Location               | Category               | Payment Option         | Serving Mode           |\n");
    printf("+------------------------+------------------------+------------------------+------------------------+\n");

    for (int i = 0; i < maxCount; i++) {
        printf("| ");
        if (i < locCount)
            printf("%-22s", locations[i]);
        else
            printf("%-22s", "");

        printf(" | ");
        if (i < catCount)
            printf("%-22s", categories[i]);
        else
            printf("%-22s", "");

        printf(" | ");
        if (i < payCount)
            printf("%-22s", payments[i]);
        else
            printf("%-22s", "");

        printf(" | ");
        if (i < serveCount)
            printf("%-22s", servings[i]);
        else
            printf("%-22s", "");

        printf(" |\n");
    }

    printf("+------------------------+------------------------+------------------------+------------------------+\n");

    if (minPrice != -1 && maxPrice != -1) {
        printf("\nAvailable Price Range:\n");
        printf("  Minimum: %d\n", minPrice);
        printf("  Maximum: %d\n", maxPrice);
    }

    printf("\n====================================================\n");
}

// Prompts the user for all filters at once
void promptFilters(char *location, char *category, char *payment, char *serving, int *min, int *max, int singleMode) {
    char buffer[20];

    if (singleMode) {
        int choice;
        printf("\n====== SINGLE FILTER OPTIONS ======\n");
        printf("1. Location\n");
        printf("2. Category\n");
        printf("3. Payment Option\n");
        printf("4. Serving Mode\n");
        printf("5. Price Range\n");
        printf("===================================\n\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                printf("Location: ");
                fgets(location, MAX_LETTERS, stdin);
                stripNewline(location);
                break;

            case 2:
                printf("Category: ");
                fgets(category, MAX_LETTERS, stdin);
                stripNewline(category);
                break;

            case 3:
                printf("Payment Option: ");
                fgets(payment, MAX_LETTERS, stdin);
                stripNewline(payment);
                break;

            case 4:
                printf("Serving Mode: ");
                fgets(serving, MAX_LETTERS, stdin);
                stripNewline(serving);
                break;

            case 5:
                printf("Min Price (leave blank to skip): ");
                fgets(buffer, sizeof(buffer), stdin);
                stripNewline(buffer);
                if (strlen(buffer) > 0) {
                    *min = atoi(buffer);
                } else {
                    *min = -1;
                }

                printf("Max Price (leave blank to skip): ");
                fgets(buffer, sizeof(buffer), stdin);
                stripNewline(buffer);
                if (strlen(buffer) > 0) {
                    *max = atoi(buffer);
                } else {
                    *max = -1;
                }
                break;

            default:
                printf("Invalid choice.\n");
                break;
        }
    } else {
        printf("\n(Leave blank to skip a filter)\n");

        printf("Location: ");
        fgets(location, MAX_LETTERS, stdin);
        stripNewline(location);

        printf("Category: ");
        fgets(category, MAX_LETTERS, stdin);
        stripNewline(category);

        printf("Payment Option: ");
        fgets(payment, MAX_LETTERS, stdin);
        stripNewline(payment);

        printf("Serving Mode: ");
        fgets(serving, MAX_LETTERS, stdin);
        stripNewline(serving);

        printf("Min Price: ");
        fgets(buffer, sizeof(buffer), stdin);
        stripNewline(buffer);
        if (strlen(buffer) > 0) {
            *min = atoi(buffer);
        } else {
            *min = -1;
        }

        printf("Max Price: ");
        fgets(buffer, sizeof(buffer), stdin);
        stripNewline(buffer);
        if (strlen(buffer) > 0) {
            *max = atoi(buffer);
        } else {
            *max = -1;
        }
    }
}
