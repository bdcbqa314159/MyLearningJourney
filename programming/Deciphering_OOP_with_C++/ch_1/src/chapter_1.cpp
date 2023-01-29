#include "ch_1_lib"
#include <iomanip>
#include <iostream>

using std::cin, std::cout, std::endl, std::setw, std::flush, std::setprecision;

namespace DataTypes
{
    int total = 0;
};

namespace AbstractDataTypes
{
    int total = 0;

};

void playing_iomanip()
{
    char name[20];
    float gpa = 0.;
    cout << "Please enter a name and a gpa: ";
    cin >> setw(20) >> name >> gpa;
    cout << "Hello " << name << flush;
    cout << ". GPA is: " << setprecision(3) << gpa << endl;
    return;
}

void playingEnum()
{
    day birthday = Monday;
    workDay payday = Fri;
    WinterHoliday myTradition = WinterHoliday::StNicholas;
    Holiday favorite = Holiday::NewYear;

    cout << "Birthday is " << birthday << endl;
    cout << "Payday is " << payday << endl;
    cout << "Traditional Winter holiday is " << static_cast<int>(myTradition) << endl;
    cout << "Favorite holiday is " << static_cast<short int>(favorite) << endl;
    return;
}

void playingNameSpaces()
{
    using namespace AbstractDataTypes;
    using DataTypes::LinkList;
    LinkList list1;
    Stack stack1;
    total = 5;

    DataTypes::total = 85;
    cout << "total " << total << endl;
    cout << "DataTypes::total " << DataTypes::total << endl;
    cout << endl;
}