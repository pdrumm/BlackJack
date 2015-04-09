/*
 * Patrick Drumm
 * cse20212
 * lab 4, Part 3
 */
#ifndef PLAYER_H
#define PLAYER_H

#include <deque>
#include <iostream>
using namespace std;

class Player {
	friend ostream &operator<<(ostream &, Player &);	// overloaded output operator
	public:
		Player(int=0, int=0);	// non-default constructor takes in input of isUser and isDealer
		void addCard(int);	// adds int to player's hand
		int handSum();		// returns the point value of the player's hand
		int getStay();		// returns if the players isStaying value
		int getIsUser();	// returns true(1) if the player is the user
		int getIsDealer();	// returns true(1) if the player is the dealer
		void userHit();		// asks the user if they would like to continue hitting (vs. staying)
		void clearHand();	// empty the player's hand and reset isStaying/turnOver to zero
		void addWin();		// add a win to player if they won the previos round
		int getWins();		// return the player's number of wins
		void setStay();		// set the player to staying mode
		void setTurnOver();	// end the player's turn
	private:
		int numWins;		// number of games the player has won
		deque<int> hand;	// player's hand of cards
		int isUser;		// true if the player is the user
		int isDealer;		// true if the player is the dealer
		int isStaying;		// 0 when player is still hitting. 1 when they are done and want to stay
		int turnOver;		// 1 when the player's turn is over

};

#endif
