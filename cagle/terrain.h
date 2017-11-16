#pragma once
#include <fstream>
#include <vector>
#include <iostream>
#include <Windows.h>


struct Pixel
{
	Pixel() {}
	Pixel(int r, int g, int b)
		:r(r), g(g), b(b) {}
	int r, g, b;
};

class Image
{
private:

	int width;
	int height;

	std::vector<std::vector<Pixel> > pixels;


	Image(int h, int w);

public:
	static Image& load_bmp(const std::string filename);

	void close();

	const int Width()	{ return width; }
	const int Height()	{ return height; }
	const Pixel Pixels(const int x, const int y) { return pixels[x][y]; }
};


class Terrain
{
private:
	int length;
	int width;

	std::vector<std::vector<float> > heights_map;



public:

	static Terrain* load_terrain(const std::string filename);

	const float Height(const int x, const int y) { return heights_map[x][y]; }

	const int Length() { return length; }
	const int Width() { return width; }

private:
	Terrain(int h, int w);
};