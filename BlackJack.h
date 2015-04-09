/*
 * Patrick Drumm
 * cse20212
 * lab 4, Part 3
 */
#ifndef BLACKJACK_H
#define BLACKJACK_H

#include "Player.h"
#include "CardDeck.h"
#include <deque>
using namespace std;

class BlackJack {
	friend ostream &operator<<(ostream &, BlackJack &);	// overloaded output operator
	public:
		BlackJack(int = 0);	// nondefault concstructo
		void newRound();	// start a new round of Black Jack
		int endBlackJack(int);	// stop the game if the user chooses so
		int getPlayerCount();	// return total number of players
		int endRound();		// end the current round of Black Jack
		void winners();		// find the winner(s) and print the round results
		Player& getPlayer(int);	// return the Player
		CardDeck& getDeck();	// return the Deck
		BlackJack & operator>(Player &);	// deal a card from the Deck to the Player's hand
	private:
		deque<Player> gamePlayers;	// deque of players in the Black Jack game
		CardDeck currentDeck;		// deque of cards used to play Black Jack
};

#endif
