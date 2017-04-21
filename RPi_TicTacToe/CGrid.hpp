#ifndef CGRID_HPP
#define CGRID_HPP

//Includes
#include<iostream>
#include<array>
#include<exception>
#include"CStaticTools.hpp"

#define NONE ' '
#define PL_1 'X'
#define PL_2 'O'

// CGrid
class CGrid{
public:

	// -- Kon/Destruktor --
	CGrid();
	~CGrid();

	// -- Methoden --
	void reset();
	bool setBox(int x, int y, char player);
	void showGrid();
	std::array<std::array<char, 3>, 3> getGrid();

	// -- Vars --
	int *times;

private:

	// -- Member Vars --
	std::array<std::array<char, 3>, 3> *_grid;

};

#endif
