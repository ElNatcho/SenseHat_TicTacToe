#include"CMiddleBot.hpp"
#include"CProgram.hpp"

// -- Konstruktor --
CMiddleBot::CMiddleBot() {
	// Alloc Memory
	_symbol = new char;
	_boxes = new std::vector<Box>();
}

// -- play --
// Methode mit der der Bot auf das Spielfeld zugreift
// @param prog: Aktuell laufendes Programm
//
void CMiddleBot::play(CProgram &prog) {
	_boxes->clear();
	getBoxes(prog.grid->getGrid(), *_symbol);
	getBoxes(prog.grid->getGrid(), (*_symbol == PL_1 ? PL_2 : PL_1));
	if (_boxes->size() > 0) {
		if (!prog.grid->setBox(_boxes->at(0).x, _boxes->at(0).y, *_symbol))
			throw "EXCEPTION: BAD_getBoxes_RESULT";
		else
			prog.flipPlayer();
	} else {
		getPosBoxes(prog.grid->getGrid());
		int rPos = rand() % _boxes->size();
		if (!prog.grid->setBox(_boxes->at(rPos).x, _boxes->at(rPos).y, *_symbol))
			throw "EXCEPTION: BAD_getPosBoxes_RESULT";
		else
			prog.flipPlayer();
	}
}

// -- getWinningBoxes --
//
void CMiddleBot::getBoxes(t_grid grid, char c) {
	// Horizontale Ebenen prüfen
	for (int i = 0; i < 3; i++) {
		if		(compare(grid.at(i), getArray(c, c, NONE))) insertBox(2, i);
		else if (compare(grid.at(i), getArray(c, NONE, c))) insertBox(1, i);
		else if (compare(grid.at(i), getArray(NONE, c, c))) insertBox(0, i);
	}

	// Vertikale Ebenen prüfen
	for (int i = 0; i < 3; i++) {
		if      (compare(getGridVer(grid, i), getArray(c, c, NONE))) insertBox(i, 2);
		else if (compare(getGridVer(grid, i), getArray(c, NONE, c))) insertBox(i, 1);
		else if (compare(getGridVer(grid, i), getArray(NONE, c, c))) insertBox(i, 0);
	}

	// Diagonalen prüfen
	// LU-RD Diagonale
	if		(compare(getDiaLU(grid), getArray(c, c, NONE))) insertBox(2, 2);
	else if (compare(getDiaLU(grid), getArray(c, NONE, c))) insertBox(1, 1);
	else if (compare(getDiaLU(grid), getArray(NONE, c, c))) insertBox(0, 0);

	// RU-LD Diagonale
	if (compare(getDiaRU(grid), getArray(c, c, NONE))) insertBox(0, 2);
	if (compare(getDiaRU(grid), getArray(c, NONE, c))) insertBox(1, 1);
	if (compare(getDiaRU(grid), getArray(NONE, c, c))) insertBox(2, 0);
}

// -- getPosBoxes --
//
void CMiddleBot::getPosBoxes(t_grid grid) {
	for (int y = 0; y < grid.size(); y++) {
		for (int x = 0; x < grid.at(y).size(); x++) {
			if (grid.at(y).at(x) == NONE) {
				insertBox(x, y);
			}
		}
	}
}

// -- insertBox --
// Fügt eine box in den _boxes-Vektor ein
// @param x, y: Position der Box
//
void CMiddleBot::insertBox(int x, int y) {
	_box.x = x;
	_box.y = y;
	_boxes->push_back(_box);
}

// -- Destruktor --
CMiddleBot::~CMiddleBot() {
	// Free Memory
	SAFE_DELETE(_symbol);
	SAFE_DELETE(_boxes);
}