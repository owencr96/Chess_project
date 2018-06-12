// <Author> Owen Raymond <Date> 05/18

// board_components.cpp implements the game of chess making use of classes and functions defined in the "board_and_players" and "board_components" files
// The game executes as a do while loop, which in essence is play the game while check_mate hasn't been reached. Within that do while are two do while loops, one
// for each player, where each player is asked to enter a move until they pick a valid move. The game is a cycle of each player entering a valid move, 
// until one of them reaches the condition of putting the opposition king in check mate, winning the game

#include "board_components.h"

// SQUARE CLASS
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// [1]  Function to convert enum piece_type intrgers into characters for outputting on the board

inline const char ToChar(piece_type p)
{
	switch (p)
	{
	case king:		return 'k';
	case queen:		return 'q';
	case rook:		return 'r';
	case bishop:	return 'b';
	case knight:	return 'n';
	case pawn:		return 'p';
	default:		return 'X';
	}
}

// [2]  Square friend function for outputing square objects to console 

std::ostream & operator<<(std::ostream &os, const square &s)
{
	os << "SQUARE:\n Row: " << s.get_row() << "Column: " << s.get_column() << "Contains piece? : " << std::boolalpha << s.is_occupied();
	return os;
}

// [3]  Unparameterised square constructor

square::square() : row_position{ 0 }, column_position{ 0 }, contains_piece{ false } {}

// [4]  Parameterised square constructor

square::square(int x, int y, bool occupied_by_piece) : row_position{ x }, column_position{ y }, contains_piece{ occupied_by_piece } {}

// [5]  Square destructor

square::~square() {}

// [6]  Function to check if the square contains a piece

bool square::is_occupied() const { return contains_piece; }

// [7]	Function to update the status of whether a square contains a piece by changing the bool "contains_piece"

void square::now_contains_piece(bool occupied_by_piece) { contains_piece = occupied_by_piece; }

// [8]  Function to retrieve the column position of the square (in the 2D game_board array)

int square::get_row() const { return row_position; }

// [9]  Function to retrieve the row position of the square (in the 2D game_board array)

int square::get_column() const { return column_position; }


// PIECE ABSTRACT BASE CLASS
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// [10] Piece friend function for outputing piece objects to console 

std::ostream & operator<<(std::ostream &os, const piece &p)
{
	char p_char = ToChar(p.identity);
	if (p.team_colour == white) {
		os << (char)toupper(p_char); //It is common in FEN notation and other text notations to have white uppercase first letter of each piece and black as lowercase
	}
	else {	//else the piece is white
		os << p_char;
	}
	return os;
}

// [11] Unparameterised piece constructor

piece::piece() : identity{ pawn }, team_colour{ white }, position{ square() } {}

// [12] Parameterised piece constructor

piece::piece(piece_type type_of_piece) : identity{ type_of_piece }, team_colour{ white }, position{ square() } {}

// [13] Parameterised piece constructor

piece::piece(square piece_position, const colour piece_colour, piece_type type_of_piece) : position{ piece_position }, team_colour{ piece_colour }, identity{ type_of_piece } {}

// [14] Virtual piece destructor (makes class abstract as cannot construct a piece now)

piece:: ~piece() {};

// [15] Overload assignment operator for deep copy of pieces

piece & piece:: operator=(piece &p) {
	if (&p == this) return *this; //if our assignments are already the same object, the object remains as it was
	//else

	identity = p.get_identity();
	team_colour = p.get_colour();
	position = p.get_square();
	return *this; // Special pointer!!!
}

// [16] Function to access piece identity

piece_type piece::get_identity() const { return identity; }

// [17] Function to access piece colour

colour piece::get_colour() const { return team_colour; }

// [18] Function to access piece square position

square piece::get_square() const { return position; }

// [19] Function for updating the square that the piece believes it is in

void piece::update_position(const square &new_position) { position = new_position; }

// [20] Virtual function for checking a piece can move in the requested way (to be overidden by derived pieces) 

bool piece::valid_piece_movement(const square &start_square, const square &end_square) const{ return false; }


// KING CLASS
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// [21] Unparameterised king constructor

King::King() : piece(king) {}

// [22] Parameterised king constructor

King::King(const square &piece_position, const colour piece_colour) : piece(piece_position, piece_colour, king) {}

// [23] King destructor

King::~King() {};

// [24] Overidden function to check King is moving in a valid way

bool King::valid_piece_movement(const square &start_square, const square &end_square) const {
	// First access the end_square column and row co-ordinates and subtract the column and row co-ordinates of the start_square from these values
	int column_movement = end_square.get_column() - start_square.get_column(); int row_movement = end_square.get_row() - start_square.get_row();
	// Now have the numbers representing the piece movement on the board, check if they are valid for a king's mobility (a king can move vertically, horizontally or diagonally to any square one square away)
	if (column_movement == 0 && row_movement == 0) return false; // staying still is not a valid piece movement
	else if (std::abs(column_movement) <= 1 && std::abs(row_movement) <= 1)  return true; //moving to any surrounding square is a valid piece movement
	else return false; //else the move is not valid
}


// QUEEN CLASS
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// [25] Unparameterised queen constructor

Queen::Queen() : piece(queen) {}

// [26] Parameterised queen constructor

Queen::Queen(const square &piece_position, const colour piece_colour) : piece(piece_position, piece_colour, queen) {}

// [27] Queen destructor

Queen::~Queen() {};

// [28] Overidden function to check queen is moving in a valid way

