#include"CAnalyse.hpp"

// -- Konstruktor --
CAnalyse::CAnalyse() {
	// Alloc Memory
	_equalChars = new int;
	_tempArr = new std::array<char, 3>();

	// Werte setzen 
	*_equalChars = 0;
}

// -- compare --
// Methode vergleicht zwei Arrays und gibt true zurück wenn sie gleich sind
// @param a, b: Arrays die verglichen werden sollen
//
bool CAnalyse::compare(std::array<char, 3> a, std::array<char, 3> b) {
	if (a.size() != 3 || b.size() != 3) {
		throw "EXCEPTION: Array_to_big";
	} else {
		*_equalChars = 0;
		for (int i = 0; i < b.size(); i++) {
			if (a.at(i) == b.at(i)) {
				*_equalChars += 1;
			}
		}
	}
	return (*_equalChars == 3 ? true : false);
}

// -- getArray --
// Methode gib ein Char-Array mit der Länge 3 zurück
// @param a, b, c: Elemente des neuen Char-Arrays
//
std::array<char, 3> CAnalyse::getArray(char a, char b, char c) {
	_tempArr->at(0) = a;
	_tempArr->at(1) = b;
	_tempArr->at(2) = c;
	return std::array<char, 3>{a, b, c};
}

// -- getGridVer --
// Methode gibt eine Spalte des Grids zurück
// @param grid: Grid dessen Spalte zurückgegeben werden soll
// @param col: Spalte die zurückgegeben werden soll
//
std::array<char, 3> CAnalyse::getGridVer(t_grid grid, int col) {
	return getArray(
		grid.at(0).at(col),
		grid.at(1).at(col), 
		grid.at(2).at(col));
}

// -- checkGrid --
// Methode prüft ob ein bestimmter Spieler gewonnen hat
// @param grid  : Spielfeld, dass geprüft werden soll
// @param player: Spieler der überprüft werden soll
//
bool CAnalyse::checkGrid(t_grid grid, char player) {
	for(int i = 0; i < 3; i++)
		if (compare(grid.at(i), getArray(player, player, player))) return true;
	for(int i = 0; i < 3; i++)
		if (compare(getGridVer(grid, i), getArray(player, player, player))) return true;
	if (compare(getDiaLU(grid), getArray(player, player, player))) return true;
	if (compare(getDiaRU(grid), getArray(player, player, player))) return true;
	return false;
}

// -- getDiaLU --
// Methode gibt die Diagonale der linken oberen Ecke zur rechten unteren Ecke zurück
// @param grid: Spielfeld dessen Diagonale zurückgegeben werden soll
//
std::array<char, 3> CAnalyse::getDiaLU(t_grid grid) {
	return getArray(grid.at(0).at(0),
					grid.at(1).at(1),
					grid.at(2).at(2));
}

// -- getDiaRU --
// Methode gibt die Diagonale der rechten oberen Ecke zur linken unteren Ecke zurück
// @param grid: Spielfeld dessen Diagonale zurückgegeben werden soll
//

std::array<char, 3> CAnalyse::getDiaRU(t_grid grid) {
	return getArray(grid.at(0).at(2),
					grid.at(1).at(1),
					grid.at(2).at(0));
}

// -- checkGrid --
// Methode prüft ob ein Spieler gewonnen hat 
// @param grid: Spielfeld, dass überprüft werden soll
//
char CAnalyse::checkGrid(t_grid grid) {
	if (checkGrid(grid, PL_1))
		return PL_1;
	else if (checkGrid(grid, PL_2))
		return PL_2;
	else
		return NONE;
}

// -- Destruktor --
CAnalyse::~CAnalyse() {
	// Free Memory
	SAFE_DELETE(_equalChars);
	SAFE_DELETE(_tempArr);
}
