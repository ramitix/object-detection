// Sample test file for the image class.
// Reads a given pgm image, draws a line, and saves it to
// another pgm image.
#include "Image.h"
#include "DisjSets.h"
#include <cstdio>
#include <iostream>
#include <string>
//#include <stdlib.h> // for atio()

using namespace std;
using namespace ComputerVisionProjects;

int
main(int argc, char **argv){
  
  if (argc!=3) {
    printf("Usage: %s file1 file2\n", argv[0]);
    return 0;
  }
  const string input_file(argv[1]);
  const string output_file(argv[2]);


  Image an_image;
  if (!ReadImage(input_file, &an_image)) {
    cout <<"Can't open file " << input_file << endl;
    return 0;
  }

  // nested loop to go through the pixels and compare the value with the threshold value
   int label= 0;
   DisjSets disjSets(400);
    for (size_t i = 0; i < an_image.num_rows(); ++i)
        for (size_t j = 0; j < an_image.num_columns(); ++j){
          int pixelValue = an_image.GetPixel(i,j);

          //check the boundaries
          if (pixelValue == 1){
            if(i==0 && j==0 && label==0){
              label+=1;
              an_image.SetPixel(i,j,label);
            }
            if(i==0 && j!=0){
              int leftPixelValue  = an_image.GetPixel(i,j-1);
              if(leftPixelValue==label){
                an_image.SetPixel(i,j,label);
              }else{
                 label+=1;
                  an_image.SetPixel(i,j,label);
              }
            }
            if (i!=0 && j!=0){
                int topPixelValue  = an_image.GetPixel(i-1,j);
                int leftPixelValue  = an_image.GetPixel(i,j-1);
                int diagonalPixelValue  = an_image.GetPixel(i-1,j-1);
              if(leftPixelValue==0 && topPixelValue==0 && diagonalPixelValue==0 ){
                // cout<<"i,j  "<<i<<","<<j<<" value= "<<an_image.GetPixel(i,j)<<endl;
                // cout<<"i-1,j  "<<i-1<<","<<j<<" value= "<<topPixelValue<<endl;
                // cout<<"i,j-1  "<<i<<","<<j-1<<" value= "<<leftPixelValue<<endl;
                 // cout<<"label before= "<<label;
                label+=1;
                // cout<<" label after= "<<label<<endl;
                an_image.SetPixel(i,j,label);
                // cout<<"i,j  "<<i<<","<<j<<" value= "<<an_image.GetPixel(i,j)<<endl<<endl;

              //three neigobhors
              }else if(leftPixelValue!=0 && topPixelValue!=0 && diagonalPixelValue!=0){
                  if (diagonalPixelValue==topPixelValue== leftPixelValue){
                    an_image.SetPixel(i,j,leftPixelValue);
                  }else if ((diagonalPixelValue==leftPixelValue)!= topPixelValue){
                    an_image.SetPixel(i,j,leftPixelValue);
                    disjSets.unionSets(disjSets.find(topPixelValue),disjSets.find(leftPixelValue));

                  }else if ((diagonalPixelValue == topPixelValue)!= leftPixelValue){
                    an_image.SetPixel(i,j,topPixelValue);
                    disjSets.unionSets(disjSets.find(leftPixelValue),disjSets.find(topPixelValue));
                  }else if ((leftPixelValue==topPixelValue)!= diagonalPixelValue){
                    an_image.SetPixel(i,j,topPixelValue);
                    disjSets.unionSets(disjSets.find(diagonalPixelValue),disjSets.find(topPixelValue));
                  }
                //top and diagonal
              }else if(leftPixelValue==0 && topPixelValue!=0 && diagonalPixelValue!=0){
                if(topPixelValue==diagonalPixelValue){
                    an_image.SetPixel(i,j,diagonalPixelValue);
                }else{
                  an_image.SetPixel(i,j,diagonalPixelValue);
                  disjSets.unionSets(disjSets.find(diagonalPixelValue),disjSets.find(topPixelValue));
                }
              
              //left and diagonal
              }else if(leftPixelValue!=0 && topPixelValue==0 && diagonalPixelValue!=0){
                if(leftPixelValue==diagonalPixelValue){
                    an_image.SetPixel(i,j,diagonalPixelValue);
                }else{
                  an_image.SetPixel(i,j,diagonalPixelValue);
                  disjSets.unionSets(disjSets.find(diagonalPixelValue),disjSets.find(leftPixelValue));
                }
              
              //left and top
              }else if(leftPixelValue!=0 && topPixelValue!=0 && diagonalPixelValue==0){
                if(leftPixelValue==topPixelValue){
                    an_image.SetPixel(i,j,leftPixelValue);
                }else{
                  an_image.SetPixel(i,j,leftPixelValue);
                  disjSets.unionSets(disjSets.find(topPixelValue),disjSets.find(leftPixelValue));
                }
              
              //one of the neigobhors is not zero
              }else if(leftPixelValue!=0 || topPixelValue!=0 || diagonalPixelValue!=0){
                if(leftPixelValue!=0){
                    an_image.SetPixel(i,j,leftPixelValue);
                }else if (topPixelValue!=0){
                  an_image.SetPixel(i,j,topPixelValue);
                }else if (diagonalPixelValue!=0){
                  an_image.SetPixel(i,j,diagonalPixelValue); 
                }
              }
              
            }
          }
        }

      // for (size_t i = 100; i < an_image.num_rows(); ++i)
        // for (size_t j = 150; j < an_image.num_columns(); ++j){
        //       cout <<an_image.GetPixel(i,j)<<" ";
        //       if (j==an_image.num_columns()-1){
        //         cout<<endl;
        //       }
        // }


    //nested loop to set consecutive labels to the objects 
    vector< int >labels;
    for (size_t i = 0; i < an_image.num_rows(); ++i)
        for (size_t j = 0; j < an_image.num_columns(); ++j){
          if (an_image.GetPixel(i,j)!=0){
              if (labels.empty()){
                labels.push_back(disjSets.find(an_image.GetPixel(i,j)));
                an_image.SetPixel(i,j,1);
              }else{
                if(find(labels.begin(),labels.end(),disjSets.find(an_image.GetPixel(i,j))) != labels.end()){
                  for (int z = 0; z < labels.size(); ++z){
                    if (labels[z]== disjSets.find(an_image.GetPixel(i,j))){
                      an_image.SetPixel(i,j,(z+1));
                      
                    }
                  }
                }else{
                  labels.push_back(disjSets.find(an_image.GetPixel(i,j)));
                  an_image.SetPixel(i,j,labels.size());
                }
              }
            }
          }
        


      // for (size_t i = 150; i < an_image.num_rows(); ++i)
      //   for (size_t j = 100; j < an_image.num_columns(); ++j){
      //         cout <<an_image.GetPixel(i,j)<<" ";
      //         if (j==an_image.num_columns()-1){
      //           cout<<endl;
      //         }
      //   }

          
    an_image.SetNumberGrayLevels(labels.size());    
    cout <<"Graylevel value = "<<an_image.num_gray_levels()<<endl;

    
    
  
  if (!WriteImage(output_file, an_image)){
    cout << "Can't write to file " << output_file << endl;
    return 0;
  }
}
