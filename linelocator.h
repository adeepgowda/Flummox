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

std::string file_read_func(std::string filename, unsigned int linenumber)
{
    std::ifstream userfile;
    std::string fileread;
    unsigned long n = filename.length();

    if (((filename[n-1]=='x')&&(filename[n-2]=='f')&&(filename[n-3]=='.'))==false)      // Evaluating from right to left
    {
        error(0, 0, 0);
        return fileread;
    }
    userfile.open(filename);
    
    if (userfile.is_open())
    {
        for (int i=0; i <= linenumber; ++i)
        {
            if(i==linenumber)
                std::getline(userfile, fileread);
            else
                userfile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            // std::getline(userfile, fileread); can also be used for above sentence
        }
        userfile.close();
    }
    else
    {
        userfile.close();
        std::cout << "Operation Failed (read). The file may not exist.\n";
        success = false;
    }
    return fileread;
}

unsigned int numberoflines (std::string filename)
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
            lines++;
    else
        std::cout << "The file doesn't exist !!!" << std::endl;
    userfile.close();
    return lines;
}

#endif /* linelocator_h */
