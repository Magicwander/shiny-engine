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

// Function prototypes for input validation
bool isValidPhoneNumber(const string& phoneNumber);
bool isValidDate(const string& date);
int stringToInt(const string& str);
bool isAllDigits(const string& str);

// Function for login
void login();
void registration();
void forgot();

// Functions for client
void clientMenu();
void bookRoom();
void viewAvailableRooms();
void checkIn();
void checkOut();
void viewBookingStatus();
void updateGuestDetails();
void viewBookingHistory();
void viewRoomStatus();

// Functions for admin
void adminMenu();
void viewAllBookings();
void viewAllGuests();
void updateRoomStatus();
void generateReport();

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
        cout << "*"<<RED<<"                                               HOTEL MANAGEMENT SYSTEM LOGIN                                         "<<RESET<<"*" << endl;
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
        if (userid.substr(0, 2) == "gu") {
            cout <<RED<<                 userid <<RESET<< "\nYour LOGIN is successful\n";
            clientMenu();
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
    string ruserid, rpassword, rpnumber;
    system("cls");
    cout <<BLUE<< "\t\t\t                                       REGISTRATION" <<RESET<< endl;
    cout << "\t\t\t                        Create a username: ";
    cin >> ruserid;

    do {
        cout << "\t\t\t                        Enter the Phone number (10 digits): ";
        cin >> rpnumber;
    } while (!isValidPhoneNumber(rpnumber));

    cout << "\t\t\t                        Create a password: ";
    cin >> rpassword;

    ofstream f1("records.txt", ios::app);
    f1 << ruserid << " " << rpassword << " " << rpnumber << endl;
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

// Access to client part
void clientMenu() {
    system("cls");
    int choice;
    do {
        cout <<RED<<"                                                     Client Menu" <<RESET<< endl;
        cout <<"\n";
        cout <<"\n";
        cout <<"\n";

        cout << "\t                         View Available Rooms" << endl;
        cout <<"\n";
        cout << "\t                         Book a Room" << endl;
        cout <<"\n";
        cout << "\t                         Check-In" << endl;
        cout <<"\n";
        cout << "\t                         Check-Out" << endl;
        cout <<"\n";
        cout << "\t                         View Booking Status" << endl;
        cout <<"\n";
        cout << "\t                         Update Guest Details" << endl;
        cout <<"\n";
        cout << "\t                         View Booking History" << endl;
        cout <<"\n";
        cout << "\t                         View Room Status" << endl;
        cout <<"\n";
        cout << "\t                         Back to Main Menu" << endl;
        cout <<"\n";
        cout <<"\n";
        cout << "\t                         Enter your choice"<<BLUE<<"(1/2/3/4/5/6/7/8/9): "<<RESET;
        cin >> choice;
        switch (choice) {
            case 1:
                viewAvailableRooms();
                break;
            case 2:
                bookRoom();
                break;
            case 3:
                checkIn();
                break;
            case 4:
                checkOut();
                break;
            case 5:
                viewBookingStatus();
                break;
            case 6:
                updateGuestDetails();
                break;
            case 7:
                viewBookingHistory();
                break;
            case 8:
                viewRoomStatus();
                break;
            case 9:
                main();
                break;
            default:
                system("cls");
                cout <<"              Invalid choice. Try again." << endl;
        }
    } while (choice != 9);
}

// Client contents
// Function to book a room
void bookRoom() {
    system("cls");
    ofstream outfile("bookings.txt", ios::app);
    if (!outfile) {
        cout <<RED<< "                    Error opening file for writing." <<RESET<< endl;
        return;
    }
    cout <<BLUE<<"                                     Book a Room\n\n\n\n"<<RESET;
    string name, roomType, date;
    cout << "\t                    Enter your username: ";
    cin.ignore();
    getline(cin, name);
    cout << "\t                    Enter room type: ";
    getline(cin, roomType);
    cout << "\t                    Enter check-in date "<<RED<<"(YYYY-MM-DD):"<<RESET;
    getline(cin, date);

    outfile << name << ";" << roomType << ";" << date << ";Pending\n";
    outfile.close();

    if (outfile.good()) {
        cout <<BLUE<< "\t              Room booked successfully!" <<RESET<< endl;
    } else {
        cout <<RED<< "\t              Error closing the file."  <<RESET<< endl;
    }
}

// Function to display available rooms
void viewAvailableRooms() {
    system("cls");
    cout<<RED<<"                                                         AVAILABLE ROOMS         \n "<<RESET;
    cout <<"\n";
    cout <<"\n";
    cout <<"\n";

    cout<<BLUE<<"                   Single Room     \n"<<RESET;
    cout <<"\n";

    cout<<"    Single room with one bed\n";
    cout <<"\n";
    cout <<"\n";

    cout<<BLUE<<"                   Double Room         \n"<<RESET;
    cout <<"\n";

    cout<<"    Double room with two beds\n";
    cout <<"\n";
    cout <<"\n";

    cout<<BLUE<<"                   Suite      \n"<<RESET;
    cout <<"\n";

    cout<<"    Suite with a living room and bedroom\n";
    cout <<"\n";
    cout <<"\n";

    cout<<BLUE<<"                   Deluxe Suite     \n"<<RESET;
    cout <<"\n";

    cout<<"    Deluxe suite with a living room, bedroom, and balcony\n";
    cout <<"\n";
    cout <<"\n";
}

// Function to check-in
void checkIn() {
    system("cls");
    string username, roomType, checkInDate;
    cout <<BLUE<<"                                     Check-In Form\n\n\n\n"<<RESET;

    cout << "\t                    Enter your username: ";
    cin.ignore();
    getline(cin, username);

    cout << "\t                    Enter room type: ";
    getline(cin, roomType);

    cout << "\t                    Enter check-in date "<<RED<<"(YYYY-MM-DD):"<<RESET;
    getline(cin, checkInDate);

    ofstream outfile("checkins.txt", ios::app);
    outfile << username << ";" << roomType << ";" << checkInDate << ";Checked-In\n";
    outfile.close();

    cout <<BLUE<< "\t              Check-in successful!" <<RESET<< endl;
}

// Function to check-out
void checkOut() {
    system("cls");
    string username, roomType, checkOutDate;
    cout <<BLUE<<"                                     Check-Out Form\n\n\n\n"<<RESET;

    cout << "\t                    Enter your username: ";
    cin.ignore();
    getline(cin, username);

    cout << "\t                    Enter room type: ";
    getline(cin, roomType);

    cout << "\t                    Enter check-out date "<<RED<<"(YYYY-MM-DD):"<<RESET;
    getline(cin, checkOutDate);

    ofstream outfile("checkouts.txt", ios::app);
    outfile << username << ";" << roomType << ";" << checkOutDate << ";Checked-Out\n";
    outfile.close();

    cout <<BLUE<< "\t              Check-out successful!" <<RESET<< endl;
}

// Function to view booking status
void viewBookingStatus() {
    system("cls");

    ifstream bookedRoomsFile("bookings.txt");
    ifstream checkinsFile("checkins.txt");

    if (!bookedRoomsFile) {
        cout <<RED<< "\t                Error opening bookings.txt for reading." <<RESET<< endl;
        return;
    }
    if (!checkinsFile) {
        cout << "Error opening checkins.txt for reading." << endl;
        return;
    }

    cout << "Booked Rooms:" << endl;
    string line;
    while (getline(bookedRoomsFile, line)) {
        size_t pos1 = line.find(';');
        size_t pos2 = line.find(';', pos1 + 1);
        size_t pos3 = line.find(';', pos2 + 1);

        if (pos1 != string::npos && pos2 != string::npos && pos3 != string::npos) {
            string name = line.substr(0, pos1);
            string roomType = line.substr(pos1 + 1, pos2 - pos1 - 1);
            string date = line.substr(pos2 + 1, pos3 - pos2 - 1);
            string status = line.substr(pos3 + 1);

            cout << "Room Type: " << roomType << "\n"<< " Date: " << date <<"\n"<< " Status: " << status<<"\n" << endl;
        } else {
            cout << "Error parsing booked rooms data." << endl;
        }
    }

    cout << "Checked-In Rooms:" << endl;
    while (getline(checkinsFile, line)) {
        size_t pos1 = line.find(';');

        if (pos1 != string::npos) {
            string date = line.substr(0, pos1);

            cout << "Date : " << date << "\n" << endl;
        } else {
            cout << "Error parsing check-in data." << endl;
        }
    }

    bookedRoomsFile.close();
    checkinsFile.close();
}

// Function to update guest details
void updateGuestDetails() {
    system("cls");
    string username, newPassword, phoneNumber;

    cout << "Enter the username of the account you want to update: ";
    cin >> username;

    ifstream infile("records.txt");
    ofstream tempFile("temp.txt");
    if (!infile || !tempFile) {
        cout << "Error opening file." << endl;
        return;
    }

    string id, pass, phone, line;
    bool found = false;

    while (infile >> id >> pass >> phone) {
        if (id == username) {
            found = true;

            cout << "Enter new password: ";
            cin >> newPassword;
            cout << "Enter new phone number: ";
            cin >> phoneNumber;

            tempFile << username << " " << newPassword << " " << phoneNumber << endl;
        } else {
            tempFile << id << " " << pass << " " << phone << endl;
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
    ifstream infile("booking_history.txt");
    if (!infile) {
        cout << "Error opening booking_history.txt for reading." << endl;
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
            string roomType = line.substr(pos1 + 1, pos2 - pos1 - 1);
            string checkInDate = line.substr(pos2 + 1, pos3 - pos2 - 1);
            string checkOutDate = line.substr(pos3 + 1);

            cout << "Username: " << username << "\nRoom Type: " << roomType
                 << "\nCheck-In Date: " << checkInDate << "\nCheck-Out Date: " << checkOutDate << "\n" << endl;
        } else {
            cout << "Error parsing booking history data." << endl;
        }
    }
    infile.close();
}

// Function to view room status
void viewRoomStatus() {
    system("cls");
    ifstream infile("room_status.txt");
    if (!infile) {
        cout << "Error opening room_status.txt for reading." << endl;
        return;
    }

    string line;
    cout << "\nRoom Status:" << endl;
    while (getline(infile, line)) {
        size_t pos1 = line.find(';');
        size_t pos2 = line.find(';', pos1 + 1);

        if (pos1 != string::npos && pos2 != string::npos) {
            string roomNumber = line.substr(0, pos1);
            string status = line.substr(pos1 + 1, pos2 - pos1 - 1);
            string lastCleaned = line.substr(pos2 + 1);

            cout << "Room Number: " << roomNumber << "\nStatus: " << status
                 << "\nLast Cleaned: " << lastCleaned << "\n" << endl;
        } else {
            cout << "Error parsing room status data." << endl;
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
        cout <<"\t\t\t                       1. View All Bookings" << endl;
        cout <<"\t\t\t                       2. View All Guests" << endl;
        cout <<"\t\t\t                       3. Update Room Status" << endl;
        cout <<"\t\t\t                       4. Generate Report" << endl;
        cout <<"\t\t\t                       5. Back to Main Menu" << endl;
        cout <<BLUE<<"\t\t\t                            Enter your choice: "<<RESET;
        cin >> choice;
        switch (choice) {
            case 1:
                viewAllBookings();
                break;
            case 2:
                viewAllGuests();
                break;
            case 3:
                updateRoomStatus();
                break;
            case 4:
                generateReport();
                break;
            case 5:
                main();
                break;
            default:
                cout << "Invalid choice. Try again." << endl;
        }
    } while (choice != 5);
}

// Contents of admin
void viewAllBookings() {
    system("cls");

    ifstream infile("bookings.txt");
    if (!infile) {
        cout <<RED<< "Error opening bookings.txt for reading." <<RESET<< endl;
        return;
    }

    string line;
    cout <<BLUE<<"\t\t\t                       \nAll Bookings:" <<RESET<< endl;
    while (getline(infile, line)) {
        size_t pos1 = line.find(';');
        size_t pos2 = line.find(';', pos1 + 1);
        size_t pos3 = line.find(';', pos2 + 1);

        if (pos1 != string::npos && pos2 != string::npos && pos3 != string::npos) {
            string name = line.substr(0, pos1);
            string roomType = line.substr(pos1 + 1, pos2 - pos1 - 1);
            string date = line.substr(pos2 + 1, pos3 - pos2 - 1);
            string status = line.substr(pos3 + 1);

            cout << "Name: " << name << "\nRoom Type: " << roomType << "\nDate: " << date << "\nStatus: " << status << "\n" << endl;
        } else {
            cout << "Error parsing booked rooms data." << endl;
        }
    }
    infile.close();
}

// Function to view all guests
void viewAllGuests() {
    system("cls");
    ifstream infile("records.txt");
    if (!infile) {
        cout << "Error opening records.txt for reading." << endl;
        return;
    }

    string line;
    cout << "\nAll Guests:" << endl;
    while (getline(infile, line)) {
        size_t pos1 = line.find(' ');
        size_t pos2 = line.find(' ', pos1 + 1);

        if (pos1 != string::npos && pos2 != string::npos) {
            string username = line.substr(0, pos1);
            string password = line.substr(pos1 + 1, pos2 - pos1 - 1);
            string phoneNumber = line.substr(pos2 + 1);

            cout << "Username: " << username << "\nPassword: " << password << "\nPhone Number: " << phoneNumber << "\n" << endl;
        } else {
            cout << "Error parsing guest data." << endl;
        }
    }
    infile.close();
}

// Function to update room status
void updateRoomStatus() {
    system("cls");
    string roomNumber, status, lastCleaned;

    cout << "Enter the room number you want to update: ";
    cin.ignore();
    getline(cin, roomNumber);

    cout << "Enter the new status: ";
    getline(cin, status);

    cout << "Enter the last cleaned date "<<RED<<"(YYYY-MM-DD):"<<RESET;
    getline(cin, lastCleaned);

    ofstream outfile("room_status.txt", ios::app);
    if (!outfile) {
        cout << "Error opening room_status.txt for writing." << endl;
        return;
    }

    outfile << roomNumber << ";" << status << ";" << lastCleaned << endl;
    outfile.close();

    if (outfile.good()) {
        cout << "Room status updated successfully!" << endl;
    } else {
        cout << "Error writing to the file." << endl;
    }
}

// Function to generate report
void generateReport() {
    system("cls");
    ifstream infile("booking_history.txt");
    if (!infile) {
        cout << "Error opening booking_history.txt for reading." << endl;
        return;
    }

    string line;
    cout << "\nBooking Report:" << endl;
    while (getline(infile, line)) {
        size_t pos1 = line.find(';');
        size_t pos2 = line.find(';', pos1 + 1);
        size_t pos3 = line.find(';', pos2 + 1);

        if (pos1 != string::npos && pos2 != string::npos && pos3 != string::npos) {
            string username = line.substr(0, pos1);
            string roomType = line.substr(pos1 + 1, pos2 - pos1 - 1);
            string checkInDate = line.substr(pos2 + 1, pos3 - pos2 - 1);
            string checkOutDate = line.substr(pos3 + 1);

            cout << "Username: " << username << "\nRoom Type: " << roomType
                 << "\nCheck-In Date: " << checkInDate << "\nCheck-Out Date: " << checkOutDate << "\n" << endl;
        } else {
            cout << "Error parsing booking history data." << endl;
        }
    }
    infile.close();
}

// Data validation part

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
