#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// Function prototypes
void registerStudent();
bool login();
void changePassword();

// Structure to hold student information
struct Student {
    string username;
    string password;
    string name;
    int age;
};

// Function to register a new student
void registerStudent() {
    ofstream outFile("students.txt", ios::app);
    if (outFile.is_open()) {
        Student newStudent;
        cout << "Enter username: ";
        cin >> newStudent.username;
        cout << "Enter password: ";
        cin >> newStudent.password;
        cout << "Enter name: ";
        cin.ignore();
        getline(cin, newStudent.name);
        cout << "Enter age: ";
        cin >> newStudent.age;

        outFile << newStudent.username << " " << newStudent.password << " " << newStudent.name << " " << newStudent.age << endl;
        cout << "Registration successful!" << endl;
        outFile.close();
    } else {
        cout << "Error: Unable to open file for writing." << endl;
    }
}

// Function to check student credentials and log in
bool login() {
    ifstream inFile("students.txt");
    if (inFile.is_open()) {
        string username, password;
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;
        
        string line;
        while (getline(inFile, line)) {
            stringstream ss(line);
            string user, pass, name;
            int age;
            ss >> user >> pass >> name >> age;
            if (username == user && password == pass) {
                cout << "Login successful! Welcome, " << name << "!" << endl;
                inFile.close();
                return true;
            }
        }
        cout << "Login failed. Invalid username or password." << endl;
        inFile.close();
    } else {
        cout << "Error: Unable to open file for reading." << endl;
    }
    return false;
}

// Function to change student password
void changePassword() {
    ifstream inFile("students.txt");
    ofstream tempFile("temp.txt");
    if (inFile.is_open() && tempFile.is_open()) {
        string username, oldPassword, newPassword;
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter old password: ";
        cin >> oldPassword;
        cout << "Enter new password: ";
        cin >> newPassword;

        string line;
        bool found = false;
        while (getline(inFile, line)) {
            stringstream ss(line);
            string user, pass, name;
            int age;
            ss >> user >> pass >> name >> age;
            if (username == user && oldPassword == pass) {
                tempFile << user << " " << newPassword << " " << name << " " << age << endl;
                found = true;
                cout << "Password changed successfully!" << endl;
            } else {
                tempFile << line << endl;
            }
        }
        inFile.close();
        tempFile.close();
        remove("students.txt");
        rename("temp.txt", "students.txt");

        if (!found) {
            cout << "Invalid username or password." << endl;
        }
    } else {
        cout << "Error: Unable to open files for reading/writing." << endl;
    }
}

int main() {
    int choice;
    do {
        cout << "\n===== College Security System =====" << endl;
        cout << "1. Register" << endl;
        cout << "2. Login" << endl;
        cout << "3. Change Password" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                registerStudent();
                break;
            case 2:
                if (login()) {
                    // Proceed with logged-in functionality
                }
                break;
            case 3:
                changePassword();
                break;
            case 4:
                cout << "Exiting program." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    } while (choice != 4);

    return 0;
}
