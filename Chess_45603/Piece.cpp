#include<iostream>

#include "Piece.h"

//Pawn
int Pawn::symbol() {
	return 1;
}
bool Pawn::get_first_turn() {
	return first_turn;
}
void Pawn::set_first_turn() {
	first_turn = 0;
}

void Pawn::move(char letter, int number, int Board[8][8]) {
	char a = get_letter();
	int b = get_number();

	if (get_color() == 0) {
		//moving
		if (number == b + 1 && letter == a && Board[8 - (number)][letter - 'a'] == 0 && !get_taken() ) { //&& on_board(letter, number)
			set_place(letter, number);
			Board[8 - b][a - 'a'] = 0;
			Board[8 - (number)][letter - 'a'] = 1;
			if (get_first_turn() == 0) {
				set_first_turn();
			}

		}
		else if (get_first_turn() && number == b + 2 && letter == a && Board[8 - (number)][letter - 'a'] == 0 && Board[8 - number + 1][letter - 'a'] == 0 && !get_taken() ) { //&& on_board(letter, number)
			set_place(letter, number);
			Board[8 - b][a - 'a'] = 0;
			Board[8 - (number)][letter - 'a'] = 1;
			set_first_turn();
		}
		else if (number == b + 1 && (letter == a + 1 || letter == a - 1) && Board[8 - (number)][letter - 'a'] != 0 && !get_taken()) {
			set_place(letter, number);
			Board[8 - b][a - 'a'] = 0;
			Board[8 - number][letter - 'a'] = 1;
			set_first_turn();
		}

		else return;
	}
	if (get_color() == 1) {
		if (number == b - 1 && letter == a && Board[8 - (number)][letter - 'a'] == 0 && !get_taken() ) { //&& on_board(letter,number)
			set_place(letter, number);
			Board[8 - b][a - 'a'] = 0;
			Board[8 - (number)][letter - 'a'] = 1;
			if (get_first_turn() == 0) {
				set_first_turn();
			}

		}
		else if (get_first_turn() && number == b - 2 && letter == a && Board[8 - (number)][letter - 'a'] == 0 && Board[8-number-1][letter-'a']==0 && !get_taken()) { // && on_board(letter, number)
			set_place(letter, number);
			Board[8 - b][a - 'a'] = 0;
			Board[8 - (number)][letter - 'a'] = 1;
			set_first_turn();

		}
		else if (number == b - 1 && (letter == a + 1 || letter == a - 1) && Board[8 - (number)][letter - 'a'] != 0 && !get_taken()) {
			set_place(letter, number);
			Board[8 - b][a - 'a'] = 0;
			Board[8 - number][letter - 'a'] = 1;
			set_first_turn();
		}
		else return;
	}
	return;
}

//Knight


int Knight::symbol() {
	return 2;
}
void Knight::move(char letter, int number, int Board[8][8]) {
	char a = get_letter();
	int b = get_number();
		//moving
		if ((a == letter + 1 || a==letter-1) && (b == number + 2 || b == number - 2) || (b == number + 1 || b == number - 1) && (a == letter + 2 || a == letter - 2)) {
			set_place(letter, number);
			Board[8 - b][a - 'a'] = 0;
			Board[8 - (number)][letter - 'a'] = 2;
		}
		else return;
}

//Bishop

int Bishop::symbol() {
	return 3;
}
void Bishop::move(char letter, int number, int Board[8][8]) {
	char a = get_letter();
	int b = get_number();
	//moving
	if (letter - a == number - b || a - letter == number - b) {
		if (a < letter && b < number) {
			for (int i = 1; i < number - b; i++) {
				if (Board[8 - (b + i)][(a + i) - 'a'] != 0) {
					return;
				}
			}
			set_place(letter, number);
			Board[8 - b][a - 'a'] = 0;
			Board[8 - (number)][letter - 'a'] = 3;
		}
		if (a > letter && b > number) {
			for (int i = 1; i < b - number ; i++) {
				if (Board[8 - (b - i)][(a - i) - 'a'] != 0) {
					return;
				}
			}
			set_place(letter, number);
			Board[8 - b][a - 'a'] = 0;
			Board[8 - (number)][letter - 'a'] = 3;
		}
		if (a < letter && b > number) {
			for (int i = 1; i < b - number; i++) {
				if (Board[8 - (b - i)][(a + i) - 'a'] != 0) {
					return;
				}
			}
			set_place(letter, number);
			Board[8 - b][a - 'a'] = 0;
			Board[8 - (number)][letter - 'a'] = 3;
		}
		if (a > letter && b < number) {
			for (int i = 1; i < number - b; i++) {
				if (Board[8 - (b + i)][(a - i) - 'a'] != 0) {
					return;
				}
			}
			set_place(letter, number);
			Board[8 - b][a - 'a'] = 0;
			Board[8 - (number)][letter - 'a'] = 3;
		}
	}
	
	else return;
}

//Rook

