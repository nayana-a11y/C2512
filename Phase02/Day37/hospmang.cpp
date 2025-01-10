#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <iomanip> // For formatting boxes
using namespace std;

struct Patient {
    string id;
    string name;
    int age;
    string ailment;
};

struct Doctor {
    string id;
    string name;
    string specialty;
};

struct Appointment {
    string id;
    string patientId;
    string doctorId;
    string date;
    string time;
};

struct MedicalHistory {
    string patientId;
    vector<string> history;
};

unordered_map<string, Patient> patients;
unordered_map<string, Doctor> doctors;
vector<Appointment> appointments;
unordered_map<string, MedicalHistory> medicalHistories;

int patientCounter = 1000;
int doctorCounter = 2000;
int appointmentCounter = 3000;

string generatePatientId() {
    return "PAT" + to_string(patientCounter++);
}

string generateDoctorId() {
    return "DOC" + to_string(doctorCounter++);
}

string generateAppointmentId() {
    return "APT" + to_string(appointmentCounter++);
}

void printBoxed(const string &header, const vector<string> &lines) {
    cout << "---------------------------------------------------\n";
    cout << "| " << setw(50) << left << header << "|\n";
    cout << "---------------------------------------------------\n";
    for (const auto &line : lines) {
        cout << "| " << setw(50) << left << line << "|\n";
    }
    cout << "---------------------------------------------------\n";
}

void addPatient() {
    Patient p;
    p.id = generatePatientId();
    cout << "Generated Patient ID: " << p.id << "\n";
    cout << "Enter Name: ";
    cin.ignore();
    getline(cin, p.name);
    cout << "Enter Age: ";
    cin >> p.age;
    cout << "Enter Ailment: ";
    cin.ignore();
    getline(cin, p.ailment);

    patients[p.id] = p;

    // Automatically add ailment to medical history
    medicalHistories[p.id].patientId = p.id;
    medicalHistories[p.id].history.push_back("Initial Ailment: " + p.ailment);

    cout << "Patient added successfully and ailment added to medical history!\n";
}

void updatePatient() {
    string patientId;
    cout << "Enter Patient ID: ";
    cin >> patientId;

    if (patients.find(patientId) == patients.end()) {
        cout << "Patient not found!\n";
        return;
    }

    Patient &p = patients[patientId];
    cout << "Current Name: " << p.name << "\n";
    cout << "Current Age: " << p.age << "\n";
    cout << "Current Ailment: " << p.ailment << "\n";

    cout << "Enter New Name (or press Enter to skip): ";
    cin.ignore();
    string newName;
    getline(cin, newName);
    if (!newName.empty()) p.name = newName;

    cout << "Enter New Age (or press 0 to skip): ";
    int newAge;
    cin >> newAge;
    if (newAge > 0) p.age = newAge;

    cout << "Enter New Ailment (or press Enter to skip): ";
    cin.ignore();
    string newAilment;
    getline(cin, newAilment);
    if (!newAilment.empty()) {
        p.ailment = newAilment;

        // Update medical history
        medicalHistories[patientId].history.push_back("Updated Ailment: " + newAilment);
    }

    cout << "Patient updated successfully!\n";
}

void addDoctor() {
    Doctor d;
    d.id = generateDoctorId();
    cout << "Generated Doctor ID: " << d.id << "\n";
    cout << "Enter Name: ";
    cin.ignore();
    getline(cin, d.name);
    cout << "Enter Specialty: ";
    getline(cin, d.specialty);

    doctors[d.id] = d;
    cout << "Doctor added successfully!\n";
}

void updateDoctor() {
    string doctorId;
    cout << "Enter Doctor ID: ";
    cin >> doctorId;

    if (doctors.find(doctorId) == doctors.end()) {
        cout << "Doctor not found!\n";
        return;
    }

    Doctor &d = doctors[doctorId];
    cout << "Current Name: " << d.name << "\n";
    cout << "Current Specialty: " << d.specialty << "\n";

    cout << "Enter New Name (or press Enter to skip): ";
    cin.ignore();
    string newName;
    getline(cin, newName);
    if (!newName.empty()) d.name = newName;

    cout << "Enter New Specialty (or press Enter to skip): ";
    string newSpecialty;
    getline(cin, newSpecialty);
    if (!newSpecialty.empty()) d.specialty = newSpecialty;

    cout << "Doctor updated successfully!\n";
}

void viewPatient() {
    string patientId;
    cout << "Enter Patient ID: ";
    cin >> patientId;

    if (patients.find(patientId) == patients.end()) {
        cout << "Patient not found!\n";
        return;
    }

    Patient p = patients[patientId];
    vector<string> details = {
        "ID: " + p.id,
        "Name: " + p.name,
        "Age: " + to_string(p.age),
        "Ailment: " + p.ailment
    };
    printBoxed("Patient Details", details);
}

void viewDoctor() {
    string doctorId;
    cout << "Enter Doctor ID: ";
    cin >> doctorId;

    if (doctors.find(doctorId) == doctors.end()) {
        cout << "Doctor not found!\n";
        return;
    }

    Doctor d = doctors[doctorId];
    vector<string> details = {
        "ID: " + d.id,
        "Name: " + d.name,
        "Specialty: " + d.specialty
    };
    printBoxed("Doctor Details", details);
}

void viewAppointments() {
    if (appointments.empty()) {
        cout << "No appointments scheduled yet.\n";
        return;
    }
    vector<string> details;
    for (const auto &a : appointments) {
        details.push_back("ID: " + a.id + ", Patient ID: " + a.patientId + ", Doctor ID: " + a.doctorId + ", Date: " + a.date + ", Time: " + a.time);
    }
    printBoxed("Appointments", details);
}

void hospitalManagementSystem() {
    int choice;
    do {
        cout << "\nWelcome to Hospital Management System\n";
        cout << "1. Add Patient\n";
        cout << "2. Update Patient\n";
        cout << "3. View Patient\n";
        cout << "4. Add Doctor\n";
        cout << "5. Update Doctor\n";
        cout << "6. View Doctor\n";
        cout << "7. View Appointments\n";
        cout << "8. Exit\n";
        cout << "Your Choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            addPatient();
            break;
        case 2:
            updatePatient();
            break;
        case 3:
            viewPatient();
            break;
        case 4:
            addDoctor();
            break;
        case 5:
            updateDoctor();
            break;
        case 6:
            viewDoctor();
            break;
        case 7:
            viewAppointments();
            break;
        case 8:
            cout << "Exiting Hospital Management System...\n";
            break;
        default:
            cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 8);
}

int main() {
    hospitalManagementSystem();
    return 0;
}
