#include <iostream>
#include <vector>
#include <fstream>

#include "Piece.h"

using namespace std;
//Turn Number
int turn_number = 0;

//The Board
int Board[8][8] = { 0,0,0,0,0,0,0,0,
					0,0,0,0,0,0,0,0,
					0,0,0,0,0,0,0,0,
					0,0,0,0,0,0,0,0,
					0,0,0,0,0,0,0,0,
					0,0,0,0,0,0,0,0,
					0,0,0,0,0,0,0,0,
					0,0,0,0,0,0,0,0 };

PieceBasic* Find_piece(char letter, int number, vector <PieceBasic*> vector ) {
	for (size_t i = 0; i < vector.size(); i++) {
		if ((*vector[i]).get_letter() == letter && (*vector[i]).get_number() == number) {
			return vector[i];
		}
	}
	return NULL; 
}

vector <PieceBasic*> White_pieces;
vector <PieceBasic*> Black_pieces;

void PrintTheBoard() {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 3; j++){
			for (int x = 0; x < 8; x++){
				if ((i + x) % 2 == 0 && j != 1) cout << "* * *";
				else if ((i + x) % 2 == 1 && j != 1) cout << "     ";
				else if ((i + x) % 2 == 0 && j == 1) {
					cout << "* ";
					switch (Board[i][x]) {
					case 0: { cout << "*"; break; }
						case 1: {
							if (Find_piece(x+'a', 8-i,White_pieces)!=NULL) {
								cout << "p";
							}
							else cout << "P";
							break;
						}
						case 2: {
							if (Find_piece(x+'a', 8-i,White_pieces)!=NULL) {
								cout << "n";
							}
							else cout << "N";
							break;
						}
						case 3: {
							if (Find_piece(x+'a', 8-i,White_pieces)!=NULL) {
								cout << "b";
							}
							else cout << "B";
							break;
						}
						case 4: {
							if (Find_piece(x+'a', 8-i,White_pieces)!=NULL) {
								cout << "r";
							}
							else cout << "R";
							break;
						}
						case 5: {
							if (Find_piece(x+'a', 8-i,White_pieces)!=NULL) {
								cout << "q";
							}
							else cout << "Q";
							break;
						}
						case 6: {
							if (Find_piece(x+'a', 8-i,White_pieces)!=NULL) {
								cout << "k";
							}
							else cout << "K";
							break;
						}		
					}
					cout << " *";
				}
				else if ((i + x) % 2 == 1 && j == 1) {
					cout << "  ";
					switch (Board[i][x]) {
					case 0: {cout << " "; break; }
					case 1: {
						if (Find_piece(x+'a', 8-i,White_pieces)!=NULL) {
							cout << "p";
						}
						else cout << "P";
						break;
					}
					case 2: {
						if (Find_piece(x+'a', 8-i,White_pieces)!=NULL) {
							cout << "n";
						}
						else cout << "N";
						break;
					}
					case 3: {
						if (Find_piece(x+'a', 8-i,White_pieces)!=NULL) {
							cout << "b";
						}
						else cout << "B";
						break;
					}
					case 4: {
						if (Find_piece(x+'a', 8-i,White_pieces)!=NULL) {
							cout << "r";
						}
						else cout << "R";
						break;
					}
					case 5: {
						if (Find_piece(x+'a', 8-i,White_pieces)!=NULL) {
							cout << "q";
						}
						else cout << "Q";
						break;
					}
					case 6: {
						if (Find_piece(x+'a', 8-i,White_pieces)!=NULL) {
							cout << "k";
						}
						else cout << "K";
						break;
					}
					}
					cout << "  ";
				}

			}
			if (j == 1) {
				cout << "   " << 8 - i;
			}
			cout << endl;
		}
	}
	cout << endl;
	for (char i = 'a'; i <= 'h'; i++){
		cout << "  " << i << "  ";

	}
	cout << endl << endl;
}

