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

// Function prototypes for input validation(DATA VALIDATION)
bool isValidPhoneNumber(const string& phoneNumber);
bool isValidDate(const string& date);
int stringToInt(const string& str);
bool isAllDigits(const string& str);

// Function for login
void login();
void registration();
void forgot();

// Functions for user
void userMenu();
void viewEvents();
void bookEvent();
void viewBookedEvents();
void cancelBooking();

// Functions for admin
void adminMenu();
void createEvent();
void viewAllEvents();
void viewAllBookings();
void deleteEvent();
void updateEvent();

// Structure to hold event details
struct Event {
    string eventID;
    string eventName;
    string eventDate;
    string eventTime;
    string eventVenue;
    string eventDescription;
    int availableSeats;
};

// Structure to hold booking details
struct Booking {
    string username;
    string eventID;
    string bookingDate;
    int numberOfSeats;
};

// Global vectors to hold events and bookings
vector<Event> events;
vector<Booking> bookings;

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
        cout << "*"<<RED<<"                                               EVENT MANAGEMENT SYSTEM LOGIN                                         "<<RESET<<"*" << endl;
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
        if (userid.substr(0, 2) == "us") {
            cout <<RED<<                 userid <<RESET<< "\nYour LOGIN is successful\n";
            userMenu();
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

// Access to user part
void userMenu() {
    system("cls");
    int choice;
    do {
        cout <<RED<<"                                                     User Menu" <<RESET<< endl;
        cout <<"\n";
        cout <<"\n";
        cout <<"\n";

        cout << "\t                         View Events" << endl;
        cout <<"\n";
        cout << "\t                         Book an Event" << endl;
        cout <<"\n";
        cout << "\t                         View Booked Events" << endl;
        cout <<"\n";
        cout << "\t                         Cancel a Booking" << endl;
        cout <<"\n";
        cout << "\t                         Back to Main Menu" << endl;
        cout <<"\n";
        cout <<"\n";
        cout << "\t                         Enter your choice"<<BLUE<<"(1/2/3/4/5): "<<RESET;
        cin >> choice;
        switch (choice) {
            case 1:
                viewEvents();
                break;
            case 2:
                bookEvent();
                break;
            case 3:
                viewBookedEvents();
                break;
            case 4:
                cancelBooking();
                break;
            case 5:
                main();
                break;
            default:
                system("cls");
                cout <<"              Invalid choice. Try again." << endl;
        }
    } while (choice != 5);
}

// User contents
void viewEvents() {
    system("cls");
    ifstream infile("events.txt");
    if (!infile) {
        cout << "Error opening events.txt for reading." << endl;
        return;
    }

    string line;
    cout << "\nAll Events:" << endl;
    while (getline(infile, line)) {
        istringstream iss(line);
        Event event;
        iss >> event.eventID >> event.eventName >> event.eventDate >> event.eventTime >> event.eventVenue >> event.eventDescription >> event.availableSeats;
        cout << "Event ID: " << event.eventID << "\nEvent Name: " << event.eventName << "\nEvent Date: " << event.eventDate
             << "\nEvent Time: " << event.eventTime << "\nEvent Venue: " << event.eventVenue << "\nEvent Description: " << event.eventDescription
             << "\nAvailable Seats: " << event.availableSeats << "\n" << endl;
    }
    infile.close();
}

void bookEvent() {
    system("cls");
    string username, eventID, bookingDate;
    int numberOfSeats;

    cout << "Enter your username: ";
    cin >> username;
    cout << "Enter the event ID you want to book: ";
    cin >> eventID;
    cout << "Enter the number of seats you want to book: ";
    cin >> numberOfSeats;

    ifstream infile("events.txt");
    if (!infile) {
        cout << "Error opening events.txt for reading." << endl;
        return;
    }

    string line;
    bool eventFound = false;
    while (getline(infile, line)) {
        istringstream iss(line);
        Event event;
        iss >> event.eventID >> event.eventName >> event.eventDate >> event.eventTime >> event.eventVenue >> event.eventDescription >> event.availableSeats;
        if (event.eventID == eventID) {
            eventFound = true;
            if (event.availableSeats >= numberOfSeats) {
                event.availableSeats -= numberOfSeats;
                ofstream outfile("bookings.txt", ios::app);
                outfile << username << " " << eventID << " " << event.eventDate << " " << numberOfSeats << endl;
                outfile.close();
                cout << "Event booked successfully!" << endl;
            } else {
                cout << "Not enough seats available." << endl;
            }
            break;
        }
    }
    infile.close();

    if (!eventFound) {
        cout << "Event not found!" << endl;
    }
}

void viewBookedEvents() {
    system("cls");
    string username;
    cout << "Enter your username: ";
    cin >> username;

    ifstream infile("bookings.txt");
    if (!infile) {
        cout << "Error opening bookings.txt for reading." << endl;
        return;
    }

    string line;
    cout << "\nYour Booked Events:" << endl;
    while (getline(infile, line)) {
        istringstream iss(line);
        Booking booking;
        iss >> booking.username >> booking.eventID >> booking.bookingDate >> booking.numberOfSeats;
        if (booking.username == username) {
            cout << "Event ID: " << booking.eventID << "\nBooking Date: " << booking.bookingDate
                 << "\nNumber of Seats: " << booking.numberOfSeats << "\n" << endl;
        }
    }
    infile.close();
}

void cancelBooking() {
    system("cls");
    string username, eventID;
    cout << "Enter your username: ";
    cin >> username;
    cout << "Enter the event ID you want to cancel: ";
    cin >> eventID;

    ifstream infile("bookings.txt");
    ofstream tempFile("temp.txt");
    if (!infile || !tempFile) {
        cout << "Error opening file." << endl;
        return;
    }

    string line;
    bool bookingFound = false;
    while (getline(infile, line)) {
        istringstream iss(line);
        Booking booking;
        iss >> booking.username >> booking.eventID >> booking.bookingDate >> booking.numberOfSeats;
        if (booking.username == username && booking.eventID == eventID) {
            bookingFound = true;
        } else {
            tempFile << line << endl;
        }
    }
    infile.close();
    tempFile.close();

    remove("bookings.txt");
    rename("temp.txt", "bookings.txt");

    if (bookingFound) {
        cout << "Booking canceled successfully!" << endl;
    } else {
        cout << "Booking not found!" << endl;
    }
}

// Access to admin part
void adminMenu() {
    int choice;
    do {
        cout <<RED<<"\t\t\t                                    Admin Menu" <<RESET<< endl;
        cout<<"\n";
        cout<<"\n";
        cout <<"\t\t\t                       1. Create Event" << endl;
        cout <<"\t\t\t                       2. View All Events" << endl;
        cout <<"\t\t\t                       3. View All Bookings" << endl;
        cout <<"\t\t\t                       4. Delete Event" << endl;
        cout <<"\t\t\t                       5. Update Event" << endl;
        cout <<"\t\t\t                       6. Back to Main Menu" << endl;
        cout <<BLUE<<"\t\t\t                            Enter your choice: "<<RESET;
        cin >> choice;
        switch (choice) {
            case 1:
                createEvent();
                break;
            case 2:
                viewAllEvents();
                break;
            case 3:
                viewAllBookings();
                break;
            case 4:
                deleteEvent();
                break;
            case 5:
                updateEvent();
                break;
            case 6:
                main();
                break;
            default:
                cout << "Invalid choice. Try again." << endl;
        }
    } while (choice != 6);
}

// Admin contents
void createEvent() {
    system("cls");
    Event event;
    cout << "Enter Event ID: ";
    cin >> event.eventID;
    cout << "Enter Event Name: ";
    cin.ignore();
    getline(cin, event.eventName);
    do {
        cout << "Enter Event Date (YYYY-MM-DD): ";
        getline(cin, event.eventDate);
    } while (!isValidDate(event.eventDate));
    cout << "Enter Event Time: ";
    getline(cin, event.eventTime);
    cout << "Enter Event Venue: ";
    getline(cin, event.eventVenue);
    cout << "Enter Event Description: ";
    getline(cin, event.eventDescription);
    cout << "Enter Available Seats: ";
    cin >> event.availableSeats;

    ofstream outfile("events.txt", ios::app);
    outfile << event.eventID << " " << event.eventName << " " << event.eventDate << " " << event.eventTime << " "
            << event.eventVenue << " " << event.eventDescription << " " << event.availableSeats << endl;
    outfile.close();

    cout << "Event created successfully!" << endl;
}

void viewAllEvents() {
    system("cls");
    ifstream infile("events.txt");
    if (!infile) {
        cout << "Error opening events.txt for reading." << endl;
        return;
    }

    string line;
    cout << "\nAll Events:" << endl;
    while (getline(infile, line)) {
        istringstream iss(line);
        Event event;
        iss >> event.eventID >> event.eventName >> event.eventDate >> event.eventTime >> event.eventVenue >> event.eventDescription >> event.availableSeats;
        cout << "Event ID: " << event.eventID << "\nEvent Name: " << event.eventName << "\nEvent Date: " << event.eventDate
             << "\nEvent Time: " << event.eventTime << "\nEvent Venue: " << event.eventVenue << "\nEvent Description: " << event.eventDescription
             << "\nAvailable Seats: " << event.availableSeats << "\n" << endl;
    }
    infile.close();
}

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
        istringstream iss(line);
        Booking booking;
        iss >> booking.username >> booking.eventID >> booking.bookingDate >> booking.numberOfSeats;
        cout << "Username: " << booking.username << "\nEvent ID: " << booking.eventID << "\nBooking Date: " << booking.bookingDate
             << "\nNumber of Seats: " << booking.numberOfSeats << "\n" << endl;
    }
    infile.close();
}

