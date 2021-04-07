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
		data[i] *= data[i];
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