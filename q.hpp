// see specs
/*!*****************************************************************************
\File q.hpp
\Author Timothy Lee Ke xin
\Par DP email: timothykexin.lee@digipen.edu.sg
\Par Course: RSE 1202
\Par Section: Transitioning From C to C++ [Part 2]
\Par Programming Lab #2
\Date 20-01-2022

\Brief
  This program takes a text file with a sequence of Tsunami events and breaks 
  down the string of text in each line to its corresponding counter parts. 
  Namely, month, day, year, number of fatalities, height(m), and location. 
  These information can be seen from the struct Tsunami indicated in namespace
  hlp2.
  From the information gathered, the program will list out the tsunamis in a 
  certain format, and give a summary information such as max and average wave 
  height, locations and wave height of tsunamis greater than the average.
  This program consists of two functions as listed below:
  
  - read_tsunami_data
      Reads the contents of the given file_name text file to determine the 
      number of tsunami events and writes the count to the max_cnt parameter. 
      It then dynamically allocates an array of the struct type Tsunami as 
      created in q.hpp with max_cnt number of elements. It then copies the 
      corresponding elements to the dynamically allocated array. If the input
      text file cannot be opened, the program will return a nullptr, else, it 
      will return a pointer to the first element of the dynamically allocated 
      array.

  - print_tsunami_data
      This function, as its name suggests, prints out the corresponding 
      information to the output text file. denoted as file_name. This function
      also registers and prints the summary information such as max and average 
      wave height, locations and wave height of tsunamis greater than the 
      average.
      
*******************************************************************************/
#ifndef Q_HPP
#define Q_HPP

#include <string> // to use C++ standard library std::string type
#include <fstream> // to use C++ file I/O interface
namespace hlp2 {

    struct Tsunami {
        int MM, DD, YYYY, fatal;
        double height;
        std::string location;
    };
    

    Tsunami* read_tsunami_data(std::string const& file_name, int& max_cnt);
    void print_tsunami_data(Tsunami const *arr,
                            int size, std::string const& file_name);
} // end namespace hlp2
#endif
