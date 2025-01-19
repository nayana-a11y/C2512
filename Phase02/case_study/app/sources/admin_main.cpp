#include<iostream>
#include<sstream>
#include<string>

#include"./../headers/admin_main.h"
#include"./../headers/ui_common.h"

class DoctorController { 
    public: 
        static void Read(std::string& name,
            int& gender,
            int& department,
            std::string& phone,
            std::string& email,
            std::string& location,
            std::string& address,
            int flags = 127) {

            if((flags & 1) != 0) {
                name = uiCommon.in.Str("Doctor Name:");
            }

            if((flags & 2) != 0) {
                gender = uiCommon.in.Int("Gender (1-Male, 2-Female, 3-Other):");
            }

            if((flags & 4) != 0) {
                department = uiCommon.in.Int("Department (1-Cardiology, 2-Neurology, 3-ENT, 4-General Physician):");
            }
 
            if((flags & 8) != 0) {
                do {
                    phone = uiCommon.in.Str("Enter Phone:");
                    if(!uiCommon.in.exist()) {
                        break;
                    }
                    std::cout << "[Phone Exist. Enter alternate phone.]" << std::endl;
                } while(true);
            }

            if((flags & 16) != 0) {
                do {
                    email = uiCommon.in.Str("Enter email:");
                    if(!uiCommon.in.exist()) {
                        break;
                    }
                    std::cout << "[Email Exist. Enter alternate email.]" << std::endl;
                } while(true);
            }

            if((flags & 32) != 0) {
                location = uiCommon.in.Str("Enter Location:");
            }

            if((flags & 64) != 0) {
                address = uiCommon.in.Str("Enter Address:");
            }
        }

        void Create() {
            uiCommon.TitleBar("Admin App > Doctor Management > Create Doctor");
            int flags = 127;
            std::string name;
            int gender = 0;
            int department = 0;
            std::string phone;
            std::string email;
            std::string location;
            std::string address;
            
            do {
                Read(name, gender, department, phone, email, location, address, flags);
                int proceedOption; 

                std::stringstream soutput; 
                soutput << "[1] edit `name`" << std::endl;
                soutput << "[2] edit `gender`" << std::endl;
                soutput << "[3] edit `department`" << std::endl;
                soutput << "[4] edit `phone`\n   [Phone already Exist. Enter alternate phone.]" << std::endl;
                soutput << "[5] edit `email`\n   [Email already Exist. Enter alternate email]" << std::endl;
                soutput << "[6] edit `location`" << std::endl;
                soutput << "[7] edit `address`" << std::endl;
                soutput << "[8] edit `name` and `gender`" << std::endl;
                soutput << "[9] edit `name` and `department`" << std::endl;
                soutput << "[10] edit `gender` and `department`" << std::endl;
                soutput << "[11] edit `Location` and `Address`" << std::endl;
                soutput << "[91] Confirm To Create" << std::endl;
                soutput << "Enter your choice:"; 
                proceedOption = uiCommon.in.Int(soutput.str());

                if(91 == proceedOption) {
                    //set to biz object
                    break;
                }
                flags = proceedOption;
            } while(true);
            std::cout << "Doctor created successfully." << std::endl;
            std::cout << "Generated doctor code is D001." << std::endl;
            std::cout << "-------------------------------------------------------------------" << std::endl;
            uiCommon.PressAnyKey(true);        
        }

        void Edit() {
            uiCommon.TitleBar("Admin App > Doctor Management > Edit Doctor");
            uiCommon.PressAnyKey(true); 
        }

        void Delete() {
            uiCommon.TitleBar("Admin App > Doctor Management > Delete Doctor");
            uiCommon.PressAnyKey(true); 
        }

        void DisplayAll() {
            uiCommon.TitleBar("Admin App > Doctor Management > List of Doctors");
            uiCommon.PressAnyKey(true); 
        }
};

static int ReadDoctorMenu() {
    int choice;
    
    uiCommon.TitleBar("Admin App > Doctor Management");

    std::stringstream soutput;
    soutput << "1 - Create Doctor" << std::endl;
    soutput << "2 - Edit Doctor" << std::endl;
    soutput << "3 - Delete Doctor" << std::endl;
    soutput << "4 - Display All Doctors" << std::endl;
    soutput << "99 - Exit" << std::endl;
    soutput << "Your choice:"; 
    choice = uiCommon.in.Int(soutput.str());
    
    uiCommon.Line('~');
    uiCommon.PressAnyKey(true); 
    return choice;
}

void ManageDoctor() { 
    DoctorController controller;
    
    int choice;

    do { 
        choice = ReadDoctorMenu();
        switch(choice) {
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
                controller.Delete();
            } break;
            case 4: {
                controller.DisplayAll();
            } break;
        }
    } while(99 != choice);
}
