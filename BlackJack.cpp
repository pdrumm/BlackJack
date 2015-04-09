/*
 * Patrick Drumm
 * cse20212
 * lab 4, Part 3
 */
#include "BlackJack.h"
#include "Player.h"
#include "CardDeck.h"
#include <iostream>
#include <cstdlib>
using namespace std;

// overloaded output operator
ostream &operator<<(ostream &output, BlackJack &bjGame) {
	// print each players hand, with variations depending on the progress of the current round
	for(int i=0; i<bjGame.getPlayerCount(); i++) {
		// print the player's tag
		if(bjGame.getPlayer(i).getIsUser()) cout<<"USER: ";
		else if(bjGame.getPlayer(i).getIsDealer()) cout<<"DEAL: ";
		else cout<<"COM"<<i-1<<": ";
		// uses overloaded output operator for Player class
		cout << bjGame.getPlayer(i) << endl;	// print the players hand
	}
	return output;
}

// constructor
BlackJack::BlackJack(int compPlayers) {
	// add user user to BlackJack game
	gamePlayers.push_back(Player(1,0) );
	// add user dealer to BlackJack game
	gamePlayers.push_back(Player(0,1) );
	// add the computer players
	for(int i=0; i<compPlayers; i++){
		gamePlayers.push_back(Player() );
	}
}

// start a new round of Black Jack
void BlackJack::newRound() {
	// shuffle the deck to start the round
	currentDeck.shuffle();
	// deal each player two cards
	for(int i=0; i<getPlayerCount(); i++){
		currentDeck.deal(2,gamePlayers[i]);
	}
}

// end the game of Black Jack(if the input is 1)
int BlackJack::endBlackJack(int gameOver) {
	// if gameOver==1, end the game
	if(gameOver) {
		// print final score board
		cout << "Here is the win breakdown by player:" << endl << endl;
		cout << "	USER: " << getPlayer(0).getWins() << endl;
		cout << "	DEAL: " << getPlayer(1).getWins() << endl;
		for(int i=2; i<getPlayerCount(); i++) {
			cout << "	COM" << i-1 << ": " << getPlayer(i).getWins() << endl;
		}
		cout << endl<< "Thanks for playing!" << endl;
	}
	return gameOver;
}

// return the total number of players
int BlackJack::getPlayerCount() {
	return gamePlayers.size();
}

// end the current round of BlackJack
int BlackJack::endRound() {
	// clear the players' hands
	for(int i=0; i<getPlayerCount(); i++){
		gamePlayers[i].clearHand();
	}
	// check to see if the user wants to quit or continue playing
	char isStillPlaying;	// user input, 'y' if the game will continue
	cout << "'y' for yes. 'n' for no.\nWould you like to continue playing?: ";
	cin >> isStillPlaying;
	// error checking
	while(tolower(isStillPlaying)!='y' && tolower(isStillPlaying)!='n') {
		cout<<"Error. Please enter 'y' to continue playing or 'n' to stop: ";
		cin >> isStillPlaying;
	}
	// clear the screen
	system("clear");

	if(tolower(isStillPlaying)=='n') return 1;	// the player opted to quit
	else return 0;					// the player still wants to play Black Jack
}

// return the Player
Player& BlackJack::getPlayer(int playerNumber) {
	return gamePlayers[playerNumber];
}

// return the Deck
CardDeck& BlackJack::getDeck(void) {
	return currentDeck;
}

// deal a card from the Deck to the Player's hand
BlackJack & BlackJack::operator>(Player & myPlayer) {
	// if it is not the user, deal until their turn is over
	if(myPlayer.getIsUser()==0){
		// continue dealing until player says to stop, or bust
		while(myPlayer.getStay()==0)
			currentDeck.deal(1,myPlayer);
		myPlayer.setTurnOver();	// end the player's turn
	}
	// else, it is the user, so deal one card at a time
	else
		currentDeck.deal(1,myPlayer);
	return(*this);
}

// finds who the winner(s) is/are and prints the results
void BlackJack::winners() {
	deque<int> wins;	// stores the winners by player number(ie. corresponding index in deque of Players
	int winIndex=0;		// used to index above array and keep count of number of winners for the round
	// for all players(except the dealer - see last line of for loop)
	for(int i=0; i<gamePlayers.size(); i++) {
		// if the players hand is higher than the dealer's(whose is below 21) and below 21 -OR- if the player's hand is less than or equal to 21(and the dealer's is above 21)
		if((getPlayer(i).handSum()>getPlayer(1).handSum()&&getPlayer(i).handSum()<=21&&getPlayer(1).handSum()<=21) || (getPlayer(i).handSum()<=21&&getPlayer(1).handSum()>21)){
			getPlayer(i).addWin();	// add a win to this player's total
			wins[winIndex]=i-1;	// keep track of who won(subtract 1 to match COM#)
			winIndex++;		// add one to the index/winner count
		}
		if(i==0) i++;	// this will skip the dealer(i=1)
	}
	// if the index was never incremented, then the dealer won
	if(winIndex==0) {
		cout << "The dealer won. Bummer." << endl << endl;
		getPlayer(1).addWin();		// add a win to the dealer's win total
	// else, either the user and/or some computers won. use the wins deque and win index to display who won
	}else{
		cout << "The winners are: ";
		for(int i=0; i<winIndex; i++){
			if(wins[i]==-1) cout<<"YOU! ";
			else cout<<"COM"<<wins[i]<<" ";
		}
		cout << endl << endl;
	}
}
