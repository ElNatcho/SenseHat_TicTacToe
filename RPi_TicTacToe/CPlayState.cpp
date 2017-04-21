#include"CPlayState.hpp"

// -- Konstruktor --
CPlayState::CPlayState() {
	// Alloc Memory
	_player_1 = new CRealPlayer();
	_player_2 = new CHardBot();
	_analyse = new CAnalyse();

	// Werte setzen
	_player_1->reset();
	_player_1->setSym(PL_1);
	_player_2->reset();
	_player_2->setSym(PL_2);
	_curPlayer = _player_1;

}

// -- run --
// Methode führt die Logik des CPlayStates aus
//
void CPlayState::run(CProgram &prog) {
	prog.gRenderer->renderGrid(prog.grid->getGrid());
	try {
		_curPlayer->play(prog);
	} catch (std::string str) {
		std::cout << str << std::endl;
	}
}

// -- flipPlayer --
// Tauscht die aktuellen Spieler
//
void CPlayState::flipPlayer(CProgram &prog) {
	*prog.grid->times += 1;
	_curPlayer = _curPlayer->getSym() == _player_1->getSym() ? _player_2 : _player_1;
	if (_analyse->checkGrid(prog.grid->getGrid()) != NONE || *prog.grid->times >= 9) {
		*prog.grid->times = 0;
		*prog.gameOver = true;
		*prog.winner = _analyse->checkGrid(prog.grid->getGrid());
		std::cout << "Spieler " << *prog.winner << "hat gewonnen." << std::endl;
	}
}

// -- Destruktor --
CPlayState::~CPlayState() {
	// Free Memory
	SAFE_DELETE(_analyse)
	SAFE_DELETE(_player_1);
	SAFE_DELETE(_player_2);
}