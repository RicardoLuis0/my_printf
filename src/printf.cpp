#include "printf.h"

#include <iostream>
#include <sstream>
#include <typeinfo>

using namespace My;

int My::vprintf(const std::string & fmt,std::vector<std::shared_ptr<ValueContainer>> args){
    std::string temp=vsprintf(fmt,args);
    std::cout<<temp;
    return temp.size();
}

enum param_types{
    PARAM_NONE,
    PARAM_C,
    PARAM_LX,
    PARAM_UX,
    PARAM_LE,
    PARAM_UE,
};

struct param_data{
    bool valid;
    bool escape;
    bool has_pad;
    bool pad_zero;
    bool has_precision;
    bool has_index;
    size_t pad;
    size_t precision;
    size_t index;
    param_types type;
};

param_data parse_param(size_t &index,const std::string & fmt){
    param_data out {};
    if(fmt[index]=='%'){//percent escape
        index++;
        out.valid=true;
        out.escape=true;
        return out;
    }
    if(isdigit(fmt[index])){//
        size_t count=0;
        for(;isdigit(fmt[index+count]);count++);//find last digit, guaranteed to have count>0, since fmt[index] is always digit in this context
        out.pad_zero=fmt[index]=='0';
        out.has_pad=true;
        out.pad=stoul(fmt.substr(index,count));
        index+=count;
    }
    if(fmt[index]=='.'){
        index++;
        if(isdigit(fmt[index])){//
            size_t count=0;
            for(;isdigit(fmt[index+count]);count++);//find last digit, guaranteed to have count>0, since fmt[index] is always digit in this context
            out.has_precision=true;
            out.precision=stoul(fmt.substr(index,count));
            index+=count;
        }
    }
    switch(fmt[index]){
    case 'c':
        out.type=PARAM_C;
        break;
    case 'x':
        out.type=PARAM_LX;
        break;
    case 'X':
        out.type=PARAM_UX;
        break;
    case 'e':
        out.type=PARAM_LE;
        break;
    case 'E':
        out.type=PARAM_UE;
        break;
    case '{':
        out.type=PARAM_NONE;
        break;
    }
    if(fmt[index]=='{'){
        index++;
        size_t count=0;
        for(;isdigit(fmt[index+count]);count++);//find last digit, not guaranteed to have count>0, since fmt[index] might not digit in this context
        if(count>0){
            out.has_index=true;
            out.index=stoul(fmt.substr(index,count));
            index+=count;
        }
        if(fmt[index]=='}'){
            index++;
            out.valid=true;
            return out;//TODO
        }
    }
    out.valid=false;
    return out;
}

std::string format_param(param_data p,std::vector<std::shared_ptr<ValueContainer>> &args){
    if(p.escape)return "%";
    
    return "";//TODO
}

std::string My::vsprintf(const std::string & fmt,std::vector<std::shared_ptr<ValueContainer>> args){
    std::ostringstream out;//std::string out;
    size_t start=0;
    size_t index=0;
    for(size_t i=0;i<fmt.size();i++){
        if(fmt[i]=='%'){
            out<<fmt.substr(start,i-start);
            i++;//skip '%'
            auto param=parse_param(i,fmt);
            if(param.valid){
                if(!param.has_index)param.index=index++;
                out<<format_param(param,args);
            }
            start=i+1;
        }
    }
    if(start<fmt.size())out<<fmt.substr(start);
    return out.str();
}
