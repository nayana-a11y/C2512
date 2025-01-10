#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
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

void addPatient() {
    Patient p;
    cout << "Enter Patient ID: ";
    cin >> p.id;
    cout << "Enter Name: ";
    cin.ignore();
    getline(cin, p.name);
    cout << "Enter Age: ";
    cin >> p.age;
    cout << "Enter Ailment: ";
    cin.ignore();
    getline(cin, p.ailment);

    patients[p.id] = p;
    cout << "Patient added successfully!\n";
}

void addDoctor() {
    Doctor d;
    cout << "Enter Doctor ID: ";
    cin >> d.id;
    cout << "Enter Name: ";
    cin.ignore();
    getline(cin, d.name);
    cout << "Enter Specialty: ";
    getline(cin, d.specialty);

    doctors[d.id] = d;
    cout << "Doctor added successfully!\n";
}

void scheduleAppointment() {
    Appointment a;
    cout << "Enter Appointment ID: ";
    cin >> a.id;
    cout << "Enter Patient ID: ";
    cin >> a.patientId;
    cout << "Enter Doctor ID: ";
    cin >> a.doctorId;
    cout << "Enter Date (YYYY-MM-DD): ";
    cin >> a.date;
    cout << "Enter Time (HH:MM): ";
    cin >> a.time;

    appointments.push_back(a);
    cout << "Appointment scheduled successfully!\n";
}

void viewAppointments() {
    if (appointments.empty()) {
        cout << "No appointments scheduled yet.\n";
        return;
    }
    cout << "Appointments:\n";
    for (const auto &a : appointments) {
        cout << "ID: " << a.id
             << ", Patient ID: " << a.patientId
             << ", Doctor ID: " << a.doctorId
             << ", Date: " << a.date
             << ", Time: " << a.time << "\n";
    }
}

void addMedicalHistory() {
    string patientId, historyEntry;
    cout << "Enter Patient ID: ";
    cin >> patientId;
    if (patients.find(patientId) == patients.end()) {
        cout << "Patient not found!\n";
        return;
    }
    cout << "Enter Medical History Entry: ";
    cin.ignore();
    getline(cin, historyEntry);

    medicalHistories[patientId].patientId = patientId;
    medicalHistories[patientId].history.push_back(historyEntry);
    cout << "Medical history added successfully!\n";
}

void viewMedicalHistory() {
    string patientId;
    cout << "Enter Patient ID: ";
    cin >> patientId;
    if (medicalHistories.find(patientId) == medicalHistories.end()) {
        cout << "No medical history found for this patient.\n";
        return;
    }
    cout << "Medical History for Patient ID " << patientId << ":\n";
    for (const auto &entry : medicalHistories[patientId].history) {
        cout << "- " << entry << "\n";
    }
}

void cancelAppointment() {
    string appointmentId;
    cout << "Enter Appointment ID to cancel: ";
    cin >> appointmentId;

    auto it = remove_if(appointments.begin(), appointments.end(),
                        [&appointmentId](const Appointment &a) {
                            return a.id == appointmentId;
                        });
    if (it != appointments.end()) {
        appointments.erase(it, appointments.end());
        cout << "Appointment canceled successfully!\n";
    } else {
        cout << "Appointment not found!\n";
    }
}

void hospitalManagementSystem() {
    int choice;
    do {
        cout << "\nWelcome to Hospital Management System\n";
        cout << "1. Add Patient\n";
        cout << "2. Add Doctor\n";
        cout << "3. Schedule Appointment\n";
        cout << "4. View Appointments\n";
        cout << "5. Add Medical History\n";
        cout << "6. View Medical History\n";
        cout << "7. Cancel Appointment\n";
        cout << "8. Exit\n";
        cout << "Your Choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            addPatient();
            break;
        case 2:
            addDoctor();
            break;
        case 3:
            scheduleAppointment();
            break;
        case 4:
            viewAppointments();
            break;
        case 5:
            addMedicalHistory();
            break;
        case 6:
            viewMedicalHistory();
            break;
        case 7:
            cancelAppointment();
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
