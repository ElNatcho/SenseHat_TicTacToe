#ifndef CGLOBALDATA_HPP
#define CGLOBALDATA_HPP

// Includes
#include<string>
#include"CJoystick.hpp"

namespace GD {
	extern std::string fb;
	extern std::string ev;
	extern CJoystick *Joystick;
}

#endif