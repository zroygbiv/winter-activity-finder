#ifndef ACTIVITY_H
#define ACTIVITY_H

/*
Z. Roth
winter_activity.h

This contains the classes that constitute the winter activities a user can learn about.
The Activity class is parent to derived classes: Skiing, Ice Skating, and Snow Tubing.
Each derived class contains members specific to their activity, while all commonalities
are members contained in the Activity class.
*/

#include <string>
#include <vector>
#include <array>

using namespace std;

class Activity
{
public:
    Activity();
    Activity(char *, string , string , int);
    Activity(const Activity & src);
    Activity & operator=(const Activity & rhs);
    ~Activity();

    friend std::ostream & operator<<(ostream & out, const Activity & op2);
    bool operator>=(const Activity & rhs);
    bool operator<(const Activity & rhs);
    void display_equipment() const;

protected:
    char * activity_type;
    string location_name;
    string address;
    int cost;
};

class Skiing: public Activity
{
public:
    Skiing(char *, const string &, const string &, array<int,3>, int);
    Skiing(const Skiing & src);
    Skiing & operator=(const Skiing & rhs);

    friend ostream & operator<<(ostream & out, const Skiing & op2);
    bool operator>=(const Skiing & op2);
    bool operator<(const Skiing & op2);
    void display_ski_equipment() const;

private:
    array<int,3> run_types;
    vector<string> ski_equipment;
};

class Ice_Skating: public Activity
{
public:
    Ice_Skating();
    Ice_Skating(char *, const string &, const string &, char *, int);
    Ice_Skating(const Ice_Skating & src);
    ~Ice_Skating();
    Ice_Skating & operator=(const Ice_Skating & rhs);

    friend ostream & operator<<(ostream & out, const Ice_Skating & op2);
    bool operator>=(const Ice_Skating & op2);
    bool operator<(const Ice_Skating & op2);
    void display_skate_equipment() const;

private:
    char * rink;
    vector<string> skate_equipment;
};

class Snow_Tubing: public Activity
{
public:
    Snow_Tubing(char *, const string &, const string &, int);
    Snow_Tubing(const Snow_Tubing & src);
    Snow_Tubing & operator=(const Snow_Tubing & rhs);

    friend ostream & operator<<(ostream & out, const Snow_Tubing & op2);
    bool operator>=(const Snow_Tubing & op2);
    bool operator<(const Snow_Tubing & op2);
    void display_snow_tube_equipment() const;

private:
    vector<string> tube_equipment;
};

#endif