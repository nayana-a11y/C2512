#include <iostream>
#include <sstream>

#include "./../headers/app_main.h"
#include "./../headers/floor_main.h"
#include "./../headers/admin_main.h"
UiCommon uiCommon;

static int ReadAppMenu() {
    int choice;
    
    uiCommon.TitleBar("Admin App");

    std::stringstream soutput;
    soutput << "1 - Doctor Management" << std::endl;
    soutput << "99 - Logout" << std::endl;
    soutput << "Your choice:"; 
    choice = uiCommon.in.Int(soutput.str()); //std::cin >> choice;
    
    uiCommon.Line('~');
    uiCommon.PressAnyKey(true); 
    return choice;
}

void ManageApp() { 
    
    int choice;

    do { 
        choice = ReadAppMenu();
        switch(choice) {
            case 99: {
                std::cout << std::endl;
            } break;
            case 1: {
                ManageDoctor();
            } break;
        }
    } while(99 != choice);
}

void AppMain() {
    ManageApp();
}
