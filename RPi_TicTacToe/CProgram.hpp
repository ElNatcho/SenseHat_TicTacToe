#ifndef CPROGRAM_HPP
#define CPROGRAM_HPP

// Includes
#include<iostream>
#include<thread>
#include<chrono>
#include<memory>
#include"CProgState.hpp"
#include"CGlobalData.hpp"
#include"CStaticTools.hpp"
#include"CGridRenderer.hpp"
#include"CAnalyse.hpp"
#include"CPlayState.hpp"
#include"CEndState.hpp"

// CProgram
class CProgram {
public:

	enum PROG_STATE {
		PLAY = 0,
		END = 1
	};

	struct selectedBox {
		int x;
		int y;
	} *curSelectedBox;

	// -- Kon/Destruktor --
	CProgram();
	~CProgram();

	// -- Methoden --
	void run(); // Führt die CORE_Logik des Programms aus
	bool isRunning(); // Gibt den aktuellen Programmstatus zurück

	void changeState(PROG_STATE newState); // Updated den aktuellen ProgramState

	void flipPlayer(); // Tauscht die aktuellen Spieler

	void reset(); // Setzt die Werte für das Spiel zurück

	// -- Vars --
	bool *running; // Aktueller Programmstatus
	CGrid *grid; // Aktuelles Spielfeld
	CGridRenderer *gRenderer; // Aktueller Spielfeldrenderer
	char *winner; // Spieler der die letzte Runde gewonnen hat
	bool *gameOver;

private:

	// -- Member Vars --
	std::unique_ptr<CProgState> _currentState;

};

#endif