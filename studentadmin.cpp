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

//functions for student
void studentMenu();
void viewStudentDetails();
void updateStudentDetails();
void viewAllStudents();

//functions for admin
void adminMenu();
void viewAllStudentRecords();
void searchStudentByID();
void deleteStudentRecord();

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
    cout << "*"<<RED<<"                                               STUDENT ADMINISTRATION SYSTEM LOGIN                                         "<<RESET<<"*" << endl;
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
        if (userid.substr(0, 2) == "st") {
            cout <<RED<<                 userid <<RESET<< "\nYour LOGIN is successful\n";
            studentMenu();
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
    string ruserid, rpassword, rpnumber, student_id, course_id;
    system("cls");
    cout <<BLUE<< "\t\t\t                                       REGISTRATION" <<RESET<< endl;
    cout << "\t\t\t                        Create a username: ";
    cin >> ruserid;

    do {
        cout << "\t\t\t                        Enter the Phone number (10 digits): ";
        cin >> rpnumber;
    } while (!isValidPhoneNumber(rpnumber));

    cout << "\t\t\t                        Enter the Student ID: ";
    cin >> student_id;
    cout << "\t\t\t                        Enter the Course ID: ";
    cin >> course_id;
    cout << "\t\t\t                        Create a password: ";
    cin >> rpassword;

    ofstream f1("records.txt", ios::app);
    f1 << ruserid << " " << rpassword << " " << rpnumber << " " << student_id << " " << course_id << endl;
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

// Access to student part
void studentMenu() {
	system("cls");
    int choice;
    do {
        cout <<RED<<"                                                     Student Menu" <<RESET<< endl;
        cout <<"\n";
        cout <<"\n";
        cout <<"\n";

        cout << "\t                         View Student Details" << endl;
        cout <<"\n";
        cout << "\t                         Update Student Details" << endl;
        cout <<"\n";
        cout << "\t                         View All Students" << endl;
        cout <<"\n";
        cout << "\t                         Back to Main Menu" << endl;
        cout <<"\n";
        cout <<"\n";
        cout << "\t                         Enter your choice"<<BLUE<<"(1/2/3/4): "<<RESET;
        cin >> choice;
        switch (choice) {
            case 1:
                viewStudentDetails();
                break;
            case 2:
            	updateStudentDetails();
                break;
            case 3:
            	viewAllStudents();
            	break;
            case 4:
            	main();
                break;
            default:
            	system("cls");
                cout <<"              Invalid choice. Try again." << endl;
        }
    } while (choice != 4);
}

// Student contents
void viewStudentDetails() {
    system("cls");
    string username, line;
    cout << "Enter your username: ";
    cin >> username;

    ifstream infile("records.txt");
    if (!infile) {
        cout << "Error opening records.txt for reading." << endl;
        return;
    }

    bool found = false;
    while (getline(infile, line)) {
        istringstream iss(line);
        string id, pass, phone, student_id, course_id;
        if (iss >> id >> pass >> phone >> student_id >> course_id) {
            if (id == username) {
                found = true;
                cout << "Username: " << id << endl;
                cout << "Password: " << pass << endl;
                cout << "Phone Number: " << phone << endl;
                cout << "Student ID: " << student_id << endl;
                cout << "Course ID: " << course_id << endl;
                break;
            }
        }
    }

    if (!found) {
        cout << "Student not found!" << endl;
    }

    infile.close();
}

void updateStudentDetails() {
    system("cls");
    string username, newPassword, phoneNumber, studentId, courseId;

    cout << "Enter the username of the account you want to update: ";
    cin >> username;

    ifstream infile("records.txt");
    ofstream tempFile("temp.txt");
    if (!infile || !tempFile) {
        cout << "Error opening file." << endl;
        return;
    }

    string id, pass, phone, student_id, course_id;
    bool found = false;

    while (infile >> id >> pass >> phone >> student_id >> course_id) {
        if (id == username) {
            found = true;

            cout << "Enter new password: ";
            cin >> newPassword;
            cout << "Enter new phone number: ";
            cin >> phoneNumber;
            cout << "Enter new student ID: ";
            cin >> studentId;
            cout << "Enter new course ID: ";
            cin >> courseId;

            tempFile << username << " " << newPassword << " " << phoneNumber << " " << studentId << " " << courseId << endl;
        } else {
            tempFile << id << " " << pass << " " << phone << " " << student_id << " " << course_id << endl;
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

void viewAllStudents() {
    system("cls");
    ifstream infile("records.txt");
    if (!infile) {
        cout << "Error opening records.txt for reading." << endl;
        return;
    }

    string line;
    cout << "\nAll Students:" << endl;
    while (getline(infile, line)) {
        istringstream iss(line);
        string id, pass, phone, student_id, course_id;
        if (iss >> id >> pass >> phone >> student_id >> course_id) {
            cout << "Username: " << id << "\nStudent ID: " << student_id << "\nCourse ID: " << course_id << "\n" << endl;
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
        cout <<"\t\t\t                       1. View All Student Records" << endl;
        cout <<"\t\t\t                       2. Search Student By ID" << endl;
        cout <<"\t\t\t                       3. Delete Student Record" << endl;
        cout <<"\t\t\t                       4. Back to Main Menu" << endl;
        cout <<BLUE<<"\t\t\t                            Enter your choice: "<<RESET;
        cin >> choice;
        switch (choice) {
            case 1:
                viewAllStudentRecords();
                break;
            case 2:
                searchStudentByID();
                break;
            case 3:
            	deleteStudentRecord();
                break;
            case 4:
            	main();
                break;
            default:
                cout << "Invalid choice. Try again." << endl;
        }
    } while (choice != 4);
}

// Admin contents
void viewAllStudentRecords() {
    system("cls");
    ifstream infile("records.txt");
    if (!infile) {
        cout << "Error opening records.txt for reading." << endl;
        return;
    }

    string line;
    cout << "\nAll Student Records:" << endl;
    while (getline(infile, line)) {
        istringstream iss(line);
        string id, pass, phone, student_id, course_id;
        if (iss >> id >> pass >> phone >> student_id >> course_id) {
            cout << "Username: " << id << "\nPassword: " << pass << "\nPhone Number: " << phone << "\nStudent ID: " << student_id << "\nCourse ID: " << course_id << "\n" << endl;
        }
    }
    infile.close();
}

void searchStudentByID() {
    system("cls");
    string studentId, id, pass, phone, line;
    bool found = false;

    cout <<"\t\t\t                Enter the student ID: ";
    cin >> studentId;

    ifstream infile("records.txt");
    if (!infile) {
        cout << "Error opening records.txt for reading." << endl;
        return;
    }

    while (infile >> id >> pass >> phone) {
        if (id == studentId) {
            found = true;
            cout << "\nStudent found!" << endl;
            cout << "Student ID: " << id << endl;
            cout << "Password: " << pass << endl;
            cout << "Phone Number: " << phone << endl;
            break;
        }
    }

    if (!found) {
        cout << "No student found with the ID: " << studentId << endl;
    }

    infile.close();
}

void deleteStudentRecord() {
    system("cls");
    string studentId, id, pass, phone, student_id, course_id;
    bool found = false;

    cout << "Enter the student ID to delete: ";
    cin >> studentId;

    ifstream infile("records.txt");
    ofstream tempFile("temp.txt");
    if (!infile || !tempFile) {
        cout << "Error opening file." << endl;
        return;
    }

    while (infile >> id >> pass >> phone >> student_id >> course_id) {
        if (student_id == studentId) {
            found = true;
        } else {
            tempFile << id << " " << pass << " " << phone << " " << student_id << " " << course_id << endl;
        }
    }

    infile.close();
    tempFile.close();

    remove("records.txt");
    rename("temp.txt", "records.txt");

    if (found) {
        cout << "Student record deleted successfully!" << endl;
    } else {
        cout << "Student not found!" << endl;
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
