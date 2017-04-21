#include"CJoystick.hpp"

// -- Konstruktor --
CJoystick::CJoystick() {
	// Alloc Memory
	
	// Werte setzen
	_curEvent = -1;
}

// -- Konstruktor --
CJoystick::CJoystick(std::string ev_path) {
	initEv(ev_path);
}

// -- initEv --
// Methode mit der man das event-Objekt öffnen kann
// @param ev_path: Pfad zum/Name des event-Objekts
//
void CJoystick::initEv(std::string ev_path) {
	_fb_fd = -1;
	_fb_fd = open(ev_path.c_str(), O_RDWR);
	if (_fb_fd < 0)
		throw ("EXCEPTION: Event-Objekt kann nicht geöffnet werden: " + ev_path);
	else
		read_thread = new std::thread(&CJoystick::_readEv, this);
}

// -- getCurEvent --
// Methode die das aktuelle Event des Joysticks zurückgibt
//
int CJoystick::getCurEvent() {
	std::lock_guard<std::mutex> lock(_mutex);
	return _curEvent;
}

// -- reset --
// Methode die _curEvent zurücksetzt
//
void CJoystick::reset() {
	_curEvent = -1;
}

// -- readEv --
// Methode die das aktuelle Event des Joysticks ausliest
//
void CJoystick::_readEv() {
	while (true) {
		_rd = read(_fb_fd, _ev, sizeof(struct input_event) * 64);

		if (_rd < (int)sizeof(struct input_event)) {
			std::cout << "ERROR: Aus dem Event-Objekt kann nicht gelesen werden!" << std::endl;
			_mutex.lock();
			_curEvent = -1;
			_mutex.unlock();
		}

		for (int i = 0; i < _rd / sizeof(struct input_event) * 64; i++) {
			if (_ev->type != EV_KEY)
				continue;
			if (_ev->value != 1)
				continue;
			_mutex.lock();
			_curEvent = _ev->code;
			_mutex.unlock();
		}
	}
}

// -- Destruktor --
CJoystick::~CJoystick() {
	read_thread->detach();
	// Free Memory
	//SAFE_DELETE(_curEvent);
}