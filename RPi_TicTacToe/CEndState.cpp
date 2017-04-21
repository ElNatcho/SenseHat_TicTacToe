#include"CEndState.hpp"

// -- Konstruktor --
CEndState::CEndState() {
	// Alloc Memory
	_joystick = GD::Joystick;
	_ledMatrix = new CLEDMatrix();

	// Werte setzen
	_ledMatrix->initFB(GD::fb);
	_joystick->initEv(GD::ev);
	_setupLEDMatrix();
}

// -- run --
// Methode führt die Logik des CPlayStates aus
// @param prog: Aktuell laufendes Program
//
void CEndState::run(CProgram &prog) {
	_displayPlayer(*prog.winner);
	if (_joystick->getCurEvent() == KEY_ENTER) {
		_joystick->reset();
		prog.reset();
		prog.changeState(CProgram::PROG_STATE::PLAY);
	}
}

// -- _setupLEDMatrix --
// Methode zeichnet die Krone
//
void CEndState::_setupLEDMatrix() {
	_ledMatrix->displayRect(0, 0, 8, 8, _ledMatrix->getColor(255, 255, 0));
	_ledMatrix->displayRect(1, 0, 6, 7, _ledMatrix->getColor(0, 0, 0));
	_ledMatrix->setPixel(1, 1, _ledMatrix->getColor(255, 255, 0));
	_ledMatrix->setPixel(2, 0, _ledMatrix->getColor(255, 255, 0));
	_ledMatrix->setPixel(3, 1, _ledMatrix->getColor(255, 255, 0));
	_ledMatrix->setPixel(4, 1, _ledMatrix->getColor(255, 255, 0));
	_ledMatrix->setPixel(5, 0, _ledMatrix->getColor(255, 255, 0));
	_ledMatrix->setPixel(6, 1, _ledMatrix->getColor(255, 255, 0));

}

// -- _displayPlayer --
// Methode stellt die Zahl eines Spielers da
// @param c: Spieler der Dargestellt werden soll
//
void CEndState::_displayPlayer(char c) {
	if (c == PL_1) {
		_ledMatrix->setPixel(3, 5, _ledMatrix->getColor(0, 0, 255));
		_ledMatrix->setPixel(4, 5, _ledMatrix->getColor(0, 0, 255));
		_ledMatrix->setPixel(5, 5, _ledMatrix->getColor(0, 0, 255));
		_ledMatrix->setPixel(4, 4, _ledMatrix->getColor(0, 0, 255));
		_ledMatrix->setPixel(4, 3, _ledMatrix->getColor(0, 0, 255));
		_ledMatrix->setPixel(3, 3, _ledMatrix->getColor(0, 0, 255));
	} else if (c == PL_2) {
		_ledMatrix->setPixel(5, 3, _ledMatrix->getColor(255, 0, 0));
		_ledMatrix->setPixel(5, 4, _ledMatrix->getColor(255, 0, 0));
		_ledMatrix->setPixel(5, 5, _ledMatrix->getColor(255, 0, 0));
		_ledMatrix->setPixel(3, 3, _ledMatrix->getColor(255, 0, 0));
		_ledMatrix->setPixel(3, 4, _ledMatrix->getColor(255, 0, 0));
		_ledMatrix->setPixel(3, 5, _ledMatrix->getColor(255, 0, 0));
	} else {
		_ledMatrix->setPixel(2, 4, _ledMatrix->getColor(128, 128, 128));
		_ledMatrix->setPixel(3, 4, _ledMatrix->getColor(128, 128, 128));
		_ledMatrix->setPixel(4, 4, _ledMatrix->getColor(128, 128, 128));
		_ledMatrix->setPixel(5, 4, _ledMatrix->getColor(128, 128, 128));
	}
}

// -- Destruktor --
CEndState::~CEndState() {
	// Free Memory
	SAFE_DELETE(_ledMatrix);
}