#include "ValueContainer.h"

using namespace My;

std::shared_ptr<ValueContainer> My::as_vcp(int32_t i){
    return std::make_shared<IntContainerImpl>(i);
}
std::shared_ptr<ValueContainer> My::as_vcp(uint32_t u){
    return std::make_shared<UIntContainerImpl>(u);
}
std::shared_ptr<ValueContainer> My::as_vcp(char c){
    return std::make_shared<CharContainerImpl>(c);
}
std::shared_ptr<ValueContainer> My::as_vcp(std::string s){
    return std::make_shared<StringContainerImpl>(s);
}
std::shared_ptr<ValueContainer> My::as_vcp(const char * s){
    return std::make_shared<CStringContainerImpl>(s);
}
std::shared_ptr<ValueContainer> My::as_vcp(void * p){
    return std::make_shared<PointerContainerImpl>(p);
}

void ValueContainer::dummy(){
    //DO NOTHING
}

IntContainerImpl::IntContainerImpl(int32_t i):i32(i){
    
}

int32_t IntContainerImpl::getInt(){
    return i32;
}

UIntContainerImpl::UIntContainerImpl(uint32_t u):ui32(u){
    
}

uint32_t UIntContainerImpl::getUInt(){
    return ui32;
}

CharContainerImpl::CharContainerImpl(char c2):c(c2){
    
}

char CharContainerImpl::getChar(){
    return c;
}

StringContainerImpl::StringContainerImpl(std::string s2):s(s2){
    
}

std::string StringContainerImpl::getString(){
    return s;
}

CStringContainerImpl::CStringContainerImpl(const char * cs2):cs(cs2){
    
}

const char * CStringContainerImpl::getCString(){
    return cs;
}

PointerContainerImpl::PointerContainerImpl(const void * p2):p(p2){
    
}

const void * PointerContainerImpl::getPointer(){
    return p;
}
