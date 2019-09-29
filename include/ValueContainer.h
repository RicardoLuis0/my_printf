#ifndef VALUECONTAINER_H
#define VALUECONTAINER_H

#include <memory>
#include <cstdint>
#include <string>

namespace My {
    class ValueContainer {
        virtual void dummy();
    };
    std::shared_ptr<ValueContainer> as_vcp(int32_t);
    std::shared_ptr<ValueContainer> as_vcp(uint32_t);
    std::shared_ptr<ValueContainer> as_vcp(char);
    std::shared_ptr<ValueContainer> as_vcp(std::string);
    std::shared_ptr<ValueContainer> as_vcp(const char *);
    std::shared_ptr<ValueContainer> as_vcp(void *);
    class IntContainer : public ValueContainer {
    public:
        virtual int32_t getInt()=0;
    };
    class UIntContainer : public ValueContainer {
    public:
        virtual uint32_t getUInt()=0;
    };
    class CharContainer : public ValueContainer {
    public:
        virtual char getChar()=0;
    };
    class StringContainer : public ValueContainer {
    public:
        virtual std::string getString()=0;
    };
    class CStringContainer : public ValueContainer {
    public:
        virtual const char * getCString()=0;
    };
    class PointerContainer : public ValueContainer {
    public:
        virtual const void * getPointer()=0;
    };
    class IntContainerImpl : public IntContainer {
        int32_t i32;
    public:
        IntContainerImpl(int32_t);
        virtual int32_t getInt() override;
    };
    class UIntContainerImpl : public UIntContainer {
        uint32_t ui32;
    public:
        UIntContainerImpl(uint32_t);
        virtual uint32_t getUInt() override;
    };
    class CharContainerImpl : public CharContainer {
        char c;
    public:
        CharContainerImpl(char c);
        virtual char getChar() override;
    };
    class StringContainerImpl : public StringContainer {
        std::string s;
    public:
        StringContainerImpl(std::string s);
        virtual std::string getString() override;
    };
    class CStringContainerImpl : public CStringContainer {
        const char * cs;
    public:
        CStringContainerImpl(const char * cs);
        virtual const char * getCString() override;
    };
    class PointerContainerImpl : public PointerContainer {
        const void * p;
    public:
        PointerContainerImpl(const void * p);
        virtual const void * getPointer() override;
    };
}

#endif // VALUECONTAINER_H
