#ifndef IMAGE_H
#define IMAGE_H

#include <iostream>
#include <vector>

class Image
{
	public:
		Image() {}
		Image(std::vector<int> data, int height, int width) { this->data = data; this->height = height; this->width = width; }
		~Image() {}
		
		int sum();
		void square();
		Image createSubImage(int minWidth, int maxWidth, int minHeight, int maxHeight);
		void drawOutline(int minWidth, int maxWidth, int minHeight, int maxHeight);

		Image operator-(const Image& i);
		//Image operator=(const Image& i) { this->data = i.data; this->height = i.height; this->width = i.width; }
		int operator[](int i);

		/*void print() 
		{
			for (auto& a : data)
				std::cout << a << std::endl;
		}*/

		int Height() { return this->height; }
		int Width() { return this->width; }
		std::vector<int> Data() { return data; }

	private:
		int height, width;
		std::vector<int> data;
};

#endif
