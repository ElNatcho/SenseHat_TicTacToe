#ifndef CENDSTATE_HPP
#define CENDSTATE_HPP

// Includes 
#include"CProgram.hpp"

// CEndState
class CEndState : public CProgState {
public:

	// -- Kon/Destruktor --
	CEndState();
	~CEndState();

	// -- Methoden --
	void run(CProgram &prog); // Methode führt die Logik des CPlayStates aus

private:

	// -- Member Vars --
	CJoystick *_joystick;
	CLEDMatrix *_ledMatrix;

	// -- Member Methods --
	void _setupLEDMatrix();
	void _displayPlayer(char c);

};

#endif