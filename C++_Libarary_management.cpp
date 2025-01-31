#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <ctime>
#include <thread>
#include <mutex>
#include <map>

// Base class for LibraryItem
class LibraryItem {
protected:
    std::string title;
    std::string id;

public:
    LibraryItem(const std::string& title, const std::string& id) : title(title), id(id) {}
    virtual ~LibraryItem() {}

    std::string getTitle() const { return title; }
    std::string getId() const { return id; }

    virtual void display() const = 0; // Pure virtual function
};

// Book class inheriting from LibraryItem
class Book : public LibraryItem {
private:
    std::string author;
    bool isAvailable;
    std::string dueDate;
    std::vector<std::string> reservations;
    double rating;
    int ratingCount;

public:
    Book(const std::string& title, const std::string& id, const std::string& author)
        : LibraryItem(title, id), author(author), isAvailable(true), dueDate("N/A"), rating(0), ratingCount(0) {}

    bool getIsAvailable() const { return isAvailable; }
    std::string getDueDate() const { return dueDate; }
    double getRating() const { return rating; }

    void setIsAvailable(bool status) { isAvailable = status; }
    void setDueDate(const std::string& date) { dueDate = date; }
    void addReservation(const std::string& memberId) { reservations.push_back(memberId); }
    void addRating(double newRating) {
        rating = (rating * ratingCount + newRating) / (ratingCount + 1);
        ratingCount++;
    }

    void display() const override {
        std::cout << "Book ID: " << id << "\nTitle: " << title << "\nAuthor: " << author
                  << "\nAvailable: " << (isAvailable ? "Yes" : "No") << "\nDue Date: " << dueDate
                  << "\nRating: " << rating << "\nReservations: ";
        for (const auto& reservation : reservations) {
            std::cout << reservation << " ";
        }
        std::cout << std::endl;
    }
};

// Member class
class Member {
private:
    std::string name;
    std::string memberId;
    std::vector<std::string> borrowedBooks;
    std::vector<std::string> reservedBooks;
    std::map<std::string, double> ratedBooks;

public:
    Member(const std::string& name, const std::string& memberId) : name(name), memberId(memberId) {}

    std::string getName() const { return name; }
    std::string getMemberId() const { return memberId; }
    std::vector<std::string> getBorrowedBooks() const { return borrowedBooks; }
    std::vector<std::string> getReservedBooks() const { return reservedBooks; }

    void borrowBook(const std::string& bookId) { borrowedBooks.push_back(bookId); }
    void returnBook(const std::string& bookId) {
        auto it = std::find(borrowedBooks.begin(), borrowedBooks.end(), bookId);
        if (it != borrowedBooks.end()) {
            borrowedBooks.erase(it);
        }
    }
    void reserveBook(const std::string& bookId) { reservedBooks.push_back(bookId); }
    void rateBook(const std::string& bookId, double rating) { ratedBooks[bookId] = rating; }

    void display() const {
        std::cout << "Member ID: " << memberId << "\nName: " << name << "\nBorrowed Books: ";
        for (const auto& bookId : borrowedBooks) {
            std::cout << bookId << " ";
        }
        std::cout << "\nReserved Books: ";
        for (const auto& bookId : reservedBooks) {
            std::cout << bookId << " ";
        }
        std::cout << "\nRated Books: ";
        for (const auto& pair : ratedBooks) {
            std::cout << pair.first << " (" << pair.second << ") ";
        }
        std::cout << std::endl;
    }
};

// Transaction class
class Transaction {
private:
    std::string memberId;
    std::string bookId;
    std::string transactionType; // "borrow" or "return"
    std::time_t timestamp;

public:
    Transaction(const std::string& memberId, const std::string& bookId, const std::string& transactionType)
        : memberId(memberId), bookId(bookId), transactionType(transactionType) {
        timestamp = std::time(nullptr);
    }

    std::time_t getTimestamp() const { return timestamp; }

    void display() const {
        std::cout << "Member ID: " << memberId << "\nBook ID: " << bookId
                  << "\nTransaction Type: " << transactionType << "\nTimestamp: " << std::ctime(&timestamp) << std::endl;
    }
};

// User class for authentication
class User {
private:
    std::string username;
    std::string password;
    std::string role; // "admin" or "member"

public:
    User(const std::string& username, const std::string& password, const std::string& role)
        : username(username), password(password), role(role) {}

