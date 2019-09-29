#include "printf.h"

#include <iostream>
#include <typeinfo>

using namespace My;

int My::vprintf(const std::string fmt,std::vector<std::shared_ptr<ValueContainer>> args){
    std::string temp=vsprintf(fmt,args);
    std::cout<<temp;
    return temp.size();
}

std::string My::vsprintf(const std::string fmt,std::vector<std::shared_ptr<ValueContainer>> args){
    //for testing, printing TODO
    std::cout<<"types:";
    for(std::shared_ptr<ValueContainer> arg:args){
        if(std::dynamic_pointer_cast<IntContainer>(arg)){
            std::cout<<"int"<<std::endl;
        }else if(std::dynamic_pointer_cast<UIntContainer>(arg)){
            std::cout<<"uint"<<std::endl;
        }else if(std::dynamic_pointer_cast<CharContainer>(arg)){
            std::cout<<"char"<<std::endl;
        }else if(std::dynamic_pointer_cast<StringContainer>(arg)){
            std::cout<<"string"<<std::endl;   
        }else if(std::dynamic_pointer_cast<CStringContainer>(arg)){
            std::cout<<"cstring"<<std::endl;
        }else if(std::dynamic_pointer_cast<PointerContainer>(arg)){
            std::cout<<"ptr"<<std::endl;
        }
    }
    return fmt;
}
