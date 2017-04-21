#include"CEasyBot.hpp"
#include"CProgram.hpp"

// -- Konstruktor --
CEasyBot::CEasyBot() {
	// Alloc Memory
	_symbol = new char;
}

// -- play --
// Methode mit der der Bot auf das Spielfeld zugreift
// @param prog: Aktuell laufendes Programm
//
void CEasyBot::play(CProgram &prog) {
	while (!prog.grid->setBox(
		rand() % 3,
		rand() % 3,
		*_symbol));
	prog.flipPlayer();
}


// -- Destruktor --
CEasyBot::~CEasyBot() {
	SAFE_DELETE(_symbol);
}