    bool authenticate(const std::string& username, const std::string& password) const {
        return this->username == username && this->password == password;
    }

    std::string getRole() const { return role; }
};

// Library class
class Library {
private:
    std::vector<Book> books;
    std::vector<Member> members;
    std::vector<Transaction> transactions;
    std::vector<User> users;
    User* currentUser;
    std::mutex mtx;

public:
    Library() : currentUser(nullptr) {
        users.emplace_back("admin", "admin123", "admin");
        users.emplace_back("member", "member123", "member");
    }

    bool login(const std::string& username, const std::string& password) {
        for (auto& user : users) {
            if (user.authenticate(username, password)) {
                currentUser = &user;
                return true;
            }
        }
        return false;
    }

    void logout() {
        currentUser = nullptr;
    }

    bool isAdmin() const {
        return currentUser && currentUser->getRole() == "admin";
    }

    void addBook(const Book& book) {
        std::lock_guard<std::mutex> lock(mtx);
        if (isAdmin()) {
            books.push_back(book);
        } else {
            std::cout << "Permission denied." << std::endl;
        }
    }

    void addMember(const Member& member) {
        std::lock_guard<std::mutex> lock(mtx);
        if (isAdmin()) {
            members.push_back(member);
        } else {
            std::cout << "Permission denied." << std::endl;
        }
    }

    void borrowBook(const std::string& memberId, const std::string& bookId) {
        std::lock_guard<std::mutex> lock(mtx);
        auto bookIt = std::find_if(books.begin(), books.end(), [&](const Book& book) {
            return book.getId() == bookId;
        });
        auto memberIt = std::find_if(members.begin(), members.end(), [&](const Member& member) {
            return member.getMemberId() == memberId;
        });

        if (bookIt != books.end() && memberIt != members.end() && bookIt->getIsAvailable()) {
            bookIt->setIsAvailable(false);
            bookIt->setDueDate(getDueDate());
            memberIt->borrowBook(bookId);
            transactions.emplace_back(memberId, bookId, "borrow");
        } else {
            std::cout << "Book not available or member not found." << std::endl;
        }
    }

    void returnBook(const std::string& memberId, const std::string& bookId) {
        std::lock_guard<std::mutex> lock(mtx);
        auto bookIt = std::find_if(books.begin(), books.end(), [&](const Book& book) {
            return book.getId() == bookId;
        });
        auto memberIt = std::find_if(members.begin(), members.end(), [&](const Member& member) {
            return member.getMemberId() == memberId;
        });

        if (bookIt != books.end() && memberIt != members.end() && !bookIt->getIsAvailable()) {
            bookIt->setIsAvailable(true);
            bookIt->setDueDate("N/A");
            memberIt->returnBook(bookId);
            transactions.emplace_back(memberId, bookId, "return");
            notifyReservations(bookId);
        } else {
            std::cout << "Book not borrowed or member not found." << std::endl;
        }
    }

    void reserveBook(const std::string& memberId, const std::string& bookId) {
        std::lock_guard<std::mutex> lock(mtx);
        auto bookIt = std::find_if(books.begin(), books.end(), [&](const Book& book) {
            return book.getId() == bookId;
        });
        auto memberIt = std::find_if(members.begin(), members.end(), [&](const Member& member) {
            return member.getMemberId() == memberId;
        });

        if (bookIt != books.end() && memberIt != members.end() && !bookIt->getIsAvailable()) {
            bookIt->addReservation(memberId);
            memberIt->reserveBook(bookId);
        } else {
            std::cout << "Book is available or member not found." << std::endl;
        }
    }

    void rateBook(const std::string& memberId, const std::string& bookId, double rating) {
        std::lock_guard<std::mutex> lock(mtx);
        auto bookIt = std::find_if(books.begin(), books.end(), [&](const Book& book) {
            return book.getId() == bookId;
        });
        auto memberIt = std::find_if(members.begin(), members.end(), [&](const Member& member) {
            return member.getMemberId() == memberId;
        });

        if (bookIt != books.end() && memberIt != members.end()) {
            bookIt->addRating(rating);
            memberIt->rateBook(bookId, rating);
        } else {
            std::cout << "Book or member not found." << std::endl;
        }
    }

    std::string getDueDate() const {
        std::time_t now = std::time(nullptr);
        std::tm* dueDate = std::localtime(&now);
        dueDate->tm_mday += 14; // 14 days from now
        std::mktime(dueDate);
        char buffer[80];
        std::strftime(buffer, 80, "%Y-%m-%d", dueDate);
        return std::string(buffer);
    }

