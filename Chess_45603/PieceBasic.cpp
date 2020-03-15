#include "PieceBasic.h"



void PieceBasic::set_color(bool a) {
	color = a;
	return;
}
bool PieceBasic::get_color() {
	return color;
}
int PieceBasic::get_number() {
	return number;
}
char PieceBasic::get_letter() {
	return letter;
}
void PieceBasic::set_place(int set_letter, int set_number) {
	number = set_number;
	letter = set_letter;
	return;
}
void PieceBasic::set_taken() {
	taken = 1;
	return;
}
bool PieceBasic::get_taken() {
	return taken;
}
/*bool PieceBasic::on_board(char letter, int number) {
	if (letter<'a' || letter>'g' || number < 1 || number>8) return false;
	else return true;
}*/
