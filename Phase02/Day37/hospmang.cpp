#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
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

bool isAppointmentConflict(const string &doctorId, const string &patientId, const string &date, const string &time) {
    for (const auto &a : appointments) {
        if ((a.doctorId == doctorId || a.patientId == patientId) && a.date == date && a.time == time) {
            return true;
        }
    }
    return false;
}

void scheduleAppointment() {
    Appointment a;
    a.id = generateAppointmentId();
    cout << "Generated Appointment ID: " << a.id << "\n";
    cout << "Enter Patient ID: ";
    cin >> a.patientId;

    if (patients.find(a.patientId) == patients.end()) {
        cout << "Error: Patient ID not found!\n";
        return;
    }

    cout << "Enter Doctor ID: ";
    cin >> a.doctorId;

    if (doctors.find(a.doctorId) == doctors.end()) {
        cout << "Error: Doctor ID not found!\n";
        return;
    }

    cout << "Enter Date (YYYY-MM-DD): ";
    cin >> a.date;
    cout << "Enter Time (HH:MM): ";
    cin >> a.time;

    if (isAppointmentConflict(a.doctorId, a.patientId, a.date, a.time)) {
        cout << "Error: Appointment conflict! Either the doctor or patient is already booked at this date and time.\n";
        return;
    }

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
