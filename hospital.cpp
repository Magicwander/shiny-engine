// Include necessary header files
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cctype>
#include <sstream>

// Define color codes for console output
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define BLUE    "\033[34m"

using namespace std;

// Function prototypes for input validation(DATA VALIDATION)
bool isValidPhoneNumber(const string& phoneNumber);
bool isValidDate(const string& date);
int stringToInt(const string& str);
bool isAllDigits(const string& str);

// Function for login
void login();
void registration();
void forgot();

//functions for patient
void patientMenu();
void bookAppointment();
void viewDoctors();
void cancelAppointment();
void viewAppointmentStatus();
void updatePatientDetails();
void viewMedicalRecords();
void viewPrescriptions();

//functions for doctor
void doctorMenu();
void viewAppointments();
void viewPatientRecords();
void updateMedicalRecords();
void prescribeMedication();
void viewCanceledAppointments();

int main() {
    int choice;
    // Display main menu
    do {
        cout << "************************************************************************************************************************" << endl;
        cout << "*                                                                                                                      *"<< endl;
        cout << "*                                                                                                                      *"<< endl;
        cout << "*                                                                                                                      *"<< endl;
        cout << "*                                                                                                                      *"<< endl;
        cout << "*                                                                                                                      *"<< endl;
        cout << "*                                                                                                                      *" << endl;
        cout << "*                                                                                                                      *" << endl;
        cout << "*                                                                                                                      *" << endl;
        cout << "*                                                                                                                      *" << endl;
        cout << "*"<<RED<<"                                               HOSPITAL MANAGEMENT SYSTEM LOGIN                                         "<<RESET<<"*" << endl;
        cout << "*                                                                                                                      *" << endl;
        cout << "*                                      +--------------------------------------------+                                  *" << endl;
        cout << "*                                      |                                            |                                  *" << endl;
        cout << "*                                      |                                            |                                  *" << endl;
        cout << "*                                      |"<<"             Login                          "<<"|                                  *" << endl;
        cout << "*                                      |"<<"             Registration                   "<<"|                                  *" << endl;
        cout << "*                                      |"<<"             Forgot Password                "<<"|                                  *" << endl;
        cout << "*                                      |"<<"             Exit                           "<<"|                                  *" << endl;
        cout << "*                                      |                                            |                                  *" << endl;
        cout << "*                                      |                                            |                                  *" << endl;
        cout << "*                                      +--------------------------------------------+                                  *" << endl;
        cout << "*                                                                                                                      *" << endl;
        cout << "*                                                                                                                      *" << endl;
        cout << "*                                                                                                                      *" << endl;
        cout << "************************************************************************************************************************" << endl;
        cout <<              "Enter your choice"<<BLUE<<"(1/2/3/4):"<<RESET;
        cin >> choice;
        switch (choice) {
            case 1:
                login();
                break;
            case 2:
                registration();
                break;
            case 3:
                forgot();
                break;
            case 4:
                cout <<RED<< "                                             Exiting the system." <<RESET<< endl;
                break;
            default:
                cout <<RED<< "                                             Invalid choice. Try again." <<RESET<< endl;
        }
    } while (choice != 4);

    return 0;
}

// Login part
void login() {
    system("cls");
    int count = 0;
    string userid, password, id, pass;

    system("cls");
    cout <<BLUE<<"\t\t\t                                       LOGIN FORM  " <<RESET<< endl;
    cout <<"\n";
    cout <<"\n";
    cout <<"\n";
    cout <<"\n ";
    cout <<"\t\t\t                       Username: ";
    cin >> userid;
    cout<<"\n";

    cout <<"\t\t\t                       Password: ";
    cin >> password;

    ifstream input("records.txt");

    while (input >> id >> pass) {
        if (id == userid && pass == password) {
            count = 1;
            system("cls");
            break;
        }
    }
    input.close();

    if (count == 1) {
        if (userid.substr(0, 2) == "pa") {
            cout <<RED<<                 userid <<RESET<< "\nYour LOGIN is successful\n";
            patientMenu();
        } else if (userid.substr(0, 2) == "do") {
            cout <<RED<<                 userid <<RESET<< "\nYour LOGIN is successful\n";
            doctorMenu();
        } else {
            cout <<RED<< "                    \nLOGIN ERROR\nInvalid user type. Please check your username.\n"<<RESET<<endl;
            main();
        }
    } else {
        cout <<RED<<"                        \nLOGIN ERROR\nPlease check your username and password\n"<<RESET<<endl;
        main();
    }
}

