/*
 * Patrick Drumm
 * cse20212
 * lab 4, Part 3
 */
#include "Player.h"
#include <deque>
#include <iostream>
#include <cstdlib>
using namespace std;

ostream &operator<<(ostream &output, Player &myPlayer) {
	cout << "[";
	// forward iterators for the player's hand deque
	deque<int>::const_iterator r = myPlayer.hand.begin();
	deque<int>::const_iterator end = myPlayer.hand.end();

	// prints first card in deck
	if(*r == 11) cout << "J";	// Jack
	else if(*r == 12) cout << "Q";	// Queen
	else if(*r == 13) cout << "K";	// King
	else if(*r == 1) cout << "A";	// Ace
	else cout << *r;		// 2-10
	// print the computers' second cards as unviewable to the user
	if(myPlayer.getIsUser()==0 && (myPlayer.handSum()<21 || myPlayer.turnOver==0) && (myPlayer.isDealer!=1 || myPlayer.turnOver!=1)) {	// if it is not the user AND either the player's hand is below 21 or their turn is not yet over AND not if it is the dealer and their turn is over
		cout << ", X";	// unviewable card to the user
		++r;		// increment iterator
	}
	// prints second or third(depending on the above if^) card through to the last card in the player's hand
	for(r = r+1; r != end; ++r) {
		cout << ", ";
		if(*r == 11) cout << "J";	// Jack
		else if(*r == 12) cout << "Q";	// Queen
		else if(*r == 13) cout << "K";	// King
		else if(*r == 1) cout << "A";	// Ace
		else cout << *r;		// 2-10
	}
	cout << "]";

	if(myPlayer.isUser==1 && myPlayer.turnOver!=1) cout << " = " << myPlayer.handSum();	// this will print the sum of the user's hand, before their turn is over

	// if the player's turn is over, then display their sum and their hand status
	if(myPlayer.turnOver){
		cout << " = " << myPlayer.handSum() << "	-> ";
		if(myPlayer.handSum() > 21)		// Bust: over 21
			cout << "Bust.";
		else if(myPlayer.handSum() == 21)	// 21 exactly!
			cout << "21!";
		else if(myPlayer.isStaying)		// Stay: under 21
			cout << "Stay!";
	}

	return output;
}

// constructor
Player::Player(int myIsUser, int myIsDealer) {
	// When a player is created...
	isStaying = 0;	// they are not is "staying" mode yet
	numWins = 0;	// they have no wins yet
	turnOver = 0;	// their turn is not yet over
	isUser = myIsUser;	// ==1 if this player is the user
	isDealer = myIsDealer;	// ==1 if this player is the dealer
}

// add a card to the players hand
void Player::addCard(int newCard) {
	// cards in the deck range [0,51]. cards in hand range [1,13]
	hand.push_back( (newCard%13)+1);	// add new card to hand
	// if the hand sum is above 16 and it is not the user, then stay
	if(handSum() >=17 && isUser!=1) isStaying=1;
}

// return the sum of the cards in the player's hand
int Player::handSum() {
	int sum=0;	// sum of cards in hand
	for(int i=0; i<hand.size(); i++) {
		if(hand[i] > 10) sum+= 10;	// if the card is a 11,12,13(J,Q,K) then the point value is 10
		else if(hand[i] == 1) sum+= 11;	// if the card is a 1(Ace) the the point value is 11
		else sum+= hand[i];		// else, the point value equals the card number [2,10]
	}
	return(sum);
}

// return if the player is staying
int Player::getStay() {
	return isStaying;
}

// return 1 if the player is the user, 0 otherwise
int Player::getIsUser() {
	return isUser;
}

// return 1 if the player is the dealer, 0 otherwise
int Player::getIsDealer() {
	return isDealer;
}

// instructions for the user when it is their turn to hit or stay
void Player::userHit() {
	char hitOrStay;	// user input, option to hit or stay
	cout << "'h' to hit. 's' to stay.\nWould you like to hit or stay?: ";
	cin >> hitOrStay;
	// error checking
	while(tolower(hitOrStay)!='s' && tolower(hitOrStay)!='h') {
		cout << "Sorry, that is not a valid option.\nPlease enter 'h' or 's'";
		cin >> hitOrStay;
	}
	// if the user is staying, set corresponding value to 1(true)
	if(tolower(hitOrStay)=='s')
		isStaying = 1;
	// clear screen
	system("clear");
	// reprint user's choice for clarity
	cout << "Would you like to hit or stay?: " << hitOrStay << endl;
}

// get rid of all cards in the player's hand
void Player::clearHand() {
	hand.clear();	// clear deque
	isStaying = 0;	// switch player out of staying mode
	turnOver = 0;	// switch player so that their turn is not over
}

// add a win to the players who won the previous round
void Player::addWin() {
	numWins++;
}

// return number of wins for the player
int Player::getWins() {
	return numWins;
}

// set the player to staying mode
void Player::setStay() {
	isStaying=1;
}

// end the player's turn
void Player::setTurnOver() {
	turnOver=1;
}
