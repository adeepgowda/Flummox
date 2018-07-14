//
//  errorfunction.h
//  CNC
//
//  Created by Adeep Gowda on 8/24/17.
//  Copyright © 2017 Adeep Gowda. All rights reserved.
//

#ifndef errorfunction_h
#define errorfunction_h

//
//Primary Error = Errors which are concerned with the actions performed pre-translation of languages. Ex.: File extension error, file not found, etc.
//Secondary Error = Errors which are concerned with the pure mechanism of translation of languages. Ex.: Syntax errors, etc.
//

extern bool success_global;
extern std::string cmd_global;

void error (int errorcode, unsigned int b, unsigned int i)
{
    bool skip = false;
    std::string cmd = cmd_global;
    if(errorcode!= 1)
        std::cout << std::endl << std::endl << "        Error " << errorcode << " : ";
    
    switch (errorcode)
    {
        case 1:
            skip = true;
            break;
            
        // Relating to all primary errors from this point on
        case 0:
            std::cout << "File Extension Error !!!";
            break;
            
        case 1000:
            std::cout << "Syntax Error / Function Not Available.";
            break;
            
        case 1001:
            std::cout << "Define the co-ordinate parameter & the measurement parameter.";
            break;
            
        case 2000:
            std::cout << "Syntax Error, Available Functions - Define";
            break;
        
        case 2001:
            std::cout << "Syntax Error, Available Functions - Absloute, Incremental with IJK & Metric, Imperial Units";
            break;
            
        case 2002:
            std::cout << "Define the ABSOLUTE positioning function correctly.";
            break;
            
        case 2003:
            std::cout << "Define the INCREMENTAL positioning function correctly.";
            break;
            
        // Relating to all functions from letter 'c' from this point on
            
        case 3000:
            std::cout << "Syntax Error, Available Functions - Change";
            break;
        
        case 3001:
            std::cout << "Syntax Error, Available Functions - Speed, Tool, Coolant";
            break;
            
        case 3002:
            std::cout << "Define the SPEED function correctly.";
            break;
            
        case 3003:
            std::cout << "Define the TOOL function correctly.";
            break;
            
        case 3004:
            std::cout << "Define the COOLANT function correctly.";
            break;
        
        case 55555:
            std::cout << "Experimental.";
            break;
        
        default:
            std::cout << "Error Code Not Recognized, Contact Dev.";
            break;
    }
    
    if((b!=0) && (i!=0) && (skip == false))
    {
        std::cout << std::endl << "        At line "<< i+1 << " & at position " << b+1 << "." << std::endl;
        std::cout << std::endl << "        " << cmd << std::endl;
        
        for (unsigned int e = 0; e!=(b+8); ++e)
            std::cout << " ";
        std::cout << "^" << std::endl;
        
        for (unsigned int e = 0; e!=(b+8); ++e)
            std::cout << " ";
        std::cout << "Here" << std::endl << std::endl;
    }
    
    if ((errorcode >= 1000) && (skip == false))              // Check if the error made is primary or secondary and enter only if error is secondary
        throw 1;                                             // and throw the exception_code
    else
    {
        if (skip == false)
        {
            success_global=false;
            throw 0;
        }
    }
}

#endif /*errorfunction_h */
