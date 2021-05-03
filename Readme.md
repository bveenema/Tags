# TAGS
Tags is a C++ Library for creating engineering tags on embedded microcontrollers. A tag can be: 
- a standard variable like a boolean, int32_t, or uint8_t
- an array or c-string, like int16_t[100] or char[32]
- or a class instance by inheriting the Tag Base class

Tags have added abilities over standard variabes, arrays and classes. They have:
- built-in event driven structures, like on-change and on-alarm
- engineering features like units, min/max/default values, and alarm values
- a standard interface so that they can be added to 
  - **Tag Providers** - which make tags accessible to world outside the microcontroller and 
  - **Tag Loggers** - which enable on-board logging of tag data

Tags use much more memory on top of standard types and therefor may not be appropriate for broadscale use on memory constrained micro-contollers. Tags are NOT meant to be used for every single variable in a program, for example, it would be inappropriate to use a tag for a loop index or temporary value within a function. Tags are meant for persistant variables and classes so that they can have a standard interface and be accessible to Tag Providers and Tag Loggers

# TABLE OF CONTENTS
- [TAGS](#tags)
- [TABLE OF CONTENTS](#table-of-contents)
- [OVERVIEW](#overview)
  - [Tag Creation](#tag-creation)
  - [Tag Units](#tag-units)
  - [Tag Defaults](#tag-defaults)
  - [Tag Alarms](#tag-alarms)
  - [Tag Events](#tag-events)
- [REFERENCE](#reference)
- [BACKGROUND](#background)
- [API](#api)

# OVERVIEW
## Tag Creation

## Tag Units

## Tag Defaults

## Tag Alarms

## Tag Events



# REFERENCE

# BACKGROUND

# API