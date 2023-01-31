/*
Z. Roth
mgr.h

This class "mgr" or "manager" acts the intermediary between the user and the data.
It's responsible for managing the user interface (outputting menus/taking user input),
generating searches for activity locations, and enabling the user to search again.
*/
#ifndef MGR_H
#define MGR_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "DLL.h"
#include "activity.h"

class Manager
{
public:
    static void display_menu() ;
    static void generate_search(fstream &);
    static void fill_lists(fstream & infile, DLL<Skiing> *&, DLL<Ice_Skating> *&,
                           DLL<Snow_Tubing> *&);
    static int user_choice();
    static void new_search() ;
    static void display_ski_submenu() ;
    static void display_skate_submenu() ;
};

#endif