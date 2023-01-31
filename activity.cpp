/*
Z. Roth

winter_activity.cpp
*/
#include <utility>
#include <iostream>
#include <cstring>

#include "activity.h"
#include "exception.h"

using namespace std;

/////////////////////////////////////////ACTIVITY CLASS
//Default Constructor
Activity:: Activity(): activity_type(nullptr), location_name("none"), cost(0),
                       address("none") {}

//Constructor
Activity::Activity(char * a_type, string  loc, string  address, int cost):
        location_name(std::move(loc)), address(std::move(address)), cost(cost)
{
    activity_type = new char[strlen(a_type) + 1];
    strcpy(activity_type, a_type);
}

//Copy Constructor
Activity::Activity(const Activity & src)
{
    activity_type = new char[strlen(src.activity_type) + 1];
    strcpy(activity_type, src.activity_type);

    location_name = src.location_name;
    address = src.address;
    cost = src.cost;
}

//Destructor
Activity::~Activity()
{
    delete [] activity_type;
}

//Assignment Operator
Activity& Activity::operator=(const Activity & rhs)
{
    if (this == &rhs) return *this;

    delete [] activity_type;
    activity_type = new char[strlen(rhs.activity_type) + 1];
    strcpy(activity_type, rhs.activity_type);

    location_name = rhs.location_name;
    address = rhs.address;
    cost = rhs.cost;

    return *this;
}

//Insertion Stream Operator
ostream & operator<<(ostream & out, const Activity & op2)
{
    try
    {
        if (!op2.activity_type)
            throw new_throw;

        out << "Location: " << op2.location_name << '\n'
            << "Address: " << op2.address << ", OR\n"
            << "Cost: " << op2.cost << '\n';
    } catch (exception& e)
    {
        out << e.what();
    }
    return out;
}

bool Activity::operator>=(const Activity & rhs)
{
    try
    {
        if (cost < 0 || rhs.cost < 0) throw new_throw;

        if (cost >= rhs.cost) return true;
        else return false;
    }
    catch (exception & e)
    {
        cout << "Cost amount(s) are invalid. Must be positive integer." << endl;
        return false;
    }
}

bool Activity::operator<(const Activity & rhs)
{
    try
    {
        if (cost < 0 || rhs.cost < 0) throw new_throw;

        if (cost < rhs.cost) return true;
        else return false;
    }
    catch (exception & e)
    {
        cout << "Cost amount(s) are invalid. Must be positive integer." << endl;
        return false;
    }
}

void Activity::display_equipment() const
{
    cout << "Equipment required: " << endl;
}

/////////////////////////////////////////SKIING CLASS
//Constructor
Skiing::Skiing(char * type, const string & loc, const string & city,
               array<int,3> run_arr, int cost): Activity(type, loc, city, cost)
{
    run_types = run_arr;
    ski_equipment = {"skis", "ski boots", "ski poles", "ski googles" };
}

//Copy Constructor
Skiing::Skiing(const Skiing & src): Activity(src)
{
    run_types = src.run_types;
    ski_equipment = src.ski_equipment;
}

//Assignment Operator
Skiing & Skiing::operator=(const Skiing & rhs)
{
    if (this == &rhs) return *this;

    Activity::operator=(rhs);
    run_types = rhs.run_types;
    ski_equipment = rhs.ski_equipment;

    return *this;
}

//Insertion Stream Operator
ostream & operator<<(ostream & out, const Skiing & op2)
{
    try
    {
        if (!op2.activity_type || op2.run_types.empty())
        {
            throw new_throw;
        }

        out << static_cast<const Activity &> (op2);
        out << "/** Run Types **/ \n"
            << "Beginner: " << op2.run_types.at(0) << "%   "
            << "Intermediate: " << op2.run_types.at(1) << "%   "
            << "Expert " << op2.run_types.at(2) << "%  "
            << '\n';

    }
    catch (exception & e)
    {
        out << e.what();
    }

    return out;
}

//Comparison Operators
bool Skiing::operator>=(const Skiing & rhs)
{
    bool result = Activity::operator>=(rhs);
    return result;
}

