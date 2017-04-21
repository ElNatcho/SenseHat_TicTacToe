#ifndef CSTATICTOOLS_HPP
#define CSTATICTOOLS_HPP

// Includes
#include<iostream>
#include<SFML/Graphics.hpp>

#define SAFE_DELETE(X) {if(X!=nullptr){delete(X); X=nullptr;}}

namespace ST {

	// CTimeMgr
	class CTimeMgr {
	public:
		
		// -- Konstruktor --
		CTimeMgr() {
			// Alloc Memory
			_clock = new sf::Clock();
		}

		// -- Destruktor --
		~CTimeMgr() {
			// Free Memory
			SAFE_DELETE(_clock);
		}

		// Methode mit der man die Zeitänderung seit der letzten abfragen abrufen kann
		void addElapsedTime(sf::Time *tempClock) {
			*tempClock += _clock->restart();
		}

	private:

		// -- Member Vars --
		sf::Clock *_clock;
	};

}

#endif
