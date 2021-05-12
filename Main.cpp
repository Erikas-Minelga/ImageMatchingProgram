#include "Image.h"

struct Match
{
	Match(int min_x, int max_x, int min_y, int max_y, float score) { this->min_x = min_x; this->max_x = max_x; this->min_y = min_y; this->max_y = max_y; this->score = score; }
	int min_x;
	int max_x;
	int min_y;
	int max_y;
	float score;
};

float calculateScore(Image &sub, Image &query)
{
	//Sum of Squared Differences algorithm is used
	Image sub2 = sub - query;
	Image sub3 = sub2.square();
	return sub3.sum();
}

int main()
{
	std::cout << "Program starting..." << std::endl;

	Image scene("scene.pgm");

	std::cout << "Scene image loaded in. Dimensions: " << scene.Height() << "x" << scene.Width() << "..." << std::endl;

	Image query("query.pgm");

	std::cout << "Query image loaded in. Dimensions: " << query.Height() << "x" << query.Width() << "..." << std::endl;

	std::vector<Match> matches;
	int num_matches;

	std::cout << "Please enter the number of closest matches you would like to find:" << std::endl;
	std::cin >> num_matches;

	std::cout << "Calculating the best matches..." << std::endl;

	for (int i = 0; i < scene.Height(); i += query.Height())
	{
		for (int j = 0; j < scene.Width(); j += query.Width())
		{
			if (i > scene.Height() - query.Height())
				i = scene.Height() - query.Height();

			if (j > scene.Width() - query.Width())
				j = scene.Width() - query.Width();

			float score = 0;
			Image sub = scene.createSubImage(j, j + query.Width(), i, i + query.Height());

			score = calculateScore(sub, query);

			if (matches.size() < num_matches)
			{
				matches.push_back(Match(j, j + sub.Width(), i, i + sub.Height(), score));
			}
			else
			{
				if (score < matches[num_matches - 1].score)
				{
					matches[num_matches - 1] = Match(j, j + sub.Width(), i, i + sub.Height(), score);
				}
			}

			if (num_matches > 1)			//No need to sort if user only wants 1 match
				std::sort(matches.begin(), matches.end(), [](Match a, Match b) {return a.score < b.score; });
			
		}
	}
	
	std::cout << "Matching completed. Drawing outlines around the closest matches..." << std::endl;
	std::cout << "INFORMATION: The darker the outline, the closer the match it is" << std::endl;

	for(int i = 0; i < matches.size(); i++)
		scene.drawOutline(matches[i].min_x, matches[i].max_x, matches[i].min_y, matches[i].max_y, i);

	std::cout << "Outlines drawn. Writing output to a pgm file..." << std::endl;

	scene.writeToFile("result.pgm");

	std::cout << "Output File Created. Press any key to continue..." << std::endl;

	std::cin.ignore();

	return 0;
}


/*
References:
1. http://www.micc.unifi.it/delbimbo/wp-content/uploads/2013/11/A33_Matching.pdf
2. https://www.youtube.com/watch?v=ngEC3sXeUb4


Test image taken from:
https://www.firstpost.com/tech/news-analysis/wheres-waldo-googles-april-fools-day-gift-will-have-you-combing-through-maps-looking-for-wally-and-his-pals-4413969.html
*/