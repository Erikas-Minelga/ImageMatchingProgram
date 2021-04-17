#include "Image.h"

struct Match
{
	Match(int min_x, int max_x, int min_y, int max_y, int score) { this->min_x = min_x; this->max_x = max_x; this->min_y = min_y; this->max_y = max_y; this->score = score; }
	int min_x;
	int max_x;
	int min_y;
	int max_y;
	int score;
};

//Sum of Squared Differences
void SSD(Image &scene, Image &query, std::vector<Match> &matches, int &num_matches)
{
	std::cout << "Calculating the best matches using Sum of Squared Differences..." << std::endl;

	for (int i = 0; i < scene.Height(); i += query.Height())
	{
		for (int j = 0; j < scene.Width(); j += query.Width())
		{
			if(i > scene.Height() - query.Height())
				i = scene.Height() - query.Height();

			if(j > scene.Width() - query.Width())
				j = scene.Width() - query.Width();

			Image* sub = scene.createSubImage(j, j + query.Width(), i, i + query.Height());

			Image sub2 = *sub - query;
			Image sub3 = sub2.square();

			int img_sum = sub3.sum();
			if (matches.size() < num_matches)
			{
				matches.push_back(Match(j, j + sub->Width(), i, i + sub->Height(), img_sum));
			}
			else
			{
				if (img_sum < matches[num_matches - 1].score)
				{
					matches[num_matches - 1] = Match(j, j + sub->Width(), i, i + sub->Height(), img_sum);
				}
			}

			std::sort(matches.begin(), matches.end(), [](Match a, Match b) {return a.score < b.score; });

			delete sub;
		}
	}
}

//Normalised Cross Correlation
void NCC(Image& scene, Image& query, std::vector<Match>& matches, int& num_matches)
{
	std::cout << "Calculating the best matches using Normalised Cross Correlation..." << std::endl;

	for (int i = 0; i < scene.Height(); i += query.Height())
	{
		for (int j = 0; j < scene.Width(); j += query.Width())
		{
			if (i > scene.Height() - query.Height())
				i = scene.Height() - query.Height();

			if (j > scene.Width() - query.Width())
				j = scene.Width() - query.Width();

			Image* sub = scene.createSubImage(j, j + query.Width(), i, i + query.Height());
			
			Image corrImg = *sub * query;		
			int corr = corrImg.sum();
			Image subSquare = sub->square();
			Image querySquare = query.square();
			float nccScore = sqrt(subSquare.sum()) * sqrt(querySquare.sum());
			float finalScore = corr / nccScore;

			if (matches.size() < num_matches)
				matches.push_back(Match(j, j + sub->Width(), i, i + sub->Height(), finalScore));
			else
			{
				if (nccScore > matches[num_matches - 1].score)
					matches[num_matches - 1] = Match(j, j + sub->Width(), i, i + sub->Height(), finalScore);
			}

			std::sort(matches.begin(), matches.end(), [](Match a, Match b) {return a.score > b.score; });

			delete sub;
		}
	}
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

	switch (algorithm)
	{
		case 1:
			SSD(scene, query, matches, num_matches);
			break;
		case 2:
			NCC(scene, query, matches, num_matches);
			break;
		default:
			break;
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