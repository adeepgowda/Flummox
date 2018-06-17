//
//  numberretriever.h
//  CNC
//
//  Created by Adeep Gowda on 11/27/17.
//  Copyright © 2017 Adeep Gowda. All rights reserved.
//

#ifndef numberretriever_h
#define numberretriever_h

struct number_gcode_datatype
{
    unsigned int b=0, i=0;
} number_gcode_variable;

struct number_retriever_datatype
{
    unsigned int b;
    std::string number;
} number_retriever_variable;

number_retriever_datatype number_retriever_func (std::string cmd, unsigned int b, bool display)
{
    bool decimal=false, minusign=false;
    unsigned int c=1;
    while ((std::isdigit(cmd[b+c])) || ((cmd[b+c]=='.')&&(decimal==false)&&(decimal=true)) ||
           ((cmd[b+c]=='-')&&(minusign==false)&&(minusign=true)))
        c++;
    
    std::string number = cmd.substr(b,c);
    number_retriever_variable.b = b+c-1;
    number_retriever_variable.number = number;
    
    if(display==true)
        std::cout << number_retriever_variable.number << " ";

    return number_retriever_variable;
}

number_gcode_datatype number_gcode_func (unsigned int b, unsigned int i, std::string cmd, bool circleinter)
{
    bool xdef=false,zdef=false,qdef=false,ydef=false,rdef=false;
    while((cmd[b+1]!=')'))
    {
        switch (cmd[b+1])
        {
            case 'X':
                if((xdef==false)&&(xdef=true)&&(b++))
                    { number_retriever_func(cmd, b, true); b = number_retriever_variable.b;}
                else error(55555, b, i);
                break;
                
            case 'Y':
                if((ydef==false)&&(ydef=true)&&(b++))
                { number_retriever_func(cmd, b,true);  b = number_retriever_variable.b;}
                else error(55555, b, i);
                break;
                
            case 'Z':
                if((zdef==false)&&(zdef=true)&&(b++))
                    { number_retriever_func(cmd, b,true); b = number_retriever_variable.b;}
                else error(55555, b, i);
                break;
                
            case 'R':
                if((rdef==false)&&(circleinter==true)&&(rdef=true)&&(b++))
                    { number_retriever_func(cmd, b, true); b = number_retriever_variable.b;}
                else error(55555, b, i);
                break;
                
            case 'r':
                if((rdef==false)&&(rdef=true)&&(b++))
                    { number_retriever_func(cmd, b, true); b = number_retriever_variable.b;}
                else error(55555, b, i);
                break;
                
            case 'Q':
                if((qdef==false)&&(qdef=true)&&(b++))
                    { number_retriever_func(cmd, b, true); b = number_retriever_variable.b;}
                else error(55555, b, i);
                break;
                
            case ' ':
                b++;
                break;
                
            case '\t':
                b++;
                break;
                
            default:
                error(55555, b, i);
                break;
        }

    }
    number_gcode_variable.b = b+1;
    number_gcode_variable.i = i;
    
    return number_gcode_variable;
}

#endif /* numberretriever_h */