void rocade(King* king, Rook* rook) {

		if ((*rook).get_letter() == 'a') {
			Board[8 - ((*rook).get_number())][(*rook).get_letter() - 'a'] = 0;
			(*rook).set_place((*king).get_letter()+1, (*king).get_number());
			Board[8 - (*king).get_number()][(*king).get_letter() + 1 - 'a'] = 4;
			(*rook).set_first_turn();
			(*king).set_first_turn();
		}
		if ((*rook).get_letter() == 'h') {
			Board[8 - ((*rook).get_number())][(*rook).get_letter() - 'a'] = 0;
			(*rook).set_place((*king).get_letter() - 1, (*king).get_number());
			Board[8 - (*king).get_number()][(*king).get_letter() - 1 - 'a'] = 4;
			(*rook).set_first_turn();
			(*king).set_first_turn();
		}
}
bool check_check(King* king,vector<PieceBasic*> vector) {
	for (size_t i = 0; i < vector.size(); i++){
		char old_letter = (*vector[i]).get_letter();
		int old_number = (*vector[i]).get_number();
		(*vector[i]).move((*king).get_letter(),(*king).get_number(),Board);
		if ((*vector[i]).get_letter() != old_letter || (*vector[i]).get_number() != old_number) {
			Board[8 - (*vector[i]).get_number()][(*vector[i]).get_letter() - 'a'] = 6;
			Board[8 - (old_number)][old_letter - 'a'] = (*vector[i]).symbol();
			(*vector[i]).set_place(old_letter, old_number);
			return true;
		}
	}
	return false;
}
bool check_mate(King* king, vector <PieceBasic*> vector_our, vector <PieceBasic*> vector_enemy) {
	char old_letter;
	int old_number;
	PieceBasic* piece;
	for (size_t i = 0; i < vector_our.size(); i++) {
		old_letter = (*vector_our[i]).get_letter();
		old_number = (*vector_our[i]).get_number();
		for (int j = 1; j <= 8; j++) {
			for (char x = 'a'; x <= 'h'; x++) {
				if (Board[8-j][x-'a'] == 0) {
					(*vector_our[i]).move(x, j, Board);
					
					if (!check_check(king, vector_enemy)) {
						Board[8 - old_number][old_letter - 'a'] = (*vector_our[i]).symbol();
						(*vector_our[i]).set_place(old_letter, old_number);
						Board[8 - j][x - 'a'] = 0;			
						return false;
					}

					Board[8 - old_number][old_letter - 'a'] = (*vector_our[i]).symbol();
					(*vector_our[i]).set_place(old_letter, old_number);
					Board[8 - j][x - 'a'] = 0;
				}
				else if (Find_piece(x, j, vector_enemy) != NULL) {
					piece = (Find_piece(x, j, vector_enemy));
					(*vector_our[i]).move(x, j, Board);
					if (!check_check(king, vector_enemy)) {
						Board[8 - old_number][old_letter - 'a'] = (*vector_our[i]).symbol();
						(*vector_our[i]).set_place(old_letter, old_number);
						vector_enemy.push_back(piece);
						Board[8 - j][x - 'a'] = (*piece).symbol();
						return false;
					}
					Board[8 - old_number][old_letter - 'a'] = (*vector_our[i]).symbol();
					(*vector_our[i]).set_place(old_letter, old_number);
					vector_enemy.push_back(piece);
					Board[8 - j][x - 'a'] = (*piece).symbol();
				}
				
			}
		}
	}
	PrintTheBoard();
	return true;
}

