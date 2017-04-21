#ifndef CREALPLAYER_HPP
#define CREALPLAYER_HPP

// Includes
#include"IPlayer.hpp"
#include"CJoystick.hpp"

// CRealPlayer
class CRealPlayer : public IPlayer {
public:

	// -- Kon/Destruktor --
	CRealPlayer();
	~CRealPlayer();

	// -- Methoden --
	void play(CProgram &program); // Methode mit der der reale Spieler mit dem Spielfeld interagieren kann
	
private:

	// -- Member Vars --
	CJoystick *_joystick;
	ST::CTimeMgr *_timeMgr;
	sf::Time *_elapsedTime;

	// -- Member Methods --
	void _reset(); // Setzt den Timer / _curEvent zurück und updatet _curSelectedBox

};

#endif