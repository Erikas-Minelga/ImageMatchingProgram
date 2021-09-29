# ImageMatchingProgram
<h2>About</h2>
Image Matching Program is an application written in C++ which takes 2 PGM images: a scene image and a query image. Then using Nearest Neighbour Search algorithm, the program finds the closest match to the query in the scene. The program uses Sum of Squared Differences formula to calculate the similarity score between the query image and every sub-image within the scene that is the same height and width as the query image. Lower scores indicate more similarity while higher scores indicate that the images are very different. 

This program can find multiple closest matches and outlines where those matches are within the scene are drawn on the image. The resulting image is outputted as "result.pgm" file. Outlines drawn get progressively lighter in shade, indicating that the particular square of pixels is less of a match than the one outlined with a darker colour.

Currently, PGM is the only supported image format.

<h2>How to run</h2>
To run the program, go over to Releases section, select ImageMatchingProgram, download ImageMatchingProgram.zip and extract it anywhere you'd like. For the program to run, 2 image files will need to be provided and placed in the same directory as the exe- scene.pgm and query.pgm. Program will create an additional file called "results.pgm" in the same directory as the exe. It is recommended to run the exe as Administrator.

<h2>More information on Nearest Neighbour Search algorithm</h2>
http://www.micc.unifi.it/delbimbo/wp-content/uploads/2013/11/A33_Matching.pdf
