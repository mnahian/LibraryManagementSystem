#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

class Book {
private:
    string title;
    string author;
    string isbn;
    bool available;

public:
    Book(); // Constructor
    void setData(string bookTitle, string bookAuthor, string bookIsbn, bool bookAvailable);
    void displayData() const;
    bool isAvailable() const;
    string getIsbn() const;
};

Book::Book() {
    title = "N/A";
    author = "N/A";
    isbn = "N/A";
    available = true;
}

void Book::setData(string bookTitle, string bookAuthor, string bookIsbn, bool bookAvailable) {
    title = bookTitle;
    author = bookAuthor;
    isbn = bookIsbn;
    available = bookAvailable;
}

void Book::displayData() const {
    cout << "Title: " << title << endl;
    cout << "Author: " << author << endl;
    cout << "ISBN: " << isbn << endl;
    cout << "Availability: " << (available ? "Available" : "Not Available") << endl;
}

bool Book::isAvailable() const {
    return available;
}

string Book::getIsbn() const {
    return isbn;
}

// Function to load library data from a file
void loadLibraryData(vector<Book>& library) {
    ifstream inputFile("library_data.txt");
    if (!inputFile) {
        cout << "Library data file not found. Creating a new library." << endl;
        return;
    }

    while (!inputFile.eof()) {
        string title, author, isbn;
        bool available;

        inputFile >> isbn >> available;
        getline(inputFile, title);
        getline(inputFile, author);
        getline(inputFile, isbn);
        library.push_back(Book());
        library.back().setData(title, author, isbn, available);
    }

    inputFile.close();
}

// Function to save library data to a file
void saveLibraryData(const vector<Book>& library) {
    ofstream outputFile("library_data.txt");

    for (const Book& book : library) {
        outputFile << book.getIsbn() << " ";
        outputFile << (book.isAvailable() ? "1" : "0") << " ";
        //outputFile << book.displayData() << endl;
    }

    outputFile.close();
}

int main() {
    vector<Book> library; // A vector to store book records

    loadLibraryData(library); // Load library data from a file

    char continueOperation;
    do {
        cout << "Library Management System" << endl;
        cout << "1. Add Book" << endl;
        cout << "2. Remove Book" << endl;
        cout << "3. Display Books" << endl;
        cout << "Enter your choice (1/2/3): ";

        int choice;
        cin >> choice;

        if (choice == 1) {
            // Adding a new book
            Book book;
            string title, author, isbn;
            bool available;

            cout << "Enter Book Title: ";
            cin.ignore();
            getline(cin, title);

            cout << "Enter Author: ";
            getline(cin, author);

            cout << "Enter ISBN: ";
            getline(cin, isbn);

            cout << "Is the book available? (1 for available, 0 for not available): ";
            cin >> available;

            book.setData(title, author, isbn, available);
            library.push_back(book);
            cout << "Book added successfully!" << endl;
        }
        else if (choice == 2) {
            // Removing a book
            string isbnToRemove;
            cout << "Enter ISBN of the book to remove: ";
            cin >> isbnToRemove;

            bool found = false;
            for (auto it = library.begin(); it != library.end(); ++it) {
                if (it->getIsbn() == isbnToRemove) {
                    library.erase(it);
                    cout << "Book removed!" << endl;
                    found = true;
                    break;
                }
            }

            if (!found) {
                cout << "Book with ISBN " << isbnToRemove << " not found." << endl;
            }
        }
        else if (choice == 3) {
            // Displaying the list of books
            cout << "Library Book List:" << endl;
            for (const Book& book : library) {
                book.displayData();
                cout << "-------------------" << endl;
            }
        }
        else {
            cout << "Invalid choice." << endl;
        }

        // Ask the user if they want to continue
        cout << "Do you want to perform another operation? (y/n): ";
        cin >> continueOperation;
    } while (continueOperation == 'y' || continueOperation == 'Y');

    saveLibraryData(library); // Save library data to a file

    return 0;
}
