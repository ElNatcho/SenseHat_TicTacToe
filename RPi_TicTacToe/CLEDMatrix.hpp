#ifndef CLEDMATRIX_HPP
#define CLEDMATRIX_HPP

// Includes
#include<iostream>
#include<linux/fb.h>
#include<arm-linux-gnueabihf/sys/mman.h>
#include<arm-linux-gnueabihf/sys/ioctl.h>
#include<exception>
#include<unistd.h>
#include<fcntl.h>
#include<SFML/Graphics.hpp>

#define SAFE_DELETE(X) {if(X!=nullptr){delete X; X=nullptr;}}

#define RED     0xF800
#define BLUE    0x001F
#define GREEN   0x7E00
#define WHITE   0xFFFF
#define BLACK   0x0000
#define YELLOW  BLUE  | GREEN
#define ORANGE  GREEN | RED
#define MAGENTA BLUE  | RED

#define MATRIX_HEIGHT 8
#define MATRIX_WIDTH  8

// CLEDMatric
class CLEDMatrix {
public:

	// Struktur repräsentiert den Framebuffer(Array)
	// der LED-Matrix als Pixel-Matrix
	struct fb_t {
		uint16_t pixel[8][8];
	};

	// -- Kon/Destruktor --
	CLEDMatrix();
	CLEDMatrix(std::string fb_path);
	~CLEDMatrix();

	// -- Methoden --
	
	// Methode mit der man den Framebuffer laden kann
	void initFB(std::string fb_path);

	// Methode mit der man normale RGB Werte zu den hier passenden
	// RGB Werten konvertieren kann
	uint16_t getColor(uint8_t r, uint8_t g, uint8_t b);

	// Methoden die alle Pixel in einer bestimmten Farbe aufleuchten lässt oder
	// alle Pixel auschaltet
	//void clearMatrix();
	void clearMatrix(uint8_t r, uint8_t g, uint8_t b);
	void clearMatrix(uint8_t color[]);
	void clearMatrix(uint16_t color = BLACK);

	// Methoden die die Farbe eines bestimmten Pixels verändert
	void setPixel(int x, int y, uint8_t r, uint8_t g, uint8_t b);
	void setPixel(int x, int y, uint8_t color[]);
	void setPixel(int x, int y, uint16_t color);

	// Methoden die ein 8x8 Bild auf der LED Matrix anzeigen
	void displayImage(std::string path);

	// Methode die ein Reckteck auf der LED Matrix anzeigt
	void displayRect(int x, int y, int size_x, int size_y, uint8_t color[]);
	void displayRect(int x, int y, int size_x, int size_y, uint16_t color);

private:

	// -- Member Vars --
	int _fb_fd;
	struct fb_fix_screeninfo _finfo; // Screen info
	struct fb_var_screeninfo _vinfo; // -----"-----

	// Pointer zum ersten Element des Framebuffers
	struct fb_t *_fbp; 

    // Image für das displayImage Objekt
	sf::Image *_img;

	// -- Member Methods --
	void _loadFB(std::string fb_path); // Methode die den Framebuffer lädt

};

#endif