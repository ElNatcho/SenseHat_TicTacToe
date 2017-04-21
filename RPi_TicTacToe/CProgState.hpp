#ifndef CPROGSTATE_HPP
#define CPROGSTATE_HPP

class CProgram;

class CProgState {
public:
	virtual void run(CProgram &prog) = 0;
	virtual void flipPlayer(CProgram &prog) {};
	virtual    ~ CProgState() {};
};

#endif