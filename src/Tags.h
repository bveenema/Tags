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
        LongUnsigned, // 64 bit
        Float,
        Double
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

protected:
    static uint32_t LastIndex;
};

uint32_t Tag::LastIndex = 0;
template <typename T>
class TagBase : public Tag
{
public:
    char Name[32];
    char Unit[12];
    T Min;
    T Max;
    T AlarmLow;
    T AlarmHigh;
    T Current;

    explicit TagBase()
    {
        Index = LastIndex++;

        AlarmState = false;
    }

    Tag::Type GetType() { return _type;}

    uint32_t GetIndex() {return Index;}

    void OnChange(void (*callback)(TagBase<T> &tag, const T, const T, const Tag::Type type) )
    {
        onChange = callback;
    }

    // Assignment Operators
    T operator   = (const T &value) { Current   = value; return HandleAssignment(); }
    T operator  += (const T &value) { Current  += value; return HandleAssignment(); }
    T operator  -= (const T &value) { Current  -= value; return HandleAssignment(); }
    T operator  *= (const T &value) { Current  *= value; return HandleAssignment(); }
    T operator  /= (const T &value) { Current  /= value; return HandleAssignment(); }
    T operator  %= (const T &value) { Current  %= value; return HandleAssignment(); }
    T operator  &= (const T &value) { Current  &= value; return HandleAssignment(); }
    T operator  |= (const T &value) { Current  |= value; return HandleAssignment(); }
    T operator  ^= (const T &value) { Current  ^= value; return HandleAssignment(); }
    T operator <<= (const T &value) { Current <<= value; return HandleAssignment(); }
    T operator >>= (const T &value) { Current >>= value; return HandleAssignment(); }

    // "Get Value" Operator
    operator const T () const {return Current;}

    // Increment/Decrement Operators
    T operator ++ () { ++Current; return HandleAssignment(); }
    T operator -- () { --Current; return HandleAssignment(); }
    T operator ++ (int) { T temp = Current++;  HandleAssignment(); return temp; }
    T operator -- (int) { T temp = Current--;  HandleAssignment(); return temp; }

protected:
    uint32_t Index;
    T Default, Previous;
    bool AlarmState;
    Tag::Type _type;

    void (*onChange)(TagBase<T> &tag, const T current, const T previous, const Tag::Type type);

    T HandleAssignment()
    {
        // if new value, call onChange function
        if(Previous != Current)
            if(onChange) onChange(*this, Current, Previous, _type);

        Previous = Current;

        return Current;
    }
};

class TagBool : public TagBase<bool>
{
public:
    TagBool() : TagBase<bool>()
    {
        _type = Tag::Bool;
        Min = 0;
        Max = 1;
        Default = 0;
        AlarmLow = 0;
        AlarmHigh = 1;
    }

    using TagBase<bool>::operator const bool;
    using TagBase<bool>::operator =;
};

class TagInt : public TagBase<int32_t>
{
public:
    TagInt() : TagBase<int32_t>()
    {
        _type = Tag::Int;
        Min = INT32_MIN;
        Max = INT32_MAX;
        Default = 0;
        AlarmLow = 0;
        AlarmHigh = 100;
    }

    using TagBase<int32_t>::operator const int32_t;
    using TagBase<int32_t>::operator =;
    
};

class TagUnsigned : public TagBase<uint32_t>
{
public:
    TagUnsigned() : TagBase<uint32_t>()
    {
        _type = Tag::Unsigned;
        Min = 0;
        Max = UINT32_MAX;
        Default = 0;
        AlarmLow = 0;
        AlarmHigh = 100;
    }

    using TagBase<uint32_t>::operator const uint32_t;
    using TagBase<uint32_t>::operator =;
    
};

class TagLongInt : public TagBase<int64_t>
{
public:
    TagLongInt() : TagBase<int64_t>()
    {
        _type = Tag::LongInt;
        Min = INT64_MIN;
        Max = INT64_MAX;
        Default = 0;
        AlarmLow = 0;
        AlarmHigh = 100;
    }

    using TagBase<int64_t>::operator const int64_t;
    using TagBase<int64_t>::operator =;
    
};

class TagLongUnsigned : public TagBase<uint64_t>
{
public:
    TagLongUnsigned() : TagBase<uint64_t>()
    {
        _type = Tag::LongUnsigned;
        Min = 0;
        Max = UINT64_MAX;
        Default = 0;
        AlarmLow = 0;
        AlarmHigh = 100;
    }

    using TagBase<uint64_t>::operator const uint64_t;
    using TagBase<uint64_t>::operator =;
    
};

class TagFloat : public TagBase<float>
{
public:
    TagFloat() : TagBase<float>()
    {
        _type = Tag::Float;
        Min = __FLT_MIN__;
        Max = __FLT_MAX__;
        Default = 0;
        AlarmLow = 0;
        AlarmHigh = 100;
    }

    using TagBase<float>::operator const float;
    using TagBase<float>::operator =;
};

class TagDouble : public TagBase<double>
{
public:
    TagDouble() : TagBase<double>()
    {
        _type = Tag::Double;
        Min = __DBL_MIN__;
        Max = __DBL_MAX__;
        Default = 0;
        AlarmLow = 0;
        AlarmHigh = 100;
    }

    using TagBase<double>::operator const double;
    using TagBase<double>::operator =;
};

#endif