//
//  linelocator.h
//  CNC
//
//  Created by Adeep Gowda on 5/20/17.
//  Copyright © 2017 Adeep Gowda. All rights reserved.
//

#ifndef linelocator_h
#define linelocator_h

#include "errorfunction.h"

extern bool success;

unsigned int number_of_lines_func (std::string filename)
{
    unsigned int lines=0;
    unsigned long n = filename.length();
    
    if (((filename[n-1]=='x')&&(filename[n-2]=='f')&&(filename[n-3]=='.'))==false)      // Evaluating from right to left
    {
        error(0, 0, 0);
        return lines;
    }

    std::string fileread;
    std::ifstream userfile;
        userfile.open(filename);
    
    if (userfile.is_open())
        while (std::getline(userfile, fileread))
            ++lines;
    else
        std::cout << "The file doesn't exist !!!" << std::endl;
    userfile.close();
    return lines;
}

std::vector<std::string> file_read_func (std::string filename, unsigned int lines)
{
    std::ifstream userfile;
    std::string temp;
    std::vector<std::string> cmd_reserve;
    unsigned long n = filename.length();
    
    userfile.open(filename);
    
    if (((filename[n-1]=='x')&&(filename[n-2]=='f')&&(filename[n-3]=='.'))==false)      // Evaluating from right to left
    {
        error(0, 0, 0);
        return cmd_reserve;
    }
    
    if(userfile.is_open())
    {
        for (int i=0; i<lines; ++i)
        {
            std::getline(userfile, temp);
            cmd_reserve.push_back(temp);
        }
        userfile.close();
    }
    else
    {
        std::cout << "Operation Failed (read). The file may not exist.\n";
        success = false;
        userfile.close();
    }
    return cmd_reserve;
}
// userfile.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); This can be used for skipping lines
#endif /* linelocator_h */
