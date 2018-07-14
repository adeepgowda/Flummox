//
//  fileretriever.h
//  CNC
//
//  Created by Adeep Gowda on 5/20/17.
//  Copyright © 2017 Adeep Gowda. All rights reserved.
//

#ifndef fileretriever_h
#define fileretriever_h

#include "errorfunction.h"

extern bool success_global;

struct file_properties_datatype
{
    unsigned int lines = 0;
    std::vector<std::string> cmd_reserve;
    
} input_file_properties;

file_properties_datatype file_read_function (std::string filename)
{
    unsigned int n = static_cast<unsigned int> (filename.length()), lines=0;
    std::ifstream userfile;
    std::string temp;
    
    if (((filename[n-1]=='x')&&(filename[n-2]=='f')&&(filename[n-3]=='.'))==false)      // Evaluating from right to left
        error(0, 0, 0);
    
    userfile.open(filename);
    
    if(userfile.is_open())
    {
        for (lines=0; std::getline(userfile, temp); ++lines)
            input_file_properties.cmd_reserve.push_back(temp);
        
        input_file_properties.lines = lines;
        userfile.close();
    }
    else
    {
        std::cout << "Operation Failed (read). The file may not exist.\n" << std::endl;
        success_global = false;
        userfile.close();
    }

    return input_file_properties;
}
// userfile.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); This can be used for skipping lines
#endif /* fileretriever_h */
