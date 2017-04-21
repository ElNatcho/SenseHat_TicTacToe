#ifndef CJOYSTICK_HPP
#define CJOYSTICK_HPP

// Includes
#include<iostream>
#include<linux/input.h>
#include<string>
#include<fcntl.h>
#include<unistd.h>
#include<thread>
#include<mutex>
#include<atomic>
#include"CStaticTools.hpp"

// CJoystick
class CJoystick {
public:

	// -- Kon/Destruktor --
	CJoystick();
	CJoystick(std::string ev_path);
	~CJoystick();

	// -- Methoden --

	// Methode mit der man das event-Objekt öffnen kann
	void initEv(std::string ev_path);

	// Methode die _curEvent zurücksetzt
	void reset();

	// Methode die das aktuelle Event des Joysticks zurückgibt
	int getCurEvent();

private:

	// -- Member Vars --
	int _fb_fd, _rd;
	struct input_event _ev[64];

	std::thread *read_thread;
	std::mutex _mutex;
	std::atomic<int> _curEvent;

	// -- Member Methods --
	void _readEv();

};

#endif