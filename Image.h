#ifndef IMAGE_H
#define IMAGE_H

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>

class Image
{
	public:
		Image() {}
		Image(std::vector<int> data, int height, int width) { this->data = data; this->height = height; this->width = width; }
		~Image() {}
		Image(std::string img_path);
		
		int sum();
		Image square();
		Image* createSubImage(int minWidth, int maxWidth, int minHeight, int maxHeight);
		void drawOutline(int minWidth, int maxWidth, int minHeight, int maxHeight, int col);
		void writeToFile(std::string path);

		Image operator-(const Image& img);
		Image operator*(const Image& img);

		int Height() { return this->height; }
		int Width() { return this->width; }
		std::vector<int> Data() { return data; }

	private:
		int height, width;
		std::vector<int> data;
};

#endif
