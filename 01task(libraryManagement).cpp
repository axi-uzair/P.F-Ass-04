#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct book {
    int BookID;
    string title;
    string author;
    int quantity;
};

string toLower(string str) {
    for (int i = 0; i < str.length(); i++) {
        str[i] = tolower(str[i]);
    }
    return str;
}

void clearInputBuffer() {
    char ch;
    while (cin.get(ch)) {
        if (ch == '\n') break;
    }
}

void addbooks(book details[], int &booksnum, int maxbooks) {
    if (booksnum >= maxbooks) {
        cout << "Inventory is full!" << endl;
        return;
    }

    cout << "Enter book ID: ";
    cin >> details[booksnum].BookID;
    clearInputBuffer();

    cout << "Enter book title: ";
    getline(cin, details[booksnum].title);

    cout << "Enter author name: ";
    getline(cin, details[booksnum].author);

    cout << "Enter quantity of book: ";
    cin >> details[booksnum].quantity;
    clearInputBuffer();

    booksnum++;
    cout << "Book details added successfully!" << endl;
}

void booksearchID(book details[], int booksnum, int search) {
    bool found = false;
    for (int i = 0; i < booksnum; i++) {
        if (details[i].BookID == search) {
            cout << "Book Found! Details of book are --->" << endl;
            cout << "\tBook ID: " << details[i].BookID << endl;
            cout << "\tTitle: " << details[i].title << endl;
            cout << "\tAuthor: " << details[i].author << endl;
            cout << "\tQuantity: " << details[i].quantity << endl;
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "Book with ID " << search << " not found in the inventory!" << endl;
    }
}

void booksearchtitle(book details[], int booksnum, string searchTitle) {
    searchTitle = toLower(searchTitle);
    bool found = false;
    for (int i = 0; i < booksnum; i++) {
        if (toLower(details[i].title) == searchTitle) {
            cout << "Book Found! Details of book are --->" << endl;
            cout << "\tBook ID: " << details[i].BookID << endl;
            cout << "\tTitle: " << details[i].title << endl;
            cout << "\tAuthor: " << details[i].author << endl;
            cout << "\tQuantity: " << details[i].quantity << endl;
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "Book with title \"" << searchTitle << "\" not found in the inventory!" << endl;
    }
}

void displayBooks(book details[], int booksnum) {
    cout << "\nDisplaying all available books in the inventory:" << endl;
    for (int i = 0; i < booksnum; i++) {
        cout << "\tBook ID: " << details[i].BookID << endl;
        cout << "\tTitle: " << details[i].title << endl;
        cout << "\tAuthor: " << details[i].author << endl;
        cout << "\tQuantity: " << details[i].quantity << endl;
        cout << "----------------------" << endl;
    }
}

void saveToFile(book details[], int booksnum, const string &filename) {
    ofstream outFile(filename);
    if (outFile.is_open()) {
        for (int i = 0; i < booksnum; i++) {
            outFile << details[i].BookID << "\t" << details[i].title << "\t" << details[i].author << "\t" << details[i].quantity << endl;
        }
        outFile.close();
        cout << "Inventory saved to file successfully!" << endl;
    } else {
        cout << "Error opening file for saving!" << endl;
    }
}

void loadFromFile(book details[], int &booksnum, const string &filename) {
    ifstream inFile(filename, ios::in);
    if (inFile.is_open()) {
        while (inFile >> details[booksnum].BookID) {
            inFile.ignore();
            getline(inFile, details[booksnum].title, '\t');
            getline(inFile, details[booksnum].author, '\t');
            inFile >> details[booksnum].quantity;
            booksnum++;
        }
        inFile.close();
        cout << "Inventory loaded from file successfully!" << endl;
    } else {
        cout << "Error opening file for loading!" << endl;
    }
}

int main() {
    char y_n = 'y';
    string searchtitle;
    int searchID;
    int operation, operationsearch;
    int maxbooks = 20;
    book details[maxbooks];
    int booksnum = 8;

    details[0] = {1, "Art of War", "Sun Tzu", 2};
    details[1] = {2, "The Art of Laziness", "Kyrie Petrakis", 1};
    details[2] = {3, "The 7 Habits of Highly Effective People", "Stephen R. Covey", 3};
    details[3] = {4, "The Power of Now", "Eckhart Tolle", 1};
    details[4] = {5, "Man's Search for Meaning", "Viktor Frankl", 2};
    details[5] = {6, "The Four Agreements", "Don Miguel Ruiz", 4};
    details[6] = {7, "Daring Greatly", "Brené Brown", 2};
    details[7] = {8, "The Alchemist", "Paulo Coelho", 2};

    while (y_n == 'y') {
        cout << "\nMenu:" << endl;
        cout << "1. Add a new book to the inventory." << endl;
        cout << "2. Search for a book." << endl;
        cout << "3. Display all available books." << endl;
        cout << "4. Save inventory to file." << endl;
        cout << "5. Load inventory from file." << endl;
        cout << "Enter a number from (1-5) to perform the desired operation: ";
        cin >> operation;
        clearInputBuffer();

        switch (operation) {
            case 1:
                addbooks(details, booksnum, maxbooks);
                break;
            case 2:
                cout << "1. Search book details by ID." << endl;
                cout << "2. Search book details by title." << endl;
                cout << "Enter a number from (1-2) to perform the desired operation: ";
                cin >> operationsearch;
                clearInputBuffer();
                if (operationsearch == 1) {
                    cout << "Enter the ID of the book to search for it: ";
                    cin >> searchID;
                    booksearchID(details, booksnum, searchID);
                } else if (operationsearch == 2) {
                    cout << "Enter the title of the book: ";
                    getline(cin, searchtitle);
                    booksearchtitle(details, booksnum, searchtitle);
                } else {
                    cout << "Invalid choice!" << endl;
                }
                break;
            case 3:
                displayBooks(details, booksnum);
                break;
            case 4:
                saveToFile(details, booksnum, "inventory.txt");
                break;
            case 5:
                loadFromFile(details, booksnum, "inventory.txt");
                break;
            default:
                cout << "Invalid operation!" << endl;
        }

        cout << "\nDo you want to perform another operation? (y/n): ";
        cin >> y_n;
        clearInputBuffer();
    }

    return 0;
}
