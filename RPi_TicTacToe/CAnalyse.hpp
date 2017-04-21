#ifndef CANALYSE_HPP
#define CANALYSE_HPP

// Includes
#include<iostream>
#include<array>
#include"CGrid.hpp"

// CAnalyse
class CAnalyse{
public:
	
	typedef std::array<std::array<char, 3>, 3> t_grid;

	// -- Kon/Destruktor --
	CAnalyse();
	~CAnalyse();

	// -- Methoden -- 

	// Methode vergleicht zwei Arrays und gibt true zur�ck wenn sie gleich sind
	bool compare(std::array<char, 3> a, std::array<char, 3> b);

	// Methode gib ein Char-Array mit der L�nge 3 zur�ck
	std::array<char, 3> getArray(char a, char b, char c);
	
	// Methode gibt eine Spalte des Grids zur�ck
	std::array<char, 3> getGridVer(t_grid grid, int col);

	// Methoden geben die Diagonalen zur�ck
	std::array<char, 3> getDiaLU(t_grid grid);
	std::array<char, 3> getDiaRU(t_grid grid);

	// Methode pr�ft ob ein bestimmter Spieler gewonnen hat
	bool checkGrid(t_grid grid, char player);

	// Methode pr�ft ob ein Spieler gewonnen hat 
	char checkGrid(t_grid grid);

private:

	// -- Member Vars --
	int *_equalChars;
	std::array<char, 3> *_tempArr;
};

#endif
