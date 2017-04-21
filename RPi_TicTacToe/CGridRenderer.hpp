#ifndef CGRIDRENDERER_HPP
#define CGRIDRENDERER_HPP

// Includes
#include<iostream>
#include<array>
#include"CLEDMatrix.hpp"
#include"CStaticTools.hpp"
#include"CGrid.hpp"
#include"CGlobalData.hpp"

// CGridRenderer
class CGridRenderer {
public:

	// -- Kon/Destruktor --
	CGridRenderer();
	~CGridRenderer();

	// -- Methoden --
	void renderGrid(std::array<std::array<char, 3>, 3 > grid);
	bool setSelected(int x, int y);

private:

	// -- Member Vars --
	CLEDMatrix *_ledMatrix;

	uint8_t _color_pl1[3] = { 0, 0, 255 };
	uint8_t _color_pl2[3] = { 255, 0, 0 };
	uint8_t _color_none[3] = { 64, 64, 64 };
	uint8_t _color_border[3] = { 180, 180, 180 };
	
	struct _selected {
		int  *x;
		int  *y;
		bool *display;
	} *_curSelected;

	ST::CTimeMgr *_timeMgr;
	sf::Time *_elapsedTime;

};

#endif