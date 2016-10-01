// Sample test file for the image class.
// Reads a given pgm image, draws a line, and saves it to
// another pgm image.
#include "Image.h"
#include <cstdio>
#include <iostream>
#include <string>
//#include <stdlib.h> // for atio()

using namespace std;
using namespace ComputerVisionProjects;

int
main(int argc, char **argv){
  
  if (argc!=4) {
    printf("Usage: %s file1 threshold_value file2\n", argv[0]);
    return 0;
  }
  const string input_file(argv[1]);
  const int threshold_value = atoi(argv[2]);
  const string output_file(argv[3]);


  Image an_image;
  if (!ReadImage(input_file, &an_image)) {
    cout <<"Can't open file " << input_file << endl;
    return 0;
  }

  // nested loop to go through the pixels and compare the value with the threshold value
    for (size_t i = 0; i < an_image.num_rows(); ++i)
        for (size_t j = 0; j < an_image.num_columns(); ++j){
            int pixel = an_image.GetPixel(i,j);
            if (pixel <= threshold_value){
                an_image.SetPixel(i,j,0);
            }else{
                an_image.SetPixel(i,j,1);
            }
        }
    an_image.SetNumberGrayLevels(1);    
    cout <<"Threshold value = "<<threshold_value<<endl;
    cout <<"Graylevel value = "<<an_image.num_gray_levels()<<endl;

    
    
  
  if (!WriteImage(output_file, an_image)){
    cout << "Can't write to file " << output_file << endl;
    return 0;
  }
}
