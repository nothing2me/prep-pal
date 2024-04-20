#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include "PrepCheck.h"

using namespace std;

// CONSTS
const char fileName[] = "students.txt";

// Prototypes
void mainMenu(fstream &studentData, int &menuChoice);
bool inputContainsNumber(string &line);
bool inputContainsChar(string &line);

int main() {
    int menuChoice = 0;

    // Run the main menu
    while(menuChoice != 6) {
        fstream studentData(fileName);
        if(!studentData){
            cout << "\n\t| Error: Could not open file:" << fileName << " |\n";
            return 1;
        }
        cout << "\n\t| MAIN MENU |";
        cout << "\n(1) Add Student\n"
                "(2) Search Database\n"
                "(3) Edit Student\n"
                "(4) Merge file to DB\n"
                "(5) Get Student Reports\n"
                "(6) Exit Program\n";
        cin >> menuChoice;
        if(!isalpha(menuChoice)){
            cin.clear();
            cin.ignore(100,'\n');
        }
        mainMenu(studentData, menuChoice);
        studentData.close();
    }

    return 0;
}

void mainMenu(fstream &studentData, int &menuChoice){
    Student student; // class and var type

    if(isalpha(menuChoice)){
        cout << "\n\t| Error: Invalid Input. |\n";
    }
    switch(menuChoice){
        case 1:
            int studentBodySize;
            cout << "\nHow many students?: ";
            cin >> studentBodySize;

            if (!studentData.is_open()) {
                cout << "\n\t| Error opening file |\n";
                return;
            }

            for(int i = 0; i < studentBodySize; i++){
                cout << "\nEnter data for student " << (i + 1) << " :\n";
                student.newStudentData(); // Get input from user
            }
            break;
        case 2:
            // Call function to view the student data
            // of a specified id entered within the function
            student.viewStudentData(studentData);
            break;
        case 3:
            // Call function to edit student data
            student.editStudentData(studentData);
            break;
        case 4:
            // Call function to merge a user inputted file
            // to the database students.txt
            student.mergeStudentData(studentData);
            break;
        case 5:
            // Call function for filter reports
            student.collegeReadinessReport(studentData);
            break;
        case 6:
            // Exit the program when the user is done
            cout << "Thanks for using prep check.\n";
            exit(0);
        default:
            cout << "\n\t| Error: Invalid Input |\n";

    }
}

