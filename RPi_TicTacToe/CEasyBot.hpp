#ifndef CEASYBOT_HPP
#define CEASYBOT_HPP

// Includes
#include"IPlayer.hpp"

// CEasyBot
class CEasyBot : public IPlayer {
public:

	// -- Kon/Destruktor --
	CEasyBot();
	~CEasyBot();

	// -- Methoden --
	void play(CProgram &prog); // Methode mit der der Bot auf das Spielfeld zugreift

private:
	
	// -- Member Vars --

};

#endif