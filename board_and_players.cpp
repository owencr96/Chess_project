// <Author> Owen Raymond <Date> 05 / 18

// board_and_players.cpp implements the functions defined in the board_and_players.h header file

#include "board_and_players.h"
#include "board_components.h"
#include <iostream>
#include <string>
#include <vector>


// BOARD CLASS
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// [1]  Overload the "<<" operator of the output stream for the board class so that it can be represented easily on the console

std::ostream & operator<<(std::ostream &os, board &b) {
	os << std::endl << "         .1    .2    .3    .4    .5    .6    .7    .8 " << std::endl;	// index the columns of the board squares on the console
	os << "        _____ _____ _____ _____ _____ _____ _____ _____ " << std::endl;
	for (int row = 0; row <8; row++) {		// Loop over the 8 row elements of 2D array of board squares 
		os << "       |     |     |     |     |     |     |     |     |" << std::endl;
		os << "  ." << row + 1 << "   |";		   // index the rows of the board squares on the console
		for (int column = 0; column < 8; column++) {		// Now looping over the columns
			if (b.game_board[row][column].is_occupied() == true) { // Access each square in the board with "b.game_board[row][column]", use member function ".is_occupied()" to check if it contains a piece
				os << "  " << *b.game_pieces[b.game_board[row][column]] << "  |"; // If square contains a piece, locate piece in the map of pieces with the corresponding square key and output it on the board
				// "b.game_board[row][column]" is a square, since a piece occupies it, it is also a key to a piece pointer in our map, so we access the piece by derefencing the pointer that we get from b.game_pieces[b.game_board[row][column]]
			}
			else { //else the square is empty so we do not output a piece, instead just output an extra " " character
				os << "     |";
			}
		}
		os << std::endl << "       |_____|_____|_____|_____|_____|_____|_____|_____|" << std::endl;
	}
	return os;
}

// [2]  Overload the "<" operator for comparing squares so that they can be used as a key for our map of pieces 

bool operator<(const square& lhs, const square& rhs) { //Set squares to be compared primarily by their row and secondarily by their column
	return(lhs.get_row() + (0.1*lhs.get_column())) < (rhs.get_row() + (0.1*rhs.get_column()));
}

// [3] A Function to look at our map of pieces, by outputing the key (square the piece is in) and the piece contained in the map belonging to that square (good for checking if the structure is storing things correctly)

void board::look_at_map() {
	for (auto const& x : game_pieces) //iterate over the map
	{
		std::cout << "\nELEMENT KEY " << x.first << "\nPIECE CONTAINED: " << *x.second << std::endl; //output the key (square) followed by the dereferenced piece* that is contained in that element
	}
}

// [4]  Unparameterised board constructor

board::board() {
	game_board = new square*[8]; // think of this as the y-coordinates of the chess board, the rows
	for (int row = 0; row < 8; row++) {
		game_board[row] = new square[8]; //for each y-coordinate allocate 8 x-coordinates of squares to form our 8x8 board of squares
	}
	//A 2D array of 64 squares has been assigned to memory, now set it up as a chess board
	for (int row = 0; row < 8; row++) { //loop over all elements
		for (int column = 0; column < 8; column++) {
			if (row == 0 || row == 1 || row == 6 || row == 7) { // The front two and back two rows of squares on a chess board are filled with pieces
				game_board[row][column] = square(row, column, true); //make sure the squares in these rows reflect this ("true" indicates a piece occupies this square)
			}
			else {	//else the other squares are initially empty, "false" parameter in "square(row, column, false)" indicates this
				game_board[row][column] = square(row, column, false);
			}
		}
	}
	// Our board array of squares has been set up, now map our pieces onto the board by assigning a chess piece to the squares that contain pieces
	for (int row = 0; row < 8; row++) {
		bool entered_once = false; bool* ptr = &entered_once;
		for (int column = 0; column < 8; column++) {
			if (row == 0 && entered_once == false) { //Create map elements with square keys that initially contain pieces on a chess board. Fill each element with the correct piece for an initially setup chessboard
				game_pieces[game_board[row][0]] = new Rook(game_board[row][0], black);    // Chess pieces contained in squares on back row aren't all the same type, initialise all separately once for black pieces
				game_pieces[game_board[row][1]] = new Knight(game_board[row][1], black);
				game_pieces[game_board[row][2]] = new Bishop(game_board[row][2], black);
				game_pieces[game_board[row][3]] = new Queen(game_board[row][3], black);
				game_pieces[game_board[row][4]] = new King(game_board[row][4], black);
				game_pieces[game_board[row][5]] = new Bishop(game_board[row][5], black);
				game_pieces[game_board[row][6]] = new Knight(game_board[row][6], black);
				game_pieces[game_board[row][7]] = new Rook(game_board[row][7], black);
				*ptr = true; //indicate that this row has been set up so no need to redo it
			}
			else if (row == 1) { // Assign black pawns to all the square keys for this row of squares in our map 
				game_pieces[game_board[row][column]] = new Pawn(game_board[row][column], black);
			}
			else if (row == 6) {
				game_pieces[game_board[row][column]] = new Pawn(game_board[row][column], white); // Now assign the white pawns a key
			}
			else if (row == 7 && entered_once == false) { //And the rest of the white team pieces there initial keys
				game_pieces[game_board[row][0]] = new Rook(game_board[row][0], white);
				game_pieces[game_board[row][1]] = new Knight(game_board[row][1], white);
				game_pieces[game_board[row][2]] = new Bishop(game_board[row][2], white);
				game_pieces[game_board[row][3]] = new Queen(game_board[row][3], white);
				game_pieces[game_board[row][4]] = new King(game_board[row][4], white);
				game_pieces[game_board[row][5]] = new Bishop(game_board[row][5], white);
				game_pieces[game_board[row][6]] = new Knight(game_board[row][6], white);
				game_pieces[game_board[row][7]] = new Rook(game_board[row][7], white);
				*ptr = true;
			}
		}
	}
	//BOARD HAS NOW BEEN INITIALISED 
}

