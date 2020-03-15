#include "PieceBasic.h"

class Pawn: public PieceBasic{
private:
	bool first_turn = 1;
public:

	Pawn(char new_letter, int new_number, int Board[8][8]) {
		set_place(new_letter, new_number);
		Board[8 - (new_number)][new_letter - 'a'] = 1;
	}

	int symbol();
	void set_first_turn();
	bool get_first_turn();
	void move(char letter, int number, int Board[8][8]);
};

class Knight : public PieceBasic {
public:
	Knight(char new_letter, int new_number, int Board[8][8]) {
		set_place(new_letter, new_number);
		Board[8 - (new_number)][new_letter - 'a'] = 2;
	}

	int symbol();
	void move(char letter, int number, int Board[8][8]);
};

class Bishop :public PieceBasic {
public:
	Bishop(char new_letter, int new_number, int Board[8][8]) {
		set_place(new_letter, new_number);
		Board[8 - (new_number)][new_letter - 'a'] = 3;
	}

	int symbol();
	void move(char letter, int number, int Board[8][8]);
};

class Rook :public PieceBasic {
private:
	bool first_turn = 1;
public:
	Rook(char new_letter, int new_number, int Board[8][8]) {
		set_place(new_letter, new_number);
		Board[8 - (new_number)][new_letter - 'a'] = 4;
	}

	int symbol();
	void move(char letter, int number, int Board[8][8]);
	void set_first_turn();
	bool get_first_turn();
};

class Queen:public PieceBasic {
public:
	Queen(char new_letter, int new_number, int Board[8][8]) {
		set_place(new_letter, new_number);
		Board[8 - (new_number)][new_letter - 'a'] = 5;
	}

	int symbol();
	void move(char letter, int number, int Board[8][8]);
};

class King :public PieceBasic {
private:
	bool check = 0;
	bool first_turn = 1;
	bool flag1 = 0;
	bool flag2 = 0;
public:
	King(char new_letter, int new_number, int Board[8][8]) {
		set_place(new_letter, new_number);
		Board[8 - (new_number)][new_letter - 'a'] = 6;
	}

	int symbol();
	void set_flag1();
	bool get_flag1();
	void set_flag2();
	bool get_flag2();
	void set_first_turn();
	void set_false_first_turn();
	bool get_first_turn();
	void set_check();
	bool get_check();
	void move(char letter, int number, int Board[8][8]);

};

