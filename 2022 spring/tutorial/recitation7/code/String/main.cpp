#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>


int main() {
  //define the paths to the input and output file
  std::string inputPath("/Users/laurent/Documents/CS_100/Tutorial6/Problem1/data.txt");
  std::string outputPath("/Users/laurent/Documents/CS_100/Tutorial6/Problem1/data_reorg.txt");

  //open the input file
  std::ifstream inputFile;
  inputFile.open( inputPath );
  if( !inputFile )
    return -1;

  //read in the first line
  std::string line;
  std::getline( inputFile, line );

  //find out the number of columns
  std::stringstream lineOne(line);
  if( !lineOne )
    return -1;
  int numberColumns = 0;
  while( lineOne.good() ) {
    std::string dummy;
    lineOne >> dummy;
    numberColumns++;
  }

  //interact with the user to obtain a new order of the columns
  std::cout << "The number of columns is " << numberColumns << "\n";
  std::cout << "Please redefine the order of the columns:\n";
  std::vector<int> newIdx(numberColumns);
  for( int i = 0; i < numberColumns; i++ )
    std::cin >> newIdx[i];
  std::cout << "The new column order that you defined is: ";
  for( int i = 0; i < numberColumns; i++ )
    std::cout << newIdx[i] << " ";
  std::cout << "\n";

  //prepare the output file
  std::ofstream outputFile(outputPath);

  //loop through every line of the input file, store the elements,
  //and output them into the output file in the new order
  bool lastRun = false;
  do {
    if( !inputFile.good() )
      lastRun = true;

    //store the elements of this line
    std::stringstream linestream(line);
    std::vector<std::string> elements;
    for( int i = 0; i < numberColumns; i++ )
    {
      std::string nextElement;
      linestream >> nextElement;
      elements.push_back(nextElement);
    }

    //output them in the new order
    for( int i = 0; i < numberColumns; i++ )
      outputFile << elements[newIdx[i]] << " ";
    outputFile << "\n";

    //get new line
    std::getline( inputFile, line );
  } while( !lastRun );

  return 0;
}