    void notifyReservations(const std::string& bookId) {
        auto bookIt = std::find_if(books.begin(), books.end(), [&](const Book& book) {
            return book.getId() == bookId;
        });

        if (bookIt != books.end()) {
            for (const auto& memberId : bookIt->reservations) {
                auto memberIt = std::find_if(members.begin(), members.end(), [&](const Member& member) {
                    return member.getMemberId() == memberId;
                });
                if (memberIt != members.end()) {
                    std::cout << "Notification: Member " << memberId << " your reserved book " << bookId << " is now available.\n";
                }
            }
            bookIt->reservations.clear();
        }
    }

    void displayBooks() const {
        std::lock_guard<std::mutex> lock(mtx);
        for (const auto& book : books) {
            book.display();
        }
    }

    void displayMembers() const {
        std::lock_guard<std::mutex> lock(mtx);
        for (const auto& member : members) {
            member.display();
        }
    }

    void displayTransactions() const {
        std::lock_guard<std::mutex> lock(mtx);
        for (const auto& transaction : transactions) {
            transaction.display();
        }
    }

    void saveToFile(const std::string& filename) const {
        std::lock_guard<std::mutex> lock(mtx);
        std::ofstream outFile(filename);
        if (outFile.is_open()) {
            for (const auto& book : books) {
                outFile << "Book\n" << book.getId() << "\n" << book.getTitle() << "\n" << book.getDueDate() << "\n";
                for (const auto& reservation : book.reservations) {
                    outFile << reservation << "\n";
                }
                outFile << "Rating\n" << book.getRating() << "\n";
            }
            for (const auto& member : members) {
                outFile << "Member\n" << member.getMemberId() << "\n" << member.getName() << "\n";
                for (const auto& bookId : member.getBorrowedBooks()) {
                    outFile << bookId << "\n";
                }
                outFile << "Reserved\n";
                for (const auto& bookId : member.getReservedBooks()) {
                    outFile << bookId << "\n";
                }
                outFile << "Rated\n";
                for (const auto& pair : member.ratedBooks) {
                    outFile << pair.first << "\n" << pair.second << "\n";
                }
            }
            for (const auto& transaction : transactions) {
                outFile << "Transaction\n" << transaction.memberId << "\n" << transaction.bookId << "\n" << transaction.transactionType << "\n" << transaction.getTimestamp() << "\n";
            }
            outFile.close();
        }
    }

    void loadFromFile(const std::string& filename) {
        std::lock_guard<std::mutex> lock(mtx);
        std::ifstream inFile(filename);
        if (inFile.is_open()) {
            std::string line;
            while (std::getline(inFile, line)) {
                if (line == "Book") {
                    std::string id, title, dueDate, reservation, ratingLine;
                    double rating;
                    std::getline(inFile, id);
                    std::getline(inFile, title);
                    std::getline(inFile, dueDate);
                    books.emplace_back(title, id, "Author"); // Assuming author is known
                    books.back().setDueDate(dueDate);
                    while (std::getline(inFile, reservation) && reservation != "Rating" && reservation != "Transaction" && reservation != "Book" && reservation != "Member") {
                        books.back().addReservation(reservation);
                    }
                    if (reservation == "Rating") {
                        std::getline(inFile, ratingLine);
                        rating = std::stod(ratingLine);
                        books.back().rating = rating;
                    }
                    if (!inFile.eof()) {
                        inFile.seekg(-reservation.length() - 1, std::ios_base::cur);
                    }
                } else if (line == "Member") {
                    std::string id, name, bookId, reservedLine, ratedLine;
                    double rating;
                    std::getline(inFile, id);
                    std::getline(inFile, name);
                    members.emplace_back(name, id);
                    while (std::getline(inFile, bookId) && bookId != "Reserved" && bookId != "Transaction" && bookId != "Book" && bookId != "Member") {
                        members.back().borrowBook(bookId);
                    }
                    if (bookId == "Reserved") {
                        while (std::getline(inFile, reservedLine) && reservedLine != "Rated" && reservedLine != "Transaction" && reservedLine != "Book" && reservedLine != "Member") {
                            members.back().reserveBook(reservedLine);
                        }
                    }
                    if (reservedLine == "Rated") {
                        while (std::getline(inFile, bookId) && std::getline(inFile, ratedLine) && ratedLine != "Transaction" && ratedLine != "Book" && ratedLine != "Member") {
                            rating = std::stod(ratedLine);
                            members.back().rateBook(bookId, rating);
                        }
                    }
                    if (!inFile.eof()) {
                        inFile.seekg(-ratedLine.length() - 1, std::ios_base::cur);
                    }
                } else if (line == "Transaction") {
                    std::string memberId, bookId, transactionType;
                    std::time_t timestamp;
                    std::getline(inFile, memberId);
                    std::getline(inFile, bookId);
                    std::getline(inFile, transactionType);
                    inFile >> timestamp;
                    inFile.ignore();
                    transactions.emplace_back(memberId, bookId, transactionType);
                }
            }
            inFile.close();
        }
    }

