//
//  errorfunction.h
//  CNC
//
//  Created by Adeep Gowda on 8/24/17.
//  Copyright © 2017 Adeep Gowda. All rights reserved.
//

#ifndef errorfunction_h
#define errorfunction_h

void error (int errorcode, unsigned int b, unsigned int i)
{
    switch (errorcode)
    {
        case -1:
            std::cout << std::endl << "Error -1 : File Extension Error !!!" << std::endl;
            break;
            
        case 0:
            std::cout << std::endl << "Error 0 : Define the co-ordinate parameter & the measurement parameter." << std::endl;
            break;
            
        case 1000:
            std::cout << std::endl << "Error 1000 : Syntax Error / Function Not Available." << std::endl;
            break;
            
        case 2000:
            std::cout << std::endl << "Error 2000 : Syntax Error, Available Functions - Define" << std::endl;
            break;
        
        case 2001:
            std::cout << std::endl << "Error 2001 : Syntax Error, Available Functions - Absloute, Incremental with IJK & Metric, Imperial Units" << std::endl;
            break;
            
        case 2002:
            std::cout << std::endl << "Error 2002 : Define the ABSOLUTE positioning function correctly." << std::endl;
            break;
            
        case 2003:
            std::cout << std::endl << "Error 2003 : Define the INCREMENTAL positioning function correctly." << std::endl;
            break;
            
        // Relating to all functions from letter 'c' this point on
            
        case 3000:
            std::cout << std::endl << "Error 3000 : Syntax Error, Available Functions - Change" << std::endl;
            break;
        
        case 3001:
            std::cout << std::endl << "Error 3001 : Syntax Error, Available Functions - Speed, Tool, Coolant" << std::endl;
            break;
            
        case 3002:
            std::cout << std::endl << "Error 3002 : Define the SPEED function correctly." << std::endl;
            break;
            
        case 3003:
            std::cout << std::endl << "Error 3003 : Define the TOOL function correctly." << std::endl;
            break;
            
        case 3004:
            std::cout << std::endl << "Error 3004 : Define the COOLANT function correctly." << std::endl;
            break;
        
        case 55555:
            std::cout << std::endl << "Error 5555 : Experimental." << std::endl;
            break;
        
        default:
            std::cout << std::endl << "Error Code Not Recognized, Contact Dev." << std::endl;
            break;
    }
    if((b!=0) && (i!=0))
        std::cout << "At line "<< i+1 << " & at position " << b+1 << "." << std::endl;
}

#endif /*errorfunction_h */