// Registration function
void registration() {
    string ruserid, rpassword, rpnumber, address, age;
    system("cls");
    cout <<BLUE<< "\t\t\t                                       REGISTRATION" <<RESET<< endl;
    cout << "\t\t\t                        Create a username: ";
    cin >> ruserid;

    do {
        cout << "\t\t\t                        Enter the Phone number (10 digits): ";
        cin >> rpnumber;
    } while (!isValidPhoneNumber(rpnumber));

    cout << "\t\t\t                        Enter the address: ";
    cin >> address;
    cout << "\t\t\t                        Enter the age: ";
    cin >> age;
    cout << "\t\t\t                        Create a password: ";
    cin >> rpassword;

    ofstream f1("records.txt", ios::app);
    f1 << ruserid << " " << rpassword << " " << rpnumber << " " << address << " " << age << endl;
    system("cls");
    cout <<BLUE<< "\n\t\t\t                                       Registration is successful\n"<<RESET;
    main();
}

// Password recovery function
void forgot() {
    int option;
    system("cls");
    cout <<RED<<"\t\t\t                       You forgot the password? No worries\n"<<RESET;
    cout <<"                             Press 1 to search your id by username" << endl;
    cout <<"                             Press 2 to get back to the main menu" << endl;
    cout <<"\t\t\t                       Enter your choice: ";
    cin >> option;

    switch (option) {
        case 1: {
            int count = 0;
            string suserid, sid, spass;
            cout << "\n\t\t\t            Enter the username which you remembered: ";
            cin >> suserid;

            ifstream f2("records.txt");
            while (f2 >> sid >> spass) {
                if (sid == suserid) {
                    count = 1;
                    break;
                }
            }
            f2.close();

            if (count == 1) {
                cout <<BLUE<< "\n\n            Your account is found!\n"<<RESET;
                cout <<BLUE<< "\n\n            Your password is: " <<RESET<< spass << endl;
                main();
            } else {
                cout <<RED<< "\n\t            Sorry! Your account is not found!\n"<<RESET;
                main();
            }
            break;
        }
        case 2:
            main();
            break;
        default:
            cout <<RED<< "\t\t\t               Wrong choice! Please try again" <<RESET<< endl;
            forgot();
            main();
    }
}

// Access to patient part
void patientMenu() {
    system("cls");
    int choice;
    do {
        cout <<RED<<"                                                     Patient Menu" <<RESET<< endl;
        cout <<"\n";
        cout <<"\n";
        cout <<"\n";

        cout << "\t                         View Doctors" << endl;
        cout <<"\n";
        cout << "\t                         Book an Appointment" << endl;
        cout <<"\n";
        cout << "\t                         Cancel an Appointment" << endl;
        cout <<"\n";
        cout << "\t                         Update Personal Information" << endl;
        cout <<"\n";
        cout << "\t                         View Appointment Status" << endl;
        cout <<"\n";
        cout << "\t                         View Medical Records" << endl;
        cout <<"\n";
        cout << "\t                         View Prescriptions" << endl;
        cout <<"\n";
        cout << "\t                         Back to Main Menu" << endl;
        cout <<"\n";
        cout <<"\n";
        cout << "\t                         Enter your choice"<<BLUE<<"(1/2/3/4/5/6/7/8/9): "<<RESET;
        cin >> choice;
        switch (choice) {
            case 1:
                viewDoctors();
                break;
            case 2:
                bookAppointment();
                break;
            case 3:
                cancelAppointment();
                break;
            case 4:
                updatePatientDetails();
                break;
            case 5:
                viewAppointmentStatus();
                break;
            case 6:
                viewMedicalRecords();
                break;
            case 7:
                viewPrescriptions();
                break;
            case 8:
                main();
                break;
            default:
                system("cls");
                cout <<"              Invalid choice. Try again." << endl;
        }
    } while (choice != 8);
}

