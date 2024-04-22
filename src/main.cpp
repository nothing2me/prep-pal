#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include "PrepCheck.h"

using namespace std;


// Prototypes
void mainMenu(fstream &studentData, int &menuChoice, string &fileName);
void changeFile(string &fileName);
bool inputContainsNumber(string &line);
bool inputContainsChar(string &line);

int main() {
    int menuChoice = 0;

    string fileName = "";
    changeFile(fileName);

    cout << "   | Welcome to PrepPal! |";

    // Run the main menu
    while(menuChoice != 7) {
        fstream studentData(fileName);
        if(!studentData) {
            cout << "\n| Error: Could not open file:" << fileName << " |\n";
            changeFile(fileName);
            continue;
        }
        cout << "\n\t| MAIN MENU |";
        cout << "\n(1) Add Student\n"
                "(2) Search Database\n"
                "(3) Edit Student\n"
                "(4) Merge File to DB\n"
                "(5) Get Student Reports\n"
                "(6) Change File To Handle\n"
                "(7) Exit Program\n";
        cin >> menuChoice;
        if(!isalpha(menuChoice)){
            cin.clear();
            cin.ignore(100,'\n');
        }
        mainMenu(studentData, menuChoice, fileName);
        studentData.close();
    }

    return 0;
}

void mainMenu(fstream &studentData, int &menuChoice, string &fileName){
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
            cout << "\n";
            break;
        case 3:
            // Call function to edit student data
            student.editStudentData(studentData);
            cout << "\n";
            break;
        case 4:
            // Call function to merge a user inputted file
            // to the database students.txt
            student.mergeStudentData(studentData);
            cout << "\n";
            break;
        case 5:
            // Call function for filter reports
            student.collegeReadinessReport(studentData);
            cout << "\n";
            break;
        case 6:
            // Call function to change file being handled
            changeFile(fileName);
            cout << "\n";
            break;
        case 7:
            // Exit the program when the user is done
            cout << "Thanks for using prep check.\n";
            exit(0);
        default:
            cout << "\n\t| Error: Invalid Input |\n";

    }
}