void deleteEvent() {
    system("cls");
    string eventID;
    cout << "Enter the Event ID to delete: ";
    cin >> eventID;

    ifstream infile("events.txt");
    ofstream tempFile("temp.txt");
    if (!infile || !tempFile) {
        cout << "Error opening file." << endl;
        return;
    }

    string line;
    bool eventFound = false;
    while (getline(infile, line)) {
        istringstream iss(line);
        Event event;
        iss >> event.eventID >> event.eventName >> event.eventDate >> event.eventTime >> event.eventVenue >> event.eventDescription >> event.availableSeats;
        if (event.eventID == eventID) {
            eventFound = true;
        } else {
            tempFile << line << endl;
        }
    }
    infile.close();
    tempFile.close();

    remove("events.txt");
    rename("temp.txt", "events.txt");

    if (eventFound) {
        cout << "Event deleted successfully!" << endl;
    } else {
        cout << "Event not found!" << endl;
    }
}

void updateEvent() {
    system("cls");
    string eventID;
    cout << "Enter the Event ID to update: ";
    cin >> eventID;

    ifstream infile("events.txt");
    ofstream tempFile("temp.txt");
    if (!infile || !tempFile) {
        cout << "Error opening file." << endl;
        return;
    }

    string line;
    bool eventFound = false;
    while (getline(infile, line)) {
        istringstream iss(line);
        Event event;
        iss >> event.eventID >> event.eventName >> event.eventDate >> event.eventTime >> event.eventVenue >> event.eventDescription >> event.availableSeats;
        if (event.eventID == eventID) {
            eventFound = true;
            cout << "Enter new Event Name: ";
            cin.ignore();
            getline(cin, event.eventName);
            do {
                cout << "Enter new Event Date (YYYY-MM-DD): ";
                getline(cin, event.eventDate);
            } while (!isValidDate(event.eventDate));
            cout << "Enter new Event Time: ";
            getline(cin, event.eventTime);
            cout << "Enter new Event Venue: ";
            getline(cin, event.eventVenue);
            cout << "Enter new Event Description: ";
            getline(cin, event.eventDescription);
            cout << "Enter new Available Seats: ";
            cin >> event.availableSeats;
            tempFile << event.eventID << " " << event.eventName << " " << event.eventDate << " " << event.eventTime << " "
                     << event.eventVenue << " " << event.eventDescription << " " << event.availableSeats << endl;
        } else {
            tempFile << line << endl;
        }
    }
    infile.close();
    tempFile.close();

    remove("events.txt");
    rename("temp.txt", "events.txt");

    if (eventFound) {
        cout << "Event updated successfully!" << endl;
    } else {
        cout << "Event not found!" << endl;
    }
}

// Data validation part
bool isValidPhoneNumber(const string& phoneNumber) {
    if (phoneNumber.length() != 10 || !isAllDigits(phoneNumber)) {
        cout <<RED<< "Invalid phone number. It should be exactly 10 digits long." <<RESET<< endl;
        return false;
    }
    return true;
}

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

int stringToInt(const string& str) {
    int result = 0;
    stringstream ss(str);
    ss >> result;
    return result;
}

bool isAllDigits(const string& str) {
    for (size_t i = 0; i < str.length(); ++i) {
        if (!isdigit(str[i])) {
            return false;
        }
    }
    return true;
}