// [5]  Board destructor

board::~board() {	// Delete all memory assigned to the 2D array of squares and the map of pieces in the destructor
	for (int row = 0; row < 8; row++) delete[] game_board[row];
	delete[] game_board; game_pieces.clear();
}

// [6]  Operator overloaded for "=" for board object

board & board:: operator=(board &b) {
	if (&b == this) return *this; //if our assignments are already the same object, the object remains as it was
	//else
	// First delete this object's array

	game_pieces = b.game_pieces;
	for (int row = 0; row < 8; row++) { //loop over all elements
		for (int column = 0; column < 8; column++) {
			game_board[row][column] = b.game_board[row][column]; //make sure the squares in these rows reflect this ("true" indicates a piece occupies this square)
		}
	}

	return *this; // Special pointer!!!
}

// [7]  A Function to allow access to one of the 2D "game_board" squares, since the array is privately stored this is necessary for other objects to be able to access the private game_board 

square board::access_board_square(int row, int column) const { return game_board[row][column]; }

// [8]  Function to add a new element to our map, which is needed when a new square (i.e. key) contains a piece. Therefore this is necessary to update our map whenever a piece is moved

void board::add_Map_element(square &new_key, piece* &piece_to_contain) {
	game_pieces[new_key] = piece_to_contain;  //When you write game_pieces[new_key], and that element doesn't exist, it is created and constructed to contain the piece
	//Checks are made outside of this function so that the square argument in this function is defintiely a valid new key for our map
}

// [9] Function to update the chess board with a move	

void board::update_board(square &piece_start, square &piece_end) {
	//update the position of the piece in the piece class before deep copying the piece into the map of pieces using the "piece_end" square key 
	bool t = true;
	bool f = false;
	if (game_board[piece_end.get_row()][piece_end.get_column()].is_occupied() == true) { //if the move is taking a piece, we will lose an element of our map structure
		game_pieces[game_board[piece_start.get_row()][piece_start.get_column()]]->update_position(game_board[piece_end.get_row()][piece_end.get_column()]);
		game_pieces[game_board[piece_end.get_row()][piece_end.get_column()]] = game_pieces[game_board[piece_start.get_row()][piece_start.get_column()]];
		game_pieces.erase(game_board[piece_start.get_row()][piece_start.get_column()]); //erase the element belonging to the old key in the map
		(game_board[piece_start.get_row()][piece_start.get_column()]).now_contains_piece(f);
	}
	else { //if we are not taking a piece the square we are trying to move to is not currently a key in our map of structures, therefore we need to add a new element and delete the old one
		game_board[piece_end.get_row()][piece_end.get_column()].now_contains_piece(t);
		//piece_end.now_contains_piece(true);
		add_Map_element(game_board[piece_end.get_row()][piece_end.get_column()], game_pieces[game_board[piece_start.get_row()][piece_start.get_column()]]);

		game_board[piece_start.get_row()][piece_start.get_column()].now_contains_piece(f);
		//piece_start.now_contains_piece(false);
		game_pieces.erase(game_board[piece_start.get_row()][piece_start.get_column()]); //erase the element belonging to the old key in the map
	}
}

