#include"CHardBot.hpp"
#include"CProgram.hpp"

// -- Konstruktor --
CHardBot::CHardBot() {
	// Alloc Memory
    _symbol = new char;
	_prioVals = new std::array<std::array<int, 3>, 3>();
}

// -- play --
// Methode mit der der Bot auf das Spielfeld zugreift
// @param prog: Aktuell laufendes Program
//
void CHardBot::play(CProgram &prog) {
	_boxes->clear();
	getBoxes(prog.grid->getGrid(), *_symbol);
	getBoxes(prog.grid->getGrid(), _getEnemy());
	_getCritBoxes(prog.grid->getGrid());
	getPosBoxes(prog.grid->getGrid());
	for (int i = 0; i < _boxes->size(); i++) {
		if (prog.grid->setBox(_boxes->at(i).x, _boxes->at(i).y, *_symbol)) {
			prog.flipPlayer();
			break;
		}
	}
}

// -- getCritBoxes --
//
void CHardBot::_getCritBoxes(t_grid grid) {
	_resetPrio();

	// Prios in den Horizontalen prüfen
	for (int i = 0; i < 3; i++) {
		if (!_checkForSym(grid.at(i), *_symbol)) {
			for (int j = 0; j < 3; j++) {
				if (grid.at(i).at(j) == NONE) {
					_prioVals->at(i).at(j) += _getAddValue(grid, j, i);
				}
			}
		}
	}
	
	// Prios in den Vertikalen prüfen
	for (int i = 0; i < 3; i++) {
		if (!_checkForSym(getGridVer(grid, i), *_symbol)) {
			for (int j = 0; j < 3; j++) {
				if (getGridVer(grid, i).at(j) == NONE) {
					_prioVals->at(j).at(i) += _getAddValue(grid, i, j);
				}
			}
		}
	}

	// Prios in den Diagonalen prüfen

	// LU-RD Diagonale
	if (!_checkForSym(getDiaLU(grid), *_symbol)) {
		for (int i = 0; i < 3; i++) {
			if (getDiaLU(grid).at(i) == NONE) {
				_prioVals->at(i).at(i) += _getAddValue(grid, i, i);
			}
		}
	}

	// LD-RU Diagonale
	if (!_checkForSym(getDiaRU(grid), *_symbol)) {
		if (getDiaRU(grid).at(0) == NONE)
			_prioVals->at(0).at(2) += _getAddValue(grid, 2, 0);
		if (getDiaRU(grid).at(1) == NONE)
			_prioVals->at(1).at(1) += _getAddValue(grid, 1, 1);
		if (getDiaRU(grid).at(2) == NONE)
			_prioVals->at(2).at(0) += _getAddValue(grid, 0, 2);
	}

	int tempMax = 0;
	for (int i = 0; i < _prioVals->size(); i++) {
		for (int j = 0; j < _prioVals->at(i).size(); j++) {
			std::cout << _prioVals->at(i).at(j) << " ";
			tempMax = tempMax < _prioVals->at(i).at(j) ? _prioVals->at(i).at(j) : tempMax;
		}
		std::cout << std::endl;
	}

	for (int i = 0; i < _prioVals->size(); i++) {
		for (int j = 0; j < _prioVals->at(i).size(); j++) {
			if (tempMax == _prioVals->at(i).at(j)) {
				insertBox(j, i);
				break;
			}
		}
	}
}

// -- _getEnemy --
// Methode gib das Zeichen des Gegners zurück
//
char CHardBot::_getEnemy() {
	return *_symbol == PL_1 ? PL_2 : PL_1;
}

// -- _checkForSym --
//
bool CHardBot::_checkForSym(std::array<char, 3> arr, char c) {
	for (int i = 0; i < arr.size(); i++) {
		if (arr.at(i) == c) {
			return true;
		}
	}
	return false;
}

// -- _resetPrio --
//
void CHardBot::_resetPrio() {
	for (int i = 0; i < _prioVals->size(); i++) {
		for (int j = 0; j < _prioVals->at(i).size(); j++) {
			_prioVals->at(i).at(j) = 0;
		}
	}
}

// -- _getAddValue--
//
int CHardBot::_getAddValue(t_grid grid, int _x, int _y) {
	int val = 1;
	int i = 0;
	for (int y = (_y - 1); y < (_y + 2); y++) {
		for (int x = (_x - 1); x < (_x + 2); x++) {
			if (x >= 0 && x <= 2 &&
				y >= 0 && y <= 2) {
				if (grid.at(y).at(x) == _getEnemy()) {
					val++;
				}
			}
		}
	}
	
	if (!_checkForSym(grid.at(_y), _getEnemy()) &&
		 _checkForSym(grid.at(_y), *_symbol)) {
		val += 2;
	}

	if (!_checkForSym(getGridVer(grid, _x), _getEnemy()) &&
		_checkForSym(getGridVer(grid, _x), *_symbol)) {
		val += 2;
	}

	return val;
}

// -- Destruktor --
CHardBot::~CHardBot() {
	// Free Memory
	SAFE_DELETE(_symbol);
	SAFE_DELETE(_prioVals);
}
