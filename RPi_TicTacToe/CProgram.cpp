#include"CProgram.hpp"

// -- Konstruktor --
CProgram::CProgram() {
	// Alloc Memory
	grid = new CGrid();
	winner = new char;
	running = new bool;
	gameOver = new bool;
	gRenderer = new CGridRenderer();
	curSelectedBox = new selectedBox;

	// Werte setzen
	reset();
	changeState(PROG_STATE::PLAY);
}

// -- run --
// Führt die CORE_Logik des Programms aus
//
void CProgram::run() {
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	if(!(*gameOver))
		_currentState->run(*this);
	else {
		gRenderer->setSelected(curSelectedBox->x, curSelectedBox->y);
		gRenderer->renderGrid(grid->getGrid());
		std::this_thread::sleep_for(std::chrono::seconds(2));
		changeState(PROG_STATE::END);
		*gameOver = false;
	}
}

// -- isRunning --
// Gibt den aktuellen Programmstatus zurück
//
bool CProgram::isRunning() {
	return *running;
}

// -- changeState --
// Updated den aktuellen ProgramState
// @param newState: Neuer ProgramState
//
void CProgram::changeState(CProgram::PROG_STATE newState) {
	switch (newState) {
	case CProgram::PROG_STATE::PLAY:
		*gameOver = false;
		_currentState = std::move(std::unique_ptr<CPlayState>(new CPlayState));
		break;
		
	case CProgram::PROG_STATE::END:
		_currentState = std::move(std::unique_ptr<CEndState>(new CEndState));
		break;

	default:
		break;
	}
}

// -- flipPlayer --
// Tauscht die aktuellen Spieler
//
void CProgram::flipPlayer() {
	_currentState->flipPlayer(*this);
}

// -- reset --
// Setzt die Werte für das Spiel zurück
//
void CProgram::reset() {
	curSelectedBox->x = 0;
	curSelectedBox->y = 0;
	grid->reset();
	*running = true;
	*gameOver = false;
	gRenderer->setSelected(0, 0);
}

// -- Destruktor --
CProgram::~CProgram() {
	// Free Memory
	SAFE_DELETE(grid);
	SAFE_DELETE(winner);
	SAFE_DELETE(running);
	SAFE_DELETE(gameOver);
	SAFE_DELETE(gRenderer);
	SAFE_DELETE(curSelectedBox);
}