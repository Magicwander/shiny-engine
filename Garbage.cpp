
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

//functions for client
void clientMenu();
void bookService();
void ourservices();
void appointment();
void cancelappointment();
void viewServiceStatus();
void updateCustomerDetails();
void viewServiceCompletionStatus();
void viewServiceRecords();


//functions of serverside
void serviceProviderMenu();
void viewBookings();
void displayAppointments();
void searchVehicleByRegistration();
void searchBookingsByUsername();
void updateServiceRecords();
void updateServiceCompletionStatus();
void displayCanceledAppointments();
 
 //when rejistering plz use "cl" for username if u are a client
 

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
    cout << "*"<<RED<<"                                               GARAGE MANAGEMENT SYSTEM LOGIN                                         "<<RESET<<"*" << endl;
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
        if (userid.substr(0, 2) == "cl") {
            cout <<RED<<                 userid <<RESET<< "\nYour LOGIN is successful\n";
            clientMenu();
        } else if (userid.substr(0, 2) == "se") {
            cout <<RED<<                 userid <<RESET<< "\nYour LOGIN is successful\n";
            serviceProviderMenu();
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
    string ruserid, rpassword, rpnumber, liscence_id, vehicle_id, vehicle_type;
    system("cls");
    cout <<BLUE<< "\t\t\t                                       REGISTRATION" <<RESET<< endl;
    cout << "\t\t\t                        Create a username: ";
    cin >> ruserid;

    do {
        cout << "\t\t\t                        Enter the Phone number (10 digits): ";
        cin >> rpnumber;
    } while (!isValidPhoneNumber(rpnumber));

    cout << "\t\t\t                        Enter the license ID: ";
    cin >> liscence_id;
    cout << "\t\t\t                        Enter the Vehicle number: ";
    cin >> vehicle_id;
    cout << "\t\t\t                        Enter the Vehicle type: ";
    cin >> vehicle_type;
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
// acess to client part
void clientMenu() {
	system("cls");
    int choice;
    do {
        cout <<RED<<"                                                     Client Menu" <<RESET<< endl;
        cout <<"\n";
        cout <<"\n";
        cout <<"\n";
        
        cout << "\t                         Our services" << endl;
        cout <<"\n";
        cout << "\t                         Book a service" << endl;
        cout <<"\n";
        cout << "\t                         Appoinment" << endl;
        cout <<"\n";
        cout << "\t                         Cancel a Appoinment" << endl;
        cout <<"\n";
        cout << "\t                         Upgrade the personal information" << endl;
        cout <<"\n";
        cout << "\t                         View the service status" << endl;
        cout <<"\n";
        cout << "\t                         View the Service Records" << endl;
        cout <<"\n";
        cout << "\t                         View the Service Completion Status" << endl;
        cout <<"\n";
        cout << "\t                         Back to Main Menu" << endl;
        cout <<"\n";
        cout <<"\n";
        cout << "\t                         Enter your choice"<<BLUE<<"(1/2/3/4/5/6/7/8/9): "<<RESET;
        cin >> choice;
        switch (choice) {
            case 1:
                ourservices();
                break;
            case 2:
            	bookService();
                break;
            case 3:
            	appointment();
            	break;
            case 4:
            	cancelappointment();
            	break;
            case 5:
            	updateCustomerDetails();
            	break;  
			case 6:
            	viewServiceStatus();
                break;
			case 7:
            	viewServiceRecords();
                break;
            case 8:
            	viewServiceCompletionStatus();
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
// client contents
// Function to book a service
void bookService() {
	system("cls");
    ofstream outfile("clients.txt", ios::app);
    if (!outfile) {
        cout <<RED<< "                    Error opening file for writing." <<RESET<< endl;
        return;
    }
    cout <<BLUE<<"                                     Choose & Book your service from the OUR SERVICES\n\n\n\n"<<RESET;
    string name, serviceType, date;
    cout << "\t                    Enter your username : ";
    cin.ignore();
    getline(cin, name);
    cout << "\t                    Enter service type : ";
    getline(cin, serviceType);
    cout << "\t                    Enter preferred date "<<RED<<"(YYYY-MM-DD) :"<<RESET;
    getline(cin, date);

    outfile << name << ";" << serviceType << ";" << date << ";Pending\n";
    outfile.close();

    if (outfile.good()) {
        cout <<BLUE<< "\t              Service booked successfully!" <<RESET<< endl;
    } else {
        cout <<RED<< "\t              Error closing the file."  <<RESET<< endl;
    }
}
// Function to display available services
void ourservices(){
	system("cls");
	cout<<RED<<"                                                         OUR SERVICES         \n "<<RESET;
	cout <<"\n";
	cout <<"\n";
	cout <<"\n";
	
	
	cout<<BLUE<<"                   RUNNING REPAIRS     \n"<<RESET;
	cout <<"\n";
	
    cout<<"    Day to day running repairs on all brands\nof vehicles using genuine parts\n";
    cout <<"\n";
    cout <<"\n";
    
    cout<<BLUE<<"                   TUNE UP'S         \n"<<RESET;
    cout <<"\n";
    
    cout<<"    Electronic injector cleaning and tune up's\nfor both petrol and diesel vehicles\n";
    cout <<"\n";
    cout <<"\n";
    
    
    cout<<BLUE<<"                   FULL SERVICE      \n"<<RESET;
    cout <<"\n";
    
    cout<<"    Full service for all brands of vehicles\nusing manufacturer recommended oils\n";
    cout <<"\n";
    cout <<"\n";
    
    
    cout<<BLUE<<"                   VEHICLE ACCESSORIES     \n"<<RESET;
    cout <<"\n";
    
    cout<<"    All vehicle accessories including leather seat covers,\ntinting, GPS/DVD players, etc.\n";
    cout <<"\n";
    cout <<"\n";
    
    
    cout<<BLUE<<"                   COLLISION REPAIRS    \n"<<RESET;
    cout <<"\n";
    
    cout<<"    2K heated booth painting with 3 year warranty\non all paint job\n";
    cout <<"\n";
    cout <<"\n";
    
    
    cout<<BLUE<<"                   VEHICLE REPAIRING    \n"<<RESET;
    cout <<"\n";
    
    cout<<"    Professional vehicle detailing using world reputed\nchemicals and products to make your vehicle look brand new\n";
    cout <<"\n";
    cout <<"\n";
    
}
// Function to make an appointment
void appointment() {
    system("cls");
    string appointmentname, appointmentDate, appointmentDetails, phonenumber, requestacall;
    bool overlap = false;
    cout <<BLUE<<"                                     Appointment Form\n\n\n\n"<<RESET;

    cout << "\t                    Enter your appointment sender's name: ";
    cin.ignore();
    getline(cin, appointmentname);

    do {
        cout << "\t                    Enter your appointment Date (YYYY-MM-DD): ";
        cin >> appointmentDate;
    } while (!isValidDate(appointmentDate));
    
    cout<<"\n";
    // Check for overlapping appointments
    ifstream infile("appointments.txt");
    string line;
    while (getline(infile, line)) {
        if (line.find(appointmentDate) != string::npos) {
            overlap = true;
            break;
        }
    }
    infile.close();

    if (overlap) {
        cout <<RED<< "\t                An appointment is already booked on this date. Please choose a different date." <<RESET<< endl;
        return;
    }
    cout<<RED<<"sorry for the inconvienience there is small error here,plz neglect it"<<RESET;
    // Get additional details and save appointment
    cout << "\t                    Enter your appointment Details: \n";
    getline(cin, appointmentDetails);

    cout << "\t                    Enter your phone number: ";
    getline(cin, phonenumber);

    cout << "\t                    Request a phone call "<<RED<<"(Yes/No):"<<RESET;
    getline(cin, requestacall);

    ofstream outfile("appointments.txt", ios::app);
    outfile << appointmentDate << ";" << appointmentname << ";" << appointmentDetails << ";" << phonenumber << ";" << requestacall << "\n";
    outfile.close();

    cout <<BLUE<< "\t                Appointment details submitted successfully!" <<RESET<< endl;
}

//here data validation part is called

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

// Function to cancel an appointment
void cancelappointment() {
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

// Function to view service status
void viewServiceStatus() {
   system("cls");

    ifstream bookedServicesFile("clients.txt");
    ifstream appointmentsFile("appointments.txt");

    if (!bookedServicesFile) {
        cout <<RED<< "\t                Error opening clients.txt for reading." <<RESET<< endl;
        return;
    }
    if (!appointmentsFile) {
        cout << "Error opening appointments.txt for reading." << endl;
        return;
    }

    cout << "Booked Services:" << endl;
    string line;
    while (getline(bookedServicesFile, line)) {
        size_t pos1 = line.find(';');
        size_t pos2 = line.find(';', pos1 + 1);
        size_t pos3 = line.find(';', pos2 + 1);

        if (pos1 != string::npos && pos2 != string::npos && pos3 != string::npos) {
            string name = line.substr(0, pos1);
            string serviceType = line.substr(pos1 + 1, pos2 - pos1 - 1);
            string date = line.substr(pos2 + 1, pos3 - pos2 - 1);
            string status = line.substr(pos3 + 1);

            cout << "Service Type: " << serviceType << "\n"<< " Date: " << date <<"\n"<< " Status: " << status<<"\n" << endl;
        } else {
            cout << "Error parsing booked services data." << endl;
        }
    }

    cout << "Booked Appointments:" << endl;
    while (getline(appointmentsFile, line)) {
        size_t pos1 = line.find(';');
        if (pos1 != string::npos) {
            string date = line.substr(0, pos1);
            

            cout << "Date : " << date << "\n" << endl;
        } else {
            cout << "Error parsing appointment data." << endl;
        }
    }

    bookedServicesFile.close();
    appointmentsFile.close();
    
}
// Function to update customer details    
void updateCustomerDetails() {
    system("cls");
    string username, newPassword, phoneNumber, licenseId, vehicleId, vehicleType;

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
            cout << "Enter new license ID: ";
            cin >> licenseId;
            cout << "Enter new vehicle ID: ";
            cin >> vehicleId;
            cout << "Enter new vehicle type: ";
            cin >> vehicleType;
            
           
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
// Function to view service records
void viewServiceRecords() {
    system("cls");
    ifstream infile("service_records.txt");
    if (!infile) {
        cout << "Error opening service_records.txt for reading." << endl;
        return;
    }

    string line;
    cout << "\nService Records:" << endl;
    while (getline(infile, line)) {
        size_t pos1 = line.find(';');
        size_t pos2 = line.find(';', pos1 + 1);
        size_t pos3 = line.find(';', pos2 + 1);

        if (pos1 != string::npos && pos2 != string::npos && pos3 != string::npos) {
            string username = line.substr(0, pos1);
            string servicePerformed = line.substr(pos1 + 1, pos2 - pos1 - 1);
            string partsReplaced = line.substr(pos2 + 1, pos3 - pos2 - 1);
            string additionalNotes = line.substr(pos3 + 1);

            cout << "Username: " << username << "\nService Performed: " << servicePerformed 
                 << "\nParts Replaced: " << partsReplaced << "\nAdditional Notes: " << additionalNotes << "\n" << endl;
        } else {
            cout << "Error parsing service records data." << endl;
        }
    }
    infile.close();
}
// Function to view service completion status
void viewServiceCompletionStatus() {
    system("cls");
    ifstream infile("service_completion.txt");
    if (!infile) {
        cout << "Error opening service_completion.txt for reading." << endl;
        return;
    }

    string line;
    cout << "\nService Completion Status:" << endl;
    while (getline(infile, line)) {
        size_t pos1 = line.find(';');
        size_t pos2 = line.find(';', pos1 + 1);

        if (pos1 != string::npos && pos2 != string::npos) {
            string username = line.substr(0, pos1);
            string serviceStatus = line.substr(pos1 + 1, pos2 - pos1 - 1);
            string completionDate = line.substr(pos2 + 1);

            cout << "Username: " << username << "\nService Status: " << serviceStatus 
                 << "\nCompletion Date: " << completionDate << "\n" << endl;
        } else {
            cout << "Error parsing service completion data." << endl;
        }
    }
    infile.close();
}


//acess to service provider
void serviceProviderMenu() {
    int choice;
    do {
        cout <<RED<<"\t\t\t                                    Service Provider Menu" <<RESET<< endl;
        cout<<"\n";
        cout<<"\n";
        cout <<"\t\t\t                       1. View Bookings" << endl;
        cout <<"\t\t\t                       2. View Appoinments" << endl;
        cout <<"\t\t\t                       3. Search Vehicle By Registration" << endl;
        cout <<"\t\t\t                       4. Search Bookings By Username" << endl;
        cout <<"\t\t\t                       5. Update Service Records" << endl;
        cout <<"\t\t\t                       6. Update Service Completion Status" << endl;
        cout <<"\t\t\t                       7. Display Canceled Appointments" << endl;
        cout <<"\t\t\t                       8. Back to Main Menu" << endl;
        cout <<BLUE<<"\t\t\t                            Enter your choice: "<<RESET;
        cin >> choice;
        switch (choice) {
            case 1:
                viewBookings();
                break;
            case 2:
                displayAppointments();
                break;
            case 3:
            	 searchVehicleByRegistration();
                break;
            case 4:
            	 searchBookingsByUsername();
                break;
            case 5:
            	 updateServiceRecords();
                break;
            case 6:
            	 updateServiceCompletionStatus();
                break;
            case 7:
            	 displayCanceledAppointments();
                break;
            case 8:
            	 main();
                break;
            default:
                cout << "Invalid choice. Try again." << endl;
        }
    } while (choice != 6);
}

//contents of service provider
void viewBookings() {
	system("cls");
	
   ifstream infile("clients.txt");
    if (!infile) {
        cout <<RED<< "Error opening clients.txt for reading." <<RESET<< endl;
        return;
    }

    string line;
    cout <<BLUE<<"\t\t\t                       \nBooked Services:" <<RESET<< endl;
    while (getline(infile, line)) {
        size_t pos1 = line.find(';');
        size_t pos2 = line.find(';', pos1 + 1);
        size_t pos3 = line.find(';', pos2 + 1);

        if (pos1 != string::npos && pos2 != string::npos && pos3 != string::npos) {
            string name = line.substr(0, pos1);
            string serviceType = line.substr(pos1 + 1, pos2 - pos1 - 1);
            string date = line.substr(pos2 + 1, pos3 - pos2 - 1);
            string status = line.substr(pos3 + 1);

            cout << "Name: " << name << "\nService Type: " << serviceType << "\nDate: " << date << "\nStatus: " << status << "\n" << endl;
        } else {
            cout << "Error parsing booked services data." << endl;
        }
    }
    infile.close();
}
// Function to display appointments
void displayAppointments() {
	system("cls");
    ifstream infile("appointments.txt");
    if (!infile) {
        cout <<RED<< "Error opening appointments.txt for reading." <<RESET<< endl;
        return;
    }

    string line;
    cout <<"\t\t\t                       \nAppointments:" << endl;
    while (getline(infile, line)) {
        size_t pos1 = line.find(';');
        size_t pos2 = line.find(';', pos1 + 1);
        size_t pos3 = line.find(';', pos2 + 1);
        size_t pos4 = line.find(';', pos3 + 1);

        if (pos1 != string::npos && pos2 != string::npos && pos3 != string::npos && pos4 != string::npos) {
            string date = line.substr(0, pos1);
            string appointmentName = line.substr(pos1 + 1, pos2 - pos1 - 1);
            string appointmentDetails = line.substr(pos2 + 1, pos3 - pos2 - 1);
            string phoneNumber = line.substr(pos3 + 1, pos4 - pos3 - 1);
            string requestCall = line.substr(pos4 + 1);

            cout << "Appointment Date: " << date << "\nName: " << appointmentName << "\nDetails: " << appointmentDetails 
                 << "\nPhone Number: " << phoneNumber << "\nRequest a Call: " << requestCall << "\n" << endl;
        } else {
            cout << "Error parsing appointment data." << endl;
        }
    }
    infile.close();
}
// Function to search vehicle by registration
void searchVehicleByRegistration() {
    system("cls");
    string registrationNumber, id, pass, phone, line;
    bool found = false;

    cout <<"\t\t\t                Enter the vehicle registration number (liscence_id): ";
    cin >> registrationNumber;

    ifstream infile("records.txt");
    if (!infile) {
        cout << "Error opening records.txt for reading." << endl;
        return;
    }

    while (infile >> id >> pass >> phone) {
        if (id == registrationNumber) {
            found = true;
            cout << "\nVehicle found!" << endl;
            cout << "Registration Number (liscence_id): " << id << endl;
            cout << "Password: " << pass << endl;
            cout << "Phone Number: " << phone << endl;
            cout << "Additional Information: " << line << endl;
            break;
        }
    }

    if (!found) {
        cout << "No vehicle found with the registration number: " << registrationNumber << endl;
    }

    infile.close();
}
// Function to search bookings by username
void searchBookingsByUsername() {
    system("cls");
    string username, name, serviceType, date, status;
    bool found = false;

    cout << "Enter the username to search for bookings: ";
    cin >> username;

    ifstream infile("clients.txt");
    if (!infile) {
        cout << "Error opening clients.txt for reading." << endl;
        return;
    }

    while (getline(infile, name, ';')) {
        getline(infile, serviceType, ';');
        getline(infile, date, ';');
        getline(infile, status);

        if (name == username) {
            found = true;
            cout << "\nBooking Details for Username: " << username << endl;
            cout << "Service Type: " << serviceType << "\nDate: " << date << "\nStatus: " << status << "\n" << endl;
        }
    }

    if (!found) {
        cout << "No bookings found for the username: " << username << endl;
    }

    infile.close();
}
// Function to update service records
void updateServiceRecords() {
    system("cls");
    string username, servicePerformed, partsReplaced, additionalNotes;

    cout << "Enter the username for which you want to update service records: ";
    cin.ignore();
    getline(cin, username);

    cout << "Enter the service performed: ";
    getline(cin, servicePerformed);

    cout << "Enter the parts replaced: ";
    getline(cin, partsReplaced);

    cout << "Enter any additional notes: ";
    getline(cin, additionalNotes);

    ofstream outfile("service_records.txt", ios::app);
    if (!outfile) {
        cout << "Error opening service_records.txt for writing." << endl;
        return;
    }

    outfile << username << ";" << servicePerformed << ";" << partsReplaced << ";" << additionalNotes << endl;
    outfile.close();

    if (outfile.good()) {
        cout << "Service records updated successfully!" << endl;
    } else {
        cout << "Error writing to the file." << endl;
    }
}
// Function to update service completion status
void updateServiceCompletionStatus() {
    system("cls");
    string username, serviceStatus, completionDate;

    cout << "Enter the username for which you want to update service status: ";
    cin.ignore();
    getline(cin, username);

    cout << "Is the service completed? (yes/no): ";
    getline(cin, serviceStatus);

    if (serviceStatus == "no") {
        cout << "Enter the expected completion date (YYYY-MM-DD): ";
        getline(cin, completionDate);
    } else {
        completionDate = "Completed";
    }

    ofstream outfile("service_completion.txt", ios::app);
    if (!outfile) {
        cout << "Error opening service_completion.txt for writing." << endl;
        return;
    }

    outfile << username << ";" << serviceStatus << ";" << completionDate << endl;
    outfile.close();

    if (outfile.good()) {
        cout << "Service status updated successfully!" << endl;
    } else {
        cout << "Error writing to the file." << endl;
    }
}
// Function to display canceled appointments
void displayCanceledAppointments() {
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
// end of the system