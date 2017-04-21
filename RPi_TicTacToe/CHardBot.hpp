#ifndef CHARDBOT_HPP
#define CHARDBOT_HPP

// Includes
#include"IPlayer.hpp"
#include"CMiddleBot.hpp"

// CHardestBot
class CHardBot : public CMiddleBot {
public:

	// -- Kon/Destruktor --
	CHardBot();
	~CHardBot();

	// -- Methoden --
	void play(CProgram &prog); // Methode mit der der Bot auf das Spielfeld zugreift

private:

	// -- Member Methods --
	void _getCritBoxes(t_grid grid);
	char _getEnemy();

	bool _checkForSym(std::array<char, 3> arr, char c);

	void _resetPrio();

	int _getAddValue(t_grid grid, int x, int y);

	std::array<std::array<int, 3>, 3> *_prioVals;


};

#endif