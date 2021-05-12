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

//Sum of Squared Differences
float SSD(Image &sub, Image &query)
{
	Image sub2 = sub - query;
	Image sub3 = sub2.square();
	return sub3.sum();
}

//Normalised Cross Correlation
float NCC(Image& sub, Image& query)
{
	Image corrImg = sub * query;		
	int corr = corrImg.sum();
	Image subSquare = sub.square();
	Image querySquare = query.square();
	float nccScore = sqrt(subSquare.sum()) * sqrt(querySquare.sum());
	return corr / nccScore;
}

Image getSubImage(Image *scene, int minWidth, int maxWidth, int minHeight, int maxHeight)
{
	//Image sub = scene->createSubImage(minWidth, maxWidth, minHeight, maxHeight);
	return scene->createSubImage(minWidth, maxWidth, minHeight, maxHeight);
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
	int algorithm;

	std::cout << "Please enter the number of closest matches you would like to find:" << std::endl;
	std::cin >> num_matches;

	std::cout << "Please select the correlation algorithm to use: 1. Sum of Squared Differences, 2. Normalised Cross Correlation" << std::endl;
	
	do
	{
		std::cin >> algorithm;
	} while (algorithm < 1 || algorithm > 2);


	std::cout << "Calculating the best matches..." << std::endl;

	for (int i = 0; i < scene.Height(); i + query.Height())
	{
		for (int j = 0; j < scene.Width(); j+ query.Width())
		{
			if (i + query.Height() > scene.Height())
				i = scene.Height() - query.Height();

			if (j + query.Width() > scene.Width())
				j = scene.Width() - query.Width();

			float score = 0;
			Image sub = scene.createSubImage(j, j + query.Width(), i, i + query.Height());

			switch (algorithm)
			{
			case 1:
				score = SSD(sub, query);
				break;
			case 2:
				score = NCC(sub, query);
				break;
			default:
				break;
			}

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
*/