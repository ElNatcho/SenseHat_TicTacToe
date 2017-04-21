#ifndef CPLAYSTATE_HPP
#define CPLAYSTATE_HPP

// Includes
#include"CProgram.hpp"
#include"CRealPlayer.hpp"
#include"CEasyBot.hpp"
#include"CMiddleBot.hpp"
#include"CHardBot.hpp"

// CPlayState
class CPlayState : public CProgState {
public:

	// -- Kon/Destruktor --
	CPlayState();
	~CPlayState();

	// -- Methoden --
	void run(CProgram &prog); // Methode führt die Logik des CPlayStates aus
	void flipPlayer(CProgram &prog); // Tauscht die aktuellen Spieler

private:

	// -- Member Vars --
	IPlayer *_curPlayer;
	IPlayer *_player_1;
	IPlayer *_player_2;

	CAnalyse *_analyse;

};

#endif