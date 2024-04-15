#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include "PrepCheck.h"

using namespace std;

void mainMenu(fstream &studentData, int &menuChoice);

// TODO INPUT VALIDATION for tsi attempts in new student function
// TODO INPUT VALIDATION FOR COMMMASSS!!!! entering a , will break the program during search
//  because it cant decipher which part is supposed to be a delimiter
// TODO Be able to pull a report for all students who are not college ready
// TODO be able to pull a report for ftic students who have violated rules for not being college ready, (are not college ready within the first 24 attempted hours
// TODO and for transfer students who are not ready in the first 30 hours

// CONSTS
const int REQUIRED_ID_LENGTH = 9; // This is the required length of a students id
const char fileName[] = "students.txt";
const int MIN_MATH_SCORE = 350, MIN_READING_SCORE = 350, MIN_WRITING_SCORE = 340;

// Prototypes
bool inputContainsNumber(string &line);
bool inputContainsChar(string &line);

int main() {
    int menuChoice = 0;

    // Run the main menu
    while(menuChoice != 5) {
        fstream studentData(fileName);
        if(!studentData){
            cout << "\n\t| Error: Could not open file: " << fileName << " |\n";
            return 1;
        }
        cout << "\n\t| MAIN MENU |";
        cout << "\n(1) Add to\n(2) Search database\n(3) Edit User\n(4) Merge file to DB"
                "\n(5) Filter by college readiness\n(6) Exit Program\n";
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
            // Call function to filter user inputted file by college readiness
            student.collegeReadinessFilter(studentData);
            break;
        case 6:
            // Exit the program when the user is done
            cout << "Thanks for using prep check.\n";
            exit(0);
        default:
            cout << "\n\t| Error: Invalid Input |\n";

    }
}

