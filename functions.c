#include "header.h"

// ----- Main Menu and Modes -----

void MainMenu(Directory *directory, char filename[]){
    int choice;
    int running = 1;

    printf("\n========== MAIN MENU ==========\n");
    printf("1. Admin Mode\n");
    printf("2. User Mode\n");
    printf("3. Load from File\n");
    printf("4. Save to File \n");
    printf("5. Exit\n");
    printf("================================\n\n");
    printf("--INPUT NUMBER ONLY--\n");
    printf("Enter choice: ");
    scanf("%d", &choice);
    getchar();  // to remove leftover newline

    while(running) {

        switch (choice) {
            case 1:
                AdminMode(directory);
                break;

            case 2:
                UserMode(directory);
                break;

            case 3: {
                printf("Enter filename to load: ");
                fgets(filename, sizeof(filename), stdin);
                stripNewline(filename);
                loadFromFile(directory, filename);
                printf("Loaded from '%s'\n", filename);
                break;
            }

            case 4:
                handleSave(directory, filename);
                break;

            case 5: {
                int saveChoice;
                printf("Save before exiting? (1 = Yes / 0 = No): ");
                scanf("%d", &saveChoice);
                getchar();

                if (saveChoice == 1) {
                    handleSave(directory, filename);
                }

                running = 0;  // Exit loop
                break;
            }

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    printf("Exiting program. Goodbye!\n");

}

void AdminMode(Directory *directory){
    int choice;
    int running = 1;

    printf("\n========== ADMIN MODE ==========\n");
    printf("1. Add Establishment\n");
    printf("2. Edit Establishment\n");
    printf("3. Delete Establishment\n");
    printf("4. Back to Main Menu\n");
    printf("================================\n\n");
    printf("--INPUT NUMBER ONLY--\n");
    printf("Enter choice: ");
    scanf("%d", &choice);
    getchar();  // to remove leftover newline

    while(running) {
        switch(choice) {
        case 1: addEstablishment(directory); break;

        case 2: editEstablishment(directory); break;

        case 3: deleteEstablishment(directory); break;

        case 4: running = 0; break;

        default: printf("Invalid Input\n");
        }
    }
}

void UserMode(Directory *directory){
    int choice;
    int running = 1;

    printf("\n========== USER MODE ==========\n");
    printf("1. Add Establishment\n");
    printf("2. Edit Establishment\n");
    printf("3. Delete Establishment\n");
    printf("4. Back to Main Menu\n");
    printf("================================\n\n");
    printf("--INPUT NUMBER ONLY--\n");
    printf("Enter choice: ");
    scanf("%d", &choice);
    getchar();  // to remove leftover newline

}

// ----- CRUD Operations -----

void addEstablishment(Directory *directory){


}

void editEstablishment(Directory *directory){

}

void deleteEstablishment(Directory *directory){

}

// ----- Search and Filters -----

void Search(Directory *directory){

}

void SingleFilter(Directory *directory){

}

void MultipleFilter(Directory *directory){

}

// ----- Display -----

void DisplayTable(EstablishmentDetails entries[], int numEntries){

}

// ----- File Handling -----
void saveToFile(Directory *directory, char filename[]){

}

void loadFromFile(Directory *directory, char filename[]){

}

// ----- Helper Functions -----
void handleSave(Directory *directory, char filename[]){

}

void stripNewline(char *str){

}

// Converts string to lowercase (used for case-insensitive match)
void toLowerCase(const char *src, char *dest){

} 

// Matches a single entry against all filters (AND logic)
int filterMatch(EstablishmentDetails *e, const char *location, const char *category, const char *payment, const char *serving, int userMin, int userMax){

}

// Displays available filter values (no duplicates)
void printFilterHints(Directory *directory){

}

// Prompts the user for all filters at once
void promptFilters(char *location, char *category, char *payment, char *serving, int *min, int *max){
    
}

