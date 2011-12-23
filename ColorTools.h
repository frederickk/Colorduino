/*
 *  ColorTools.h
 *
 *  Ken Frederick
 *  ken.frederick@gmx.de
 *
 *  http://cargocollective.com/kenfrederick/
 *  http://kenfrederick.blogspot.com/
 *
 *	A Collection of color converting methods
 *
 */


#ifndef _COLORTOOLS
#define _COLORTOOLS

//-----------------------------------------------------------------------------
// includes
//-----------------------------------------------------------------------------
#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include <String.h>



//-----------------------------------------------------------------------------
// structs
//-----------------------------------------------------------------------------
typedef struct ColorRGB {
	unsigned char r;
	unsigned char g;
	unsigned char b;
} ColorRGB;

typedef struct ColorHSV {
  unsigned char h;
  unsigned char s;
  unsigned char v;
} ColorHSV;



class ColorTools {
protected:
	//-----------------------------------------------------------------------------
	// properties
	//-----------------------------------------------------------------------------

	

public:
	//-----------------------------------------------------------------------------
	// constructor
	//-----------------------------------------------------------------------------
	ColorTools() {
	}



	//-----------------------------------------------------------------------------
	// denstructor
	//-----------------------------------------------------------------------------
	~ColorTools() {
	}



	//-----------------------------------------------------------------------------
	// methods
	//-----------------------------------------------------------------------------
	void HSVtoRGB(void *vRGB, void *vHSV) {
		float r, g, b, h, s, v; //this function works with floats between 0 and 1
		float f, p, q, t;
		int i;
		ColorRGB *colorRGB = (ColorRGB *)vRGB;
		ColorHSV *colorHSV = (ColorHSV *)vHSV;

		h = (float)(colorHSV->h / 256.0);
		s = (float)(colorHSV->s / 256.0);
		v = (float)(colorHSV->v / 256.0);

		//if saturation is 0, the color is a shade of grey
		if(s == 0.0) {
			b = v;
			g = b;
			r = g;
		} else {
			//if saturation > 0, more complex calculations are needed
			h *= 6.0; 				// to bring hue to a number between 0 and 6, better for the calculations
			i = (int)(floor(h));	// e.g. 2.7 becomes 2 and 3.01 becomes 3 or 4.9999 becomes 4
			f = h - i;				// the fractional part of h

			p = (float)(v * (1.0 - s));
			q = (float)(v * (1.0 - (s * f)));
			t = (float)(v * (1.0 - (s * (1.0 - f))));

			switch(i) {
				case 0: r=v; g=t; b=p; break;
				case 1: r=q; g=v; b=p; break;
				case 2: r=p; g=v; b=t; break;
				case 3: r=p; g=q; b=v; break;
				case 4: r=t; g=p; b=v; break;
				case 5: r=v; g=p; b=q; break;
				default: r = g = b = 0; break;
			}
		}
		colorRGB->r = (int)(r * 255.0);
		colorRGB->g = (int)(g * 255.0);
		colorRGB->b = (int)(b * 255.0);
	}


	//-----------------------------------------------------------------------------
	int HextoInt(String hex) {
		int value = 0;
		int a = 0;
		int b = hex.length() - 1;

		for (; b >= 0; a++, b--) {
			if (hex[b] >= '0' && hex[b] <= '9') {
				value += (hex[b] - '0') * (1 << (a * 4));
			} else {
				switch (hex[b]) {
				case 'A':
				case 'a':
					value += 10 * (1 << (a * 4));
					break;
				case 'B':
				case 'b':
					value += 11 * (1 << (a * 4));
					break;
				case 'C':
				case 'c':
					value += 12 * (1 << (a * 4));
					break;
				case 'D':
				case 'd':
					value += 13 * (1 << (a * 4));
					break;
				case 'E':
				case 'e':
					value += 14 * (1 << (a * 4));
					break;
				case 'F':
				case 'f':
					value += 15 * (1 << (a * 4));
					break;
				default:
					//cout << "Error, invalid charactare '" << hex[a] << "' in hex number" << endl;
					break;
				}
			}
		}

		return value;
	}

	
	//-----------------------------------------------------------------------------
	/*
	ColorRGB HextoRGB(String hex) {
		ColorRGB color;
		String prefix = hex.substring(0);
		String redString = "";
		String greenString = "";
		String blueString = "";

		//if( prefix == "#" ) {
			// if the prefix # was attached to hex, use the following code
			//redString = hex.substring(1, 2);
			//greenString = hex.substring(3, 2);
			//blueString = hex.substring(5, 2);

		//} else if( prefix == "0" && hex.substring(1) == "x" ) {
			// if the prefix 0x was attached to hex, use the following code
			//redString = hex.substring(2, 2);
			//greenString = hex.substring(4, 2);
			//blueString = hex.substring(6, 2);

		//} else {
			// if there is no prefix attached to hex, use this code
			redString = hex.substring(0, 2);
			greenString = hex.substring(2, 2);
			blueString = hex.substring(4, 2);
		//}

		unsigned char red = (unsigned char) ( HextoInt(redString) );
		unsigned char green = (unsigned char) ( HextoInt(greenString) );
		unsigned char blue = (unsigned char) ( HextoInt(blueString) );

		color.r = red;
		color.g = green;
		color.b = blue;
	}
	*/


	//-----------------------------------------------------------------------------
	int RGBtoInt(void *vRGB) {
		ColorRGB *colorRGB=(ColorRGB *)vRGB;
		return (((unsigned int)colorRGB->r)<<16) + (((unsigned int)colorRGB->g)<<8) + (unsigned int)colorRGB->b;
	}
	



	//-----------------------------------------------------------------------------
	// gets
	//-----------------------------------------------------------------------------
	int GetBrightness(ColorRGB color) {
		return (0.2126 * color.r) + (0.7152 * color.g) + (0.0722 * color.b);
	}



	//-----------------------------------------------------------------------------
	//sets
	//-----------------------------------------------------------------------------

};

#endif

