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

std::string floattostring (float num);

int main(int argc, const char * argv[])
{
    unsigned int lines=0, emptylines=0;
    std::string filename,cmd;
    std::vector<std::string> varname;
    std::vector<float> varvalue;
    bool spindledefine=false, tooldefine=false, definecood=false, definemeasure=false, definitionpass=false;
    
    std::cout << "Enter the name of File : ";
        std::cin >> filename;
    clock_t start = clock();
    lines = numberoflines(filename);

    for (unsigned int i=0; i<lines; i++)
    {
        def: cmd = file_read_func(filename, i);
                
        if(cmd.length()!=0)
        {
            std::cout << "N" << (i+1-emptylines)*10 << " ";

            for (unsigned int b=0; (b < cmd.length()&&(cmd[b]!=EOF)); b++)
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
                                else { error(2002,b,i); return 0; }
                            }
                            else if ((((cmd[b+1]=='i')&&(cmd[b+2]=='m')&&(cmd[b+3]=='p')&&(b=b+3)) ||
                                    ((cmd[b+1]=='b')&&(cmd[b+2]=='r')&&(cmd[b+3]=='i')&&(cmd[b+4]=='t')&&(b=b+4)))&&(definemeasure=true))
                                std::cout << "G20 ";
                            else if ((cmd[b+1]=='i')&&(cmd[b+2]=='n')&&(cmd[b+3]=='c')&&(b=b+3)&&(definecood=true))
                            {
                                if ((cmd[b+1]=='\0')||(cmd[b+1]==' ')||(cmd[b+1]=='\t'))
                                    std::cout << "G91 ";
                                else if ((cmd[b+1]=='.')&&(cmd[b+2]=='i')&&(cmd[b+3]=='j')&&(cmd[b+4]=='k')&&(b=b+4))
                                    std::cout << "G91.1 ";
                                else { error(2003,b,i); return 0; }
                            }
                            else if ((cmd[b+1]=='m')&&(cmd[b+2]=='k')&&(cmd[b+3]=='s')&&(b=b+3)&&(definemeasure=true))
                                std::cout << "G21 ";
                            else { error(2001,b,i); return 0; }
                        }
                        else { error(2000,b,i); return 0; }
                        break;
                    
                    case ' ': break;
                        
                    case '\t': break;
                        
                    case 'c':
                        if((definecood==true)&&(definemeasure==true)&&(definitionpass=true));   else {error(0,b,i); return 0;}
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
                                        spindlespeed = floattostring(varvalue[pos]);
                                    }
                                    b=b+c;
                                }
                                else
                                {
                                    while(cmd[b]==' ') b++;
                                    while (std::isdigit(cmd[c+b]))
                                        c++;
                                    if ((c==0)||(cmd[b]=='0'))
                                    {
                                        std::cout << "M05";     break;
                                    }
                                    spindlespeed = cmd.substr(b,c);
                                    b=b+c-1;
                                }
                                while(cmd[b+1]==' ') b++;
                                if ((cmd[b+1]=='c') && (cmd[b+2]=='w')&&(b=b+2))
                                    std::cout << "M03 ";
                                else if ((cmd[b+1]=='c') && (cmd[b+2]=='c') && (cmd[b+3]=='w') && (b=b+3))
                                    std::cout << "M04 ";
                                else { error(3002, b, i); return 0; }
                                std::cout << "S" << spindlespeed;
                            }
                            else if ((cmd[b+1]=='T')&&(b=b+2)&&(tooldefine=true))
                            {
                                while (std::isdigit(cmd[c+b]))
                                    c++;
                                if(c==0)
                                    { error(3003, b, i); return 0; }
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
                                else { error(3004, b, i); return 0; }
                            }
                            else { error(3001, b, i); return 0; }
                        }
                        else { error(3000, b, i); return 0; }
                        break;

                    case 'd':
                        if((definecood==true)&&(definemeasure==true)&&(definitionpass=true));   else {error(0,b,i); return 0;}
                        if ((cmd[b+1]=='e')&&(cmd[b+2]=='c')&&(cmd[b+3]=='l')&&(cmd[b+4]=='.')&&(b=b+4))
                        {
                            if ((cmd[b+1]=='v')&&(cmd[b+2]=='a')&&(cmd[b+3]=='r')&&(cmd[b+4]==' ')&&(b=b+4))
                            {
                                if(cmd[b+1]=='\0') goto error;
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
                                            goto error;
                                        }
                                        varvalue.push_back(std::atof((cmd.substr(b,c)).c_str()));
                                        b=b+c;
                                    }
                                }
                            }
                            else goto error;
                        }
                        else goto error;
                        break;
                        
                    case 'm':
                        if((definecood==true)&&(definemeasure==true)&&(definitionpass=true));   else {error(0,b,i); return 0;}
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
                            else goto error;

                            number_gcode_func(b, i, cmd, circleinter);
                            b = number_gcode_variable.b;
                            i = number_gcode_variable.i;
                        }
                        else goto error;
                        break;
                        
                    case 's':
                        if((definecood==true)&&(definemeasure==true)&&(definitionpass=true));   else {error(0,b,i); return 0;}
                        if((cmd[b+1]=='t')&&(cmd[b+2]=='d')&&(cmd[b+3]=='.')&&(b=b+3))
                        {
                            if((cmd[b+1]=='c')&&(cmd[b+2]=='a')&&(cmd[b+3]=='n')&&(cmd[b+4]=='(')&&(b=b+4))
                            {
                                std::cout << "G77 ";
                                number_gcode_func(b, i, cmd, false);
                                b = number_gcode_variable.b;
                                i = number_gcode_variable.i;
                            }
                            else goto error;
                            std::cout << std::endl << "N" << ((i+1-emptylines)*10+5) <<" G80";
                        }
                        else goto error;
                        break;
                        
                    case 'E':
                        if((definecood==true)&&(definemeasure==true)&&(definitionpass=true));   else {error(0,b,i); return 0;}
                        if ((cmd[b+1]=='O')&&(cmd[b+2]=='P')&&(b=b+2))
                            if ((cmd[b+1]=='.')&&(cmd[b+2]=='R')&&(cmd[b+3]=='e')&&(cmd[b+4]=='t')&&(b=b+4))
                            {
                                std::cout << "M30" << std::endl;
                                goto exit;
                            }
                            else std::cout << "M02 ";
                        else if((cmd[b+1]=='O')&&(cmd[b+2]=='O')&&(b=b+2))
                            std::cout << "M00 ";
                        else goto error;
                        break;
                    
                    case '\0': break;
                    
                    case'/':
                        if(cmd[b+1]=='/')
                        {
                            i++;
                            std::cout << std::endl;
                            goto def;
                        }

                    default: error:
                        if (definitionpass==false)
                            std::cout<< std::endl << "Define the co-ordinate parameter & the measurement parameter." << std::endl;
                        else
                        {
                            std::cout << std::endl << "Syntax Error : ";
                            std::cout << "At line "<< i+1 << " & at position " << b+1 << "." << std::endl;
                            std:: cout << cmd[b] << std::endl;
                        }
                        return 0;
                }
            }
            std::cout << std::endl;
        }
        else emptylines++;
    }
    
exit:
    clock_t end = clock();
    unsigned int runtime = unsigned((end-start)*1000000)/CLOCKS_PER_SEC;
    std::cout << "The Program Has Been Generated Successfully. (Runtime = "<< runtime << " microseconds)" << std::endl;
    return 0;
}

std::string floattostring (float num)
{
    std::ostringstream buffer;
    buffer << num;
    return buffer.str();
}

// usefile.open("location", ios::in); use this for reading a file from a specific path\
