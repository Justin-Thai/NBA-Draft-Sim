/*
 * A nbadraft class that runs the NBA draft simulator  
 * 
 * @author Aaron Dang, Justin Thai
 * @version 23 November 2020
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "Team.c"

// Function prototypes
void validate(int);
void serpentine(int, struct league, struct player*);
void botSelect(int, struct league, struct player*);

// Main function 
int main(void) {
    // Initializing player list
    struct player allPlayers[ALL_PLAYERS];
    getAllPlayers(allPlayers);

    // Starting draft simulation and asks user for number of teams in mock draft 
    int members;
    printf("\nWelcome to your own Mock Fantasy NBA Draft!\n\n");
    printf("Rules:\n- Each player will be allowed to draft 2 guards (G), 2 forwards (F), 1 center (C), and 1 bench player (any position)\n- Draft will be in a serpentine order\n");
    printf("Please enjoy and best wishes to your team!\n");
    printf("\nPlease enter the amount of players (6, 8, 10, 12): ");
    scanf("%d", &members);
    validate(members);

    // Initializing league with indicated number of teams
    struct league theLeague;
    theLeague.numTeams = members;
    initializeLeague(&theLeague, theLeague.numTeams);

    // Starting the serpentine draft
    serpentine(theLeague.numTeams, theLeague, allPlayers);

    // Printing the lineup for each team in the league and exiting program
    // viewLineups(theLeague.numTeams, theLeague, allPlayers);
    printf("\nThank you for using our application! Best of wishes to your team!");
    return 0;
}

/*
 * Validates the number of teams indicated by the user
 * 
 * @param numTeams the number of teams indicated by the user
 */ 
void validate(int numTeams){
    if(numTeams == 6 || numTeams == 8 || numTeams == 10 || numTeams == 12) {
        printf("Amount of players have been confirmed\n\n");
    }
    else {
        printf("Amount of players are not valid.");
        exit(1);
    }
}

/*
 * Program autonomously chooses players for other teams by random
 * 
 * @param i the team that is drafting their player
 * @param theLeague the league that holds teams
 * @param *allPlayers pointer to array of players 
 */ 
void botSelect(int i, struct league theLeague, struct player *allPlayers) {
    // Generating a random number that is used to pick the team's player 
    int lower = 1; 
    int upper = 150;
    srand(time(0));
    int random_number = (rand() % (upper - lower + 1)) + lower;
    struct player currentPlayer = allPlayers[random_number-1];
    // Random number continues to be generated until program picks an 
    // undrafted player that fits in their lineup
    while(!addPlayer(&theLeague.allTeams[i], random_number, allPlayers)) {
    	random_number = (rand() % (upper - lower + 1)) + lower;
        currentPlayer = allPlayers[random_number-1];
    }
    // Printing drafted player 
    printf("Player %d selects: %s %s, %c, %s\n", i+1, currentPlayer.firstName, currentPlayer.lastName, 
        currentPlayer.position, currentPlayer.team);
}

/*
 * Runs draft using serpentine format (e.g. Teams 1-6 pick, then 6-1) and 
 * prints the final lineup of the user's team
 * 
 * @param numTeams number of teams in league
 * @param theLeague the league that holds teams
 * @param *allPlayers pointer to array of players
 */ 
