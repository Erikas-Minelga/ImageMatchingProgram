#ifndef IMAGE_H
#define IMAGE_H

#include <iostream>
#include <vector>

class Image
{
	public:
		Image() {}
		Image(std::initializer_list<int> data, int height, int width) { this->data = data; this->height = height; this->width = width; }
		Image(std::vector<int> data, int height, int width) { this->data = data; this->height = height; this->width = width; }
		~Image() {}
		
		int sum();
		void square();
		Image operator-(const Image& i);
		Image operator=(std::initializer_list<int> data) { this->data = data; }

		void print() 
		{
			for (auto& a : data)
				std::cout << a << std::endl;
		}

		int Height() { return this->height; }
		int Width() { return this->width; }

	private:
		int height, width;
		std::vector<int> data;
};

#endif
