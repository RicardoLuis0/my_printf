#include "printf.h"

#include <iostream>
#include <iomanip>
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
    PARAM_F,
    PARAM_LX,
    PARAM_UX,
    PARAM_LE,
    PARAM_UE,
};

struct param_data{
    bool valid;
    bool escape;
    bool has_size;
    bool pad_zero;
    bool has_precision;
    bool has_index;
    size_t size;
    size_t precision;
    size_t index;
    param_types type;
};

param_data parse_param(size_t &index,const std::string & fmt){
    param_data out {};
    if(fmt[index]=='%'){//percent escape
        out.valid=true;
        out.escape=true;
        return out;
    }
    if(isdigit(fmt[index])){//
        size_t count=0;
        for(;isdigit(fmt[index+count]);count++);//find last digit, guaranteed to have count>0, since fmt[index] is always digit in this context
        out.pad_zero=fmt[index]=='0';
        out.has_size=true;
        out.size=stoul(fmt.substr(index,count));
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
    case 'f':
        out.type=PARAM_F;
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
            out.valid=true;
            return out;//TODO
        }
    }
    out.valid=false;
    return out;
}

void format_stream(param_data p,std::ostringstream &o){
    if(p.has_precision){
        o<<std::setprecision(p.precision);
    }
    switch(p.type){
    default:
        break;
    case PARAM_F:
        o<<std::fixed;
        break;
    case PARAM_UX:
        o<<std::uppercase;
    case PARAM_LX:
        o<<std::hex;
        break;
    case PARAM_UE:
        o<<std::uppercase;
    case PARAM_LE:
        o<<std::scientific;
        break;
    }
    if(p.has_size){
        o<<std::setfill(p.pad_zero?'0':' ');
        o<<std::setw(p.size);
    }
}

std::string format_param(param_data p,std::vector<std::shared_ptr<ValueContainer>> &args){
    if(p.escape)return "%";
    if(auto s=std::dynamic_pointer_cast<StringContainer>(args[p.index])){
        const std::string & str=s->getString();
        if(p.has_size){
            if(p.size>str.size()){
                return std::string(p.size-str.size(),' ')+str;
            }else{
                return str.substr(0,p.size);
            }
        }else{
            return std::string(str);
        }
    }else if(auto s=std::dynamic_pointer_cast<CStringContainer>(args[p.index])){
        std::string str(s->getCString());
        if(p.has_size){
            if(p.size>str.size()){
                return std::string(p.size-str.size(),' ')+str;
            }else{
                return str.substr(0,p.size);
            }
        }else{
            return str;
        }
    }else if(auto f=std::dynamic_pointer_cast<FloatContainer>(args[p.index])){
        std::ostringstream fmt;
        format_stream(p,fmt);
        fmt<<f->getFloat();
        return fmt.str();
    }else if(auto d=std::dynamic_pointer_cast<DoubleContainer>(args[p.index])){
        std::ostringstream fmt;
        format_stream(p,fmt);
        fmt<<d->getDouble();
        return fmt.str();
    }else if(auto i8=std::dynamic_pointer_cast<Int8Container>(args[p.index])){
        if(p.type==PARAM_C){
            return std::string(1,(char)i8->getInt8());
        }else{
            std::ostringstream fmt;
            format_stream(p,fmt);
            fmt<<i8->getInt8();
            return fmt.str();
        }
    }else if(auto ui8=std::dynamic_pointer_cast<UInt8Container>(args[p.index])){
        if(p.type==PARAM_C){
            return std::string(1,(unsigned char)ui8->getUInt8());
        }else{
            std::ostringstream fmt;
            format_stream(p,fmt);
            fmt<<ui8->getUInt8();
            return fmt.str();
        }
    }else if(auto i16=std::dynamic_pointer_cast<Int16Container>(args[p.index])){
        if(p.type==PARAM_C){
            return std::string(1,(char)i16->getInt16());
        }else{
            std::ostringstream fmt;
            format_stream(p,fmt);
            fmt<<i16->getInt16();
            return fmt.str();
        }
    }else if(auto ui16=std::dynamic_pointer_cast<UInt16Container>(args[p.index])){
        if(p.type==PARAM_C){
            return std::string(1,(unsigned char)ui16->getUInt16());
        }else{
            std::ostringstream fmt;
            format_stream(p,fmt);
            fmt<<ui16->getUInt16();
            return fmt.str();
        }
    }else if(auto i32=std::dynamic_pointer_cast<Int32Container>(args[p.index])){
        if(p.type==PARAM_C){
            return std::string(1,(char)i32->getInt32());
        }else{
            std::ostringstream fmt;
            format_stream(p,fmt);
            fmt<<i32->getInt32();
            return fmt.str();
        }
    }else if(auto ui32=std::dynamic_pointer_cast<UInt32Container>(args[p.index])){
        if(p.type==PARAM_C){
            return std::string(1,(unsigned char)ui32->getUInt32());
        }else{
            std::ostringstream fmt;
            format_stream(p,fmt);
            fmt<<ui32->getUInt32();
            return fmt.str();
        }
    }else if(auto i64=std::dynamic_pointer_cast<Int64Container>(args[p.index])){
        if(p.type==PARAM_C){
            return std::string(1,(char)i64->getInt64());
        }else{
            std::ostringstream fmt;
            format_stream(p,fmt);
            fmt<<i64->getInt64();
            return fmt.str();
        }
    }else if(auto ui64=std::dynamic_pointer_cast<UInt64Container>(args[p.index])){
        if(p.type==PARAM_C){
            return std::string(1,(unsigned char)ui64->getUInt64());
        }else{
            std::ostringstream fmt;
            format_stream(p,fmt);
            fmt<<ui64->getUInt64();
            return fmt.str();
        }
    }else if(auto vp=std::dynamic_pointer_cast<PointerContainer>(args[p.index])){
        std::ostringstream fmt;
        fmt<<vp->getPointer();
        return fmt.str();
    }else{
        //unknown type
        throw std::runtime_error("unknown object class");
    }
}

std::string My::vsprintf(const std::string & fmt,std::vector<std::shared_ptr<ValueContainer>> args){
    std::ostringstream out;//std::string out;
    size_t start=0;
    size_t index=0;
    size_t param_num=1;
    for(size_t i=0;i<fmt.size();i++){
        if(fmt[i]=='%'){
            out<<fmt.substr(start,i-start);
            i++;//skip '%'
            auto param=parse_param(i,fmt);
            if(param.valid){
                param_num++;
                if(!param.has_index)param.index=index++;
                out<<format_param(param,args);
            }else{
                throw std::runtime_error("invalid format string parameter "+std::to_string(param_num));
            }
            start=i+1;
        }
    }
    if(start<fmt.size())out<<fmt.substr(start);
    return out.str();
}
