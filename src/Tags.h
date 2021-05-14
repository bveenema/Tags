#ifndef _TAGS_H_
#define _TAGS_H_

#include <Arduino.h>

class Tag
{
public:
    enum Type
    {
        Bool,
        Int, // 32 bit
        Unsigned, // 32 bit
        LongInt, // 64 bit
        LongUnsigned // 64 bit
    };

template <typename T>
struct Description
    {
        uint32_t Index;
        char Name[32];
        char Unit[12];
        T Min;
        T Max;
        T Default;
        T AlarmLow;
        T AlarmHigh;
    };
};
template <typename T>
class TagBase
{
public:
    char Name[32];
    char Unit[12];
    T Min;
    T Max;
    T AlarmLow;
    T AlarmHigh;
    T Current;

    explicit TagBase(){}

    explicit TagBase(Tag::Description<T> tag):
    Min(tag.Min),
    Max(tag.Max),
    AlarmLow(tag.AlarmLow),
    AlarmHigh(tag.AlarmHigh),
    Default(tag.Default)
    {
        strcpy(Name, tag.Name);
        strcpy(Unit, tag.Unit);

        if(tag.Index)
        {
            Index = tag.Index;
            LastIndex = tag.Index;
        }
        else
        {
            Index = LastIndex + 1;
            LastIndex = Index;
        }
        AlarmState = false;
    }

    Tag::Type GetType()
    {
        return _type;
    }

    void SetType(Tag::Type type)
    {
        _type = type;
    }

    void OnChange(void (*callback)(TagBase<T> &tag, const T, const T, const Tag::Type type) )
    {
        onChange = callback;
    }

    T operator=(const T &value) // Assignment Operator
    {
        // Do nothing if assigned to same value
        if(value == Current) return Current;

        // if new value, call onChange function
        if(onChange) onChange(*this, value, Current, _type);
        
        // Store new value
        Current = value;

        return Current;
    } 
    operator const T () const {return Current;} // "Get Value Operator"
    T operator+(const T &value) {return Current + value;} // Add operator


protected:
    uint32_t Index;
    static uint32_t LastIndex;
    T Default;
    bool AlarmState;
    Tag::Type _type;

    void (*onChange)(TagBase<T> &tag, const T current, const T previous, const Tag::Type type);
};


class TagInt : public TagBase<int>//, public AddHelper<int>
{
public:
    TagInt() : TagBase<int>()
    {
        _type = Tag::Int;
    }

    using TagBase<int>::operator const int;
    using TagBase<int>::operator =;
    using TagBase<int>::operator +;
    
};

#endif