// Patient contents
// Function to book an appointment
void bookAppointment() {
    system("cls");
    ofstream outfile("appointments.txt", ios::app);
    if (!outfile) {
        cout <<RED<< "                    Error opening file for writing." <<RESET<< endl;
        return;
    }
    cout <<BLUE<<"                                     Book your appointment\n\n\n\n"<<RESET;
    string name, doctorName, date;
    cout << "\t                    Enter your username : ";
    cin.ignore();
    getline(cin, name);
    cout << "\t                    Enter doctor's name : ";
    getline(cin, doctorName);
    cout << "\t                    Enter preferred date "<<RED<<"(YYYY-MM-DD) :"<<RESET;
    getline(cin, date);

    outfile << name << ";" << doctorName << ";" << date << ";Pending\n";
    outfile.close();

    if (outfile.good()) {
        cout <<BLUE<< "\t              Appointment booked successfully!" <<RESET<< endl;
    } else {
        cout <<RED<< "\t              Error closing the file."  <<RESET<< endl;
    }
}

// Function to display available doctors
void viewDoctors(){
    system("cls");
    cout<<RED<<"                                                         AVAILABLE DOCTORS         \n "<<RESET;
    cout <<"\n";
    cout <<"\n";
    cout <<"\n";

    cout<<BLUE<<"                   Dr. John Doe     \n"<<RESET;
    cout <<"\n";

    cout<<"    Specialization: Cardiology\n";
    cout <<"\n";
    cout <<"\n";

    cout<<BLUE<<"                   Dr. Jane Smith         \n"<<RESET;
    cout <<"\n";

    cout<<"    Specialization: Dermatology\n";
    cout <<"\n";
    cout <<"\n";

    cout<<BLUE<<"                   Dr. Robert Brown      \n"<<RESET;
    cout <<"\n";

    cout<<"    Specialization: Orthopedics\n";
    cout <<"\n";
    cout <<"\n";

    cout<<BLUE<<"                   Dr. Emily Davis     \n"<<RESET;
    cout <<"\n";

    cout<<"    Specialization: Pediatrics\n";
    cout <<"\n";
    cout <<"\n";

    cout<<BLUE<<"                   Dr. Michael Wilson    \n"<<RESET;
    cout <<"\n";

    cout<<"     Specialization: Neurology\n";
    cout <<"\n";
    cout <<"\n";

    cout<<BLUE<<"                   Dr. Jessica Moore    \n"<<RESET;
    cout <<"\n";

    cout<<"    Specialization: Gynecology\n";
    cout <<"\n";
    cout <<"\n";
}

// Function to cancel an appointment
void cancelAppointment() {
    system("cls");
    cout <<BLUE<<"                                       Appointment Cancel Form\n\n\n\n"<<RESET;
    ofstream outfile("cancelappointments.txt", ios::app);
    if (!outfile) {
        cout <<RED<< "Error opening file for writing." <<RESET<< endl;
        return;
    }

    string appointmentname;
    cout << "\t                    Enter your appointment sender's name: ";
    cin.ignore();
    getline(cin, appointmentname);
    outfile << appointmentname << "\n";

    string appointmentDate;
    cout << "\t                    Enter your appointment & service Date "<<RED<<"(YYYY-MM-DD): "<<RESET;
    cin.ignore();
    getline(cin, appointmentDate);
    outfile << appointmentDate << "\n";

    string appointmentDetails;
    cout << "\t                    Enter your appointment & service Details: ";
    cin.ignore();
    getline(cin, appointmentDetails);
    outfile << appointmentDetails << "\n";

    string reasonforcancel;
    cout << "\t                    Reason for Canceling: ";
    cin.ignore();
    getline(cin, reasonforcancel);
    outfile << reasonforcancel << "\n";

    outfile.close();

    cout <<BLUE<< "\t                Appointment Canceled successfully!" <<RESET<< endl;
}

