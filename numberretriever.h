//
//  numberretriever.h
//  CNC
//
//  Created by Adeep Gowda on 11/27/17.
//  Copyright © 2017 Adeep Gowda. All rights reserved.
//

#ifndef numberretriever_h
#define numberretriever_h

struct gcode_number_datatype
{
    unsigned int b=0;
    bool gcode_success = false;

} gcode_number_variable;

struct number_retriever_datatype
{
    bool success = false;
    unsigned int b;
    float number = 0;
    
} number_retriever_variable;

number_retriever_datatype number_retriever_func (std::string cmd, unsigned int b, unsigned int i, int error_reference, bool display)
{
    number_retriever_variable.success = false;
    number_retriever_variable.number = 0;
    bool decimal=false, minusign=false;
    unsigned int c=1;
    
    while ((std::isdigit(cmd[b+c])) || ((cmd[b+c]=='.')&&(decimal==false)&&(decimal=true)) || ((cmd[b+c]=='-')&&(minusign==false)&&(minusign=true)))
        ++c;
    --c;
    if(c==0)
        error(error_reference, b, i);
    else
    {
        float number = std::stof(cmd.substr(b+1,c));
        number_retriever_variable.b = b+c;
        number_retriever_variable.number = number;
        number_retriever_variable.success = true;
    }
    
    if(display==true)
        std::cout << number_retriever_variable.number << " ";

    return number_retriever_variable;
}

gcode_number_datatype number_gcode_func (std::string cmd, unsigned int b, unsigned int i, bool circleinter)
{
    gcode_number_variable.gcode_success = false;
    gcode_number_variable.b = 0;
    bool xdef=false,zdef=false,qdef=false,ydef=false,rdef=false;
    
    while((cmd[b+1]!=')')&&(success_global==true))
    {
        switch (cmd[b+1])
        {
            case 'X':
                if((xdef==false)&&(xdef=true)&&(++b)&&(std::cout << "X"))
                    { number_retriever_func(cmd, b, i, 55555,true); b = number_retriever_variable.b;}
                else error(55555, b, i);
                break;
                
            case 'Y':
                if((ydef==false)&&(ydef=true)&&(++b)&&(std::cout << "Y"))
                { number_retriever_func(cmd, b, i, 55555,true);  b = number_retriever_variable.b;}
                else error(55555, b, i);
                break;
                
            case 'Z':
                if((zdef==false)&&(zdef=true)&&(++b)&&(std::cout << "Z"))
                    { number_retriever_func(cmd, b, i, 55555,true); b = number_retriever_variable.b;}
                else error(55555, b, i);
                break;
                
            case 'R':
                if((rdef==false)&&(circleinter==true)&&(rdef=true)&&(++b)&&(std::cout << "R"))
                    { number_retriever_func(cmd, b, i, 55555,true); b = number_retriever_variable.b;}
                else error(55555, b, i);
                break;
                
            case 'r':
                if((rdef==false)&&(rdef=true)&&(++b)&&(std::cout << "r"))
                    { number_retriever_func(cmd, b, i, 55555,true); b = number_retriever_variable.b;}
                else error(55555, b, i);
                break;
                
            case 'Q':
                if((qdef==false)&&(qdef=true)&&(++b)&&(std::cout << "Q"))
                    { number_retriever_func(cmd, b, i, 55555,true); b = number_retriever_variable.b;}
                else error(55555, b, i);
                break;
                
            case ' ':
                ++b;
                break;
                
            case '\t':
                ++b;
                break;
                
            default:
                error(55555, b, i);
                break;
        }

    }
    gcode_number_variable.b = ++b;
    gcode_number_variable.gcode_success = true;
    
    return gcode_number_variable;
}

#endif /* numberretriever_h */