// [10] Function to check if a move is valid for the board, check various things like squares being on the board, squares containing pieces and certain piece movement paths being valid 

bool board::valid_board_move(colour team_colour, square &start_position, square &new_position){
	// Check that a piece to be moved actually occupies in the start_position square, and check that it belongs to the players team colour
	if (start_position.is_occupied() == false || game_pieces[start_position]->get_colour() != team_colour) {
		return false; //if start position is unoccupied return false
	}
	//Now check if the position the piece is being moved to is already occupied by a piece that the player owns
	else if (new_position.is_occupied() == true && game_pieces[new_position]->get_colour() == team_colour) {
		return false; //if it is already occupied by a piece you own the move is not valid so return false		
	}
	//Now check if the movement is valid for the piece, if it isn't then return false
	else if (game_pieces[start_position]->valid_piece_movement(start_position, new_position) == false) {
		return false;
	}
	else { // the piece move is valid for the piece, but is it valid for the board?
		//for certain pieces, the bishop, the rook, the queen and the pawn when it moves two spaces, the paths to their destination need to be clear for the move to be possible
		//for these pieces check that the path is clear for their moves to be valid
		piece_type piece_moving = game_pieces[start_position]->get_identity();
		if (piece_moving == queen || piece_moving == rook || piece_moving == bishop){
			int start_row = start_position.get_row(); int start_column = start_position.get_column();
			int row_movement = new_position.get_row() - start_row; int column_movement = new_position.get_column() - start_column;
			//since the queen can move like a rook and a bishop, check all of the movement conditions together for bishops rooks and queens
			if (row_movement == 0 && column_movement < 0) {
				// ROOK MOVEMENT, LEFT ALONG A ROW
				for (int i = 1; i < -column_movement; i++) {
					//if the piece has negative column_movement it is moving along a row from a high index number column to a low index number column
					if (game_board[start_row][start_column - i].is_occupied() == true) return false;
				}
			}
			else if (row_movement == 0 && column_movement > 0) {	// ROOK MOVEMENT, RIGHT ALONG A ROW
				for (int i = 1; i < row_movement; i++) {
					//if the piece has positive column_movement it is moving along a row from a low index number column to a high index number column
					if (game_board[start_row][start_column + i].is_occupied() == true) return false;
				}
			}
			else if (row_movement < 0 && column_movement == 0) {	// ROOK MOVEMENT, DOWN A COLUMN ON THE BOARD
				for (int i = 1; i < -row_movement; i++) {
					//if the piece has negative row_movement it is moving along a column from a hign index number row to a low index number row
					if (game_board[start_row - i][start_column].is_occupied() == true) return false;
				}
			}
			else if (row_movement > 0 && column_movement == 0) {	// ROOK MOVEMENT, UP A COLUMN ON THE BOARD
				for (int i = 1; i < row_movement; i++) {
					//if the piece has positive row_movement it is moving along a column from a low index number row to a high index number row
					if (game_board[start_row + i][start_column].is_occupied() == true) return false;
				}
			}
			if (row_movement < 0 && column_movement < 0) {			// BISHOP MOVEMENT, UP BOARD AND LEFT
				for (int i = 1; i < -row_movement; i++) { //since "row_movement" is negative, take the negative of that 
					//if the piece has negative row_movement and negative column movement it is moving from a high index number row to a low and a high index number column to a low one
					if (game_board[start_row - i][start_column - i].is_occupied() == true) return false;
				}
			}
			else if (row_movement < 0 && column_movement > 0) {		// BISHOP MOVEMENT, UP BOARD AND RIGHT
				for (int i = 1; i < -row_movement; i++) {
					//if the piece has negative row_movement and positive column movement it is moving from a high index number row to a low one and a low index number column to a high one
					if (game_board[start_row - i][start_column + i].is_occupied() == true) return false;
				}
			}
			else if (row_movement > 0 && column_movement < 0) {		// BISHOP MOVEMENT, DOWN BOARD AND LEFT
				for (int i = 1; i < row_movement; i++) {
					//if the piece has positive row_movement and negative column movement it is moving from a low index number row to a high one and a high index number column to a low one
					if (game_board[start_row + i][start_column - i].is_occupied() == true) return false;
				}
			}
			else if (row_movement > 0 && column_movement > 0) {		// BISHOP MOVEMENT, DOWN BOARD AND RIGHT
				for (int i = 1; i < row_movement; i++) {
					//if the piece has positive row_movement and positive column movement it is moving from a low index number row to a high one and a low index number column to a high one
					if (game_board[start_row + i][start_column + i].is_occupied() == true) return false;
				}
			}
			// if one of the loops doesn't return false then the no pieces lie in the way of the castle, bishop or queen and so the move is valid
			return true;
		}
		else if (game_pieces[start_position]->get_identity() == pawn){
			//deal with the pawn separately to queen bishop and rook since it's movement is a lot more specific
			int start_row = start_position.get_row(); int start_column = start_position.get_column();
			int row_movement = new_position.get_row() - start_row; int column_movement = new_position.get_column() - start_column;

			if (game_pieces[start_position]->get_colour() == white) { //White pawns can only move up the board (since they start on the bottom side)
				if (row_movement == -2){ //row_movement is negative since the white pawns move from high index number rows up the board to low index number rows
					if (game_board[start_row - 1][start_column].is_occupied() == true) return false;
				}
			}
			else {//else the pawn is black
				if (row_movement == 2) { //row_movement is positive since the black pawns move from low index number rows down the board to high index number rows
					if (game_board[start_row + 1][start_column].is_occupied() == true) return false;
				}
			}
			//If it wasn't a black or white pawn moving two rows from its original position, or the path of pawns doing that was empty, the move is valid so return true
			return true;
		}
		else{ //else the piece being move was not a pawn, queen, rook or bishop and the path of the piece does not need to be considered when deciding if the move is valid for the board
			return true;
		}
	}
}

