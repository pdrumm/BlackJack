/*
 * Patrick Drumm
 * cse20212
 * lab 4, Part 3
 */
#ifndef CARDDECK_H
#define CARDDECK_H

#include <deque>
#include <iostream>
#include "Player.h"
using namespace std;

class CardDeck {
	public:
		CardDeck(int=52);	// constructor with default deck of size 52
		int getSize(void);	// return size of deque(ie. number of cards in deck)
		void shuffle(void);	// shuffle cards in the deck
		void deal(int,Player&);	// deals int cards to Player
		void openNewDeck(void);	// add a new deck if the current one is running low
	private:
		deque<int> cards;	// deque stores cards
};

#endif
