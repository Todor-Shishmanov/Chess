
class PieceBasic{
private:
	int number;
	char letter;
	bool color=0; //white - 0 , black - 1
	bool taken=0;
public:
	void set_color(bool a);
	bool get_color();
	int get_number();
	char get_letter();
	void set_place(int set_letter, int set_number);
	void set_taken();
	bool get_taken();
	//bool on_board(char letter, int number);
	virtual void move(char letter, int number, int Board[8][8]) = 0;
	virtual int symbol() = 0;
};