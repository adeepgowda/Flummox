//
//  main.cpp
//  CNC
//
//  Created by Adeep Gowda on 5/10/17.
//  Copyright © 2017 Adeep Gowda. All rights reserved.
//

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cctype>
#include <vector>
#include <ctime>

#include "linelocator.h"
#include "errorfunction.h"
#include "numberretriever.h"

std::string float_to_string (float num);

std::string cmd_global;
bool success = true;

int main(int argc, const char * argv[])
{
    unsigned int lines=0, emptylines=0, i=0;
    std::string filename,cmd;
    std::vector<std::string> varname;
    std::vector<float> varvalue;
    bool spindledefine=false, tooldefine=false, definecood=false, defineunits=false, definitionpass=false;

    std::cout << "Enter the name of File : ";
        std::cin >> filename;
    std::cout << "Retrieving the file '" << filename << "'" << std::endl << std::endl;
    clock_t start = clock();

nxt:
try
    {
    lines = numberoflines(filename);
    for ( i=i; ((i<lines)&&(success==true)); ++i)
    {
        cmd = file_read_func(filename, i);
        cmd_global = cmd;

        if(cmd.length()!=0)
        {
            std::cout << "N" << (i+1-emptylines)*10 << " ";

            for (unsigned int b = 0; b < cmd.length(); ++b)
            {
                switch (cmd[b])
                {
                    case '#':
                        if ((cmd[b+1]=='d')&&(cmd[b+2]=='e')&&(cmd[b+3]=='f')&&(cmd[b+4]=='.')&&(b=b+4))
                        {
                            if ((cmd[b+1]=='a')&&(cmd[b+2]=='b')&&(cmd[b+3]=='s')&&(b=b+3)&&(definecood=true))
                            {
                                if ((cmd[b+1]=='\0')||(cmd[b+1]==' ')||(cmd[b+1]=='\t'))
                                    std::cout << "G90 ";
                                else if ((cmd[b+1]=='.')&&(cmd[b+2]=='i')&&(cmd[b+3]=='j')&&(cmd[b+4]=='k')&&(b=b+4))
                                    std::cout << "G90.1 ";
                                else error(2002,b,i);
                            }
                            else if ((((cmd[b+1]=='i')&&(cmd[b+2]=='m')&&(cmd[b+3]=='p')&&(b=b+3)) ||
                                    ((cmd[b+1]=='b')&&(cmd[b+2]=='r')&&(cmd[b+3]=='i')&&(cmd[b+4]=='t')&&(b=b+4)))&&(defineunits=true))
                                std::cout << "G20 ";
                            else if ((cmd[b+1]=='i')&&(cmd[b+2]=='n')&&(cmd[b+3]=='c')&&(b=b+3)&&(definecood=true))
                            {
                                if ((cmd[b+1]=='\0')||(cmd[b+1]==' ')||(cmd[b+1]=='\t'))
                                    std::cout << "G91 ";
                                else if ((cmd[b+1]=='.')&&(cmd[b+2]=='i')&&(cmd[b+3]=='j')&&(cmd[b+4]=='k')&&(b=b+4))
                                    std::cout << "G91.1 ";
                                else error(2003,b,i);
                            }
                            else if ((cmd[b+1]=='m')&&(cmd[b+2]=='k')&&(cmd[b+3]=='s')&&(b=b+3)&&(defineunits=true))
                                std::cout << "G21 ";
                            else error(2001,b,i);
                            if((definecood==true)&&(defineunits==true)&&(definitionpass=true)) //Check if all necessary terms are defined
                                ;
                        }
                        else error(2000,b,i);
                             break;
                    
                    case ' ': break;
                        
                    case '\t': break;
                        
                    case 'c':
                        if(definitionpass==true);   else error(0,b,i);
                        if ((cmd[b+1]=='h')&&(cmd[b+2]=='g')&&(cmd[b+3]=='.')&&(b=b+3))
                        {
                            unsigned int c=0;
                            std::string spindlespeed;
                            if ((cmd[b+1]=='S')&&(cmd[b+2]=='p')&&(cmd[b+3]=='e')&&(cmd[b+4]=='e')&&(cmd[b+5]=='d')&&(b=b+6)&&(spindledefine=true))
                            {
                                if ((cmd[b]=='.')&&(b=b+1))
                                {
                                    c=0;
                                    while ((cmd[b+c]!=',')&&(cmd[b+c]!='=')&&(cmd[b+c]!='\0')&&(cmd[b+c]!=' ')&(cmd[b+c]!='\t'))
                                        c++;
                                    if (std::find(varname.begin(),varname.end(),cmd.substr(b,c))!=varname.end())
                                    {
                                        long unsigned int pos = std::distance(varname.begin(),std::find(varname.begin(),varname.end(),cmd.substr(b,c)));
                                        spindlespeed = float_to_string(varvalue[pos]);
                                    }
                                    b=b+c;
                                }
                                else
                                {
                                    while(cmd[b]==' ') ++b;
                                    while (std::isdigit(cmd[c+b]))
                                        c++;
                                    if ((c==0)||(cmd[b]=='0'))
                                    {
                                        std::cout << "M05";     break;
                                    }
                                    spindlespeed = cmd.substr(b,c);
                                    b=b+c-1;
                                }
                                while(cmd[b+1]==' ') ++b;
                                if ((cmd[b+1]=='c') && (cmd[b+2]=='w')&&(b=b+2))
                                    std::cout << "M03 ";
                                else if ((cmd[b+1]=='c') && (cmd[b+2]=='c') && (cmd[b+3]=='w') && (b=b+3))
                                    std::cout << "M04 ";
                                else error(3002, b, i);
                                std::cout << "S" << spindlespeed;
                            }
                            else if ((cmd[b+1]=='T')&&(b=b+2)&&(tooldefine=true))
                            {
                                while (std::isdigit(cmd[c+b]))
                                    c++;
                                if(c==0)
                                    error(3003, b, i);
                                std::string toolchange = cmd.substr(b,c);
                                b=b+c;
                                std::cout << "M06 T" << toolchange;
                            }
                            else if((cmd[b+1]=='C')&&(cmd[b+2]=='o')&&(cmd[b+3]=='o')&&(cmd[b+4]=='l')&&(b=b+4))
                            {
                                if ((cmd[b+1]==' ')||(cmd[b+1]=='\0')||(cmd[b+1]=='\t'))
                                {
                                    std::cout << "M09";     break;
                                }
                                else if ((cmd[b+1]=='.')&&(cmd[b+2]=='M')&&(cmd[b+3]=='i')&&(cmd[b+4]=='s')&&(cmd[b+5]=='t')&&(b=b+5))
                                    std::cout << "M07";
                                else if ((cmd[b+1]=='.')&&(cmd[b+2]=='F')&&(cmd[b+3]=='l')&&(cmd[b+4]=='o')&&(cmd[b+5]=='o')&&(cmd[b+6]=='d')&&(b=b+6))
                                    std::cout << "M08";
                                else error(3004, b, i);
                            }
                            else error(3001, b, i);
                        }
                        else error(3000, b, i);
                        break;

                    case 'd':
                        if(definitionpass==true);   else error(0,b,i);
                        if ((cmd[b+1]=='e')&&(cmd[b+2]=='c')&&(cmd[b+3]=='l')&&(cmd[b+4]=='.')&&(b=b+4))
                        {
                            if ((cmd[b+1]=='v')&&(cmd[b+2]=='a')&&(cmd[b+3]=='r')&&(cmd[b+4]==' ')&&(b=b+4))
                            {
                                if(cmd[b+1]=='\0')
                                    error(55555,b,i);
                                while ((cmd[b+1]!=' ')&&(cmd[b+1]!='\0')&&(b=b+1))
                                {
                                    unsigned int c=0;
                                    while ((cmd[b+c]!=',')&&(cmd[b+c]!='=')&&(cmd[b+c]!='\0')&&(cmd[b+c]!=' ')&&(cmd[b+c]!='\t'))
                                        c++;
                                    if(c!=0)
                                        varname.push_back(cmd.substr(b,c));
                                    b=b+c;
                                    
                                    if ((cmd[b]=='=')&&(b=b+1))
                                    {
                                        c=0;
                                        while (std::isdigit(cmd[b+c]))
                                            c++;
                                        if (c==0)
                                        {
                                            std:: cout << "Enter A Valid Number !!!" << std::endl;
                                            error(55555,b,i);
                                        }
                                        varvalue.push_back(std::atof((cmd.substr(b,c)).c_str()));
                                        b=b+c;
                                    }
                                }
                            }
                            else error(55555,b,i);
                        }
                        else error(55555,b,i);
                        break;
                        
                    case 'm':
                        if(definitionpass==true);   else error(0,b,i);
                        if((cmd[b+1]=='o')&&(cmd[b+2]=='v')&&(cmd[b+3]=='.')&&(b=b+3))
                        {
                            bool circleinter=false;
                            
                            if((cmd[b+1]=='a')&&(cmd[b+2]=='b')&&(cmd[b+3]=='s')&&(cmd[b+4]=='(')&&(b=b+4))
                                std::cout << "G00 ";
                            else if((cmd[b+1]=='l')&&(cmd[b+2]=='i')&&(cmd[b+3]=='n')&&(cmd[b+4]=='(')&&(b=b+4))
                                std::cout << "G01 ";
                            else if((cmd[b+1]=='c')&&(cmd[b+2]=='l')&&(cmd[b+3]=='o')&&(cmd[b+4]=='c')&&(cmd[b+5]=='(')&&(circleinter=true)&&(b=b+5))
                                std::cout << "G02 ";
                            else if((cmd[b+1]=='a')&&(cmd[b+2]=='c')&&(cmd[b+3]=='l')&&(cmd[b+4]=='o')&&(cmd[b+5]=='c')&&(cmd[b+6]=='(')&&(circleinter=true)&&(b=b+6))
                                std::cout << "G03 ";
                            else error(55555,b,i);

                            if(number_gcode_func(b, i, cmd, circleinter).gcode_success==true)
                            {
                                b = number_gcode_variable.b;
                                i = number_gcode_variable.i;
                            } else { std::cout << "Came"; goto exit; }
                        }
                        else error(55555,b,i);
                        break;
                        
                    case 's':
                        if(definitionpass==true);   else error(0,b,i);
                        if((cmd[b+1]=='t')&&(cmd[b+2]=='d')&&(cmd[b+3]=='.')&&(b=b+3))
                        {
                            if((cmd[b+1]=='c')&&(cmd[b+2]=='a')&&(cmd[b+3]=='n')&&(cmd[b+4]=='(')&&(b=b+4))
                            {
                                std::cout << "G77 ";
                                if(number_gcode_func(b, i, cmd, false).gcode_success==true)
                                {
                                    b = number_gcode_variable.b;
                                    i = number_gcode_variable.i;
                                } else goto exit;
                            }
                            else error(55555,b,i);
                            std::cout << std::endl << "N" << ((i+1-emptylines)*10+5) <<" G80";
                        }
                        else error(55555,b,i);
                        break;
                        
                    case 'E':
                        if(definitionpass==true);   else error(0,b,i);
                        if ((cmd[b+1]=='O')&&(cmd[b+2]=='P')&&(b=b+2))
                            if ((cmd[b+1]=='.')&&(cmd[b+2]=='R')&&(cmd[b+3]=='e')&&(cmd[b+4]=='t')&&(cmd[b+5]=='u')&&(cmd[b+6]=='r')&&(cmd[b+7]=='n')&&(b=b+7))
                            {
                                std::cout << "M30" << std::endl;
                                goto exit;
                            }
                            else std::cout << "M02 ";
                        else if((cmd[b+1]=='O')&&(cmd[b+2]=='O')&&(b=b+2))
                            std::cout << "M00 ";
                        else error(55555,b,i);
                        break;
                    
                    case '\0': break;
                    
                    case'/':
                        if(cmd[b+1]=='/')
                            b = static_cast<unsigned int>(cmd.length());    // Intentionally causing the for condtion to fail to exit the loop
                        break;

                    default:
                        error(55555, b, i);
                }                               // Ending of the switch (cmd[b]) i.e., evaluates each letter in the string 'cmd'
            }                                   // Ending of the for (unsigned int b = 0; b < cmd.length(); ++b)
            std::cout << std::endl;
        }                                       // Ending of the if(cmd.length()!=0) i.e., check if the loaded string 'cmd' is empty or not
        else emptylines++;
        
    }                                           // Ending of the for (unsigned int i = 0; ((i<lines)&&(success==true)); ++i) i.e., line evaluator
    }                                           // Ending of the try block
    
    catch (int exp)
    {
        ++i;
        switch (exp)
        {
            case 0:
                std::cout << "Exiting the program";
                break;
            
            case 1:
                goto nxt;
                break;
                
            default:
                break;
        }
        if (exp == 0)
            goto exit;
        else
            goto nxt;
    }
    
exit:
    if(success==true)
    {
        clock_t end = clock();
        unsigned int runtime = unsigned((end-start)*1000000)/CLOCKS_PER_SEC;
        std::cout << std::endl;
        std::cout << std::endl << "The Program Has Been Generated Successfully. (Runtime = "<< runtime << " microseconds)" << std::endl;
    }
    return 0;
}                                               // Ending of main function

std::string float_to_string (float num)
{
    std::ostringstream buffer;
    buffer << num;
    return buffer.str();
}

// usefile.open("location", ios::in); use this for reading a file from a specific path
// use std::to_string(arg) for the above function
// seperate the function out from the main switch case, lik in std.can
// declare std as the class and the 'can' as one of the functions in it
