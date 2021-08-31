/*
 * A Player class that manages the players in the NBA mock draft pool
 * 
 * @author Aaron Dang, Justin Thai
 * @version 23 November 2020
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Constants 
#define MAX_NAME 20
#define ALL_PLAYERS 150

// Player structure
struct player {
    char firstName[MAX_NAME];
    char lastName[MAX_NAME];
    char position;
    char team[4];
    bool drafted;
};

// Function prototypes
void getAllPlayers(struct player*);
void viewPlayers(struct player*, int);

/*
 * Gets all players from text file and puts them into an array of structures
 * 
 * @param *playerList pointer to array of structures to accept players
 */ 
void getAllPlayers(struct player *playerList) {
    FILE *fp;
    fp = fopen("NBAPlayerPool.txt", "r");
    if(fp == NULL) {
        printf("Failed to open file");
        exit(1);
    }
    // Inserting players from text file into playerList array
    for(int i = 0; i < ALL_PLAYERS; i++) {
        fscanf(fp, "%s %s %c %s", playerList[i].lastName, playerList[i].firstName, 
            &playerList[i].position, playerList[i].team);
        playerList[i].drafted = false;
    }
    fclose(fp);
}

/*
 * Prints all players in player list and marks drafted players as unavailable
 * 
 * @param *playerList pointer to array of strucutres with players
 * @param arraySize size of playerList
 */ 
void viewPlayers(struct player *playerList, int arraySize) {
    int playerCount = 0;
    for(int i = 0; i < arraySize; i++) {
        playerCount++;
        // Printing undrafted players
        if(playerList[i].drafted == false) {
            printf("%d. %s %s, %c, %s\n", playerCount, playerList[i].firstName,
                playerList[i].lastName, playerList[i].position, playerList[i].team);
        }
        // Marking drafted players as unavailable and printing it
        else {
            printf("%d. %s %s, %c, %s (Unavailable)\n", playerCount, playerList[i].firstName, 
                playerList[i].lastName, playerList[i].position, playerList[i].team);
        }
    }
    printf("\n");
}