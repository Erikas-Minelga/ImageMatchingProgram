# ImageMatchingProgram
A program which finds an image within a larger image using Sum of Squared Differences algorithm

<h1>Features</h1>
  *Images of any size can be used but only PGM format is supported
  *Program can find multiple matches and the number can be determined by the user
  *The closest matches calculated by the program are highlighted with outlines which get lighter in colour the further the match the sub-image is
  
 <h1>To do</h1>
  *Add support for more image types (e.g. .jpg, .png, etc.)
  *Make improvements as to how algorithm steps through the large image to create sub-images to compare to
    *So far, program steps through the image in the increments of the size of the query image (image to find) which results in a lot of sub-images being missed. This affects the accuracy of the algorithm. 
  *Research and experiment with different image maching algorithms