bool Queen::valid_piece_movement(const square &start_square, const square &end_square) const {
	// First access the end_square column and row co-ordinates and subtract the column and row co-ordinates of the start_square from these values
	int column_movement = end_square.get_column() - start_square.get_column(); int row_movement = end_square.get_row() - start_square.get_row();

	//queen has movement capabilities of bishop and a rook (which is that it can move horizontally, vertically, like a rook, or diagonally, like a bishop, as far as the board permits)
	if (column_movement == 0 && row_movement == 0) return false; //staying still is not a valid piece movement
	else if ((std::abs(column_movement) < 8 && row_movement == 0) || (column_movement == 0 && std::abs(row_movement) < 8)) return true; //moving vertically along a column or horizontally along a row is a valid piece movement
	else if (std::abs(column_movement) == std::abs(row_movement)) return true; //moving along diagonals like a bishop is also valid
	else return false; //else the proposed movement is not valid
}


// ROOK CLASS
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// [29] Unparameterised rook constructor

Rook::Rook() : piece(rook) {}

// [30] Parameterised rook constructor

Rook::Rook(const square &piece_position, const colour piece_colour) : piece(piece_position, piece_colour, rook) {}

// [31] Rook destructor

Rook::~Rook() {};

// [32] Overidden function to check rook is moving in a valid way

bool Rook::valid_piece_movement(const square &start_square, const square &end_square) const{
	// First access the end_square column and row co-ordinates and subtract the column and row co-ordinates of the start_square from these values
	int column_movement = end_square.get_column() - start_square.get_column(); int row_movement = end_square.get_row() - start_square.get_row();

	if (column_movement == 0 && row_movement == 0) return false; //staying still is not a valid piece movement
	else if ((std::abs(column_movement) < 8 && row_movement == 0) || (column_movement == 0 && std::abs(row_movement) < 8)) 	return true; //moving vertically along a column or horizontally along a row is a valid piece movement	
	else return false; //any other proposed movement is not valid
}


// BISHOP CLASS
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// [33] Unparameterised bishop constructor

Bishop::Bishop() : piece(bishop) {}

// [34] Parameterised bishop constructor

Bishop::Bishop(const square &piece_position, const colour piece_colour) : piece(piece_position, piece_colour, bishop) {}

// [35] Bishop destructor

Bishop::~Bishop() {};

// [36] Overidden function to check bishop is moving in a valid way

bool Bishop::valid_piece_movement(const square &start_square, const square &end_square) const {
	// First access the end_square column and row co-ordinates and subtract the column and row co-ordinates of the start_square from these values
	int column_movement = end_square.get_column() - start_square.get_column(); int row_movement = end_square.get_row() - start_square.get_row();
	if (column_movement == 0 && row_movement == 0) return false; //staying still is not a valid piece movement
	if (std::abs(column_movement) == std::abs(row_movement))  return true;
	else return false;
}


// KNIGHT CLASS
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// [37] Unparameterised knight constructor

Knight::Knight() : piece(knight) {}

// [38] Parameterised knight constructor

Knight::Knight(const square &piece_position, const colour piece_colour) : piece(piece_position, piece_colour, knight) {}

// [39] Knight destructor

Knight::~Knight() {};

// [40] Overidden function to check knight is moving in a valid way

bool Knight::valid_piece_movement(const square &start_square, const square &end_square)const {
	// First access the end_square column and row co-ordinates and subtract the column and row co-ordinates of the start_square from these values
	int column_movement = end_square.get_column() - start_square.get_column(); int row_movement = end_square.get_row() - start_square.get_row();
	if ((std::abs(column_movement) == 2 && std::abs(row_movement) == 1) || (std::abs(column_movement) == 1 && std::abs(row_movement) == 2)) return true;
	else return false;
}


// PAWN CLASS
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// [41] Unparameterised pawn constructor

Pawn::Pawn() : piece(pawn) {}

// [42] Parameterised pawn constructor

Pawn::Pawn(const square &piece_position, const colour piece_colour) : piece(piece_position, piece_colour, pawn) {}

// [43] Pawn destructor

Pawn::~Pawn() {};

// [44] Overidden function to check pawn is moving in a valid way

bool Pawn::valid_piece_movement(const square &start_square, const square &end_square) const {
	// First access the end_square column and row co-ordinates and subtract the column and row co-ordinates of the start_square from these values
	int column_movement = end_square.get_column() - start_square.get_column(); int row_movement = end_square.get_row() - start_square.get_row();

	if (column_movement == 0 && row_movement == 0) return false; //staying still is not a valid piece movement

	//Pawns are unique from the other pieces in that they move diagonally forward to take pieces, but move forward along a column of the board if they are not taking a piece
	if (end_square.is_occupied() == true) { //when pawn is moving to take a piece
		if (get_colour() == white) {
			if (std::abs(column_movement) == 1 && row_movement == -1) return true; //for white pawns moving forward corresponds to negative row movement, here we check they are moving forward and diagonally
			else return false;
		}
		else { //colour of piece is black
			if (std::abs(column_movement) == 1 && row_movement == 1) return true; //for black pawns moving forwards corresponds to positive row movement
			else return false;
		}
	}
	else { // the pawn is not taking a piece and the piece is only allowed to move along the same column it is in
		if (get_colour() == white && get_square().get_row() == 6) { //There is another condition when pawns are in their starting positons they are allowed to move forwards two squares or one
			if (column_movement == 0 && (row_movement == -1 || row_movement == -2)) return true;
			else return false;
		}
		else if (get_colour() == black && get_square().get_row() == 1) { //Black pawns in their starting row are also allowed to move 2 or 1 spaces forward 
			if (column_movement == 0 && (row_movement == 1 || row_movement == 2)) return true;
			else return false;
		}
		else if (get_colour() == white) { //if the pieces aren't in their starting positon they can only move one square forward
			if (column_movement == 0 && row_movement == -1) return true;
			else return false;
		}
		else {//colour of piece is black
			if (column_movement == 0 && row_movement == 1) return true;
			else return false;
		}
	}
}