// Function to view appointment status
void viewAppointmentStatus() {
    system("cls");

    ifstream bookedAppointmentsFile("appointments.txt");
    ifstream canceledAppointmentsFile("cancelappointments.txt");

    if (!bookedAppointmentsFile) {
        cout <<RED<< "\t                Error opening appointments.txt for reading." <<RESET<< endl;
        return;
    }
    if (!canceledAppointmentsFile) {
        cout << "Error opening cancelappointments.txt for reading." << endl;
        return;
    }

    cout << "Booked Appointments:" << endl;
    string line;
    while (getline(bookedAppointmentsFile, line)) {
        size_t pos1 = line.find(';');
        size_t pos2 = line.find(';', pos1 + 1);
        size_t pos3 = line.find(';', pos2 + 1);

        if (pos1 != string::npos && pos2 != string::npos && pos3 != string::npos) {
            string name = line.substr(0, pos1);
            string doctorName = line.substr(pos1 + 1, pos2 - pos1 - 1);
            string date = line.substr(pos2 + 1, pos3 - pos2 - 1);
            string status = line.substr(pos3 + 1);

            cout << "Doctor Name: " << doctorName << "\n"<< " Date: " << date <<"\n"<< " Status: " << status<<"\n" << endl;
        } else {
            cout << "Error parsing booked appointments data." << endl;
        }
    }

    cout << "Canceled Appointments:" << endl;
    while (getline(canceledAppointmentsFile, line)) {
        size_t pos1 = line.find(';');
        if (pos1 != string::npos) {
            string date = line.substr(0, pos1);

            cout << "Date : " << date << "\n" << endl;
        } else {
            cout << "Error parsing canceled appointment data." << endl;
        }
    }

    bookedAppointmentsFile.close();
    canceledAppointmentsFile.close();
}

// Function to update patient details
void updatePatientDetails() {
    system("cls");
    string username, newPassword, phoneNumber, address, age;

    cout << "Enter the username of the account you want to update: ";
    cin >> username;

    ifstream infile("records.txt");
    ofstream tempFile("temp.txt");
    if (!infile || !tempFile) {
        cout << "Error opening file." << endl;
        return;
    }

    string id, pass, phone, addr, ag, line;
    bool found = false;

    while (infile >> id >> pass >> phone >> addr >> ag) {
        if (id == username) {
            found = true;

            cout << "Enter new password: ";
            cin >> newPassword;
            cout << "Enter new phone number: ";
            cin >> phoneNumber;
            cout << "Enter new address: ";
            cin >> address;
            cout << "Enter new age: ";
            cin >> age;

            tempFile << username << " " << newPassword << " " << phoneNumber << " " << address << " " << age << endl;

        } else {
            tempFile << id << " " << pass << " " << phone << " " << addr << " " << ag << endl;
        }
    }

    infile.close();
    tempFile.close();

    remove("records.txt");
    rename("temp.txt", "records.txt");

    if (found) {
        cout << "Details updated successfully!" << endl;
    } else {
        cout << "User not found!" << endl;
    }
}

// Function to view medical records
void viewMedicalRecords() {
    system("cls");
    ifstream infile("medical_records.txt");
    if (!infile) {
        cout << "Error opening medical_records.txt for reading." << endl;
        return;
    }

    string line;
    cout << "\nMedical Records:" << endl;
    while (getline(infile, line)) {
        size_t pos1 = line.find(';');
        size_t pos2 = line.find(';', pos1 + 1);
        size_t pos3 = line.find(';', pos2 + 1);

        if (pos1 != string::npos && pos2 != string::npos && pos3 != string::npos) {
            string username = line.substr(0, pos1);
            string diagnosis = line.substr(pos1 + 1, pos2 - pos1 - 1);
            string treatment = line.substr(pos2 + 1, pos3 - pos2 - 1);
            string additionalNotes = line.substr(pos3 + 1);

            cout << "Username: " << username << "\nDiagnosis: " << diagnosis
                 << "\nTreatment: " << treatment << "\nAdditional Notes: " << additionalNotes << "\n" << endl;
        } else {
            cout << "Error parsing medical records data." << endl;
        }
    }
    infile.close();
}

