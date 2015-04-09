/*
 * Patrick Drumm
 * cse20212
 * lab 4, part 2
 *
 * This file is the driver program for a BlackJack game! This game uses the following .h files: BlackJack, CardDeck, Player
 */

#include "BlackJack.h"
#include "CardDeck.h"
#include "Player.h"
#include <iostream>
#include <cstdlib>

int main()
{
	int isGameOver = 0;
	system("clear");
	cout << "Let's play Black Jack!!!" << endl;

	// Let user choose number of computer players at the table
	cout << "\nHow many computer players would you like at your table?" << endl;
	int compPlayers;
	cin >> compPlayers;
	// Ensure that there are a nonnegative number of computer players
	if(compPlayers < 0){
		cout << "An invalid number was entered. There will be a default 1 computer player at your table." << endl;
		compPlayers = 1;	// default number of computers
	}
	// Add the computer players to the game as input to nondefault constructor
	BlackJack currGame(compPlayers); // begin black jack game
//
	while(isGameOver!=1){
		currGame.newRound();	// start the first round
		cout << "Here are the initial hands..." << endl;
		cout << currGame << endl;

		// Deal to all of the computer players
		if(compPlayers>0){
			cout << "Now the computer players will go..." << endl << endl;
			for(int i=2; i<2+compPlayers; i++){
				currGame>(currGame.getPlayer(i));
			}
			cout << "Here is the board after the computer turns..." << endl << currGame << endl;
		}
		// User plays through
		while(!currGame.getPlayer(0).getStay() && currGame.getPlayer(0).handSum()<21){	// while the user has not yet said to stay and has not busted...
			currGame.getPlayer(0).userHit();
			if(!currGame.getPlayer(0).getStay())
				currGame>(currGame.getPlayer(0));
			if(currGame.getPlayer(0).getStay()==1 || currGame.getPlayer(0).handSum()>=21){
				currGame.getPlayer(0).setTurnOver();
			}else{
				cout << endl << currGame << endl;
			}
		}
		if(currGame.getPlayer(0).handSum()>21) {
			cout<<"\nSorry, you busted!\n";
			currGame.getPlayer(0).setStay();
			currGame.getPlayer(0).setTurnOver();
		}
		else if(currGame.getPlayer(0).handSum()==21) {
			cout<<"\nYou hit 21!!\n";
			currGame.getPlayer(0).setStay();
			currGame.getPlayer(0).setTurnOver();
		}
		cout << endl << currGame << endl;
		// Dealer plays through
		cout << "Now the dealer will go..." << endl;
		currGame>(currGame.getPlayer(1));	// dealer hits until >=17
		currGame.getPlayer(1).setTurnOver();
		cout << currGame << endl;

		currGame.winners();
		isGameOver = currGame.endBlackJack(currGame.endRound() );
	}
}
