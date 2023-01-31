/*
Z. Roth
main.cpp
NOTE: When running the program from the terminal, you must include the location_data.txt
      file as an argument in the command line:
      example:    ./a.out location_data.txt
*/
#include <iostream>
#include <fstream>
#include "mgr.h"

using namespace std;

int main(int argc, char** argv) {
    if (argc != 2)
    {
        cout << "Usage: " << argv[0] << " <datafile>" << endl;
        exit(0);
    }
    char * datafile = argv[1];

    Manager mgr;
    bool main_menu = true;

    while (main_menu)
    {
        mgr.display_menu();
        fstream infile(datafile);
        if (!infile) cerr << "File could not be opened" << endl;

        mgr.generate_search(infile);
        mgr.new_search();

        char repeat_menu;
        cin >> repeat_menu;
        if (repeat_menu == 'y') main_menu = true;
        else main_menu = false;

        infile.close();
    }

    return 0;
}