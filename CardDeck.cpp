/*
 * Patrick Drumm
 * cse20212
 * lab 4, part 3
 */
#include "CardDeck.h"
#include <iostream>
#include <deque>
#include <algorithm>
#include <iterator>
#include <cstdlib>
#include "Player.h"
using namespace std;

CardDeck::CardDeck(int mySize) {
	for(int i=0; i<mySize; i++){
		cards.push_back(i);
	}
	// call srand() here
	srand(time(NULL) );
}

// return the number of cards in the deck
int CardDeck::getSize() {
	return cards.size();
}

// shuffle the cards in the deck
void CardDeck::shuffle() {
	// use random_suffle() algorithm
	random_shuffle(cards.begin(), cards.end() );
}

// deals numCards cards from the deck to currPlayer
void CardDeck::deal(int numCards, Player &currPlayer) {
	// error flag
	if(numCards<=0) cout<<"ERROR. dealt cards<=0"<<endl;
	for(int i=0; i<numCards; i++){
		currPlayer.addCard(cards[0] );	// adds the top card of the deck to the players hand
		cards.pop_front();		// delete the dealt card from the deck
		if(getSize()<15) openNewDeck();	// if the deck is running low, open a new deck
	}
}

// add a new deck, if the current one is running low
void CardDeck::openNewDeck() {
	// add 52 more cards
	for(int i=0; i<52; i++){
		cards.push_back(i);
	}
	shuffle();	// randomly shuffle after new deck is added
}