// Function to view prescriptions
void viewPrescriptions() {
    system("cls");
    ifstream infile("prescriptions.txt");
    if (!infile) {
        cout << "Error opening prescriptions.txt for reading." << endl;
        return;
    }

    string line;
    cout << "\nPrescriptions:" << endl;
    while (getline(infile, line)) {
        size_t pos1 = line.find(';');
        size_t pos2 = line.find(';', pos1 + 1);

        if (pos1 != string::npos && pos2 != string::npos) {
            string username = line.substr(0, pos1);
            string medication = line.substr(pos1 + 1, pos2 - pos1 - 1);
            string dosage = line.substr(pos2 + 1);

            cout << "Username: " << username << "\nMedication: " << medication
                 << "\nDosage: " << dosage << "\n" << endl;
        } else {
            cout << "Error parsing prescriptions data." << endl;
        }
    }
    infile.close();
}

// Access to doctor part
void doctorMenu() {
    int choice;
    do {
        cout <<RED<<"\t\t\t                                    Doctor Menu" <<RESET<< endl;
        cout<<"\n";
        cout<<"\n";
        cout <<"\t\t\t                       1. View Appointments" << endl;
        cout <<"\t\t\t                       2. View Patient Records" << endl;
        cout <<"\t\t\t                       3. Update Medical Records" << endl;
        cout <<"\t\t\t                       4. Prescribe Medication" << endl;
        cout <<"\t\t\t                       5. View Canceled Appointments" << endl;
        cout <<"\t\t\t                       6. Back to Main Menu" << endl;
        cout <<BLUE<<"\t\t\t                            Enter your choice: "<<RESET;
        cin >> choice;
        switch (choice) {
            case 1:
                viewAppointments();
                break;
            case 2:
                viewPatientRecords();
                break;
            case 3:
                updateMedicalRecords();
                break;
            case 4:
                prescribeMedication();
                break;
            case 5:
                viewCanceledAppointments();
                break;
            case 6:
                main();
                break;
            default:
                cout << "Invalid choice. Try again." << endl;
        }
    } while (choice != 6);
}

// Contents of doctor
void viewAppointments() {
    system("cls");
    ifstream infile("appointments.txt");
    if (!infile) {
        cout <<RED<< "Error opening appointments.txt for reading." <<RESET<< endl;
        return;
    }

    string line;
    cout <<BLUE<<"\t\t\t                       \nAppointments:" <<RESET<< endl;
    while (getline(infile, line)) {
        size_t pos1 = line.find(';');
        size_t pos2 = line.find(';', pos1 + 1);
        size_t pos3 = line.find(';', pos2 + 1);
        size_t pos4 = line.find(';', pos3 + 1);

        if (pos1 != string::npos && pos2 != string::npos && pos3 != string::npos && pos4 != string::npos) {
            string date = line.substr(0, pos1);
            string patientName = line.substr(pos1 + 1, pos2 - pos1 - 1);
            string doctorName = line.substr(pos2 + 1, pos3 - pos2 - 1);
            string status = line.substr(pos3 + 1);

            cout << "Appointment Date: " << date << "\nPatient Name: " << patientName << "\nDoctor Name: " << doctorName
                 << "\nStatus: " << status << "\n" << endl;
        } else {
            cout << "Error parsing appointment data." << endl;
        }
    }
    infile.close();
}

// Function to view patient records
void viewPatientRecords() {
    system("cls");
    ifstream infile("medical_records.txt");
    if (!infile) {
        cout << "Error opening medical_records.txt for reading." << endl;
        return;
    }

    string line;
    cout << "\nPatient Records:" << endl;
    while (getline(infile, line)) {
        size_t pos1 = line.find(';');
        size_t pos2 = line.find(';', pos1 + 1);
        size_t pos3 = line.find(';', pos2 + 1);

        if (pos1 != string::npos && pos2 != string::npos && pos3 != string::npos) {
            string username = line.substr(0, pos1);
            string diagnosis = line.substr(pos1 + 1, pos2 - pos1 - 1);
            string treatment = line.substr(pos2 + 1, pos3 - pos2 - 1);
            string additionalNotes = line.substr(pos3 + 1);

            cout << "Username: " << username << "\nDiagnosis: " << diagnosis
                 << "\nTreatment: " << treatment << "\nAdditional Notes: " << additionalNotes << "\n" << endl;
        } else {
            cout << "Error parsing patient records data." << endl;
        }
    }
    infile.close();
}

