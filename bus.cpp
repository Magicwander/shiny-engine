// Include necessary header files
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cctype>
#include <sstream>
#include <vector>
#include <algorithm>

// Define color codes for console output
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define BLUE    "\033[34m"

using namespace std;

// Function prototypes for input validation (DATA VALIDATION)
bool isValidPhoneNumber(const string& phoneNumber);
bool isValidDate(const string& date);
int stringToInt(const string& str);
bool isAllDigits(const string& str);

// Function for login
void login();
void registration();
void forgot();

// Functions for passenger
void passengerMenu();
void bookTicket();
void viewSchedules();
void cancelTicket();
void viewTicketStatus();
void updatePassengerDetails();
void viewBookingHistory();

// Functions for admin
void adminMenu();
void addBus();
void removeBus();
void viewAllBuses();
void viewAllBookings();
void viewAllPassengers();
void updateBusDetails();
void updateBusSchedule();

// Global variables
vector<string> buses;
vector<string> bookings;
vector<string> passengers;

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
        cout << "*"<<RED<<"                                               BUS MANAGEMENT SYSTEM LOGIN                                         "<<RESET<<"*" << endl;
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
            passengerMenu();
        } else if (userid.substr(0, 2) == "ad") {
            cout <<RED<<                 userid <<RESET<< "\nYour LOGIN is successful\n";
            adminMenu();
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

// Access to passenger part
void passengerMenu() {
    system("cls");
    int choice;
    do {
        cout <<RED<<"                                                     Passenger Menu" <<RESET<< endl;
        cout <<"\n";
        cout <<"\n";
        cout <<"\n";

        cout << "\t                         View Schedules" << endl;
        cout <<"\n";
        cout << "\t                         Book a Ticket" << endl;
        cout <<"\n";
        cout << "\t                         Cancel a Ticket" << endl;
        cout <<"\n";
        cout << "\t                         Update Personal Information" << endl;
        cout <<"\n";
        cout << "\t                         View Ticket Status" << endl;
        cout <<"\n";
        cout << "\t                         View Booking History" << endl;
        cout <<"\n";
        cout << "\t                         Back to Main Menu" << endl;
        cout <<"\n";
        cout <<"\n";
        cout << "\t                         Enter your choice"<<BLUE<<"(1/2/3/4/5/6/7/8): "<<RESET;
        cin >> choice;
        switch (choice) {
            case 1:
                viewSchedules();
                break;
            case 2:
                bookTicket();
                break;
            case 3:
                cancelTicket();
                break;
            case 4:
                updatePassengerDetails();
                break;
            case 5:
                viewTicketStatus();
                break;
            case 6:
                viewBookingHistory();
                break;
            case 7:
                main();
                break;
            default:
                system("cls");
                cout <<"              Invalid choice. Try again." << endl;
        }
    } while (choice != 7);
}

// Passenger contents
// Function to book a ticket
void bookTicket() {
    system("cls");
    ofstream outfile("bookings.txt", ios::app);
    if (!outfile) {
        cout <<RED<< "                    Error opening file for writing." <<RESET<< endl;
        return;
    }
    cout <<BLUE<<"                                     Book your ticket\n\n\n\n"<<RESET;
    string name, busNumber, date;
    cout << "\t                    Enter your username : ";
    cin.ignore();
    getline(cin, name);
    cout << "\t                    Enter bus number : ";
    getline(cin, busNumber);
    cout << "\t                    Enter travel date "<<RED<<"(YYYY-MM-DD) :"<<RESET;
    getline(cin, date);

    outfile << name << ";" << busNumber << ";" << date << ";Pending\n";
    outfile.close();

    if (outfile.good()) {
        cout <<BLUE<< "\t              Ticket booked successfully!" <<RESET<< endl;
    } else {
        cout <<RED<< "\t              Error closing the file."  <<RESET<< endl;
    }
}

// Function to display available schedules
void viewSchedules(){
    system("cls");
    cout<<RED<<"                                                         AVAILABLE SCHEDULES         \n "<<RESET;
    cout <<"\n";
    cout <<"\n";
    cout <<"\n";

    cout<<BLUE<<"                   Bus 1     \n"<<RESET;
    cout <<"\n";

    cout<<"    Route: City A to City B\n";
    cout <<"\n";
    cout <<"\n";

    cout<<BLUE<<"                   Bus 2         \n"<<RESET;
    cout <<"\n";

    cout<<"    Route: City C to City D\n";
    cout <<"\n";
    cout <<"\n";

    cout<<BLUE<<"                   Bus 3      \n"<<RESET;
    cout <<"\n";

    cout<<"    Route: City E to City F\n";
    cout <<"\n";
    cout <<"\n";

    cout<<BLUE<<"                   Bus 4     \n"<<RESET;
    cout <<"\n";

    cout<<"    Route: City G to City H\n";
    cout <<"\n";
    cout <<"\n";

    cout<<BLUE<<"                   Bus 5    \n"<<RESET;
    cout <<"\n";

    cout<<"    Route: City I to City J\n";
    cout <<"\n";
    cout <<"\n";

    cout<<BLUE<<"                   Bus 6    \n"<<RESET;
    cout <<"\n";

    cout<<"    Route: City K to City L\n";
    cout <<"\n";
    cout <<"\n";
}

// Function to cancel a ticket
void cancelTicket() {
    system("cls");
    cout <<BLUE<<"                                       Ticket Cancel Form\n\n\n\n"<<RESET;
    ofstream outfile("cancelbookings.txt", ios::app);
    if (!outfile) {
        cout <<RED<< "Error opening file for writing." <<RESET<< endl;
        return;
    }

    string bookingname;
    cout << "\t                    Enter your booking sender's name: ";
    cin.ignore();
    getline(cin, bookingname);
    outfile << bookingname << "\n";

    string bookingDate;
    cout << "\t                    Enter your booking & travel Date "<<RED<<"(YYYY-MM-DD): "<<RESET;
    cin.ignore();
    getline(cin, bookingDate);
    outfile << bookingDate << "\n";

    string bookingDetails;
    cout << "\t                    Enter your booking & travel Details: ";
    cin.ignore();
    getline(cin, bookingDetails);
    outfile << bookingDetails << "\n";

    string reasonforcancel;
    cout << "\t                    Reason for Canceling: ";
    cin.ignore();
    getline(cin, reasonforcancel);
    outfile << reasonforcancel << "\n";

    outfile.close();

    cout <<BLUE<< "\t                Ticket Canceled successfully!" <<RESET<< endl;
}

// Function to view ticket status
void viewTicketStatus() {
    system("cls");

    ifstream bookedTicketsFile("bookings.txt");
    ifstream canceledTicketsFile("cancelbookings.txt");

    if (!bookedTicketsFile) {
        cout <<RED<< "\t                Error opening bookings.txt for reading." <<RESET<< endl;
        return;
    }
    if (!canceledTicketsFile) {
        cout << "Error opening cancelbookings.txt for reading." << endl;
        return;
    }

    cout << "Booked Tickets:" << endl;
    string line;
    while (getline(bookedTicketsFile, line)) {
        size_t pos1 = line.find(';');
        size_t pos2 = line.find(';', pos1 + 1);
        size_t pos3 = line.find(';', pos2 + 1);

        if (pos1 != string::npos && pos2 != string::npos && pos3 != string::npos) {
            string name = line.substr(0, pos1);
            string busNumber = line.substr(pos1 + 1, pos2 - pos1 - 1);
            string date = line.substr(pos2 + 1, pos3 - pos2 - 1);
            string status = line.substr(pos3 + 1);

            cout << "Bus Number: " << busNumber << "\n"<< " Date: " << date <<"\n"<< " Status: " << status<<"\n" << endl;
        } else {
            cout << "Error parsing booked tickets data." << endl;
        }
    }

    cout << "Canceled Tickets:" << endl;
    while (getline(canceledTicketsFile, line)) {
        size_t pos1 = line.find(';');
        if (pos1 != string::npos) {
            string date = line.substr(0, pos1);

            cout << "Date : " << date << "\n" << endl;
        } else {
            cout << "Error parsing canceled ticket data." << endl;
        }
    }

    bookedTicketsFile.close();
    canceledTicketsFile.close();
}

// Function to update passenger details
void updatePassengerDetails() {
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

// Function to view booking history
void viewBookingHistory() {
    system("cls");
    ifstream infile("bookings.txt");
    if (!infile) {
        cout << "Error opening bookings.txt for reading." << endl;
        return;
    }

    string line;
    cout << "\nBooking History:" << endl;
    while (getline(infile, line)) {
        size_t pos1 = line.find(';');
        size_t pos2 = line.find(';', pos1 + 1);
        size_t pos3 = line.find(';', pos2 + 1);

        if (pos1 != string::npos && pos2 != string::npos && pos3 != string::npos) {
            string username = line.substr(0, pos1);
            string busNumber = line.substr(pos1 + 1, pos2 - pos1 - 1);
            string date = line.substr(pos2 + 1, pos3 - pos2 - 1);
            string status = line.substr(pos3 + 1);

            cout << "Username: " << username << "\nBus Number: " << busNumber
                 << "\nDate: " << date << "\nStatus: " << status << "\n" << endl;
        } else {
            cout << "Error parsing booking history data." << endl;
        }
    }
    infile.close();
}

// Access to admin part
void adminMenu() {
    int choice;
    do {
        cout <<RED<<"\t\t\t                                    Admin Menu" <<RESET<< endl;
        cout<<"\n";
        cout<<"\n";
        cout <<"\t\t\t                       1. Add Bus" << endl;
        cout <<"\t\t\t                       2. Remove Bus" << endl;
        cout <<"\t\t\t                       3. View All Buses" << endl;
        cout <<"\t\t\t                       4. View All Bookings" << endl;
        cout <<"\t\t\t                       5. View All Passengers" << endl;
        cout <<"\t\t\t                       6. Update Bus Details" << endl;
        cout <<"\t\t\t                       7. Update Bus Schedule" << endl;
        cout <<"\t\t\t                       8. Back to Main Menu" << endl;
        cout <<BLUE<<"\t\t\t                            Enter your choice: "<<RESET;
        cin >> choice;
        switch (choice) {
            case 1:
                addBus();
                break;
            case 2:
                removeBus();
                break;
            case 3:
                viewAllBuses();
                break;
            case 4:
                viewAllBookings();
                break;
            case 5:
                viewAllPassengers();
                break;
            case 6:
                updateBusDetails();
                break;
            case 7:
                updateBusSchedule();
                break;
            case 8:
                main();
                break;
            default:
                cout << "Invalid choice. Try again." << endl;
        }
    } while (choice != 8);
}

// Admin contents
// Function to add a bus
void addBus() {
    system("cls");
    string busNumber, route, capacity;
    cout << "Enter the bus number: ";
    cin >> busNumber;
    cout << "Enter the route: ";
    cin >> route;
    cout << "Enter the capacity: ";
    cin >> capacity;

    ofstream outfile("buses.txt", ios::app);
    if (!outfile) {
        cout << "Error opening file for writing." << endl;
        return;
    }

    outfile << busNumber << ";" << route << ";" << capacity << endl;
    outfile.close();

    cout << "Bus added successfully!" << endl;
}

// Function to remove a bus
void removeBus() {
    system("cls");
    string busNumber;
    cout << "Enter the bus number to remove: ";
    cin >> busNumber;

    ifstream infile("buses.txt");
    ofstream tempFile("temp.txt");
    if (!infile || !tempFile) {
        cout << "Error opening file." << endl;
        return;
    }

    string line;
    bool found = false;

    while (getline(infile, line)) {
        size_t pos = line.find(';');
        if (pos != string::npos && line.substr(0, pos) == busNumber) {
            found = true;
            continue;
        }
        tempFile << line << endl;
    }

    infile.close();
    tempFile.close();

    remove("buses.txt");
    rename("temp.txt", "buses.txt");

    if (found) {
        cout << "Bus removed successfully!" << endl;
    } else {
        cout << "Bus not found!" << endl;
    }
}

// Function to view all buses
void viewAllBuses() {
    system("cls");
    ifstream infile("buses.txt");
    if (!infile) {
        cout << "Error opening buses.txt for reading." << endl;
        return;
    }

    string line;
    cout << "\nAll Buses:" << endl;
    while (getline(infile, line)) {
        size_t pos1 = line.find(';');
        size_t pos2 = line.find(';', pos1 + 1);

        if (pos1 != string::npos && pos2 != string::npos) {
            string busNumber = line.substr(0, pos1);
            string route = line.substr(pos1 + 1, pos2 - pos1 - 1);
            string capacity = line.substr(pos2 + 1);

            cout << "Bus Number: " << busNumber << "\nRoute: " << route
                 << "\nCapacity: " << capacity << "\n" << endl;
        } else {
            cout << "Error parsing bus data." << endl;
        }
    }
    infile.close();
}

// Function to view all bookings
void viewAllBookings() {
    system("cls");
    ifstream infile("bookings.txt");
    if (!infile) {
        cout << "Error opening bookings.txt for reading." << endl;
        return;
    }

    string line;
    cout << "\nAll Bookings:" << endl;
    while (getline(infile, line)) {
        size_t pos1 = line.find(';');
        size_t pos2 = line.find(';', pos1 + 1);
        size_t pos3 = line.find(';', pos2 + 1);

        if (pos1 != string::npos && pos2 != string::npos && pos3 != string::npos) {
            string username = line.substr(0, pos1);
            string busNumber = line.substr(pos1 + 1, pos2 - pos1 - 1);
            string date = line.substr(pos2 + 1, pos3 - pos2 - 1);
            string status = line.substr(pos3 + 1);

            cout << "Username: " << username << "\nBus Number: " << busNumber
                 << "\nDate: " << date << "\nStatus: " << status << "\n" << endl;
        } else {
            cout << "Error parsing booking data." << endl;
        }
    }
    infile.close();
}

// Function to view all passengers
void viewAllPassengers() {
    system("cls");
    ifstream infile("records.txt");
    if (!infile) {
        cout << "Error opening records.txt for reading." << endl;
        return;
    }

    string line;
    cout << "\nAll Passengers:" << endl;
    while (getline(infile, line)) {
        size_t pos1 = line.find(' ');
        size_t pos2 = line.find(' ', pos1 + 1);
        size_t pos3 = line.find(' ', pos2 + 1);
        size_t pos4 = line.find(' ', pos3 + 1);

        if (pos1 != string::npos && pos2 != string::npos && pos3 != string::npos && pos4 != string::npos) {
            string username = line.substr(0, pos1);
            string password = line.substr(pos1 + 1, pos2 - pos1 - 1);
            string phoneNumber = line.substr(pos2 + 1, pos3 - pos2 - 1);
            string address = line.substr(pos3 + 1, pos4 - pos3 - 1);
            string age = line.substr(pos4 + 1);

            cout << "Username: " << username << "\nPassword: " << password
                 << "\nPhone Number: " << phoneNumber << "\nAddress: " << address
                 << "\nAge: " << age << "\n" << endl;
        } else {
            cout << "Error parsing passenger data." << endl;
        }
    }
    infile.close();
}

// Function to update bus details
void updateBusDetails() {
    system("cls");
    string busNumber, newRoute, newCapacity;
    cout << "Enter the bus number to update: ";
    cin >> busNumber;

    ifstream infile("buses.txt");
    ofstream tempFile("temp.txt");
    if (!infile || !tempFile) {
        cout << "Error opening file." << endl;
        return;
    }

    string line;
    bool found = false;

    while (getline(infile, line)) {
        size_t pos1 = line.find(';');
        size_t pos2 = line.find(';', pos1 + 1);

        if (pos1 != string::npos && pos2 != string::npos && line.substr(0, pos1) == busNumber) {
            found = true;
            cout << "Enter new route: ";
            cin >> newRoute;
            cout << "Enter new capacity: ";
            cin >> newCapacity;
            tempFile << busNumber << ";" << newRoute << ";" << newCapacity << endl;
        } else {
            tempFile << line << endl;
        }
    }

    infile.close();
    tempFile.close();

    remove("buses.txt");
    rename("temp.txt", "buses.txt");

    if (found) {
        cout << "Bus details updated successfully!" << endl;
    } else {
        cout << "Bus not found!" << endl;
    }
}

// Function to update bus schedule
void updateBusSchedule() {
    system("cls");
    string busNumber, newSchedule;
    cout << "Enter the bus number to update the schedule: ";
    cin >> busNumber;

    ifstream infile("buses.txt");
    ofstream tempFile("temp.txt");
    if (!infile || !tempFile) {
        cout << "Error opening file." << endl;
        return;
    }

    string line;
    bool found = false;

    while (getline(infile, line)) {
        size_t pos1 = line.find(';');
        size_t pos2 = line.find(';', pos1 + 1);

        if (pos1 != string::npos && pos2 != string::npos && line.substr(0, pos1) == busNumber) {
            found = true;
            cout << "Enter new schedule: ";
            cin >> newSchedule;
            tempFile << busNumber << ";" << newSchedule << ";" << line.substr(pos2 + 1) << endl;
        } else {
            tempFile << line << endl;
        }
    }

    infile.close();
    tempFile.close();

    remove("buses.txt");
    rename("temp.txt", "buses.txt");

    if (found) {
        cout << "Bus schedule updated successfully!" << endl;
    } else {
        cout << "Bus not found!" << endl;
    }
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
