# TAGS
Tags is a C++ Library for creating engineering tags on embedded microcontrollers. A tag can be: 
- a standard type like a boolean, int32_t, or uint8_t
- an array or c-string, like int16_t[100] or char[32]
- or a class instance by inheriting the Tag Base class

Tags have added abilities over standard types, arrays and classes. They have:
- built-in event driven structures, like on-change and on-alarm
- engineering features like units, min/max/default values, and alarm values
- a standard interface so that they can be added to 
  - **Tag Providers** - which make tags accessible to world outside the microcontroller and 
  - **Tag Persistors** - which make tag values persistant
  - **Tag Historians** - which enable on-board logging of tag data

Tags use more memory than standard types and therefor may not be appropriate for broadscale use on memory constrained micro-contollers. Tags are NOT meant to be used for every single variable in a program, for example, it would be inappropriate to use a tag for a loop index or temporary value within a function. Tags are meant for program lifetime variables and classes so that they can have a standard interface and be accessible to Tag Providers, Persistors, and Historians.

# TABLE OF CONTENTS
- [TAGS](#tags)
- [TABLE OF CONTENTS](#table-of-contents)
- [OVERVIEW](#overview)
  - [Tag Creation](#tag-creation)
  - [Tag Names and Indexes](#tag-names-and-indexes)
  - [Tag Units](#tag-units)
  - [Tag Defaults](#tag-defaults)
  - [Tag Alarms](#tag-alarms)
  - [Tag Events](#tag-events)
- [REFERENCE](#reference)
- [BACKGROUND](#background)
- [API](#api)

# OVERVIEW
## Tag Creation
All Tags are an instance of a class. Standard types like boolean, int, or uint32_t are instances of a templated class. If you're not familiar with template class syntax, [Tutorials Point](https://www.tutorialspoint.com/cplusplus/cpp_templates.htm) has a good primer.
The syntax looks like this:
```cpp
#include <TagStdInt.h>

Tag<bool> MyBoolTag;
Tag<int> MyIntTag;
Tag<uint32_t> MyUint32_tTag;
```
## Tag Names and Indexes
Tag names are mutable while Indexes are immutable. Tag names are important for Tag Providers and can also be referenced in Tag Historians. Tag Persistors and Tag Historians rely on the immutable index to keep accurate records. Indexes can be assigned to tags in the constructor or they are automatically assigned.

```cpp
#include <TagStdInt.h>

Tag<bool> MyBoolTag; // Name = "", Index = 0
Tag<int> MyIntTag("MyIntTag"); // Name = "MyIntTag", Index = 1
Tag<uint32_t> MyUint32_tTag(7, "MyUint32_tTag"); // Name = "MyUint32_tTag", Index = 7

int main()
{
  MyBoolTag.Name = "MyBoolTag"; // Change name of MyBoolTag to "MyBoolTag"

  printf("MyIntTag is named: \"%s\" and is Tag Index %lu", MyIntTag.Name, MyIntTag.GetIndex());
}
```

## Tag Units
- Mutable but care should be used as unit may not represent actual
- In future can be used by Historians or Providers to create conversions
- Uses following list of abbreviations: TODO

```cpp
#include <TagStdInt.h>

Tag<bool> MyBoolTag; // Unit = ""
Tag<int> MyIntTag("MyIntTag", "mm"); // Name = "MyIntTag", Unit = "mm"

int main()
{
  MyBoolTag.Unit = "in"; // Change unit of MyBoolTag to in (inches)

  printf("MyIntTag has units %s", MyIntTag.Unit);
}
```

## Tag Defaults
- Has Min, Max and Default values
- Min cannot be greater than Max-1
- Mins and Maxs are checked when setting new tag values
- Default is the initialized value and is immutable. Persistors are used for Tags where new settings can be stored and used with Default values, enable things like "restore factory defaults"

```cpp
#include <TagStdInt.h>

Tag<bool> MyBoolTag; // Index = 0, Min = 0, Max = 1, Default = 0
Tag<int> MyIntTag(2); // Index = 2, Min = -2,147,483,648, Max = 2,147,483,648, Default = 0
Tag<uint32_t> MyUint32_tTag(7, 100, 500, 300); // Index = 7, Min = 100, Max = 500, Default = 300

int main()
{
  MyIntTag.Min = -200; // Change Min of MyIntTag to -200

  printf("MyIntTag has min %li, max %li, default %li", MyIntTag.Min, MyIntTag.Max, MyIntTag.GetDefault());
}
```

## Tag Alarms

## Tag Events



# REFERENCE

# BACKGROUND

# API