void serpentine(int numTeams, struct league theLeague, struct player *allPlayers){
    int playerIndex;
    struct player currentPlayer;
    // Running draft for 6 teams
    if(numTeams == 6) {
        for(int j = 0; j < MAX_PLAYERS / 2; j++) {
            // Player 1 (User) selects player 
            printf("All Players Available:\n");
            viewPlayers(allPlayers, ALL_PLAYERS);
            // Asking user for desried player (by choosing corresponding number)
            printf("Please choose a number corresponding to the player you want to draft: ");
            scanf("%d", &playerIndex);
            currentPlayer = allPlayers[playerIndex-1];
            // Continues to ask user to choose a player until an undrafted player fits their lineup 
            while(!addPlayer(&theLeague.allTeams[0], playerIndex, allPlayers)) {
                printf("Failed to add player. Make sure that you do not exceed the position limits (2 Guards, 2 Forwards, 1 Center, 1 Bench of any position).\nPlease choose another player: ");
                scanf("%d", &playerIndex);
                currentPlayer = allPlayers[playerIndex-1];
            }
            // Printing selected player
            printf("You selected: %s %s, %c, %s\n\n", currentPlayer.firstName, currentPlayer.lastName, 
                currentPlayer.position, currentPlayer.team);

            // Players 2-6 (Bots) select players
            botSelect(1, theLeague, allPlayers);
            botSelect(2, theLeague, allPlayers);
            botSelect(3, theLeague, allPlayers);
            botSelect(4, theLeague, allPlayers);
            botSelect(5, theLeague, allPlayers);
            printf("\n");
            // Players 6-2 (Bots) select players
            botSelect(5, theLeague, allPlayers);
            botSelect(4, theLeague, allPlayers);
            botSelect(3, theLeague, allPlayers);
            botSelect(2, theLeague, allPlayers);
            botSelect(1, theLeague, allPlayers);           
            
            // Player 1 (User) selects player 
            printf("\nAll Players Available:\n");
            viewPlayers(allPlayers, ALL_PLAYERS);
            // Asking user for desried player (by choosing corresponding number)
            printf("Please choose a number corresponding to the player you want to draft: ");
            scanf("%d", &playerIndex);
            currentPlayer = allPlayers[playerIndex-1];
            // Continues to ask user to choose a player until an undrafted player fits their lineup 
            while(!addPlayer(&theLeague.allTeams[0], playerIndex, allPlayers)) {
                printf("Failed to add player. Make sure that you do not exceed the position limits (2 Guards, 2 Forwards, 1 Center, 1 Bench of any position).\nPlease choose another player: ");
                scanf("%d", &playerIndex);
                currentPlayer = allPlayers[playerIndex-1];
            }
            // Printing selected player
            printf("You selected: %s %s, %c, %s\n\n", currentPlayer.firstName, currentPlayer.lastName, 
                currentPlayer.position, currentPlayer.team);
        }
        printf("Your team's roster is:\n");
        for(int j = 0; j < MAX_PLAYERS; j++) {
            struct player thisPlayer = allPlayers[(theLeague.allTeams[0].lineup[j] - 1)];
            printf("%d. %s %s, %c, %s\n", j+1, thisPlayer.firstName, thisPlayer.lastName,
                thisPlayer.position, thisPlayer.team);
        }
    }
    // Running draft for 8 teams
    if(numTeams == 8) {
        for(int j = 0; j < MAX_PLAYERS / 2; j++) {
            // Player 1 (User) selects player 
            printf("All Players Available:\n");
            viewPlayers(allPlayers, ALL_PLAYERS);
            // Asking user for desried player (by choosing corresponding number)
            printf("Please choose a number corresponding to the player you want to draft: ");
            scanf("%d", &playerIndex);
            currentPlayer = allPlayers[playerIndex-1];
            // Continues to ask user to choose a player until an undrafted player fits their lineup 
            while(!addPlayer(&theLeague.allTeams[0], playerIndex, allPlayers)) {
                printf("Failed to add player. Make sure that you do not exceed the position limits (2 Guards, 2 Forwards, 1 Center, 1 Bench of any position).\nPlease choose another player: ");
                scanf("%d", &playerIndex);
                currentPlayer = allPlayers[playerIndex-1];
            }
            // Printing selected player
            printf("You selected: %s %s, %c, %s\n\n", currentPlayer.firstName, currentPlayer.lastName, 
                currentPlayer.position, currentPlayer.team);

            // Players 2-8 (Bots) select players
            botSelect(1, theLeague, allPlayers);
            botSelect(2, theLeague, allPlayers);
            botSelect(3, theLeague, allPlayers);
            botSelect(4, theLeague, allPlayers);
            botSelect(5, theLeague, allPlayers);
            botSelect(6, theLeague, allPlayers);
            botSelect(7, theLeague, allPlayers);
            printf("\n");
            // Players 6-2 (Bots) select players
            botSelect(7, theLeague, allPlayers);
            botSelect(6, theLeague, allPlayers);
            botSelect(5, theLeague, allPlayers);
            botSelect(4, theLeague, allPlayers);
            botSelect(3, theLeague, allPlayers);
            botSelect(2, theLeague, allPlayers);
            botSelect(1, theLeague, allPlayers);           
            
            // Player 1 (User) selects player 
            printf("\nAll Players Available:\n");
            viewPlayers(allPlayers, ALL_PLAYERS);
            // Asking user for desried player (by choosing corresponding number)
            printf("Please choose a number corresponding to the player you want to draft: ");
            scanf("%d", &playerIndex);
            currentPlayer = allPlayers[playerIndex-1];
            // Continues to ask user to choose a player until an undrafted player fits their lineup 
            while(!addPlayer(&theLeague.allTeams[0], playerIndex, allPlayers)) {
                printf("Failed to add player. Make sure that you do not exceed the position limits (2 Guards, 2 Forwards, 1 Center, 1 Bench of any position).\nPlease choose another player: ");
                scanf("%d", &playerIndex);
                currentPlayer = allPlayers[playerIndex-1];
            }
            // Printing selected player
            printf("You selected: %s %s, %c, %s\n\n", currentPlayer.firstName, currentPlayer.lastName, 
                currentPlayer.position, currentPlayer.team);
        }
        printf("Your team's roster is:\n");
        for(int j = 0; j < MAX_PLAYERS; j++) {
            struct player thisPlayer = allPlayers[(theLeague.allTeams[0].lineup[j] - 1)];
            printf("%d. %s %s, %c, %s\n", j+1, thisPlayer.firstName, thisPlayer.lastName,
                thisPlayer.position, thisPlayer.team);
        }
    }
    // Running teams for 10 teams
    if(numTeams == 10) {
        for(int j = 0; j < MAX_PLAYERS / 2; j++) {
            // Player 1 (User) selects player 
            printf("All Players Available:\n");
            viewPlayers(allPlayers, ALL_PLAYERS);
            // Asking user for desried player (by choosing corresponding number)
            printf("Please choose a number corresponding to the player you want to draft: ");
            scanf("%d", &playerIndex);
            currentPlayer = allPlayers[playerIndex-1];
            // Continues to ask user to choose a player until an undrafted player fits their lineup 
            while(!addPlayer(&theLeague.allTeams[0], playerIndex, allPlayers)) {
                printf("Failed to add player. Make sure that you do not exceed the position limits (2 Guards, 2 Forwards, 1 Center, 1 Bench of any position).\nPlease choose another player: ");
                scanf("%d", &playerIndex);
                currentPlayer = allPlayers[playerIndex-1];
            }
            // Printing selected player
            printf("You selected: %s %s, %c, %s\n\n", currentPlayer.firstName, currentPlayer.lastName, 
                currentPlayer.position, currentPlayer.team);

            // Players 2-10 (Bots) select players
            botSelect(1, theLeague, allPlayers);
            botSelect(2, theLeague, allPlayers);
            botSelect(3, theLeague, allPlayers);
            botSelect(4, theLeague, allPlayers);
            botSelect(5, theLeague, allPlayers);
            botSelect(6, theLeague, allPlayers);
            botSelect(7, theLeague, allPlayers);
            botSelect(8, theLeague, allPlayers);
            botSelect(9, theLeague, allPlayers);
            printf("\n");
            // Players 10-2 (Bots) select players
            botSelect(9, theLeague, allPlayers);
            botSelect(8, theLeague, allPlayers);
            botSelect(7, theLeague, allPlayers);
            botSelect(6, theLeague, allPlayers);
            botSelect(5, theLeague, allPlayers);
            botSelect(4, theLeague, allPlayers);
            botSelect(3, theLeague, allPlayers);
            botSelect(2, theLeague, allPlayers);
            botSelect(1, theLeague, allPlayers);           
            
            // Player 1 (User) selects player 
            printf("\nAll Players Available:\n");
            viewPlayers(allPlayers, ALL_PLAYERS);
            // Asking user for desried player (by choosing corresponding number)
            printf("Please choose a number corresponding to the player you want to draft: ");
            scanf("%d", &playerIndex);
            currentPlayer = allPlayers[playerIndex-1];
            // Continues to ask user to choose a player until an undrafted player fits their lineup 
            while(!addPlayer(&theLeague.allTeams[0], playerIndex, allPlayers)) {
                printf("Failed to add player. Make sure that you do not exceed the position limits (2 Guards, 2 Forwards, 1 Center, 1 Bench of any position).\nPlease choose another player: ");
                scanf("%d", &playerIndex);
                currentPlayer = allPlayers[playerIndex-1];
            }
            // Printing selected player
            printf("You selected: %s %s, %c, %s\n\n", currentPlayer.firstName, currentPlayer.lastName, 
                currentPlayer.position, currentPlayer.team);
        }
        printf("Your team's roster is:\n");
        for(int j = 0; j < MAX_PLAYERS; j++) {
            struct player thisPlayer = allPlayers[(theLeague.allTeams[0].lineup[j] - 1)];
            printf("%d. %s %s, %c, %s\n", j+1, thisPlayer.firstName, thisPlayer.lastName,
                thisPlayer.position, thisPlayer.team);
        }
    }
    // Running draft for 12 teams
    if(numTeams == 12) {
        for(int j = 0; j < MAX_PLAYERS / 2; j++) {
            // Player 1 (User) selects player 
            printf("All Players Available:\n");
            viewPlayers(allPlayers, ALL_PLAYERS);
            // Asking user for desried player (by choosing corresponding number)
            printf("Please choose a number corresponding to the player you want to draft: ");
            scanf("%d", &playerIndex);
            currentPlayer = allPlayers[playerIndex-1];
            // Continues to ask user to choose a player until an undrafted player fits their lineup 
            while(!addPlayer(&theLeague.allTeams[0], playerIndex, allPlayers)) {
                printf("Failed to add player. Make sure that you do not exceed the position limits (2 Guards, 2 Forwards, 1 Center, 1 Bench of any position).\nPlease choose another player: ");
                scanf("%d", &playerIndex);
                currentPlayer = allPlayers[playerIndex-1];
            }
            // Printing selected player
            printf("You selected: %s %s, %c, %s\n\n", currentPlayer.firstName, currentPlayer.lastName, 
                currentPlayer.position, currentPlayer.team);

            // Players 2-12 (Bots) select players
            botSelect(1, theLeague, allPlayers);
            botSelect(2, theLeague, allPlayers);
            botSelect(3, theLeague, allPlayers);
            botSelect(4, theLeague, allPlayers);
            botSelect(5, theLeague, allPlayers);
            botSelect(6, theLeague, allPlayers);
            botSelect(7, theLeague, allPlayers);
            botSelect(8, theLeague, allPlayers);
            botSelect(9, theLeague, allPlayers);
            botSelect(10, theLeague, allPlayers);
            botSelect(11, theLeague, allPlayers);
            printf("\n");
            // Players 12-2 (Bots) select players
            botSelect(11, theLeague, allPlayers);
            botSelect(10, theLeague, allPlayers);
            botSelect(9, theLeague, allPlayers);
            botSelect(8, theLeague, allPlayers);
            botSelect(7, theLeague, allPlayers);
            botSelect(6, theLeague, allPlayers);
            botSelect(5, theLeague, allPlayers);
            botSelect(4, theLeague, allPlayers);
            botSelect(3, theLeague, allPlayers);
            botSelect(2, theLeague, allPlayers);
            botSelect(1, theLeague, allPlayers);             
            
            // Player 1 (User) selects player 
            printf("\nAll Players Available:\n");
            viewPlayers(allPlayers, ALL_PLAYERS);
            // Asking user for desried player (by choosing corresponding number)
            printf("Please choose a number corresponding to the player you want to draft: ");
            scanf("%d", &playerIndex);
            currentPlayer = allPlayers[playerIndex-1];
            // Continues to ask user to choose a player until an undrafted player fits their lineup 
            while(!addPlayer(&theLeague.allTeams[0], playerIndex, allPlayers)) {
                printf("Failed to add player. Make sure that you do not exceed the position limits (2 Guards, 2 Forwards, 1 Center, 1 Bench of any position).\nPlease choose another player: ");
                scanf("%d", &playerIndex);
                currentPlayer = allPlayers[playerIndex-1];
            }
            // Printing selected player
            printf("You selected: %s %s, %c, %s\n\n", currentPlayer.firstName, currentPlayer.lastName, 
                currentPlayer.position, currentPlayer.team);
        }
        printf("Your team's roster is:\n");
        for(int j = 0; j < MAX_PLAYERS; j++) {
            struct player thisPlayer = allPlayers[(theLeague.allTeams[0].lineup[j] - 1)];
            printf("%d. %s %s, %c, %s\n", j+1, thisPlayer.firstName, thisPlayer.lastName,
                thisPlayer.position, thisPlayer.team);
        }
    }
} 