// [11] Function to locate and return the king location for a given team colour

square board::find_king_square(colour king_colour){
	for (auto const& piece : game_pieces) //auto iterating through game_pieces map
	{	//piece.first = map key, piece.second = what's contained in that element
		if (piece.second->get_identity() == king && piece.second->get_colour() == king_colour) return access_board_square(piece.first.get_row(), piece.first.get_column());
	}
	return square(); //in reality the board will never not have your king, this is just a formality
}

// [12] Function to check if the king is in check, looks to see if any pieces of opposing team are threatening to take the king

bool board::is_king_in_check(square &king_square, colour king_colour){

	//Now we have found the king, lets see if any pieces are in a position to validly take the king unless a move is made to prevent this
	//iterate through the game_pieces again looking at the opposite team and checking if their square to the kings square is a valid move
	for (auto const& piece : game_pieces) //auto iterating through game_pieces map
	{	//piece.first = map key, piece.second = what's contained in that element
		if (piece.second->get_colour() != king_colour){ //if the piece is from the enemy team
			square piece_square = game_board[piece.first.get_row()][piece.first.get_column()];
			if (valid_board_move(piece.second->get_colour(), piece_square, king_square) == true){
				return true; //KING IS IN CHECK
			}
		}
	}
	return false; //Else the KING IS NOT IN CHECK

}

// [13] Function to check if a move can be made to get the king out of check, including taking the threat piece, blocking the threat piece or moving the king out of the way

