NBA Mock Draft Simulator README 

By: Aaron Dang, Justin Thai
CS 49C, Section 1
23 November 2020

********************************************************************************************

This program allows the user to simulate an NBA mock draft in the command line. They can use 
this simulator to build their dream NBA lineup. The user will compete against other teams 
(which are controlled by the program) to draft players and form their team. 

********************************************************************************************

Features/Rules:
- The mock draft has a serpentine draft order
	- e.g. If there are six teams (1-6) in the league, the draft order goes: 
		Team 1 -> Team 2 -> Team 3 -> Team 4 -> Team 5 -> Team 6 -> Team 6 ->
		Team 5 -> Team 4 -> Team 3 -> Team 2 -> Team 1
- Each mock draft can either have 6, 8, 10 or 12 teams in the league (inluding the user)
- Each team consists of 6 players:
	- 2 Guards (G)
	- 2 Forwards (F)
	- 1 Center (C)
	- 1 Bench (any position)
- Each team can choose from 150 current NBA players
	- All players used in this mock draft can be found in "NBAPlayerPool.txt" 
	- NOTE: Do NOT make any edits to "NBAPlayerPool.txt" as doing so can cause the 
	program to produce unexpected behaviors
- The user's lineup will be printed on the command line at the end of the draft

********************************************************************************************

How to Run NBA Mock Draft Simulator: 
1) Make sure all class files and text files are in the same folder. These files are:
	- "Player.c"
	- "Team.c"
	- "nbadraft.c"
	- "NBAPlayerPool.txt"
2) Open "nbadraft.c"
3) Compile and run "nbadraft.c"
4) Command line will prompt user to input the number of teams desired
	- User should either enter 6, 8, 10, or 12
5) Program will start the draft and allow the user to choose players when it is their turn
	- User should enter a number between 1-150 that corresponds to the player they want
	- Keep in mind of players that have been already been drafted (marked unavailable)
	and the position limits that each team has (2 guards, 2 forwards, 1 center, and
	1 bench of any position)
6) Program will end after all teams have drafted their lineup
	- Program will print the final lineup of the user's team

********************************************************************************************

Thank you for using our program and we hope you enjoy!
 


   