// <Author> Owen Raymond <Date> 05/18

// ChessGame.cpp implements the game of chess making use of classes and functions defined in the "board_and_players" and "board_components" files
// The game executes as a do while loop, which in essence is play the game while check_mate hasn't been reached. Within that do while are two do while loops, one
// for each player, where each player is asked to enter a move until they pick a valid move. The game is a cycle of each player entering a valid move, 
// until one of them reaches the condition of putting the opposition king in check mate, winning the game

#pragma once
#include"board_and_players.h"
#include"board_components.h"

int main()
{
	//Instantiate a chessboard and two chess players, p1 to control the white pieces and p2 to control the black pieces
	board chessboard{ board() };
	game_player p1{ game_player(white) };
	game_player p2{ game_player(black) };
	
	//Print out help for the players on how to recognise their own pieces and how to input moves 
	std::cout << "\n\n\t\t   TWO PLAYER CHESS GAME\n\t\t -------------------------" <<  std::endl;
	std::cout << "\nWhite pieces have capital letters and black pieces are in lower case\ne.g. white pawns are indicated by 'P' characters on the board" << std::endl;
	std::cout << "\nTo inpute moves, enter square column index followed by the row" << std::endl;
	std::cout << "e.g. input '48' for initial white queen square (square containing 'Q') \n" << std::endl;
	
	//Game is run in a do while loop, while playing_game = true
	bool playing_game = true;

	do {
		//In a game of chess the white team makes the first move
		//Print the board to console before the start of every move
		std::cout << chessboard << std::endl;
		
		//Initially white(p1) has not entered a move so initialise a bool to false to indicate this, which will only be set to true once white has entered a valid move
		bool white_valid_move = false;
		bool* ptr_white = &white_valid_move;

		do {
			//The first thing to do before asking p1 to input a move is to check whether their king is in check
			if (chessboard.is_king_in_check(chessboard.find_king_square(white), white) == true){
				//if white's king is in check then it could also be in check mate
				if (chessboard.any_valid_moves(white) == false){
					//if there are no valid moves for white's pieces to get the king out of check then black has won and the game can exit
					std::cout << "\nCheck Mate... Black Wins!\n\nThank you for playing...\n\n" << std::endl;
					//release memory
					chessboard.~board(); p1.~game_player(); p2.~game_player();
					system("pause");
					exit(1);
				}
				else {
					//else there are valid moves for the king to get out of check, and white can still make a move and compete to win the game
					std::cout << "\nWhite King in Check!" << std::endl << "White Move: ";
					// set *ptr_white ( which is "white_valid_move") to equal the game_player class member function attempt_move which will return true if a valid move has been made
					*ptr_white = p1.attempt_move(chessboard); //if the move was invalid the chessboard won't be updated and the code will be unable to exit the do while loop 
				}
			}
			else { // else the king wasn't in check and white can be prompted to enter a move immediately
				std::cout <<  "\nWhite Move: ";	
				*ptr_white = p1.attempt_move(chessboard);
			}		
		} while (white_valid_move == false);

		//Print the chessboard before black is asked to make a move so that they can see the move that white has just made
		std::cout << chessboard << std::endl; 
		
		//Initially black(p2) has not entered a move so initialise a bool to false to indicate this, which will only be set to true once black has entered a valid move
		bool black_can_make_move = false;
		bool* ptr_black = &black_can_make_move;

		do {
			//The procedure is the same for black as it is for white
			//Check if black's king is in check --> then check if it is in check mate, if it isn't then get player to input a move
			//if it was never in check then get black to input a move straight away
			if (chessboard.is_king_in_check(chessboard.find_king_square(black), black) == true){
				if (chessboard.any_valid_moves(black) == false){
					std::cout << "\nCheck Mate... White Wins!\n\nThank you for playing..." << std::endl;
					//release memory
					chessboard.~board(); p1.~game_player(); p2.~game_player();
					system("pause");
					exit(1);
				}
				else {
					std::cout << "\nBlack King in Check!" << std::endl << "Black Move: ";
					*ptr_black = p2.attempt_move(chessboard); // if this sets can_make_move to true, the board is also updated with the move
				}
			}
			else { 
				std::cout << "\nBlack Move: ";
				*ptr_black = p2.attempt_move(chessboard); // if this sets can_make_move to true, the board is also updated with the move
			}
		} while (black_can_make_move == false);

	} while (playing_game == true); 

	return 0;
}


