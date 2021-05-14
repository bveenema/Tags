#ifndef _TAGS_H_
#define _TAGS_H_

#include <Arduino.h>
class Tag
{
public:
    enum TagType
    {
        Bool,
        Int, // 32 bit
        Unsigned, // 32 bit
        LongInt, // 64 bit
        LongUnsigned // 64 bit
    };

    Tag(){}

    void Update()
    {
        Serial.println("TagBase");
    }
};

class TagInt : public Tag
{
public:
    TagInt()
    {
        _type = Tag::Int;
    }

    Tag::TagType GetType()
    {
        return _type;
    }

    void SetType(Tag::TagType type)
    {
        _type = type;
    }

private:
    Tag::TagType _type;
};

#endif