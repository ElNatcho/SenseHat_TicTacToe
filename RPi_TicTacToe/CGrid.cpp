#include"CGrid.hpp"

// -- Konstruktor --
CGrid::CGrid() {
	// Free Memory
	_grid = new std::array<std::array<char, 3>, 3>();
	times = new int;

	// Spielfeld zurücksetzen
	reset();
	*times = 0;
}

// -- reset --
// Setzt das Spielfeld zurück
//
void CGrid::reset(){
	for(int i = 0; i < _grid->size(); i++){
		for(int j = 0; j < _grid->at(i).size(); j++){
			_grid->at(i).at(j) = NONE;
		}
	}
}

// -- setBox --
// Methode setzt ein Feld 
// @param x,y: Feld, dass gesetzt werden soll
// @param player: Zeichen, dass  gesetzt werden soll
// 
bool CGrid::setBox(int x, int y, char player) {
	if(x >= 3 || y >= 3){
		throw "EXCEPTION: Grid_out_of_Range";
		return false;
	}
	
	if(_grid->at(y).at(x) == NONE){
		_grid->at(y).at(x) = player;
		return true;
	}else{
		return false;
	}
}	

// -- showGrid --
// Methode zeigt das aktuelle Feld an
//
void CGrid::showGrid() {
	for(int i = 0; i < _grid->size(); i++){
		for(int j = 0; j < _grid->at(i).size(); j++){
			std::cout << _grid->at(i).at(j);
			if(j <= 1)
				std::cout << "|";
		}
		std::cout << std::endl;
		if(i <= 1)
			std::cout << "-+-+-" << std::endl;
	}
}

// -- getGrid --
// Methode gib das aktuelle Spielfeld zurück
//
std::array<std::array<char, 3>, 3> CGrid::getGrid() {
	return *_grid;
}

// -- Destruktor --
CGrid::~CGrid() {
	// Free Memory
	SAFE_DELETE(_grid);
	SAFE_DELETE(times);
}





















