/*
Z. Roth
mgr.cpp
*/

#include "mgr.h"
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

//Output for main menu
void Manager::display_menu()
{
    cout << "\n*********************************************************/" << endl;
    cout << "Seasons greetings" << endl << endl;
    cout << "Interested in finding out more about a few popular winter activities";
    cout << "\nfound here in the great state of Oregon?" << endl;
    cout << "\nWell, look no further! You can choose an option below by entering";
    cout << "\nthe corresponding number on the menu for more details!" << endl;
    cout << "\n*********************************************************/" << endl;
    cout << "LOCATIONS FOR WINTER ACTIVITIES:" << endl;
    cout << "1. Skiing" << endl << endl;
    cout << "2. Ice Skating" << endl << endl;
    cout << "3. Snow Tubing" << endl << endl;
    cout << "*********************************************************/" << endl;
}

//User input function
int Manager::user_choice()
{
    int choice;
    cout << "\nPlease enter a number from the menu above to choose an option: " << endl;
    cin >> choice;
    cout << endl << endl;

    return choice;
}

//Display sub-search options specific to certain winter activity
void Manager::display_ski_submenu()
{
    cout << "\nSKIING:" << endl;
    cout << "\n*********************************************************/" << endl;
    cout << "OPTIONS:" << endl;
    cout << "1. All locations" << endl;
    cout << "2. Top 3 Expert runs" << endl;
    cout << "3. Top 3 Beginner runs" << endl;
    cout << "4. Cost of daily lift pass" << endl << endl;
    cout << "*********************************************************/" << endl;
}

//Display sub-search options specific to certain winter activity
void Manager::display_skate_submenu()
{
    cout << "\nSKATING:" << endl;
    cout << "*********************************************************/" << endl;
    cout << "SORT BY:" << endl;
    cout << "1. Indoor rinks" << endl;
    cout << "2. Outdoor rinks" << endl;
    cout << "3. Cost of admission" << endl << endl;
    cout << "*********************************************************/" << endl;
}

//Option for client to return to main menu and complete another search
void Manager::new_search()
{
    cout << "\nLooks like you're finished with your current search..." << endl;
    cout << "Would you like to go back to the main menu? (y/n): " << endl;
}

//Interface for client to choose activity for more location info
void Manager::generate_search(fstream & infile)
{
    //Activity lists
    auto * ski_list = new DLL<Skiing>();
    auto * skate_list = new DLL<Ice_Skating>();
    auto * tubing_list = new DLL<Snow_Tubing>();

    fill_lists(infile, ski_list, skate_list, tubing_list);

    //User choice from main menu dictates which activity list to work with
    int choice = user_choice();
    switch (choice)
    {
        case 1:
        {
            cout << "*********************************************************/" << endl;
            cout << "Places to go skiing:" << endl;
            cout << "*********************************************************/" << endl;
            Skiing sk = ski_list->get_head()->get_data();
            sk.display_ski_equipment();
            ski_list->display();
            break;
        }
        case 2:
        {
            cout << "*********************************************************/" << endl;
            cout << "Places to go ice skating:" << endl;
            cout << "*********************************************************/" << endl;
            Ice_Skating is = skate_list->get_head()->get_data();
            is.display_skate_equipment();
            skate_list->display();
            break;
        }
        case 3:
        {
            cout << "*********************************************************/" << endl;
            cout << "Places to go snow tubing:" << endl;
            cout << "*********************************************************/" << endl;
            Snow_Tubing tu = tubing_list->get_head()->get_data();
            tu.display_snow_tube_equipment();
            tubing_list->display();
            break;
        }
        default:
        {
            cout << "Invalid choice..." << endl;
        }
    }
}

//Reads text file, parses fields, creates new objects and adds to activity lists
void Manager::fill_lists(fstream & infile, DLL<Skiing> *& ski, DLL<Ice_Skating> *& skate,
                         DLL<Snow_Tubing> *& tubing)
{
    //Field variables
    char type[10];
    string loc, rink, address, line;
    int begin = 0, inter = 0, exp = 0, cost = 0;
    array<int,3> run_arr{};

    //Reads each text line in file, parses fields
    //and assigns to new activity objects
    while(getline(infile, line))
    {
        stringstream text_line(line);
        text_line >> type >> loc >> address;
        replace(loc.begin(), loc.end(), '_', ' ');
        replace(address.begin(), address.end(), '_', ' ');

        if (strcmp(type,"SKI") == 0) {
            text_line >> begin >> inter >> exp >> cost;
            array<int, 3> run_levels{};
            run_arr.at(0) = begin;
            run_arr.at(1) = inter;
            run_arr.at(2) = exp;

            Skiing new_ski = Skiing(type, loc, address,
                                    run_arr, cost);
            ski->append(new_ski);
        }

        else if (strcmp(type,"SKATE") == 0)
        {
            text_line >> rink >> cost;
            char c_rink[rink.size() + 1];
            strcpy(c_rink, rink.c_str());
            Ice_Skating new_skate = Ice_Skating(type, loc, address,
                                                c_rink, cost);
            skate->append(new_skate);
        }

        else
        {
            text_line >> cost;
            Snow_Tubing new_tubing = Snow_Tubing(type, loc, address, cost);
            tubing->append(new_tubing);
        }
    }
}