// Sample test file for the image class.
// Reads a given pgm image, draws a line, and saves it to
// another pgm image.
#include "Image.h"
#include "DisjSets.h"
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <math.h> 
//#include <stdlib.h> // for atio()

#define PI 3.14159265

using namespace std;
using namespace ComputerVisionProjects;

int main(int argc, char **argv){
  
  if (argc!=4) {
    printf("Usage: %s file1 file2 file3\n", argv[0]);
    return 0;
  }
  const string input_file(argv[1]);
  const string database_file(argv[2]);
  const string output_file(argv[3]);


  Image an_image;
  if (!ReadImage(input_file, &an_image)) {
    cout <<"Can't open file " << input_file << endl;
    return 0;
  }


  

  //values[*][0] is object label
  //values[*][1] is sum of i 
  //values[*][2] is sum of j
  //values[*][3] is sum of i^2
  //values[*][4] is sum of i*j
  //values[*][5] is sum of j^2
  vector< vector<int> > values(an_image.num_gray_levels());
  for (int i = 0; i < values.size(); ++i){
    values[i].resize(6);
    values[i][0]=0;
  }
  // nested loop to go through the pixels 
    for (int i = 0; i < an_image.num_rows(); ++i)
        for (int j = 0; j < an_image.num_columns(); ++j){
          int pixelValue = an_image.GetPixel(i,j);
          if (pixelValue != 0){
            for (int z=0; z<an_image.num_gray_levels(); ++z){
              if ((z+1)==pixelValue){
                values[z][0]+=1;
                values[z][1]+=i;
                values[z][2]+=j;  
                values[z][3]+=i*i;
                values[z][4]+=i*j;
                values[z][5]+=j*j;
              } 
            }
          }
        }  
        
 //filling a 2D vector with database values from the text file
  vector< vector<double> > database_values(an_image.num_gray_levels()); 
  for (int i = 0; i < values.size(); ++i){
    database_values[i].resize(7);
    database_values[i][0]=0;
  }
  ifstream database (database_file);
  string dummyLine;
  getline(database, dummyLine);
  int index=0;
  while (!database.eof()) {


    database >> database_values[index][0]//label
             >> database_values[index][1]//xbar  
             >> database_values[index][2]//ybar
             >> database_values[index][3]//area
             >> database_values[index][4]//theta
             >> database_values[index][5]//p
             >> database_values[index][6];//E 

    // cout<< database_values[index][0]<<" "<<database_values[index][1]<<" "
    //          << database_values[index][2]<<" "<<database_values[index][3]<<" "
    //          << database_values[index][4]<<" "<<database_values[index][5]<<" "
    //          << database_values[index][6]<<endl;
             index++;

 }



  for (int i = 0; i <values.size(); ++i){

    cout<<endl<<"label: "<<i+1<<"   sum of x: "<<values[i][1]<<"   sum of y: "<<values[i][2]<<"  area: "<<values[i][0]<<endl;
    double xbar = (double)values[i][1]/values[i][0];
    double ybar = (double)values[i][2]/values[i][0];
    double area = values[i][0];
    cout<<"x̄: "<<xbar<<"   ȳ: "<<ybar<<endl;
    cout<< "a': "<< values[i][3]<<"  b': "<<2*values[i][4]<<"  c': "<<values[i][5]<<endl;
    // a'-(xbar^2*Area)
    double a = (values[i][3])-((xbar*xbar)*area);
    cout<<"a: "<< a;
    // b'-(2*xbar*ybar*area)
    double b = (2*values[i][4])-(2*(xbar*ybar*area));
    cout<<"  b: "<< b;
    // c'-(ybar^2*area)
    double c =(values[i][5])-((ybar*ybar)*area);
    cout<<"  c: "<< c <<endl;
    // calculating Theta
    double theta = (atan2 (b,(a-c)))/2;
    if (theta<0){
      theta+=PI;
    }
    cout<<"theta: "<<theta<<endl ;
    //calculating P
    double p = (ybar*cos(theta))-(xbar*sin(theta));
    cout <<"p: "<< p <<endl;
    //calculating the minimum moment of inertia
    double E = (a*(sin(theta)*sin(theta)))-(b*sin(theta)*cos(theta))+(c*(cos(theta)*cos(theta)));
    cout <<"E: "<<E<<endl;
    int y1 = (p+(xbar-30)*(sin(theta)))/cos(theta);
    int y2 = (p+(xbar+30)*(sin(theta)))/cos(theta);
    
    for (int z = 0;  z <database_values.size(); ++z){
        //calculate the presentage of the difference between areas
        double area_diff = (area-database_values[z][3])/area; 
        //calculate the presentage of the difference between E "minimum moment of inertia"       
        double E_diff = (E-database_values[z][6])/E;
        //if the difference is negative convert it to positive
        if (area_diff<0) {area_diff=area_diff*(-1);}
        if (E_diff<0) {E_diff=E_diff*(-1);}
        //if the differences is less than 15% of the value item is found
        if(area_diff<0.15 && E_diff<0.15){
          DrawLine(xbar-30, y1, xbar+30, y2, 20,&an_image); 
          DrawLine(xbar, ybar, xbar, ybar, 0,&an_image); 
        }
    }
 
  }

  database.close();
  an_image.SetNumberGrayLevels(values.size()); 


  
  
  if (!WriteImage(output_file, an_image)){
    cout << "Can't write to file " << output_file << endl;
    return 0;
  }
}
