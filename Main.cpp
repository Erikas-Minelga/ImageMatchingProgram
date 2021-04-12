#include <algorithm>
#include "Image.h"
#include <map>

struct Match
{
	Match(int min_x, int max_x, int min_y, int max_y, int score) { this->min_x = min_x; this->max_x = max_x; this->min_y = min_y; this->max_y = max_y; this->score = score; }
	int min_x;
	int max_x;
	int min_y;
	int max_y;
	int score;
};

int main()
{
	std::cout << "Program starting..." << std::endl;

	Image scene("scene.pgm");

	std::cout <<"Scene image loaded in. Dimensions: " << scene.Height() << "x" << scene.Width() << "..." << std::endl;

	Image query("query.pgm");

	std::cout << "Query image loaded in. Dimensions: " << query.Height() << "x" << query.Width() << "..." << std::endl;

	std::vector<Match> matches;
	int num_matches;

	std::cout << "Please enter the number of closest matches you would like to find:" << std::endl;
	std::cin >> num_matches;

	std::cout << "Finding the best matches to query image in the scene image..." << std::endl;

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
			
			//Sum of Squared Differences;
			Image sub2 = query - sub;
			sub2.square();

			int img_sum = sub2.sum();
			if (matches.size() < num_matches)
			{
				matches.push_back(Match(j, j + sub2.Width(), i, i + sub2.Height(), img_sum));
			}
			else
			{
				if (sub2.sum() < matches[num_matches - 1].score)
				{
					matches[num_matches - 1] = Match(j, j + sub2.Width(), i, i + sub2.Height(), sub2.sum());
					std::sort(matches.begin(), matches.end(), [](Match a, Match b) {return a.score < b.score; });
				}
			}
		}
	}
	std::cout << "Matching completed. Drawing outlines around the closest matches..." << std::endl;

	for(int i = 0; i < matches.size(); i++)
		scene.drawOutline(matches[i].min_x, matches[i].max_x, matches[i].min_y, matches[i].max_y, i);

	std::cout << "Outlines drawn. Writing output to a pgm file..." << std::endl;

	scene.writeToFile("result.pgm");

	std::cout << "Output File Created. Press any key to continue..." << std::endl;

	std::cin.ignore();

	return 0;
}
