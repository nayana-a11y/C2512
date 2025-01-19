#include <iostream>
#include <sstream>
#include <string>

#include "./../headers/floor_main.h"
#include "./../headers/ui_common.h"

class DoctorController {
public:
    static void Read(std::string& doctorName, int flags = 3) {
        if ((flags & 1) != 0) {
            std::cout << "Doctor Name:";
            std::cin >> doctorName;
        }
    }

    void Create() {
        uiCommon.TitleBar("Admin App > Doctor Management > Create Doctor");
        int flags = 3;
        std::string doctorName;

        do {
            Read(doctorName, flags);
            int proceedOption;

            std::stringstream soutput;
            soutput << "1 - Edit `Doctor Name`." << std::endl;
            soutput << "91 - Proceed to create doctor." << std::endl;
            soutput << "\tYour choice:";
            proceedOption = uiCommon.in.Int(soutput.str());

            if (91 == proceedOption) {
                // Set to business object
                break;
            }
            flags = proceedOption;
        } while (true);

        std::cout << "Doctor is created successfully." << std::endl;
        uiCommon.PressAnyKey(true);
    }

    void Edit() {
        uiCommon.TitleBar("Admin App > Doctor Management > Edit Doctor");
        uiCommon.PressAnyKey(true);
    }

    void View() {
        uiCommon.TitleBar("Admin App > Doctor Management > View Doctor");
        uiCommon.PressAnyKey(true);
    }

    void Search() {
        uiCommon.TitleBar("Admin App > Doctor Management > Search Doctor");
        uiCommon.PressAnyKey(true);
    }

    void Deactivate() {
        uiCommon.TitleBar("Admin App > Doctor Management > Deactivate Doctor");
        uiCommon.PressAnyKey(true);
    }
};

static int ReadDoctorMenu() {
    int choice;

    uiCommon.TitleBar("Admin App > Doctor Management");

    std::stringstream soutput;
    soutput << "1 - Create Doctor" << std::endl;
    soutput << "2 - Edit Doctor" << std::endl;
    soutput << "3 - View Doctor" << std::endl;
    soutput << "4 - Search Doctor" << std::endl;
    soutput << "5 - Deactivate Doctor" << std::endl;
    soutput << "99 - Exit" << std::endl;
    soutput << "Your choice:";
    choice = uiCommon.in.Int(soutput.str());

    if (choice < 1 || (choice > 5 && choice != 99)) {
        std::cout << "[Invalid choice. Please select a valid option.]" << std::endl;
        choice = -1; // Return invalid choice
    }

    uiCommon.Line('~');
    uiCommon.PressAnyKey(true);
    return choice;
}

void ManageDoctor() {
    DoctorController controller;

    int choice;

    do {
        choice = ReadDoctorMenu();
        if (choice == -1) {
            continue; // Skip invalid choice handling
        }

        switch (choice) {
            case 99: {
                std::cout << "Exiting Doctor Management." << std::endl;
            } break;
            case 1: {
                controller.Create();
            } break;
            case 2: {
                controller.Edit();
            } break;
            case 3: {
                controller.View();
            } break;
            case 4: {
                controller.Search();
            } break;
            case 5: {
                controller.Deactivate();
            } break;
            default: {
                // This should never be reached as invalid choices are handled earlier
                std::cout << "[Invalid choice. Please select a valid option.]" << std::endl;
            } break;
        }
    } while (choice != 99);
}