    void searchBooksByTitle(const std::string& title) const {
        std::lock_guard<std::mutex> lock(mtx);
        for (const auto& book : books) {
            if (book.getTitle().find(title) != std::string::npos) {
                book.display();
            }
        }
    }

    void searchMembersByName(const std::string& name) const {
        std::lock_guard<std::mutex> lock(mtx);
        for (const auto& member : members) {
            if (member.getName().find(name) != std::string::npos) {
                member.display();
            }
        }
    }

    void calculateFines() const {
        std::lock_guard<std::mutex> lock(mtx);
        std::time_t now = std::time(nullptr);
        for (const auto& member : members) {
            for (const auto& bookId : member.getBorrowedBooks()) {
                auto bookIt = std::find_if(books.begin(), books.end(), [&](const Book& book) {
                    return book.getId() == bookId;
                });
                if (bookIt != books.end() && !bookIt->getIsAvailable()) {
                    std::tm dueDate = {};
                    std::istringstream(bookIt->getDueDate()) >> std::get_time(&dueDate, "%Y-%m-%d");
                    std::time_t dueTime = std::mktime(&dueDate);
                    double diff = std::difftime(now, dueTime);
                    if (diff > 0) {
                        double fine = (diff / (24 * 3600)) * 0.5; // 0.5 units per day
                        std::cout << "Member ID: " << member.getMemberId() << "\nBook ID: " << bookId << "\nFine: " << fine << " units\n";
                    }
                }
            }
        }
    }

    void recommendBooks(const std::string& memberId) const {
        std::lock_guard<std::mutex> lock(mtx);
        auto memberIt = std::find_if(members.begin(), members.end(), [&](const Member& member) {
            return member.getMemberId() == memberId;
        });

        if (memberIt != members.end()) {
            std::map<std::string, int> recommendations;
            for (const auto& pair : memberIt->ratedBooks) {
                if (pair.second > 3.0) { // Consider books rated higher than 3.0
                    auto bookIt = std::find_if(books.begin(), books.end(), [&](const Book& book) {
                        return book.getId() == pair.first;
                    });
                    if (bookIt != books.end()) {
                        for (const auto& otherBook : books) {
                            if (otherBook.getAuthor() == bookIt->getAuthor() && otherBook.getId() != pair.first) {
                                recommendations[otherBook.getId()]++;
                            }
                        }
                    }
                }
            }
            std::cout << "Recommended Books for Member " << memberId << ":\n";
            for (const auto& pair : recommendations) {
                auto bookIt = std::find_if(books.begin(), books.end(), [&](const Book& book) {
                    return book.getId() == pair.first;
                });
                if (bookIt != books.end()) {
                    std::cout << "Book ID: " << bookIt->getId() << "\nTitle: " << bookIt->getTitle() << "\n";
                }
            }
        } else {
            std::cout << "Member not found." << std::endl;
        }
    }

    void generateAdminReport() const {
        std::lock_guard<std::mutex> lock(mtx);
        if (isAdmin()) {
            std::cout << "Admin Report:\n";
            std::cout << "Total Books: " << books.size() << "\n";
            std::cout << "Total Members: " << members.size() << "\n";
            std::cout << "Total Transactions: " << transactions.size() << "\n";
            std::cout << "Books with Ratings:\n";
            for (const auto& book : books) {
                if (book.getRating() > 0) {
                    std::cout << "Book ID: " << book.getId() << "\nTitle: " << book.getTitle() << "\nRating: " << book.getRating() << "\n";
                }
            }
        } else {
            std::cout << "Permission denied." << std::endl;
        }
    }
};