int Rook::symbol() {
	return 4;
}
void Rook::set_first_turn() {
	first_turn = 0;
	return;
}
bool Rook::get_first_turn() {
	return first_turn;
}
void Rook::move(char letter, int number, int Board[8][8]) {
	char a = get_letter();
	int b = get_number();
	//moving
	if (letter == a ) {
		if (b > number) {
			for (int i = 1; i < b-number; i++) {
				if (Board[8 - (b - i)][a - 'a'] != 0) {
					return;
				}
			}
			set_place(letter, number);
			Board[8 - b][a - 'a'] = 0;
			Board[8 - (number)][letter - 'a'] = 4;
		}
		else if (b < number) {
			for (int i = 1; i <number-b; i++) {
				if (Board[8 - (b + i)][a - 'a'] != 0) {
					return;
				}
			}
			set_place(letter, number);
			Board[8 - b][a - 'a'] = 0;
			Board[8 - (number)][letter - 'a'] = 4;
		}
	}
	else if (number == b) {
		if (letter  < a) {
			for (int i = 1; i < a - letter; i++) {
				if (Board[8 - b][(a - i) - 'a'] != 0) {
				
					return;
				}
			}
			set_place(letter, number);
			Board[8 - b][a - 'a'] = 0;
			Board[8 - (number)][letter - 'a'] = 4;
		}
		if (letter > a) {
			for (int i = 1; i < letter - a; i++) {
				if (Board[8 - b][(a + i) - 'a'] != 0) {
				
					return;
				}
			}
			set_place(letter, number);
			Board[8 - b][a - 'a'] = 0;
			Board[8 - (number)][letter - 'a'] = 4;
		}
	}
	else return;
}

//Queen

int Queen::symbol() {
	return 5;
}
void Queen::move(char letter, int number, int Board[8][8]) {
	char a = get_letter();
	int b = get_number();
	if (letter == a) {
		if (b > number) {
			for (int i = 1; i < b - number; i++) {
				if (Board[8 - (b - i)][a - 'a'] != 0) {
					
					return;
				}
			}
			set_place(letter, number);
			Board[8 - b][a - 'a'] = 0;
			Board[8 - (number)][letter - 'a'] = 5;
		}
		else if (b < number) {
			for (int i = 1; i < number - b; i++) {
				if (Board[8 - (b + i)][a - 'a'] != 0) {
					
					return;
				}
			}
			set_place(letter, number);
			Board[8 - b][a - 'a'] = 0;
			Board[8 - (number)][letter - 'a'] = 5;
		}
	}
	else if (number == b) {
		if (letter < a) {
			for (int i = 1; i < a - letter; i++) {
				if (Board[8 - b][(a - i) - 'a'] != 0) {
					
					return;
				}
			}
			set_place(letter, number);
			Board[8 - b][a - 'a'] = 0;
			Board[8 - (number)][letter - 'a'] = 5;
		}
		if (letter > a) {
			for (int i = 1; i < letter - a; i++) {
				if (Board[8 - b][(a + i) - 'a'] != 0) {
					
					return;
				}
			}
			set_place(letter, number);
			Board[8 - b][a - 'a'] = 0;
			Board[8 - (number)][letter - 'a'] = 5;
		}
	}
	else if (letter - a == number - b || a - letter == number - b) {
		if (a < letter && b < number) {
			for (int i = 1; i < number - b; i++) {
				if (Board[8 - (b + i)][(a + i) - 'a'] != 0) {
					
					return;
				}
			}
			set_place(letter, number);
			Board[8 - b][a - 'a'] = 0;
			Board[8 - (number)][letter - 'a'] = 5;
		}
		if (a > letter && b > number) {
			for (int i = 1; i < b - number; i++) {
				if (Board[8 - (b - i)][(a - i) - 'a'] != 0) {
					
					return;
				}
			}
			set_place(letter, number);
			Board[8 - b][a - 'a'] = 0;
			Board[8 - (number)][letter - 'a'] = 5;
		}
		if (a < letter && b > number) {
			for (int i = 1; i < b - number; i++) {
				if (Board[8 - (b - i)][(a + i) - 'a'] != 0) {
					
					return;
				}
			}
			set_place(letter, number);
			Board[8 - b][a - 'a'] = 0;
			Board[8 - (number)][letter - 'a'] = 5;
		}
		if (a > letter && b < number) {
			for (int i = 1; i < number - b; i++) {
				if (Board[8 - (b + i)][(a - i) - 'a'] != 0) {
					
					return;
				}
			}
			set_place(letter, number);
			Board[8 - b][a - 'a'] = 0;
			Board[8 - (number)][letter - 'a'] = 5;
		}
	}
	else return;
}

//King

int King::symbol() {
	return 6;
}
void King::set_flag1() {
	flag1 = 1;
	return;
}
bool King::get_flag1() {
	return flag1;
}
void King::set_flag2() {
	flag2 = 1;
	return;
}
bool King::get_flag2() {
	return flag2;
}
void King::set_first_turn() {
	first_turn = 0;
	return;
}
void King::set_false_first_turn(){
	first_turn = 1;
	return;
}
bool King::get_first_turn() {
	return first_turn;
}
void King::set_check() {
	check = 1;
	return;
}
bool King::get_check() {
	return check;
}
void King::move(char letter, int number, int Board[8][8]) {
	char a = get_letter();
	int b = get_number();

	if ((a == letter + 1 || a == letter - 1 || a == letter) && (b == number + 1 || b == number - 1 || b == number) && (a != letter || number != b)) {
		set_place(letter, number);
		Board[8 - b][a - 'a'] = 0;
		Board[8 - (number)][letter - 'a'] = 6;
		set_first_turn();
	}
	else if (get_first_turn() && number == b && letter == a + 2 && Board[8 - number ][5] == 0) {
		set_place(letter, number);
		Board[8 - b][a - 'a'] = 0;
		Board[8 - (number)][letter - 'a'] = 6;
		set_first_turn();
		set_flag2();
	}
	else if (get_first_turn() && number == b && letter == a - 2 && Board[8 - number][1] == 0 && Board[8-number][3]==0) {
		set_place(letter, number);
		Board[8 - b][a - 'a'] = 0;
		Board[8 - (number)][letter - 'a'] = 6;
		set_first_turn();
		set_flag1();
	}
	else return;
}