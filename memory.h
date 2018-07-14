//
//  memory.h
//  CNC
//
//  Created by Adeep Gowda on 7/11/18.
//  Copyright © 2018 Adeep Gowda. All rights reserved.
//

#ifndef memory_h
#define memory_h

struct memory_allocator_datatype
{
    bool success = false;
    unsigned int b=0;
    std::string varname;
    float varvalue=0;
    
} memory_allocator_variable;

memory_allocator_datatype memory_allocator_function(std::string cmd, unsigned int b, unsigned int i)
{
    unsigned int c=1;
    while ((cmd[b+c]!=',')&&(cmd[b+c]!='=')&&(cmd[b+c]!='\0')&&(cmd[b+c]!=' ')&&(cmd[b+c]!='\t'))
        ++c;
    --c;
    
    if(c!=0)
        memory_allocator_variable.varname = cmd.substr(b+1,c);
    else
        error(55555, b, i);
        
    b = b+c;
    if ((cmd[b+1]=='=')&&(b=b+1)&&(number_retriever_func(cmd, b, i, 55555, false).success == true))
    {
        b = number_retriever_variable.b;
        memory_allocator_variable.varvalue = number_retriever_variable.number;
    }

    memory_allocator_variable.b = b;
    memory_allocator_variable.success = true;
    
    return memory_allocator_variable;
}

#endif /* memory_h */
