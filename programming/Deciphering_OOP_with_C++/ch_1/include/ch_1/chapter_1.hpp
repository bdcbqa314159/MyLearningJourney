#ifndef CHAPTER_1_H
#define CHAPTER_1_H

enum day
{
    Sunday,
    Monday,
    Tuesday,
    Wednesday,
    Thursday,
    Friday,
    Saturday
};

enum workDay
{
    Mon = 1,
    Tues,
    Wed,
    Thurs,
    Fri
};

enum struct WinterHoliday
{
    Diwali,
    Hanukkah,
    ThreeKings,
    WinterSolstice,
    StLucia,
    StNicholas,
    Christmas,
    Kwanzaa
};

enum class Holiday : short int
{
    NewYear = 1,
    MLK,
    Memorial,
    Independence,
    Labor,
    Thanksgiving
};

namespace DataTypes
{
    extern int total;
    class LinkList
    {
    };

    class Stack
    {
    };
};

namespace AbstractDataTypes
{
    class Stack
    {
    };
    class Queue
    {
    };
};

namespace AbstractDataTypes
{
    extern int total;
    class Tree
    {
    };
};

void playing_iomanip();

void playingEnum();

void playingNameSpaces();

#endif