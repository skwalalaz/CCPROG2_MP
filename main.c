#include "header.h"
#include "functions.c"

/******************************************************************************
This is to certify that this project is my own work, based on my personal
efforts in studying and applying the concepts learned. I have constructed
the functions and their respective algorithms and corresponding code by
myself. The program was run, tested, and debugged by my own efforts. I
further certify that I have not copied in part or whole or otherwise
plagiarized the work of other students and/or persons.

<ANTONIO, Juan Carlos T.> - <12348090> - <S26>
<LUCAS, Gian Carlo H.> - <12346829> - <S26>
******************************************************************************/

int main() {

    Directory directory;
    char filename[MAX_LETTERS] = ""; //starts as an empty string, will be updated later on with load/save option

    //Initialize directory to be empty upon program start (default)
    directory.numEntries = 0;

    printf("Welcome to the Greenie Food Directory!\n");
    printf("You may load an existing directory or create a new one inside the menu.\n");

    MainMenu(&directory, filename);

    return 0;
}