bool board::any_valid_moves(colour king_colour){//include taking check piece, blocking path, moving king
	square king_square = find_king_square(king_colour); int king_row = king_square.get_row(); int king_column = king_square.get_column();
	std::vector < square > threat_squares; //In here we can store the positions that are threatening the king, including the squares in the path of the threat to the king
	std::vector < square > team_squares; //In here we can store all of the team_square positions

	//LAMBDAS
	auto king_moves = [&]() -> bool { //[&] means it captures every variable and function currently in scope by reference
		for (int i = -1; i < 2; i++){
			for (int j = -1; j < 2; j++){ //Loop through all possible movement of the king
				if (king_row + j < 8 && king_row + j >= 0 && king_column + i < 8 && king_column + i >= 0){
					if (valid_board_move(king_colour, game_board[king_row][king_column], game_board[king_row + j][king_column + i]) == true){ //check if king can make any valid moves
						// Create a temporary board to make this valid move on 
						board temporary_board = board();
						temporary_board = *this;

						temporary_board.update_board(temporary_board.game_board[king_row][king_column], temporary_board.game_board[king_row + j][king_column + i]); //can update the board and return true to indicate the move has been made	
						//check if the king is in check after making this move
						if (temporary_board.is_king_in_check(temporary_board.find_king_square(king_colour), king_colour) == false) return true; //return true to indicate king can be moved out of check
						// else keep looping through
					}
				}
			}
		}
		return false; //if no king moves caused the lambda to return true then return false indicating the king can't be moved to get out of check
	};
	auto piece_moves = [&](int a, int b) -> bool { // "a" will be the index in the vector of team_squares that we will use to access the separate team squares
		int team_piece_column = team_squares[a].get_column(); int team_piece_row = team_squares[a].get_row();
		int threat_piece_column = threat_squares[b].get_column(); int threat_piece_row = threat_squares[b].get_row();
		//Need to create a temporary copy of the chessboard and then we can see if each attempted move produces a playable board for the next move
		//We are not looking to make any of these moves, just see if there are any possible moves for the user to find

		if (valid_board_move(king_colour, game_board[team_piece_row][team_piece_column], game_board[threat_piece_row][threat_piece_column]) == true){
			board temporary_board = board();
			temporary_board = *this;

			temporary_board.update_board(temporary_board.game_board[team_piece_row][team_piece_column], temporary_board.game_board[threat_piece_row][threat_piece_column]); //can update the board and return true to indicate the move has been made	

			if (temporary_board.is_king_in_check(temporary_board.find_king_square(king_colour), king_colour) == false) return true; //return true to indicate there are piece moves
			else return false; //return false to indicate this isn't a valid piece move
		}
		else return false;
	};

	//Now we have found the king, lets see if any pieces are in a position to validly take the king unless a move is made to prevent this
	//iterate through the game_pieces again looking at the opposite team and checking if their square to the kings square is a valid move
	for (auto const& piece : game_pieces) //auto iterating through game_pieces map
	{	//piece.first = map key, piece.second = what's contained in that element
		square piece_square = piece.first;
		if (piece.second->get_colour() != king_colour){ //if the piece is from the enemy team
			if (valid_board_move(piece.second->get_colour(), piece_square, king_square) == true){
				threat_squares.push_back(piece_square); //Lets store the threatening positions
			}
		}//else the piece is the same colour as the king 
		else if (piece.second->get_identity() != king){ //so as long as it is not the king we can store it in the team_squares vector
			team_squares.push_back(piece_square);
		}
	}


	//We need to store the path squares from the threat_square to the king_square, in our threat_squares vector
	//at the moment the maximum threat_squares there could be are 2 (if a piece moves to check the king, while moving out of the way of a piece that is now also checking the king)
	//these threat squares aren't in the same path
	piece_type threat_piece = game_pieces[threat_squares[0]]->get_identity();
	if (threat_piece == queen || threat_piece == rook || threat_piece == bishop){
		//we can add to the threat squares if it is one of these pieces		
		int row_movement = threat_squares[0].get_row() - king_row; int column_movement = threat_squares[0].get_column() - king_column;
		//since the queen can move like a rook and a bishop, check all of the movement conditions together for bishops rooks and queens

		if (row_movement == 0 && column_movement < -1) {// ROOK MOVEMENT, LEFT ALONG A ROW		
			for (int i = 1; i < -column_movement; i++) {
				threat_squares.push_back(game_board[king_row][king_column - i]);
			}
		}
		else if (row_movement == 0 && column_movement > 1) {	// ROOK MOVEMENT, RIGHT ALONG A ROW
			for (int i = 1; i < row_movement; i++) {
				threat_squares.push_back(game_board[king_row][king_column + i]);
			}
		}
		else if (row_movement < -1 && column_movement == 0) {	// ROOK MOVEMENT, DOWN A COLUMN ON THE BOARD
			for (int i = 1; i < -row_movement; i++) {
				threat_squares.push_back(game_board[king_row - i][king_column]);
			}
		}
		else if (row_movement > 1 && column_movement == 0) {	// ROOK MOVEMENT, UP A COLUMN ON THE BOARD
			for (int i = 1; i < row_movement; i++) {
				threat_squares.push_back(game_board[king_row + i][king_column]);
			}
		}
		if (row_movement < -1 && column_movement < -1) {			// BISHOP MOVEMENT, UP BOARD AND LEFT
			for (int i = 1; i < -row_movement; i++) {
				threat_squares.push_back(game_board[king_row - i][king_column - i]);
			}
		}
		else if (row_movement < -1 && column_movement > 1) {		// BISHOP MOVEMENT, UP BOARD AND RIGHT
			for (int i = 1; i < -row_movement; i++) {
				threat_squares.push_back(game_board[king_row - i][king_column + i]);
			}
		}
		else if (row_movement > 1 && column_movement < -1) {		// BISHOP MOVEMENT, DOWN BOARD AND LEFT
			for (int i = 1; i < row_movement; i++) {
				threat_squares.push_back(access_board_square(king_row + i, king_column - i));
			}
		}
		else if (row_movement > 1 && column_movement > 1) {		// BISHOP MOVEMENT, DOWN BOARD AND RIGHT
			for (int i = 1; i < row_movement; i++) {
				threat_squares.push_back(game_board[king_row + i][king_column + i]);
			}
		}
		//else do nothing
	}


	//first check if a piece can move to relieve the check
	int amount_of_team_squares = team_squares.size(); int amount_of_threat_squares = threat_squares.size();

	for (int i = 0; i < amount_of_team_squares; i++){
		for (int j = 0; j < amount_of_threat_squares; j++){
			if (piece_moves(i, j) == true) {
				team_squares.clear();
				threat_squares.clear();
				return true;
			}
		}
	}

	//our last hope is the king can move to get out of check
	if (king_moves() == true){
		team_squares.clear();
		threat_squares.clear();
		return true;
	}
	else { // if king also can't move out of check and none of its team can relieve the threat then return false to indicate checkmate
		team_squares.clear();
		threat_squares.clear();
		return false; //indicate check mate
	}
}