// Function to update medical records
void updateMedicalRecords() {
    system("cls");
    string username, diagnosis, treatment, additionalNotes;

    cout << "Enter the username for which you want to update medical records: ";
    cin.ignore();
    getline(cin, username);

    cout << "Enter the diagnosis: ";
    getline(cin, diagnosis);

    cout << "Enter the treatment: ";
    getline(cin, treatment);

    cout << "Enter any additional notes: ";
    getline(cin, additionalNotes);

    ofstream outfile("medical_records.txt", ios::app);
    if (!outfile) {
        cout << "Error opening medical_records.txt for writing." << endl;
        return;
    }

    outfile << username << ";" << diagnosis << ";" << treatment << ";" << additionalNotes << endl;
    outfile.close();

    if (outfile.good()) {
        cout << "Medical records updated successfully!" << endl;
    } else {
        cout << "Error writing to the file." << endl;
    }
}

// Function to prescribe medication
void prescribeMedication() {
    system("cls");
    string username, medication, dosage;

    cout << "Enter the username for which you want to prescribe medication: ";
    cin.ignore();
    getline(cin, username);

    cout << "Enter the medication: ";
    getline(cin, medication);

    cout << "Enter the dosage: ";
    getline(cin, dosage);

    ofstream outfile("prescriptions.txt", ios::app);
    if (!outfile) {
        cout << "Error opening prescriptions.txt for writing." << endl;
        return;
    }

    outfile << username << ";" << medication << ";" << dosage << endl;
    outfile.close();

    if (outfile.good()) {
        cout << "Prescription added successfully!" << endl;
    } else {
        cout << "Error writing to the file." << endl;
    }
}

// Function to display canceled appointments
void viewCanceledAppointments() {
    system("cls"); // Clear the screen

    ifstream infile("cancelappointments.txt");
    if (!infile) {
        cout << "Error opening cancelappointments.txt for reading." << endl;
        return;
    }

    string line;
    cout << "\nCanceled Appointments:" << endl;

    while (getline(infile, line)) {
        // Display each canceled appointment's details
        cout << "Canceled Appointment:" << endl;
        cout << "Name: " << line << endl;

        // Read and display additional details
        getline(infile, line);
        cout << "Date: " << line << endl;

        getline(infile, line);
        cout << "Details: " << line << endl;

        getline(infile, line);
        cout << "Reason for Canceling: " << line << endl;

        cout << endl;
    }

    infile.close();
}

// Here data validation part is called

// Function to validate phone number
bool isValidPhoneNumber(const string& phoneNumber) {
    if (phoneNumber.length() != 10 || !isAllDigits(phoneNumber)) {
        cout <<RED<< "Invalid phone number. It should be exactly 10 digits long." <<RESET<< endl;
        return false;
    }
    return true;
}

// Function to validate date
bool isValidDate(const string& date) {
    if (date.length() != 10 || date[4] != '-' || date[7] != '-' ||
        !isdigit(date[0]) || !isdigit(date[1]) || !isdigit(date[2]) || !isdigit(date[3]) ||
        !isdigit(date[5]) || !isdigit(date[6]) || !isdigit(date[8]) || !isdigit(date[9])) {
        cout <<RED<< "Invalid date format. Please use YYYY-MM-DD." <<RESET<< endl;
        return false;
    }

    int year = stringToInt(date.substr(0, 4));
    int month = stringToInt(date.substr(5, 2));
    int day = stringToInt(date.substr(8, 2));

    if (year < 2000 || year > 2100 || month < 1 || month > 12 || day < 1 || day > 31) {
        cout <<RED<< "Invalid date. Please enter a valid date." <<RESET<< endl;
        return false;
    }

    return true;
}

// Helper function to convert string to integer
int stringToInt(const string& str) {
    int result = 0;
    stringstream ss(str);
    ss >> result;
    return result;
}

// Helper function to check if all characters in a string are digits
bool isAllDigits(const string& str) {
    for (size_t i = 0; i < str.length(); ++i) {
        if (!isdigit(str[i])) {
            return false;
        }
    }
    return true;
}
