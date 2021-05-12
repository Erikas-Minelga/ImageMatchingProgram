# ImageMatchingProgram
A program which finds an image within a larger image using Sum of Squared Differences algorithm

<h1>Features</h1>
<ul>
 <li>mages of any size can be used but only PGM format is supported</li>
  <li>Program can find multiple matches and the number can be determined by the user</li>
  <li>The closest matches calculated by the program are highlighted with outlines which get lighter in colour the further the match the sub-image is</li>
 </ul>

 <h1>To do</h1>
 <ul>
  <li>Add support for more image types (e.g. .jpg, .png, etc.)</li>
  <li>Make improvements as to how algorithm steps through the large image to create sub-images to compare to. So far, program steps through the image in the increments of the size of the query image (image to find) which results in a lot of sub-images being missed. This affects the accuracy of the algorithm. </li>
  <li>Research and experiment with different image maching algorithms</li>
 </ul>
