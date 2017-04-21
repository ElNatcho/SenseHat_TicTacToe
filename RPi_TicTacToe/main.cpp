#include"CProgram.hpp"

int main(int argc, char **argv) {
	if (argc != 3) {
		std::cout << "RPi_TicTacToe <FB_PATH> <EV_PATH>" << std::endl;
		return 0;
	}

	GD::fb = argv[1];
	GD::ev = argv[2];

	GD::Joystick->initEv(GD::ev);

	CProgram *program = new CProgram();

	try {
		while (program->isRunning()) {
			program->run();
		}
	} catch (std::string &str) {
		std::cout << str << std::endl;
	}

	return 0;
}
