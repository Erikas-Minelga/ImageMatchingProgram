#include "Image.h"

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
			img.push_back(data[maxWidth * i + j]);
		}
	}

	Image i(img, maxHeight - minHeight, maxWidth - minWidth);
	return i;
}

void Image::drawOutline(int minWidth, int maxWidth, int minHeight, int maxHeight)
{
	for (int i = minHeight; i < maxHeight; i++)
	{
		for (int j = minWidth; j < maxWidth; j++)
		{
			if (i > minHeight && i < maxHeight && j > minWidth && j < maxWidth)
				continue;

			this->data[j * maxWidth + i] = 0;
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