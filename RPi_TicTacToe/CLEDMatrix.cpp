#include"CLEDMatrix.hpp"

// -- Konstruktor --
CLEDMatrix::CLEDMatrix() {
	// Alloc Memory
	_img = new sf::Image();
}

// -- Konstruktor --
// @param fb_path: Pfad zum/Name des Framebuffers der geladen werden soll
//
CLEDMatrix::CLEDMatrix(std::string fb_path) : CLEDMatrix() {
	initFB(fb_path);
}

// -- loadFB --
// Lädt und initialisiert den Framebuffer des Sense Hats
// @param fb_path: Pfad zum/Name des Framebuffers der geladen werden soll
//
void CLEDMatrix::initFB(std::string fb_path) {
	_loadFB(fb_path); // FB öffnen
	ioctl(_fb_fd, FBIOGET_VSCREENINFO, &_vinfo); // Screeninfos laden 
	ioctl(_fb_fd, FBIOGET_FSCREENINFO, &_finfo); // --------"--------
	_fbp = (struct fb_t*)mmap(0, (_vinfo.yres_virtual * _finfo.line_length),
					  PROT_READ | PROT_WRITE, MAP_SHARED, _fb_fd, (off_t)0);
}

// -- getColor --
// Methode die eine 24-bit Farbe (RGB ohne Alpha) zu einer
// 16-bit Farbe "konvertiert"
// @param r, g, b: RGB Wert der Farbe
//
uint16_t CLEDMatrix::getColor(uint8_t r, uint8_t g, uint8_t b) {
	r &= 0xF8;
	g &= 0xFC;
	b &= 0xF8;
	return (r << 8) | (g << 3) | (b >> 3);
}

// -- clearMatrix --
// Methode die alle Pixel der LED-Matrix in einer bestimmten Farbe aufleuchten lässt
// @param r, g, b: RGB Wert der Farbe
//
void CLEDMatrix::clearMatrix(uint8_t r, uint8_t g, uint8_t b) {
	clearMatrix(getColor(r, g, b));
}

// -- clearMatrix --
// Methode die alle Pixel der LED-Matrix in einer bestimmten Farbe aufleuchten lässt
// @param color[]: Array das die Farben beinhaltet
//
void CLEDMatrix::clearMatrix(uint8_t color[]) {
	if (sizeof(color) / sizeof(uint8_t) != 3) { // Testen ob das Array die richtige Länge hat
		throw 0x0001;
		return;
	} else {
		clearMatrix(getColor(color[0], color[1], color[3]));
	}
}

// -- clearMatrix --
// Methode die alle Pixel der LED-Matrix in einer bestimmten Farbe aufleuchten lässt
// @param color: 16-bit Farbwert der gesetzt werden soll
//
void CLEDMatrix::clearMatrix(uint16_t color) {
	for (int i = 0; i < MATRIX_HEIGHT; i++)
		for (int j = 0; j < MATRIX_WIDTH; j++)
			setPixel(i, j, color);
}

// -- setPixel --
// Methode mit der man die Farbe eines bestimmten Pixels verändern kann
// @param x, y: Position des Pixels
// @param r, g, b: Neue Farbe des Pixels (RGB-Wert)
//
void CLEDMatrix::setPixel(int x, int y, uint8_t r, uint8_t g, uint8_t b) {
	setPixel(x, y, getColor(r, g, b));
}

// -- setPixel --
// Methode mit der man die Farbe eines bestimmten Pixels verändern kann
// @param x, y: Position des Pixels
// @param color[]: Array das die Neue Farbe beinhaltet
//
void CLEDMatrix::setPixel(int x, int y, uint8_t color[]) {
	if (sizeof(color) / sizeof(uint8_t) != 3) {
		throw 0x0002;
		return;
	} else {
		setPixel(x, y, getColor(color[0], color[1], color[2]));
	}
}

// -- setPixel --
// Methode mit der man die Farbe eines bestimmten Pixels verändern kann
// @param x, y: Position des Pixels
// @param color: 16-bit Farbwert der gesetzt werden soll
//
void CLEDMatrix::setPixel(int x, int y, uint16_t color) {
	if (x >= 8 || x < 0 || y >= 8 || y < 0) {
		throw 0x0004;
		return;
	}
	_fbp->pixel[y][x] = color;
}

// -- displayImage --
// Methode zeigt ein Bild auf dem Display an
// @param path: Pfad zum/Name des Bildes das angezeigt werden soll
//
void CLEDMatrix::displayImage(std::string path) {
	_img->loadFromFile(path);
	for (int y = 0; y < (_img->getSize().y > 8 ? MATRIX_HEIGHT : _img->getSize().y); y++) {
		for (int x = 0; x < (_img->getSize().x > 8 ? MATRIX_WIDTH : _img->getSize().x); x++) {
			try {
				setPixel(x, y, _img->getPixel(x, y).r, _img->getPixel(x, y).g, _img->getPixel(x, y).b);
			} catch (int e) {
				std::cout << e << ": Cannot set Pixel at Position x=" << x << " y=" << y << std::endl;
			}
		}
	}
}

// -- displayRect --
// Methode zeicht ein Rechteck auf der LED Matrix an
// @param x, y: Position des Rechtecks
// @param size_x, size_y: Größe des Rechtecks
// @param color: Farbe des Rechtecks
//
void CLEDMatrix::displayRect(int _x, int _y, int size_x, int size_y, uint16_t color) {
	for (int y = _y; y < (size_y + _y); y++) {
		for (int x = _x; x < (size_x + _x); x++) {
			try {
				setPixel(x, y, color);
			} catch (int e) {
				std::cout << e << ": Cannot set Pixel at Position x=" << x << " y=" << y << std::endl;
			}
		}
	}
}

// -- displayRect --
// Methode zeicht ein Rechteck auf der LED Matrix an
// @param x, y: Position des Rechtecks
// @param size_x, size_y: Größe des Rechtecks
// @param color: Farbe des Rechtecks
//
void CLEDMatrix::displayRect(int _x, int _y, int size_x, int size_y, uint8_t color[]) {
	for (int y = _y; y < (size_y + _y); y++) {
		for (int x = _x; x < (size_x + _x); x++) {
			try {
				setPixel(x, y, getColor(color[0], color[1], color[2]));
			} catch (int e) {
				std::cout << e << ": Cannot set Pixel at Position x=" << x << " y=" << y << std::endl;
			}
		}
	}
}

// -- _loadFB --
// Methode die den Framebuffer der LED-Matrix lädt und in _fb_fd abspeichert
// @param fb_path: Pfad zum / Name des Framebuffers der geladen werden soll
//
void CLEDMatrix::_loadFB(std::string fb_path) {
	_fb_fd = -1;
	_fb_fd = open(fb_path.c_str(), O_RDWR);
	if (_fb_fd < 0) {
		throw 0x0003;
	}
}

// -- Destruktor --
CLEDMatrix::~CLEDMatrix() {
	close(_fb_fd);

	// Free Memory
	SAFE_DELETE(_img);
}