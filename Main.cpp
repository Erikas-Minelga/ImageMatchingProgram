#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include "Image.h"

Image readFromFile(std::string path)
{
	std::fstream f;
	std::vector<int> pixels;
	int height = 0, width = 0, lnCtr = 1, pxCtr = 0;
	std::stringstream ss;
	std::string ln;

	f.open(path.c_str());

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
			ss >> width >> height;
			pixels.resize(height * width);
		}
		else
		{
			ss << ln;
			ss >> pixels[pxCtr];
			pxCtr++;
		}

		ss.clear();

		lnCtr++;
	}

	f.close();

	return Image(pixels, height, width);
}

void writeToFile(Image &img, std::string path)
{
	std::ofstream f(path.c_str());		//Have to use ofstream to write to a file

	f << "P2" << std::endl;
	f << "# Created by NearestNeighbourSearch program" << std::endl;
	f << img.Width() << " " << img.Height() << std::endl;
	f << "255" << std::endl;

	for (int i = 0; i < img.Height() * img.Width(); i++)
		f << img[i] << std::endl;

	f.close();
}

int main()
{
	std::cout << "Program starting..." << std::endl;

	Image scene = readFromFile("scene.pgm");

	std::cout <<"Scene image loaded in. Dimensions: " << scene.Height() << "x" << scene.Width() << "..." << std::endl;

	Image query = readFromFile("query.pgm");

	std::cout << "Query image loaded in. Dimensions: " << query.Height() << "x" << query.Width() << "..." << std::endl;

	std::cout << "Finding the best match to query image in the scene image..." << std::endl;

	int min_x = 0, max_x = 0, min_y = 0, max_y = 0;		//Keep track of the coordinates of the best match, to draw outline in the scene image based on it
	int ssd = 1000000000;		//The lower the score, the better the match

	for (int i = 0; i < scene.Height(); i += query.Height())
	{
		for (int j = 0; j < scene.Width(); j += query.Width())
		{
			//Readjust i and j when close to the edges
			if (i > scene.Height() - query.Height())
				i = scene.Height() - query.Height();
			if (j > scene.Width() - query.Width())
				j = scene.Width() - query.Width();
			
			Image sub = scene.createSubImage(j, j + query.Width(), i, i + query.Height());

			scene.drawOutline(j, j + query.Width(), i, i + query.Height());
			writeToFile(scene, "result.pgm");
			
			//Sum of Squared Differences;
			sub = sub - query;
			sub.square();

			int img_sum = sub.sum();
			if (sub.sum() < ssd)
			{
				ssd = sub.sum();
				min_x = j;
				max_x = j + query.Width();
				min_y = i;
				max_y = i + query.Height();
			}
		}
	}
	std::cout << "Matching completed. Drawing black outline around the closest match..." << std::endl;

	//scene.drawOutline(min_x, max_x, min_y, max_y);

	std::cout << "Outline drawn. Writing output to a pgm file..." << std::endl;

	writeToFile(scene, "result.pgm");

	std::cout << "Output File Created. Press any key to continue..." << std::endl;

	std::cin.ignore();

	return 0;
}
