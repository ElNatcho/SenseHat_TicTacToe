#ifndef CMIDDLEPLAYER_HPP
#define CMIDDLEPLAYER_HPP

// Includes
#include<vector>
#include"IPlayer.hpp"
#include"CAnalyse.hpp"

// CMiddlePlayer
class CMiddleBot : public IPlayer, public CAnalyse {
public:

	// -- Kon/Destruktor --
	CMiddleBot();
	~CMiddleBot();

	// -- Methoden --
	virtual void play(CProgram &prog); // Methode mit der der Bot auf das Spielfeld zugreift

protected:

	// -- "Member" Vars --
	struct Box {
		int x;
		int y;
	} _box;

	std::vector<Box> *_boxes;

	// -- "Member" Methods --
	void getBoxes(t_grid grid, char c);
	void getPosBoxes(t_grid grid);
	void insertBox(int x, int y); // Fügt eine box in den _boxes-Vektor ein

private:

};

#endif