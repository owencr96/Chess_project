// <Author> Owen Raymond <Date> 05/18

// board_components.cpp implements the functions defined in the board_components.h header file

#ifndef BOARD_COMPONENTS_H
#define BOARD_COMPONENTS_H

#include<map>
#include<iostream>

enum colour { black = 0, white = 1 };																							// Define enum for black and white team colours
enum piece_type { king = 100, queen = 9, rook = 5, bishop = 4, knight = 3, pawn = 1 };											// Also for the different types of peices (numbers indicate repective values of each piece)

inline const char ToChar(piece_type p);																							// [1]  Function to convert enum piece_type intrgers into characters for outputting on the board

																																// SQUARE CLASS
class square {																													//--------------------------------------------------------------------------------------------------------
	friend std::ostream & operator<<(std::ostream &os, const square &s);
protected:
	int row_position;		  // Member data includes the row and column index values of the 
	int column_position;	  // square on the board and whether the square contains a piece
	bool contains_piece;
public:
	square();																													// [3]  Unparameterised square constructor
	square(int x, int y, bool occupied_by_piece);																				// [4]  Parameterised square constructor
	~square();																													// [5]  Square destructor

	bool is_occupied() const;																									// [6]  Function to check if the square contains a piece
	void now_contains_piece(bool occupied_by_piece);																			// [7]  Function to update the status of whether a square contains a piece
	int get_row() const;																										// [8]  Function to retrieve the column position of the square (in the 2D game_board array)
	int get_column() const;																										// [9]  Function to retrieve the row position of the square (in the 2D game_board array)
};

																																// PIECE ABSTRACT BASE CLASS
class piece	{																													//--------------------------------------------------------------------------------------------------------{
	friend std::ostream & operator<<(std::ostream &os, const piece &p);															// [10] Piece friend function for outputing piece objects to console 
protected:
	piece_type identity;		// Member data includes the types of piece and the piece colour 
	colour team_colour;			// as well as the square the piece is in
	square position;
public:
	piece();																													// [11] Unparameterised piece constructor
	piece(const piece_type type_of_piece);																						// [12] Parameterised piece constructor
	piece(const square piece_position, const colour piece_colour, const piece_type type_of_piece);							 	// [13] Parameterised piece constructor	
	virtual ~piece();																											// [14] Virtual piece destructor 

	piece &operator=(piece &p);																									// [15] Overload assignment operator for deep copy of pieces																					
	piece_type get_identity() const;																							// [16] Function to access piece identity
	colour get_colour() const;																									// [17] Function to access piece colour
	square get_square() const;																									// [18] Function to access piece square position
	void update_position(const square &new_position);																			// [19] Function for updating the square that the piece believes it is in
	virtual bool valid_piece_movement(const square &start_square, const square &end_square) const;								// [20] Virtual function for checking a piece can move in the requested way (to be overidden by derived pieces) 
};

																																// KING PIECE CLASS
class King : public piece {																										//--------------------------------------------------------------------------------------------------------
public:
	King();																														// [21] Unparameterised king constructor
	King(const square &piece_position, const colour piece_colour);																// [22] Parameterised king constructor
	~King();																													// [23] King destructor
	bool valid_piece_movement(const square &start_square, const square &end_square) const;										// [24] Overidden function to check King is moving in a valid way
};

																																// QUEEN PIECE CLASS
class Queen : public piece {																									//--------------------------------------------------------------------------------------------------------
public:
	Queen();																													// [25] Unparameterised queen constructor
	Queen(const square &piece_position, const colour piece_colour);																// [26] Parameterised queen constructor
	~Queen();																													// [27] Queen destructor
	bool valid_piece_movement(const square &start_square, const square &end_square) const;										// [28] Overidden function to check queen is moving in a valid way
};

																																// ROOK PIECE CLASS
class Rook : public piece {																										//--------------------------------------------------------------------------------------------------------
public:
	Rook();																														// [29] Unparameterised rook constructor
	Rook(const square &piece_position, const colour piece_colour);																// [30] Parameterised rook constructor
	~Rook();																													// [31] Rook destructor
	bool valid_piece_movement(const square &start_square, const square &end_square) const;										// [32] Overidden function to check rook is moving in a valid way
};

																																// BISHOP PIECE CLASS
class Bishop : public piece {																									//--------------------------------------------------------------------------------------------------------
public:
	Bishop();																													// [33] Unparameterised bishop constructor
	Bishop(const square &piece_position, const colour piece_colour);															// [34] Parameterised bishop constructor
	~Bishop();																													// [35] Bishop destructor
	bool valid_piece_movement(const square &start_square, const square &end_square) const;										// [36] Overidden function to check bishop is moving in a valid way
};

																																// KNIGHT PIECE CLASS
class Knight : public piece {																									//--------------------------------------------------------------------------------------------------------
public:
	Knight();																													// [37] Unparameterised knight constructor
	Knight(const square &piece_position, const colour piece_colour);															// [38] Parameterised knight constructor
	~Knight();																													// [39] Knight destructor
	bool valid_piece_movement(const square &start_square, const square &end_square) const;										// [40] Overidden function to check knight is moving in a valid way
};

																																// PAWN PIECE CLASS
class Pawn : public piece {																										//--------------------------------------------------------------------------------------------------------
public:
	Pawn();																														// [41] Unparameterised pawn constructor
	Pawn(const square &piece_position, const colour piece_colour);																// [42] Parameterised pawn constructor
	~Pawn();																													// [43] Pawn destructor
	bool valid_piece_movement(const square &start_square, const square &end_square) const;										// [44] Overloaded function to check pawn is moving in a valid way 
};

#endif