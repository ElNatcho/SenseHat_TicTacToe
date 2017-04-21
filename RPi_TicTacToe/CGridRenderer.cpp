#include"CGridRenderer.hpp"

// -- Konstruktor --
CGridRenderer::CGridRenderer() {
	// Alloc Memory
	_timeMgr = new ST::CTimeMgr();
	_ledMatrix = new CLEDMatrix(GD::fb);
	_curSelected = new _selected{};
	_elapsedTime = new sf::Time();
	_curSelected->x = new int;
	_curSelected->y = new int;
	_curSelected->display = new bool;

	// Werte setzen
	*_curSelected->x = -1;
	*_curSelected->y = -1;
	*_curSelected->display = true;
}

// -- renderGrid --
// Methode die das TicTacToe-Spielfeld in der LED-Matrix rendert
// @param grid: Spielfeld, dass gezeichnet werden soll
//
void CGridRenderer::renderGrid(std::array<std::array<char, 3>, 3> grid) {
	_timeMgr->addElapsedTime(_elapsedTime);
	if (_elapsedTime->asSeconds() >= 0.5F) {
		*_curSelected->display = *_curSelected->display ? false : true;
		*_elapsedTime = _elapsedTime->Zero;
	}
	_ledMatrix->clearMatrix();
	for (int i = 0; i < grid.size(); i++) {
		for (int j = 0; j < grid.at(i).size(); j++) {
			if ((*_curSelected->x == j && *_curSelected->y == i && *_curSelected->display) || 
				(*_curSelected->x != j || *_curSelected->y != i)) {
				if (grid.at(i).at(j) == PL_1)
					_ledMatrix->displayRect(j * 3, i * 3, 2, 2, _color_pl1);
				else if (grid.at(i).at(j) == PL_2)
					_ledMatrix->displayRect(j * 3, i * 3, 2, 2, _color_pl2);
				else if (grid.at(i).at(j) == NONE)
					_ledMatrix->displayRect(j * 3, i * 3, 2, 2, _color_none);
			}
		}
	}
	_ledMatrix->displayRect(2, 0, 1, 8, _color_border);
	_ledMatrix->displayRect(5, 0, 1, 8, _color_border);
	_ledMatrix->displayRect(0, 2, 8, 1, _color_border);
	_ledMatrix->displayRect(0, 5, 8, 1, _color_border);
}

// -- setSelected --
// Methode die das selectierte Feld auswählt
// @param x, y: Feld, dass ausgewählt werden soll
//
bool CGridRenderer::setSelected(int x, int y) {
	if (x >= 0 && x <= 2 && y >= 0 && y <= 2) {
		*_curSelected->x = x;
		*_curSelected->y = y;
		*_curSelected->display = true;
		*_elapsedTime = _elapsedTime->Zero;
		return true;
	} else {
		return false;
	}
}

// -- Destruktor --
CGridRenderer::~CGridRenderer() {
	// Free Memory
	SAFE_DELETE(_timeMgr);
	SAFE_DELETE(_ledMatrix);
	SAFE_DELETE(_curSelected);
	SAFE_DELETE(_elapsedTime);
}