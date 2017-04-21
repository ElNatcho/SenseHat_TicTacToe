#include"CGrid.hpp"

int main() {
	CGrid *grid = new CGrid();
	
	char pl_input;
	char curPl = PL_1;
	int posX, posY;

	try{	
		while(true) {
			std::cout << std::endl;
			grid->showGrid();
			std::cout << "Feld <s>etzen oder <n>eues Spiel: ";
			std::cin >> pl_input;
			if(pl_input == 's' || pl_input == 'S'){
				std::cout << "X: ";
				std::cin >> posX;
				std::cout << "Y: ";
				std::cin >> posY;
				try{
					if(!grid->setBox(posX, posY, curPl))
						continue;
				}catch(const char* e){
					continue;
				}
				curPl = curPl == PL_1 ? PL_2 : PL_1;
			}else if(pl_input == 'n' || pl_input == 'N') {
				grid->reset();
				continue;
				system("clear");
			}else{
				continue;
			}

		}

	}catch(const char* e){
		std::cout << e << std::endl;
	}

	return 0;
}
