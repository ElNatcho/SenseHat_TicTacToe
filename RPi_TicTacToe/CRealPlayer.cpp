#include"CRealPlayer.hpp"
#include"CProgram.hpp"

// -- Konstruktor --
CRealPlayer::CRealPlayer() {
	// Alloc Memory
	_symbol = new char;
	_timeMgr = new ST::CTimeMgr();
	_joystick = GD::Joystick;
	_elapsedTime = new sf::Time();

	// Werte setzen
	reset();
}

// -- play --
// Methode mit der der reale Spieler mit dem Spielfeld interagieren kann
// @param prog: Aktuell laufendes Programm
//
void CRealPlayer::play(CProgram &prog) {
	_timeMgr->addElapsedTime(_elapsedTime);
	if (_elapsedTime->asSeconds() >= 1.F) {
		switch (_joystick->getCurEvent()) {
		case KEY_ENTER:
			if (prog.grid->setBox(prog.curSelectedBox->x, prog.curSelectedBox->y, *_symbol)) {
				prog.flipPlayer();
				prog.grid->showGrid();
				_reset();
			}
			break;

		case KEY_UP:
			if (prog.gRenderer->setSelected(prog.curSelectedBox->x, prog.curSelectedBox->y - 1)) {
				prog.curSelectedBox->y = prog.curSelectedBox->y - 1;
				_reset();
			}
			break;

		case KEY_DOWN:
			if (prog.gRenderer->setSelected(prog.curSelectedBox->x, prog.curSelectedBox->y + 1)) {
				prog.curSelectedBox->y = prog.curSelectedBox->y + 1;
				_reset();
			}
			break;

		case KEY_RIGHT:
			if (prog.gRenderer->setSelected(prog.curSelectedBox->x + 1, prog.curSelectedBox->y)) {
				prog.curSelectedBox->x = prog.curSelectedBox->x + 1;
				_reset();
			}
			break;

		case KEY_LEFT:
			if (prog.gRenderer->setSelected(prog.curSelectedBox->x - 1, prog.curSelectedBox->y)) {
				prog.curSelectedBox->x = prog.curSelectedBox->x - 1;
				_reset();
			}
			break;

		default:
			break;
		}
	}
}

void CRealPlayer::_reset() {
	_joystick->reset();
	*_elapsedTime = _elapsedTime->Zero;
}

// -- Destruktor --
CRealPlayer::~CRealPlayer() {
	// Free Memory
	SAFE_DELETE(_symbol);
	SAFE_DELETE(_timeMgr);
	SAFE_DELETE(_elapsedTime);
}