bool Game() {
	bool checkmate = 0;
	char letter, new_letter;
	int number, new_number;
	bool correct_move = 0;

	Pawn a2('a', 2, Board), //white pieces on the board
		b2('b', 2, Board),
		c2('c', 2, Board),
		d2('d', 2, Board),
		e2('e', 2, Board),
		f2('f', 2, Board),
		g2('g', 2, Board),
		h2('h', 2, Board),

		a7('a', 7, Board), //black pieces on the board
		b7('b', 7, Board),
		c7('c', 7, Board),
		d7('d', 7, Board),
		e7('e', 7, Board),
		f7('f', 7, Board),
		g7('g', 7, Board),
		h7('h', 7, Board);

	Knight Nb1('b', 1, Board),
		   Ng1('g', 1, Board),
		   Nb8('b', 8, Board),
		   Ng8('g', 8, Board);

	Bishop Bc1('c', 1, Board),
		Bf1('f', 1, Board),
		Bc8('c', 8, Board),
		Bf8('f', 8, Board);

	Rook Ra1('a', 1, Board),
		Rh1('h', 1, Board),
		Ra8('a', 8, Board),
		Rh8('h', 8, Board);

	Queen Qd1('d', 1, Board),
		  Qd8('d', 8, Board);

	King Ke1('e', 1, Board),
		 Ke8('e', 8, Board);
		

	White_pieces.push_back(&a2);
	White_pieces.push_back(&b2);
	White_pieces.push_back(&c2);
	White_pieces.push_back(&d2);
	White_pieces.push_back(&e2);
	White_pieces.push_back(&f2);
	White_pieces.push_back(&h2);
	White_pieces.push_back(&g2);
	White_pieces.push_back(&Nb1);
	White_pieces.push_back(&Ng1);
	White_pieces.push_back(&Bc1);
	White_pieces.push_back(&Bf1);
	White_pieces.push_back(&Ra1);
	White_pieces.push_back(&Rh1);
	White_pieces.push_back(&Qd1);
	White_pieces.push_back(&Ke1);

	Black_pieces.push_back(&a7);
	Black_pieces.push_back(&b7);
	Black_pieces.push_back(&c7);
	Black_pieces.push_back(&d7);
	Black_pieces.push_back(&e7);
	Black_pieces.push_back(&f7);
	Black_pieces.push_back(&h7);
	Black_pieces.push_back(&g7);
	Black_pieces.push_back(&Nb8);
	Black_pieces.push_back(&Ng8);
	Black_pieces.push_back(&Bc8);
	Black_pieces.push_back(&Bf8);
	Black_pieces.push_back(&Ra8);
	Black_pieces.push_back(&Rh8);
	Black_pieces.push_back(&Qd8);
	Black_pieces.push_back(&Ke8);

	for (size_t i = 0; i < Black_pieces.size(); i++){
		(*Black_pieces[i]).set_color(1);
	}
	
	PrintTheBoard();

	//Start the game
	while (checkmate == 0) {

		//check for mate and check
		if (check_check(&Ke1, Black_pieces)) {
			if (check_mate(&Ke1, White_pieces, Black_pieces)) {
				cout << "Checkmate! Black win!" << endl;
				correct_move = 1;
				checkmate = 1;
				return 1;
			}
			else {
				cout << "Check!" << endl;
				correct_move = 0;
				cout << "White's turn. Which piece you want to move?" << endl;
			}
		}
		else {
			cout << "White's turn. Which piece you want to move?" << endl;
			correct_move = 0;
		}
		//white's turn starts
		while (correct_move == 0) {
			cin >> letter >> number;
			while (letter<'a' || letter>'h' || number < 1 || number>8) {
				cout << "Invalid command." << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cin >> letter >> number;
			}
			PieceBasic* piece = Find_piece(letter, number, White_pieces);
			//there is no piece
			if (Board[8 - number][letter - 'a'] == 0) cout << "There is no piece there! Enter again." << endl;
			//there is a piece, but its not white
			else if (piece == NULL) cout << "The piece is black! Type carefully" << endl;
			//its our piece
			else {
				cout << (*piece).get_letter() << (*piece).get_number() << " goes to?" << endl;;
				cin >> new_letter >> new_number;
				if (new_letter<'a' || new_letter>'h' || new_number < 1 || new_number>8) {
					cout << "Invalid command. Which piece you want to move?" << endl;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');

				}
				//there is no piece on the square we want to go
				else if (Find_piece(new_letter, new_number, White_pieces) == NULL && Find_piece(new_letter, new_number, Black_pieces) == NULL) {

					(*piece).move(new_letter, new_number, Board);

					//if you moved and there is a check
					if ((*piece).get_letter() == new_letter && (*piece).get_number() == new_number && check_check(&Ke1, Black_pieces)) {
						cout << "You are in check, invalid command!" << endl;
						Board[8 - (*piece).get_number()][(*piece).get_letter() - 'a'] = 0;
						(*piece).set_place(letter, number);
						Board[8 - (number)][letter - 'a'] = (*piece).symbol();

					}

					//if you moved and there is no check
					else if ((*piece).get_letter() == new_letter && (*piece).get_number() == new_number && !check_check(&Ke1, Black_pieces)) {
						bool flag = true;
						/*if (piece == &Ke1 && Ke1.get_flag1()) {
							rocade(&Ke1, &Ra1);
						}
						else if (piece == &Ke1 && Ke1.get_flag2()) {
							rocade(&Ke1, &Rh1);
						}*/
						if (piece == &Ke1 && Ke1.get_flag1() && Ra1.get_first_turn() && Ra1.get_number() == Ke1.get_number()) {
							for (int i = 1; i < 4 && flag==true; i++){
								King *temp_K = new King (i + 'a', 1, Board);
								if (check_check(temp_K, Black_pieces)) {
									Board[7][i] = 0;
									flag = false;
								}
								delete temp_K;
							}
						if (flag == true) {
							rocade(&Ke1, &Ra1);
						}
						else {
							Board[7][2] = 0;
							Board[7][4] = 6;
							Ke1.set_place('e', 1);
							Ke1.set_false_first_turn();
						}
						}
						else if (piece == &Ke1 && Ke1.get_flag2() && Rh1.get_first_turn() && Rh1.get_number() == Ke1.get_number()) {
					
						for (int i = 5; i < 7 && flag == true; i++) {
							King *temp_K = new King(i + 'a', 1, Board);
							if (check_check(temp_K, Black_pieces)) {
								Board[7][i] = 0;
								flag = false;
							}
							delete temp_K;
						}
						if (flag == true) {
							rocade(&Ke1, &Rh1);
						}
						else {
							Board[7][6] = 0;
							Board[7][4] = 6;
							Ke1.set_place('e', 1);
							Ke1.set_false_first_turn();
						}
						}
						//Pawn promotion
						else if ((*piece).symbol() == 1 && new_number == 8) {
							char new_piece_symbol;
							cout << (*piece).get_letter() << (*piece).get_number() << " will turn into?"<< endl;
							cin >> new_piece_symbol;
							while (new_piece_symbol != 'n' && new_piece_symbol != 'b' && new_piece_symbol != 'r' && new_piece_symbol != 'q') {
								cout << "Invalid command. Please type one of the following: n/b/r/q" << endl;
								cin.clear();
								cin.ignore(numeric_limits<streamsize>::max(), '\n');
								cin >> new_piece_symbol;
							}
							for (size_t i=0; i < White_pieces.size(); i++) {

								if(White_pieces[i]==piece){
									switch (new_piece_symbol) {

										case 'n': {
											White_pieces.erase(White_pieces.begin()+i);
											Knight *ptr = new Knight((*piece).get_letter(), (*piece).get_number(), Board);
											White_pieces.push_back(ptr);
											break;
										}
										case 'b': {
											White_pieces.erase(White_pieces.begin() + i);
											Bishop *ptr = new Bishop((*piece).get_letter(), (*piece).get_number(), Board);
											White_pieces.push_back(ptr);
											break;
										}
										case 'r': {
											White_pieces.erase(White_pieces.begin() + i);
											Rook *ptr = new Rook((*piece).get_letter(), (*piece).get_number(), Board);
											White_pieces.push_back(ptr);
											break;
										}
										case 'q': {
											White_pieces.erase(White_pieces.begin() + i);
											Queen *ptr = new Queen((*piece).get_letter(), (*piece).get_number(), Board);
											White_pieces.push_back(ptr);
											break;
										}
												  
									}
									
								}
							}
						}
						if (flag) {
							correct_move = 1;
							system("CLS");

							PrintTheBoard();
						}
						
				}

					//if you didn't move
					else cout << "Not a valid command, try again!" << endl;
			}

				//if there is a black piece
				else if (Find_piece(new_letter, new_number, Black_pieces) != NULL) {

					
					(*piece).move(new_letter, new_number, Board);

					//you moved and there is no check
					if ((*piece).get_letter() == new_letter && (*piece).get_number() == new_number && !check_check(&Ke1, Black_pieces)) {
						//Pawn promotion
						if ((*piece).symbol() == 1 && new_number == 8) {
							char new_piece_symbol;
							cout << (*piece).get_letter() << (*piece).get_number() << " will turn into?" << endl;
							cin >> new_piece_symbol;
							while (new_piece_symbol != 'n' && new_piece_symbol != 'b' && new_piece_symbol != 'r' && new_piece_symbol != 'q') {
								cout << "Invalid command. Please type one of the following: n/b/r/q" << endl;
								cin.clear();
								cin.ignore(numeric_limits<streamsize>::max(), '\n');
								cin >> new_piece_symbol;
							}
							for (size_t i = 0; i < White_pieces.size(); i++) {

								if (White_pieces[i] == piece) {
									switch (new_piece_symbol) {

									case 'n': {
										White_pieces.erase(White_pieces.begin() + i);
										Knight *ptr = new Knight((*piece).get_letter(), (*piece).get_number(), Board);
										White_pieces.push_back(ptr);
										break;
									}
									case 'b': {
										White_pieces.erase(White_pieces.begin() + i);
										Bishop *ptr = new Bishop((*piece).get_letter(), (*piece).get_number(), Board);
										White_pieces.push_back(ptr);
										break;
									}
									case 'r': {
										White_pieces.erase(White_pieces.begin() + i);
										Rook *ptr = new Rook((*piece).get_letter(), (*piece).get_number(), Board);
										White_pieces.push_back(ptr);
										break;
									}
									case 'q': {
										White_pieces.erase(White_pieces.begin() + i);
										Queen *ptr = new Queen((*piece).get_letter(), (*piece).get_number(), Board);
										White_pieces.push_back(ptr);
										break;
									}

									}

								}
							}
						}
						correct_move = 1;
						system("CLS");
						PrintTheBoard();
						for (size_t i = 0; i < Black_pieces.size(); i++) {
							if (Find_piece(new_letter, new_number, Black_pieces) == Black_pieces[i]) Black_pieces.erase(Black_pieces.begin() + i);
						}
					}
					//you moved and there is a check
					else if ((*piece).get_letter() == new_letter && (*piece).get_number() == new_number && check_check(&Ke1, Black_pieces)) {

						cout << "You are in check, invalid command!" << endl;
						Board[8 - (*piece).get_number()][(*piece).get_letter() - 'a'] = (*Find_piece(new_letter, new_number, Black_pieces)).symbol();
						(*piece).set_place(letter, number);
						Board[8 - (number)][letter - 'a'] = (*piece).symbol();

					}
					//if you didn't move
					else cout << "Not a valid command, try again!" << endl;
				}
				else cout << "Not a valid command" << endl;
			}
		}

		//check for mate and check
		if (check_check(&Ke8, White_pieces)) {
			if (check_mate(&Ke8, Black_pieces, White_pieces)) {
				cout << "Checkmate! White win!" << endl;
				correct_move = 1;
				checkmate = 1;
				return 0;
			}
			else {
				cout << "Check!" << endl;
				correct_move = 0;
				cout << "Black's turn. Which piece you want to move?" << endl;
			}
		}
		else if (checkmate != 1) {
			cout << "Black's turn. Which piece you want to move?" << endl;
			correct_move = 0;
		}
		//Black's turn
		while (correct_move == 0) {
			cin >> letter >> number;
			while (letter<'a' || letter>'h' || number < 1 || number>8) {
				cout << "Invalid command." << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cin >> letter >> number;
			}
			PieceBasic* piece = Find_piece(letter, number, Black_pieces);
			if (Board[8 - number][letter - 'a'] == 0) cout << "There is no piece there! Enter again." << endl;
			else if (piece == NULL) cout << "The piece is white! Type carefully" << endl;
			else {
				cout << (*piece).get_letter() << (*piece).get_number() << " goes to?" << endl;;
				cin >> new_letter >> new_number;

				if (new_letter<'a' || new_letter>'h' || new_number < 1 || new_number>8) {
					cout << "Invalid command. Which piece you want to move?" << endl;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
				}

				else if (Find_piece(new_letter, new_number, White_pieces) == NULL && Find_piece(new_letter, new_number, Black_pieces) == NULL) {

					(*piece).move(new_letter, new_number, Board);
					//you moved and there is check
					if ((*piece).get_letter() == new_letter && (*piece).get_number() == new_number && check_check(&Ke8, White_pieces)) {
						cout << "You are in check, invalid command!" << endl;
						Board[8 - (*piece).get_number()][(*piece).get_letter() - 'a'] = 0;
						(*piece).set_place(letter, number);
						Board[8 - (number)][letter - 'a'] = (*piece).symbol();

					}
					//you moved and there is no check
					else if ((*piece).get_letter() == new_letter && (*piece).get_number() == new_number && !check_check(&Ke8, White_pieces)) {
						bool flag = true;
						/*if (piece == &Ke8 && Ke8.get_flag1()) {
							rocade(&Ke8, &Ra8);
						}
						else if (piece == &Ke8 && Ke8.get_flag2()) {
							rocade(&Ke8, &Rh8);
						}*/
						if (piece == &Ke8 && Ke8.get_flag1() && Ra8.get_first_turn() && Ra8.get_number() == Ke8.get_number()) {
							for (int i = 1; i < 4 && flag == true; i++) {
								King *temp_K = new King(i + 'a', 8, Board);
								if (check_check(temp_K, White_pieces)) {
									Board[0][i] = 0;
									flag = false;
								}
								delete temp_K;
							}
							if (flag == true) {
								rocade(&Ke8, &Ra8);
							}
							else {
								Board[0][2] = 0;
								Board[0][4] = 6;
								Ke8.set_place('e', 8);
								Ke8.set_false_first_turn();
							}
						}
						else if (piece == &Ke8 && Ke8.get_flag2() && Rh8.get_first_turn() && Rh8.get_number() == Ke8.get_number()) {
							for (int i = 5; i < 7 && flag == true; i++) {
								King *temp_K = new King(i + 'a', 8, Board);
								if (check_check(temp_K, White_pieces)) {
									Board[0][i] = 0;
									flag = false;
								}
								delete temp_K;
							}
							if (flag == true) {
								rocade(&Ke8, &Rh8);
							}
							else {
								Board[0][6] = 0;
								Board[0][4] = 6;
								Ke8.set_place('e', 8);
								Ke8.set_false_first_turn();
							}
						}
					else if ((*piece).symbol() == 1 && new_number == 1) {
							char new_piece_symbol;
							cout << (*piece).get_letter() << (*piece).get_number() << " will turn into?" << endl;
							cin >> new_piece_symbol;
							while (new_piece_symbol != 'N' && new_piece_symbol != 'B' && new_piece_symbol != 'R' && new_piece_symbol != 'Q') {
								cout << "Invalid command. Please type one of the following: N/B/R/Q" << endl;
								cin.clear();
								cin.ignore(numeric_limits<streamsize>::max(), '\n');
								cin >> new_piece_symbol;
							}
							for (size_t i=0; i < Black_pieces.size(); i++) {

								if (Black_pieces[i] == piece) {
									switch (new_piece_symbol) {

									case 'N': {
										Black_pieces.erase(Black_pieces.begin() + i);
										Knight *ptr = new Knight((*piece).get_letter(), (*piece).get_number(), Board);
										Black_pieces.push_back(ptr);
										(*ptr).set_color(1);
										break;
									}
									case 'B': {
										Black_pieces.erase(Black_pieces.begin() + i);
										Bishop *ptr = new Bishop((*piece).get_letter(), (*piece).get_number(), Board);
										Black_pieces.push_back(ptr);
										(*ptr).set_color(1);
										break;
									}
									case 'R': {
										Black_pieces.erase(Black_pieces.begin() + i);
										Rook *ptr = new Rook((*piece).get_letter(), (*piece).get_number(), Board);
										Black_pieces.push_back(ptr);
										(*ptr).set_color(1);
										break;
									}
									case 'Q': {
										Black_pieces.erase(Black_pieces.begin() + i);
										Queen *ptr = new Queen((*piece).get_letter(), (*piece).get_number(), Board);
										Black_pieces.push_back(ptr);
										(*ptr).set_color(1);
										break;
									}
											 
									}
									
								}
							}
						}
						if (flag) {
							correct_move = 1;
							system("CLS");
							PrintTheBoard();
						}
					}
					//you didn't move
					else cout << "Not a valid command, try again!" << endl;
				}
				else if (Find_piece(new_letter, new_number, White_pieces) != NULL) {

					(*piece).move(new_letter, new_number, Board);

					if ((*piece).get_letter() == new_letter && (*piece).get_number() == new_number && !check_check(&Ke8, White_pieces)) {
						if ((*piece).symbol() == 1 && new_number == 1) {
							char new_piece_symbol;
							cout << (*piece).get_letter() << (*piece).get_number() << " will turn into?" << endl;
							cin >> new_piece_symbol;
							while (new_piece_symbol != 'N' && new_piece_symbol != 'B' && new_piece_symbol != 'R' && new_piece_symbol != 'Q') {
								cout << "Invalid command. Please type one of the following: N/B/R/Q" << endl;
								cin.clear();
								cin.ignore(numeric_limits<streamsize>::max(), '\n');
								cin >> new_piece_symbol;
							}
							for (size_t i=0; i < Black_pieces.size(); i++) {

								if (Black_pieces[i] == piece) {
									switch (new_piece_symbol) {

									case 'N': {
										Black_pieces.erase(Black_pieces.begin() + i);
										Knight *ptr = new Knight((*piece).get_letter(), (*piece).get_number(), Board);
										Black_pieces.push_back(ptr);
										(*ptr).set_color(1);
										break;
									}
									case 'B': {
										Black_pieces.erase(Black_pieces.begin() + i);
										Bishop *ptr = new Bishop((*piece).get_letter(), (*piece).get_number(), Board);
										Black_pieces.push_back(ptr);
										(*ptr).set_color(1);
										break;
									}
									case 'R': {
										Black_pieces.erase(Black_pieces.begin() + i);
										Rook *ptr = new Rook((*piece).get_letter(), (*piece).get_number(), Board);
										Black_pieces.push_back(ptr);
										(*ptr).set_color(1);
										break;
									}
									case 'Q': {
										Black_pieces.erase(Black_pieces.begin() + i);
										Queen *ptr = new Queen((*piece).get_letter(), (*piece).get_number(), Board);
										Black_pieces.push_back(ptr);
										(*ptr).set_color(1);
										break;
									}
											 
									}
									
								}
							}
						}
						correct_move = 1;
						system("CLS");
						PrintTheBoard();
						for (size_t i = 0; i < White_pieces.size(); i++) {
							if (Find_piece(new_letter, new_number, White_pieces) == White_pieces[i]) White_pieces.erase(White_pieces.begin() + i);
						}
					}
					else if ((*piece).get_letter() == new_letter && (*piece).get_number() == new_number && !check_check(&Ke1, Black_pieces)) {

						cout << "You are in check, invalid command!" << endl;
						Board[8 - (*piece).get_number()][(*piece).get_letter() - 'a'] = (*Find_piece(new_letter, new_number, White_pieces)).symbol();
						(*piece).set_place(letter, number);
						Board[8 - (number)][letter - 'a'] = (*piece).symbol();

					}
					else cout << "Not a valid command, try again!" << endl;
				}
				else cout << "Not a valid command" << endl;
			}
		}

	}
	
}
int main() {
	char name2[11];
	char name1[11];
	string file_name="C:/Users/User/source/repos/Chess_45603/Files/";
	cout << "Hi there! " << endl << "Enter your fabulous name:" << endl;
	cin.getline(name2, 10);
	cout << name2 << " will be facing: ";
	cin.getline(name1, 10);
	cout << name2 << " is white" << endl << name1 << " is black" << endl;

	file_name += name2;
	file_name +="-";
	file_name += name1;
	file_name += ".txt";

	ofstream chess_input(file_name.c_str(), ios::app);
	if (!chess_input) {
		cerr << "File couldn’t be opened!\n";
	}
	chess_input << name2 << " - " << name1;

	if (Game()) {
		chess_input << endl << "0 - 1";
	}
	else chess_input << endl << "1 - 0";
	chess_input << endl;

	
	cout << "works";
	system("PAUSE");
	return 0;
}