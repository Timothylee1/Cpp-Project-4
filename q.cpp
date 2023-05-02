/*!*****************************************************************************
\File q.cpp
\Author Timothy Lee Ke xin
\Par DP email: timothykexin.lee@digipen.edu.sg
\Par Course: RSE 1202
\Par Section: Transitioning From C to C++ [Part 2]
\Par Programming Lab #2
\Date 20-01-2022

\Brief
  This program takes a text file with a sequence of Tsunami events and breaks 
  down the string of text in each line to its corresponding counter parts. 
  Namely, month, day, year, number of fatalities, height(m), and location. From 
  the information gathered, the program will list out the tsunamis in a 
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
#include <string>  // to use C++ standard library std::string type
#include <fstream> // to use C++ file I/O interface
#include <sstream>
#include "q.hpp"
#include <iomanip>

namespace hlp2 {

/******************************************************************************
/*! 
  \brief
    Reads the contents of the given file_name text file to determine the number
    of tsunami events and writes the count to the max_cnt parameter. It then 
    dynamically allocates an array of the struct type Tsunami as created in 
    q.hpp with max_cnt number of elements. It then copies the corresponding 
    elements to the dynamically allocated array. If the input text file cannot 
    be opened, the program will return a nullptr, else, it will return a pointer
    to the first element of the dynamically allocated array.

  \param file_name
  The name of the text file containing the tsunami event records.

  \param max_cnt
  The max count of tsunami events.

  \param ifs
  The fstream variable for the file associated to file_name.

  \param ch
  A char variable to read through each character of the text file.

  \param check_newl
  A boolean expression to determine if a newline has been detected.

  \param check_ch
  A boolean expression to determine if a character other than a newline has 
  been detected.

  \param ptr
  The dynamically allocated struct Tsunami array pointer. It also is the 
  return parameter.

  \param str_strm
  A stringstream variable which breaks down the line word by word.
  
  \param line
  A string variable that contains the entire line of text in the file_name file.
  
  \param tmp_line
  A string variable that collects the word from str_strm.
  
  \param destination
  A string variable that contains the location aspect of the tsunami events.
  
  \param temp_int
  A int variable that collects the int values of tmp_line.
  
  \param array_int
  An array of ints for assignment of month, day, year, number of fatalities.
  
  \param cnt
  A counter to check that array_int does not read and write from outside 
  allocated memory space.
  
  \param ptr
  The dynamically allocated struct Tsunami array pointer.
*******************************************************************************/
    Tsunami* read_tsunami_data(std::string const& file_name, int& max_cnt) {

        //check if file_name can be opened
        std::fstream ifs(file_name, std::ios_base::in);
        if (!ifs.is_open()) {                                           //check if 
            return nullptr;
        }
        char ch;
        bool check_newl = false, check_ch = false;
        max_cnt = 0;                                                    //initialise max_cnt
        while (ifs >> std::noskipws >> ch) {
            if (ch == '\n') {
                check_newl = true;
            }
            else {
                check_ch = true;
                check_newl = false;
            }

            if (check_newl && check_ch) {
                check_ch = false;
                check_newl = false;
                max_cnt++;
            }
        }
        struct Tsunami *ptr = { new Tsunami [max_cnt] }; 
        ifs.clear();                                                    //clear eof flag
        ifs.seekg(0, std::ios_base::beg);                               //move to beginning of file
        std::stringstream str_strm;
        std::string line, tmp_line, destination = "";
        int tmp_int, array_int[4] = {}, cnt = 0;
        
        for (int i = 0; i < max_cnt; i++) { 
            getline (ifs, line);
            str_strm << line;
            while (str_strm) {
                str_strm >> tmp_line;            
                if (tmp_line.find('.') != std::string::npos) {
                    (ptr+i)->height = std::stod(tmp_line);
                }
                else if (std::stringstream(tmp_line) >> tmp_int) {
                    if (cnt > 3)
                       (ptr+i)->height = tmp_int;
                    else 
                        array_int[cnt++] = tmp_int;
                }
                else {
                    destination.append(tmp_line);
                    destination.append(" ");
                }
                tmp_line = "";                                          //clear tmp string
            }
            destination.erase(destination.find_last_not_of(" ")+1);     //remove last char
            str_strm.clear();                                           //clear str_strm string
            (ptr+i)->MM = array_int[0];                                 //assign month
            (ptr+i)->DD = array_int[1];                                 //assign day
            (ptr+i)->YYYY = array_int[2];                               //assign year
            (ptr+i)->fatal = array_int[3];                              //assign num of fatalities
            (ptr+i)->location = destination;                            //assign location
            cnt = 0;                                                    //reset cnt
            destination = "";                                           //resent destination contents
        }
        
        ifs.close();
        return ptr;
    }    
   
/*!*****************************************************************************
\brief
   This function, as its name suggests, prints out the corresponding information
   to the output text file. denoted as file_name. This function also registers 
   and prints the summary information such as max and average wave height, 
   locations and wave height of tsunamis greater than the average.

\param file_name
  The name of the output text file for which the program will print to.

\param arr
  The read only pointer that signifies ptr from the previous function, which
  is the struct Tsunami dynamically allocated array.

\param size
  An int variable similar to the max_cnt of the previous function, which 
  represents the total number of tsunami events.

\param ofs
  The fstream variable for the file associated to file_name.

\param max
  A double variable that contains the maximum wave height.

\param total_height
  The total wave heights of all tsunami events.

\param avg
  A double variable of the average wave height of all events.

\param i
  An int that represents the number of times the loop has been completed.
*******************************************************************************/
    void print_tsunami_data(Tsunami const *arr,
                            int size, std::string const& file_name) {
        std::fstream ofs(file_name, std::ios_base::out);
                                   
        double max{}, total_height{}, avg{};
        ofs << "List of tsunamis:\n" << std::setw(18) << std::setfill('-');
        ofs << "\n";
        for (int i{}; i < size; i++) {
            ofs << std::setfill('0') << std::setw(2) << (arr+i)->MM << " " 
            << std::setfill('0') << std::setw(2) << (arr+i)->DD << " "
            << std::setw(4) << (arr+i)->YYYY << std::setfill(' ') 
            << std::setw(7) << std::right << (arr+i)->fatal 
            << std::setw(11) << std::right << std::fixed 
            << std::setprecision(2) << (arr+i)->height 
            << std::setw(5) << "     " << (arr+i)->location << '\n';
            max = max > (arr+i)->height ? max : (arr+i)->height;
            total_height += (arr+i)->height;
        }
        
        avg = total_height / size;
        ofs << "\nSummary information for tsunamis\n" << std::setw(34) 
        << std::setfill('-');
        ofs << "\n\n" << std::setfill(' ');
        ofs << "Maximum wave height (in meters): " << std::setprecision(2) 
        << std::right << std::setw(5) << max << "\n\n";
        ofs << "Average wave height (in meters): " << std::setprecision(2) 
        << std::right << std::setw(5) << avg << "\n\n";
        ofs << "Tsunamis with greater than average height " 
        << std::setprecision(2) << avg << ":\n";

        for (int i{}; i < size; ++i) {
            if (avg < ((arr+i)->height)) {
                ofs << std::left <<std::setprecision(2) << std::setw(10) 
                << std::setfill(' ') << (arr+i)->height 
                << (arr+i)->location << "\n";
            }
        }
        ofs.close();
    }

}