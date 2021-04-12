#ifndef IMAGE_H
#define IMAGE_H

#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <vector>

class Image
{
	public:
		//Constructors
		Image() {}
		Image(std::string img_path);
		Image(std::vector<int> data, int height, int width) { this->data = data; this->height = height; this->width = width; }
		~Image() {}
		
		//Methods
		int sum();
		void square();
		Image createSubImage(int minWidth, int maxWidth, int minHeight, int maxHeight);
		void drawOutline(int minWidth, int maxWidth, int minHeight, int maxHeight, int col);
		void writeToFile();

		//Operator overloads
		Image operator-(const Image& i);
		int operator[](int i);

		//Getters
		int Height() { return this->height; }
		int Width() { return this->width; }
		std::vector<int> Data() { return data; }

	private:
		int height, width;
		std::vector<int> data;
};

#endif
