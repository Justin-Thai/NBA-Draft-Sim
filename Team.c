/*
 * A Team class that manages the teams in the NBA mock draft pool
 * 
 * @author Aaron Dang, Justin Thai
 * @version 23 November 2020
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Player.c"

// Constants 
#define MAX_PLAYERS 6
#define MAX_TEAMS 12

// Team structure
struct team { 
    int playerCount;
    int numGuard;
    int numForward;
    int numCenter;
    int numBench;
    int lineup[MAX_PLAYERS];
};

// League structure (holds all teams)
struct league {
    int numTeams;
    struct team allTeams[MAX_TEAMS];
};

// Function prototypes
void initializeTeam(struct team*);
void initializeLeague(struct league*, int);
bool addPlayer(struct team*, int, struct player*);
 
/*
 * Initializes team with required fields
 * 
 * @param thisTeam team to add selected player
 */ 
void initializeTeam(struct team *thisTeam) {
    thisTeam->playerCount = 0;
    thisTeam->numGuard = 2;
    thisTeam->numForward = 2;
    thisTeam->numCenter = 1;
    thisTeam->numBench = MAX_PLAYERS - 5;
}

/*
 * Initializes league with indicated number of teams
 * 
 * @param thisLeague the league to be initialized
 * @param totalTeam number of teams in league
 */ 
void initializeLeague(struct league *thisLeague, int totalTeams) {
    for(int i = 0; i < totalTeams; i++) {
        initializeTeam(&thisLeague->allTeams[i]);
    }
}

/*
 * Adds selected player to team
 * 
 * @param thisTeam team to add selected player
 * @param playerNumber number order of player in playersList 
 * @param playersList pointer to array of strucutres with players
 * @return if adding player was success
 */ 
bool addPlayer(struct team *thisTeam, int playerNumber, struct player *playersList) {
    // Checking to see if selected player is not drafted
    if(playersList[playerNumber-1].drafted == false) {
        // Checking to see if player is a guard
        if(playersList[playerNumber-1].position == 'G' && thisTeam->numGuard > 0) {
            thisTeam->lineup[thisTeam->playerCount] = playerNumber;
            playersList[playerNumber-1].drafted = true;
            thisTeam->playerCount++;
            thisTeam->numGuard--;
            return true;
        }
        // Checking to see if player is a forward
        else if(playersList[playerNumber-1].position == 'F' && thisTeam->numForward > 0) {
            thisTeam->lineup[thisTeam->playerCount] = playerNumber;
            playersList[playerNumber-1].drafted = true;
            thisTeam->playerCount++;
            thisTeam->numForward--;
            return true;
        }
        // Checking to see if player is a center
        else if(playersList[playerNumber-1].position == 'C' && thisTeam->numCenter == 1) {
            thisTeam->lineup[thisTeam->playerCount] = playerNumber;
            playersList[playerNumber-1].drafted = true;
            thisTeam->playerCount++;
            thisTeam->numCenter--;
            return true;
        }
        // Adding selected player as bench player (when numGuard, numForward, or numCenter is 0)
        else if(thisTeam->numBench > 0) {
            thisTeam->lineup[thisTeam->playerCount] = playerNumber;
            playersList[playerNumber-1].drafted = true;
            thisTeam->playerCount++;
            thisTeam->numBench--;
            return true;
        }
        else {
            return false;
        }
    }
    // Selected player was already drafted or input was invalid
    else {
        return false;
    }
}