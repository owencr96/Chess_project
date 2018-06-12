// <Author> Owen Raymond <Date> 05/18

// board_and_players.h is a header file which declares the classes, the board class and the game_player class which encompass everything needed to play the game of chess
// The board class is the chessboard which contains all of the pieces and their positions which has important member functions to check if moves are valid on the board, update the chess board
// find if the king is in check and if there any valid moves on the board to get hte king out of check. The game_player class has a key member function which gets the
// player to attempt a move, and then the move is checked to be valid by using some of the chessboard member functions

#ifndef BOARD_AND_PLAYERS_H
#define BOARD_AND_PLAYERS_H

#include "board_components.h"
#include <map>
																										// BOARD CLASS
class board																								//--------------------------------------------------------------------------------------------------------
{
	friend std::ostream & operator<<(std::ostream &os, board &b);										// [1]  Board friend function for outputing board objects to console 
private:
	square **game_board; // "game_board" is a 2D array of squares
	std::map<square,piece*> game_pieces; // Map is our associative container where a square is the key
	
	// NOTE!! To make custom classes, in this case the square, work as keys for std::map containers we need to provide a way for the map to sort the keys 
	// [2] The "<" operator was overloaded for the comparison of two squares objects so that they could be used as a key in the map of pieces, or an unordered_map could be used		

public:
	void look_at_map();																					// [3]  Function to output our map (the keys and corresponding pieces of each element in the map, good for error checking) 
	board();																							// [4]  Unparameterised board constructor
	~board();																							// [5]  Board destructor
	board &operator=(board &b);																			// [6]  Operator overloaded for "=" for board object
	
	square access_board_square(int row, int column) const;												// [7]  Function to allow access to one of the 2D "game_board" squares
	void add_Map_element(square &new_key, piece* &piece_to_contain);									// [8]  Function to add a new element to our map (introduce a new square to the map which contains a piece) 
	void update_board(square &piece_start, square &piece_end);											// [9]  Function to update the chess board with a move		
	bool valid_board_move(colour team_colour, square &start_position, square &end_position);			// [10] Function to check if a move is valid for the board
	square find_king_square(colour king_colour);														// [11] Function to locate and return the king location for a given team colour
	bool is_king_in_check(square &king_square, colour king_colour);										// [12] Function to check if the king is in check 
	bool any_valid_moves(colour king_colour);															// [13] Function to check if a move can be made to get the king out of check
};

																										// PLAYER CLASS
class game_player																						//--------------------------------------------------------------------------------------------------------
{
private:
	colour team_colour;	// Player is defined by what their team colour is, white or black
public:
	game_player();																						// [14] Unparameterised player constructor
	game_player(colour team);																			// [15] Parameterised player constructor
	~game_player();																						// [16] Player destructor

	colour get_team_colour()const;																		// [17] Function to access game_player's team_colour
	bool attempt_move(board &chessboard);																// [18] Function to allow player to attempt to make a move
};

#endif