void displayMenu() {
    std::cout << "Library Management System\n";
    std::cout << "1. Login\n";
    std::cout << "2. Add Book (Admin only)\n";
    std::cout << "3. Add Member (Admin only)\n";
    std::cout << "4. Borrow Book\n";
    std::cout << "5. Return Book\n";
    std::cout << "6. Reserve Book\n";
    std::cout << "7. Rate Book\n";
    std::cout << "8. Display Books\n";
    std::cout << "9. Display Members\n";
    std::cout << "10. Display Transactions\n";
    std::cout << "11. Search Books by Title\n";
    std::cout << "12. Search Members by Name\n";
    std::cout << "13. Calculate Fines\n";
    std::cout << "14. Recommend Books\n";
    std::cout << "15. Generate Admin Report\n";
    std::cout << "16. Save to File\n";
    std::cout << "17. Load from File\n";
    std::cout << "18. Logout\n";
    std::cout << "19. Exit\n";
    std::cout << "Enter your choice: ";
}

int main() {
    Library library;
    int choice;
    std::string username, password, title, id, author, name, memberId, bookId, transactionType, searchTitle, searchName, filename;
    double rating;

    while (true) {
        displayMenu();
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Enter username: ";
                std::cin >> username;
                std::cout << "Enter password: ";
                std::cin >> password;
                if (library.login(username, password)) {
                    std::cout << "Login successful.\n";
                } else {
                    std::cout << "Login failed.\n";
                }
                break;
            case 2:
                if (library.isAdmin()) {
                    std::cout << "Enter book title: ";
                    std::cin.ignore();
                    std::getline(std::cin, title);
                    std::cout << "Enter book ID: ";
                    std::cin >> id;
                    std::cout << "Enter book author: ";
                    std::cin.ignore();
                    std::getline(std::cin, author);
                    library.addBook(Book(title, id, author));
                } else {
                    std::cout << "Permission denied.\n";
                }
                break;
            case 3:
                if (library.isAdmin()) {
                    std::cout << "Enter member name: ";
                    std::cin.ignore();
                    std::getline(std::cin, name);
                    std::cout << "Enter member ID: ";
                    std::cin >> memberId;
                    library.addMember(Member(name, memberId));
                } else {
                    std::cout << "Permission denied.\n";
                }
                break;
            case 4:
                std::cout << "Enter member ID: ";
                std::cin >> memberId;
                std::cout << "Enter book ID: ";
                std::cin >> bookId;
                library.borrowBook(memberId, bookId);
                break;
            case 5:
                std::cout << "Enter member ID: ";
                std::cin >> memberId;
                std::cout << "Enter book ID: ";
                std::cin >> bookId;
                library.returnBook(memberId, bookId);
                break;
            case 6:
                std::cout << "Enter member ID: ";
                std::cin >> memberId;
                std::cout << "Enter book ID: ";
                std::cin >> bookId;
                library.reserveBook(memberId, bookId);
                break;
            case 7:
                std::cout << "Enter member ID: ";
                std::cin >> memberId;
                std::cout << "Enter book ID: ";
                std::cin >> bookId;
                std::cout << "Enter rating: ";
                std::cin >> rating;
                library.rateBook(memberId, bookId, rating);
                break;
            case 8:
                library.displayBooks();
                break;
            case 9:
                library.displayMembers();
                break;
            case 10:
                library.displayTransactions();
                break;
            case 11:
                std::cout << "Enter book title to search: ";
                std::cin.ignore();
                std::getline(std::cin, searchTitle);
                library.searchBooksByTitle(searchTitle);
                break;
            case 12:
                std::cout << "Enter member name to search: ";
                std::cin.ignore();
                std::getline(std::cin, searchName);
                library.searchMembersByName(searchName);
                break;
            case 13:
                library.calculateFines();
                break;
            case 14:
                std::cout << "Enter member ID for recommendations: ";
                std::cin >> memberId;
                library.recommendBooks(memberId);
                break;
            case 15:
                library.generateAdminReport();
                break;
            case 16:
                std::cout << "Enter filename to save: ";
                std::cin >> filename;
                library.saveToFile(filename);
                break;
            case 17:
                std::cout << "Enter filename to load: ";
                std::cin >> filename;
                library.loadFromFile(filename);
                break;
            case 18:
                library.logout();
                std::cout << "Logout successful.\n";
                break;
            case 19:
                std::cout << "Exiting...\n";
                return 0;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
