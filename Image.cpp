#include "Image.h"

Image::Image(std::string img_path)
{
	std::fstream f;
	//std::vector<int> pixels;
	this->height = 0; 
	this->width = 0;
	int lnCtr = 1, pxCtr = 0;
	std::stringstream ss;
	std::string ln;

	f.open(img_path.c_str());

	while (std::getline(f, ln))
	{
		if (lnCtr == 1 || lnCtr == 2 || lnCtr == 4)
		{
			lnCtr++;
			continue;
		}
		else if (lnCtr == 3)
		{
			ss << ln;
			ss >> this->width >> this->height;
			this->data.resize(height * width);
		}
		else
		{
			ss << ln;
			ss >> this->data[pxCtr];
			pxCtr++;
		}

		ss.clear();

		lnCtr++;
	}

	f.close();
}

int Image::sum()
{
	int sum = 0;

	for (auto& a : data)
		sum += a;

	return sum;
}

void Image::square()
{
	for (int i = 0; i < data.size(); i++)
		this->data[i] *= this->data[i];
}

Image Image :: createSubImage(int minWidth, int maxWidth, int minHeight, int maxHeight)
{
	std::vector<int> img;

	for (int i = minHeight; i < maxHeight; i++)
	{
		for (int j = minWidth; j < maxWidth; j++)
		{
			int index = this->width * i + j;
			img.push_back(data[index]);
		}
	}

	Image i(img, maxHeight - minHeight, maxWidth - minWidth);
	return i;
}

void Image::drawOutline(int minWidth, int maxWidth, int minHeight, int maxHeight, int col)
{
	for (int i = minHeight; i < maxHeight; i++)
	{
		for (int j = minWidth; j < maxWidth; j++)
		{
			if(i <= minHeight + 6 || i >= maxHeight - 7 || j <= minWidth + 6 || j >= maxWidth - 7)
				this->data[this->width * i + j] = col + 5;		//The brighter the colour, the less a match
		}
	}
}

Image Image :: operator-(const Image& img)
{
	if (this->height != img.height || this->width != img.width)
		return Image();

	std::vector<int> tmp;
	tmp.resize(img.height * img.width);
	for (int i = 0; i < this->data.size(); i++)
		tmp[i] = data[i] -= img.data[i];

	return Image(tmp, img.height, img.width);
}

int Image :: operator[](int i)
{
	return data[i];
}