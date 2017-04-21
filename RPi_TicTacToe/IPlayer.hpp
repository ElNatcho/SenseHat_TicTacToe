#ifndef IPLAYER_HPP
#define IPLAYER_HPP

// Includes
#include<iostream>

class CProgram;

// IPlayer
class IPlayer {
public:

	virtual void play(CProgram &prog) = 0;
	virtual void setSym(char c) { *_symbol = c; };
	virtual char getSym() { return *_symbol; };
	virtual void reset() { };
	virtual    ~ IPlayer() {};

protected:

	char *_symbol;

};

#endif