#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct patient {
    int patientID;
    string name;
    int age;
    string disease;
    int roomNumber;
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

void addPatient(patient details[], int &patientsNum, int maxPatients) {
    if (patientsNum >= maxPatients) {
        cout << "Hospital is at full capacity!" << endl;
        return;
    }
    cout << "Enter patient ID: ";
    cin >> details[patientsNum].patientID;
    clearInputBuffer();
    cout << "Enter patient name: ";
    getline(cin, details[patientsNum].name);
    cout << "Enter patient age: ";
    cin >> details[patientsNum].age;
    clearInputBuffer();
    cout << "Enter patient's disease: ";
    getline(cin, details[patientsNum].disease);
    cout << "Enter patient's room number: ";
    cin >> details[patientsNum].roomNumber;
    clearInputBuffer();
    patientsNum++;
    cout << "Patient details added successfully!" << endl;
}

void patientSearchByID(patient details[], int patientsNum, int search) {
    bool found = false;
    for (int i = 0; i < patientsNum; i++) {
        if (details[i].patientID == search) {
            cout << "Patient Found! Details are --->" << endl;
            cout << "\tPatient ID: " << details[i].patientID << endl;
            cout << "\tName: " << details[i].name << endl;
            cout << "\tAge: " << details[i].age << endl;
            cout << "\tDisease: " << details[i].disease << endl;
            cout << "\tRoom Number: " << details[i].roomNumber << endl;
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "Patient with ID " << search << " not found in the records!" << endl;
    }
}

void patientSearchByName(patient details[], int patientsNum, string searchName) {
    searchName = toLower(searchName);
    bool found = false;
    for (int i = 0; i < patientsNum; i++) {
        if (toLower(details[i].name) == searchName) {
            cout << "Patient Found! Details are --->" << endl;
            cout << "\tPatient ID: " << details[i].patientID << endl;
            cout << "\tName: " << details[i].name << endl;
            cout << "\tAge: " << details[i].age << endl;
            cout << "\tDisease: " << details[i].disease << endl;
            cout << "\tRoom Number: " << details[i].roomNumber << endl;
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "Patient with name \"" << searchName << "\" not found in the records!" << endl;
    }
}

void displayPatients(patient details[], int patientsNum) {
    cout << "\nDisplaying all patients in the hospital:" << endl;
    for (int i = 0; i < patientsNum; i++) {
        cout << "\tPatient ID: " << details[i].patientID << endl;
        cout << "\tName: " << details[i].name << endl;
        cout << "\tAge: " << details[i].age << endl;
        cout << "\tDisease: " << details[i].disease << endl;
        cout << "\tRoom Number: " << details[i].roomNumber << endl;
        cout << "----------------------" << endl;
    }
}

void saveToFile(patient details[], int patientsNum, const string &filename) {
    ofstream outFile(filename, ios::out);
    if (outFile.is_open()) {
        for (int i = 0; i < patientsNum; i++) {
            outFile << details[i].patientID << "\t" << details[i].name << "\t" << details[i].age << "\t" << details[i].disease << "\t" << details[i].roomNumber << endl;
        }
        outFile.close();
        cout << "Patient records saved to file successfully!" << endl;
    } else {
        cout << "Error opening file for saving!" << endl;
    }
}

void loadFromFile(patient details[], int &patientsNum, const string &filename) {
    ifstream inFile(filename, ios::in);
    if (inFile.is_open()) {
        while (inFile >> details[patientsNum].patientID) {
            inFile.ignore();
            getline(inFile, details[patientsNum].name, '\t');
            inFile >> details[patientsNum].age;
            inFile.ignore();
            getline(inFile, details[patientsNum].disease, '\t');
            inFile >> details[patientsNum].roomNumber;
            patientsNum++;
        }
        inFile.close();
        cout << "Patient records loaded from file successfully!" << endl;
    } else {
        cout << "Error opening file for loading!" << endl;
    }
}

void editPatientDetails(patient details[], int patientsNum, int searchID) {
    bool found = false;
    for (int i = 0; i < patientsNum; i++) {
        if (details[i].patientID == searchID) {
            cout << "Editing details for Patient ID: " << details[i].patientID << endl;
            cout << "Enter new name: ";
            getline(cin, details[i].name);
            cout << "Enter new age: ";
            cin >> details[i].age;
            clearInputBuffer();
            cout << "Enter new disease: ";
            getline(cin, details[i].disease);
            cout << "Enter new room number: ";
            cin >> details[i].roomNumber;
            clearInputBuffer();
            cout << "Patient details updated successfully!" << endl;
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "Patient with ID " << searchID << " not found in the records!" << endl;
    }
}

void deletePatient(patient details[], int &patientsNum, int searchID) {
    bool found = false;
    for (int i = 0; i < patientsNum; i++) {
        if (details[i].patientID == searchID) {
            for (int j = i; j < patientsNum - 1; j++) {
                details[j] = details[j + 1];
            }
            patientsNum--;
            cout << "Patient with ID " << searchID << " has been deleted!" << endl;
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "Patient with ID " << searchID << " not found in the records!" << endl;
    }
}

int main() {
    char y_n = 'y';
    string searchName;
    int searchID;
    int operation, operationSearch;
    int maxPatients = 50;
    patient details[maxPatients];
    int patientsNum = 8;

    details[0] = {1, "John Doe", 45, "Pneumonia", 101};
    details[1] = {2, "Jane Smith", 33, "Fever", 102};
    details[2] = {3, "Sam Wilson", 29, "Broken Leg", 103};
    details[3] = {4, "Alice Brown", 60, "Heart Disease", 104};
    details[4] = {5, "Bob White", 50, "Diabetes", 105};
    details[5] = {6, "Catherine Green", 40, "Cancer", 106};
    details[6] = {7, "David Black", 25, "Asthma", 107};
    details[7] = {8, "Eve Blue", 37, "High Blood Pressure", 108};

    while (y_n == 'y') {
        cout << "\nMenu:" << endl;
        cout << "1. Add a new patient to the hospital." << endl;
        cout << "2. Search for a patient." << endl;
        cout << "3. Display all patients." << endl;
        cout << "4. Save patient records to file." << endl;
        cout << "5. Load patient records from file." << endl;
        cout << "6. Edit patient details." << endl;
        cout << "7. Delete a patient record." << endl;
        cout << "Enter a number from (1-7) to perform the desired operation: ";
        cin >> operation;
        clearInputBuffer();

        switch (operation) {
            case 1:
                addPatient(details, patientsNum, maxPatients);
                break;
            case 2:
                cout << "1. Search patient details by ID." << endl;
                cout << "2. Search patient details by name." << endl;
                cout << "Enter a number from (1-2) to perform the desired operation: ";
                cin >> operationSearch;
                clearInputBuffer();
                if (operationSearch == 1) {
                    cout << "Enter the ID of the patient to search: ";
                    cin >> searchID;
                    patientSearchByID(details, patientsNum, searchID);
                } else if (operationSearch == 2) {
                    cout << "Enter the name of the patient to search: ";
                    getline(cin, searchName);
                    patientSearchByName(details, patientsNum, searchName);
                } else {
                    cout << "Invalid choice!" << endl;
                }
                break;
            case 3:
                displayPatients(details, patientsNum);
                break;
            case 4:
                saveToFile(details, patientsNum, "patients_inventory.txt");
                break;
            case 5:
                loadFromFile(details, patientsNum, "patients_inventory.txt");
                break;
            case 6:
                cout << "Enter the patient ID to edit: ";
                cin >> searchID;
                clearInputBuffer();
                editPatientDetails(details, patientsNum, searchID);
                break;
            case 7:
                cout << "Enter the patient ID to delete: ";
                cin >> searchID;
                clearInputBuffer();
                deletePatient(details, patientsNum, searchID);
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