bool Skiing::operator<(const Skiing & rhs)
{
    bool result = Activity::operator<(rhs);
    return result;
}

void Skiing::display_ski_equipment() const
{
    Activity::display_equipment();
    for (string s: ski_equipment)
    {
        cout << s << "  ";
    }
    cout << endl << endl;
}

/////////////////////////////////////////ICE SKATING CLASS
//Default Constructor
Ice_Skating::Ice_Skating(): rink(nullptr)
{}

//Constructor
Ice_Skating::Ice_Skating(char * type, const string & loc, const string & city,
                         char * r, int cost)
        : Activity(type, loc, city, cost)
{
    rink = new char[strlen(r) + 1];
    strcpy(rink, r);
    skate_equipment = {"Ice skates", "Winter coat", "Gloves"};
}

//Copy Constructor
Ice_Skating::Ice_Skating(const Ice_Skating & src): Activity(src)
{
    rink = new char[strlen(src.rink) + 1];
    strcpy(rink, src.rink);
    skate_equipment = src.skate_equipment;
}

Ice_Skating::~Ice_Skating()
{
    delete [] rink;
}

//Assignment Operator
Ice_Skating & Ice_Skating::operator=(const Ice_Skating &rhs)
{
    if (this == &rhs) return *this;

    Activity::operator=(rhs);

    delete [] rink;
    rink = new char[strlen(rhs.rink) + 1];
    strcpy(rink, rhs.rink);
    skate_equipment = rhs.skate_equipment;

    return *this;
}

//Insertion Stream Operator
ostream & operator<<(ostream & out, const Ice_Skating & op2)
{
    try
    {
        if (!op2.activity_type || !op2.rink)
        {
            throw new_throw;
        }

        out << static_cast<const Activity &> (op2);
        out << "Rink: " << op2.rink << '\n';
    }
    catch (exception & e)
    {
        out << e.what() << endl;
    }

    return out;
}

//Comparison Operators
bool Ice_Skating::operator>=(const Ice_Skating & rhs)
{
    bool result = Activity::operator>=(rhs);
    return result;
}

bool Ice_Skating::operator<(const Ice_Skating & rhs)
{
    bool result = Activity::operator<(rhs);
    return result;
}

void Ice_Skating::display_skate_equipment() const
{
    Activity::display_equipment();
    for (string s: skate_equipment)
    {
        cout << s << "  ";
    }
    cout << endl << endl;
}

/////////////////////////////////////////SNOW TUBING CLASS
//Constructor
Snow_Tubing::Snow_Tubing(char * type, const string & loc, const string & city, int cost)
        : Activity(type, loc, city, cost)
{
    tube_equipment = {"Snow tube", "Winter coat", "Gloves", "Snow pants", "Knit cap"};
}

//Copy Constructor
Snow_Tubing::Snow_Tubing(const Snow_Tubing &src): Activity(src)
{
    tube_equipment = src.tube_equipment;
}

//Assignment Operator
Snow_Tubing & Snow_Tubing::operator=(const Snow_Tubing & rhs)
{
    if (this == &rhs) return *this;

    Activity::operator=(rhs);
    tube_equipment = rhs.tube_equipment;

    return *this;
}

//Insertion Stream Operator
ostream & operator<<(ostream & out, const Snow_Tubing & op2)
{
    try
    {
        if (!op2.activity_type) throw new_throw;

        out << static_cast<const Activity &> (op2);
    }
    catch (exception & e)
    {
        out << e.what();
    }

    return out;
}

//Comparison Operators
bool Snow_Tubing::operator>=(const Snow_Tubing & rhs)
{
    bool result = Activity::operator>=(rhs);
    return result;
}

bool Snow_Tubing::operator<(const Snow_Tubing & rhs)
{
    bool result = Activity::operator<(rhs);
    return result;
}

void Snow_Tubing::display_snow_tube_equipment() const
{
    Activity::display_equipment();
    for (string t: tube_equipment)
    {
        cout << t << "  ";
    }
    cout << endl << endl;
}