// GAME_PLAYER CLASS
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// [14]  Unparameterised player constructor

game_player::game_player() : team_colour{ white } {}

// [15] Parameterised player constructor

game_player::game_player(colour team) : team_colour{ team } {}

// [16] Player destructor

game_player::~game_player() {}

// [17] Function to access game_player's team_colour

colour game_player::get_team_colour()const{ return team_colour; }

// [18] Attempt move function- When the player attempts a move this function will return false if it is not possible. If the move is possible the board is updated with the move and the function returns true

bool game_player::attempt_move(board &chessboard) {
	// Check that a piece to be moved actually occupies in the start_position square, and check that it belongs to the players team colour
	std::string start_square, end_square;
	std::cout << "From Square: "; std::getline(std::cin, start_square);
	std::cout << "To Square: "; std::getline(std::cin, end_square);
	if (start_square.size() != 2 || end_square.size() != 2) { std::cerr << "Invalid Input!" << std::endl; return false; }
	//start_square[0] = start square column index on console board, start_square[1] = start square row index on console board
	//The Console outputs the game board with index numbers one higher than the corresponding row and column index numbers of the "game_board" 2D array of squares
	//Therefore to access the players desired square, take 1 away from each of the index numbers chosen by the player
	int from_row = start_square[1] - '0';  //Converting a string to an int converts it to its ASCII code, but " - '0' " converts this to the actual integer value in the string
	int from_column = start_square[0] - '0';
	int to_row = end_square[1] - '0';
	int to_column = end_square[0] - '0';
	//std::cout << "Column From, Row From: " << from_column << " , " << from_row << " Column to, Row to :" << to_column << " , " << to_row << std::endl;

	if (from_column <= 8 && from_column > 0 && from_row <= 8 && from_row > 0 && to_column <= 8 && to_column > 0 && to_row <= 8 && to_row > 0) {
		if (chessboard.valid_board_move(get_team_colour(), chessboard.access_board_square(from_row - 1, from_column - 1), chessboard.access_board_square(to_row - 1, to_column - 1)) == true){ //if the board move is valid
			//create a temporary version of this board and check on this board if your king is now check, if it is then the move is not valid, if it isn't then the move can be updated on your main board
			board temporary_board{ board() }; //MAY NEED TO DEEP COPY THIS
			temporary_board = chessboard;
			temporary_board.update_board(temporary_board.access_board_square(from_row - 1, from_column - 1), temporary_board.access_board_square(to_row - 1, to_column - 1)); //can update the board and return true to indicate the move has been made

			if (temporary_board.is_king_in_check(temporary_board.find_king_square(team_colour), team_colour) == false){
				chessboard.update_board(chessboard.access_board_square(from_row - 1, from_column - 1), chessboard.access_board_square(to_row - 1, to_column - 1));
				return true;
			}//else the king is in check after this proposed move, so don't update the board and return false
			else { std::cerr << "Invalid Move!" << std::endl; return false; }
		}
		else { std::cerr << "Invalid Move!" << std::endl; return false; } //else the move was not valid for the board, so return false so this function can be called again in the main function until a valid move is input	
	}
	else { std::cerr << "Invalid Move!" << std::endl; return false; } //return false as the input squares are not on the board
}


