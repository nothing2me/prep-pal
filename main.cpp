#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cctype>

using namespace std;

class Student {

private:
    struct ContactInfo {
        string studentId,
                lastName,
                firstName,
                studentEmail;
    };
    struct Scores {
        int tsiMathScore,
                tsiWritingScore,
                tsiReadingScore;
    };
    struct Attempts {
        int tsiMathAttempts,
                tsiReadingAttempts,
                attemptedCollegeHours;
    };
    struct Status {
        bool transferStatus;
    };
    ContactInfo contactInfo;
    Scores scores;
    Attempts attempts;
    Status status;
public:
    const int requiredLength = 9; // This is the required length of a students id
    // Maybe put these in private or a data structure
    /*
    string studentId,
            lastName,
            firstName,
            studentEmail;
    int tsiMathScore,
            tsiWritingScore,
            tsiReadingScore,
            attemptedCollegeHours,
            tsiMathAttempts,
            tsiReadingAttempts;
    // 1 for transfer 0 for FTIC, need to add for parse
    bool transferStatus;
*/
    // Construct data
    Student(const string &_studentId = "",
            const string &_lastName = "", const string &_firstName = "",
            const string &_studentEmail = "",
            const int &_tsiMathScore = 0, const int &_tsiWritingScore = 0,
            const int &_tsiReadingScore = 0, const int &_attemptedCollegeHours = 0,
            const int &_tsiMathAttempts = 0, const int &_tsiReadingAttempts = 0,
            const bool &_transferStatus = false)
            : scores({_tsiMathScore, _tsiWritingScore, _tsiReadingScore}), // Initialize Scores struct
              attempts({_tsiMathAttempts, _tsiReadingAttempts}) { // Initialize Attempts struct
    }


    void checkTsiStatus(int mathScore, int readingScore, int writingScore){
        const int minMathScore = 350, minReadingScore = 351, minWritingScore = 340;
        cout << "Math    : " << (mathScore >= minMathScore ? "Ready" : "Not ready") << "\n";
        cout << "Reading : " << (readingScore >= minReadingScore ? "Ready" : "Not ready") << "\n";
        cout << "Writing : " << (writingScore >= minWritingScore ? "Ready" : "Not ready") << "\n\n";
    }

    void viewStudentData(fstream& studentData) {
        /*
       * STUDENT DATA FORMAT
       * # is any number
       * ! is either 1 if a transfer student, 0 if not
       * // add math and reading attempts
       * A0#######,email@islander.tamucc.edu,LASTNAME,FIRSTNAME,!(transfer Status),(ATTEMPTED COLlEGE HOURS)###,##(math tsi attemps), ##(reading tsi attempts),(MATH)###,(READING)###, WRITING(###)
       */
        string studentId;
        const int requiredLength = 9; // Assuming the required length of student ID

        // Input student ID with validation
        do {
            cout << "Enter Student ID:";
            cin >> studentId;
        } while (studentId.length() != requiredLength);

        string line;
        bool found = false;

        // Get each line of studentData
        while (getline(studentData, line)) {
            stringstream ss(line);
            string token;
            vector<string> tokens;

            // Tokenize each line of data
            while (getline(ss, token, ',')) {
                tokens.push_back(token);
            }

            // Check if the line contains requested studentId
            if (tokens.size() > 0 && tokens[0] == studentId) {
                found = true;

                // Parse information from tokens
                string studentEmail = tokens[1];
                string lastName = tokens[2];
                string firstName = tokens[3];
                bool transferStatus = stoi(tokens[4]);
                int attemptedHours = stoi(tokens[5]);
                int readingAttempts = stoi(tokens[6]);
                int mathScore = stoi(tokens[7]);
                int readingScore = stoi(tokens[8]);
                int writingScore = stoi(tokens[9]);
                int mathAttempts = stoi(tokens[10]);

                // Print student information
                cout << "Student " << studentId << " found:" << "\n";
                cout << "First Name         : " << firstName << "\n";
                cout << "Last Name          : " << lastName << "\n";
                cout << "Student Email      : " << studentEmail << "\n";
                cout << "Transfer           : " << (transferStatus ? "Yes" : "No") << "\n";
                if(transferStatus)
                    cout << "Attempted Hours    : " << attemptedHours << "\n";
                cout << "Writing Score      : " << writingScore << "\n";
                cout << "Reading Score      : " << readingScore << "\n";
                cout << "Math Score         : " << mathScore << "\n";
                cout << "Reading Attempts   : " << readingAttempts << "\n";
                cout << "Math Attempts      : " << mathAttempts << "\n";
                cout << "TSI Status:" << "\n";
                checkTsiStatus(mathScore, readingScore, writingScore);

                // Clear studentData for next run through
                studentData.clear();
                studentData.seekg(0, ios::beg);
                break; // Exit the loop after finding studentId
            }
        }

        // If no ID was found
        if (!found) {
            cout << "Error: Student ID " << studentId << " not found." << "\n";
        }
    }


    bool inputContainsNumber(string &line){
        for (char i : line){
            if(isdigit(i)){
                return true;
            }
        }
        return false;
    }

    bool inputContainsChar(string &line){
        for(char i : line){
            if(!isdigit(i)){
                return true;
            }
        }
        return false;
    }
// Heres where it gets bad.
    void newStudentData(){
        // Lots of do while loops here for input validation,
        // some inputs only accept chars, others, such as scores
        // & attempts only accept int
        bool validStrInput = false;
        string mathAttemptsStr,
                readingAttemptsStr,
                mathScoreStr,
                readingScoreStr,
                writingScoreStr,
                attemptedHoursStr;
        // Get & validate id
        do {
            cout << "Enter ID: ";
            cin >> contactInfo.studentId;
        }while(contactInfo.studentId.length() < requiredLength || contactInfo.studentId.length() > requiredLength);
        // Get & validate names
        do{
            cout << "Last name: ";
            cin >> contactInfo.lastName;
            cout << "First Name: ";
            cin >> contactInfo.firstName;
            if(!inputContainsNumber(contactInfo.lastName) && !inputContainsNumber((contactInfo.firstName))) {
                validStrInput = true;
            } else
                cout << "\nError: Names cannot contain numbers.\n";
        }while(!validStrInput);
        // Doesnt need validation due to variance
        cout << "Student email: ";
        cin >> contactInfo.studentEmail;

        // Input validation for transferStatus, I use an int and then use the result
        // of that int to set transferStatus
        int transferInput;
        string tempInput;
        do {
            cout << "Transfer status (1 for transfer, 0 for FTIC): ";
            cin >> tempInput;
            if(!inputContainsChar(tempInput)){
                stringstream ss(tempInput);
                ss >> transferInput;
            } else
                cout << "\nError: Invalid Input\n";
        }while(inputContainsChar(tempInput) || transferInput > 1 || transferInput < 0);
        if (transferInput == 1) {
            status.transferStatus = true;
            do {
                cout << "Attempted College Credits: ";
                cin >> attemptedHoursStr;
            }while(inputContainsChar(attemptedHoursStr));
            // Convert str to int
            attempts.attemptedCollegeHours = stoi(attemptedHoursStr);
        } else {
            status.transferStatus = false;
            attempts.attemptedCollegeHours = 0;
        }
        // Get & validate tsi Attempts
        do {
            cout << "Math Tsi Attempts: ";
            cin >> mathAttemptsStr;
            cout << "Reading Tsi Attempts: ";
            cin >> readingAttemptsStr;
        }while(inputContainsChar(mathAttemptsStr) && inputContainsChar(readingAttemptsStr));
        // Convert string to int after validation
        attempts.tsiMathAttempts = stoi(mathAttemptsStr);
        attempts.tsiReadingAttempts = stoi(readingAttemptsStr);
        // If the attempts is greater than 0, ask for the highest score
        if(attempts.tsiMathAttempts > 0){
            do {
                cout << "Enter the highest attempted math score: ";
                cin >> mathScoreStr;
            }while(inputContainsChar(mathScoreStr));
        } else
            scores.tsiMathScore = 0;
        if(attempts.tsiReadingAttempts > 0){
            do {
                cout << "Enter the highest attempted reading score: ";
                cin >> scores.tsiReadingScore;
                cout << "Enter the highest attempted writing score: ";
                cin >> scores.tsiWritingScore;
            }while(inputContainsChar(readingScoreStr) && inputContainsChar(writingScoreStr));
        } else {
            scores.tsiReadingScore = 0;
            scores.tsiWritingScore = 0;
        }
    }

    void saveStudentData(const std::string& filename) {
        ofstream file(filename, std::ios::app); // Open in append mode
        if (file.is_open()) {
            file << contactInfo.studentId << ','
                 << contactInfo.studentEmail << ','
                 << contactInfo.lastName << ','
                 << contactInfo.firstName << ','
                 << status.transferStatus << ','
                 << attempts.attemptedCollegeHours << ','
                 << attempts.tsiMathAttempts << ','
                 << attempts.tsiReadingAttempts << ','
                 << scores.tsiMathScore << ','
                 << scores.tsiReadingScore << ','
                 << scores.tsiWritingScore << '\n'; // Use '\n' for correct newline
            file.close(); // Close the file
        } else {
            cout << "Error writing to file: " << filename << '\n';
        }
    }


    // TODO INPUT VALIDATION FOR EVERY INPUT (done, but just need menuchoice)
    // TODO add function to merge a new student database file to students.txt
    // TODO add function to edit student data
    // TODO void mergeNewStudentData, this will append new lines and not overwrite the file
};

void mainMenu(const string& fileName, int &menuChoice){
    Student student; // class and var type
    // TODO Input validation for menuChoice
    cout << "\n(1) Add to\n(2) Search database\n(3) Edit User\n(4) Merge file to DB\n(5) Exit Program\n";

    cin >> menuChoice;
    fstream studentFile(fileName);
    switch(menuChoice){
        case 1:
            int studentBodySize;
            cout << "\nHow many students?: ";
            cin >> studentBodySize;

            if (!studentFile.is_open()) {
                cout << "Error opening file\n";
                return;
            }

            for(int i = 0; i < studentBodySize; i++){
                cout << "\nEnter data for student " << (i + 1) << " :\n";
                student.newStudentData(); // Get input from user
                student.saveStudentData(fileName); // Save input to students.txt
            }
            break;
        case 2:
            // Call function to view the student data
            // of a specified id entered within the function
            student.viewStudentData(studentFile);
            break;
        case 3:
            // Call function to edit student data here
            // student.editStudentData();
            break;
        case 4:
            // Call function to merge a user inputted file
            // to the database students.txt
            // student.mergeFileToDatabase();
            break;
        case 5:
            // Exit the program when the user is done
            cout << "Thanks for using prep check.\n";
            exit(0);
        default:
            cout << "error";
    }
}

int main() {
    const char fileName[] = "students.txt";
    int menuChoice;
    fstream studentData(fileName);

    if(!studentData){
        cout << "Error opening file\n";
        return 1;
    }
    while(menuChoice != 5) {
        mainMenu(fileName, menuChoice);
    }
    studentData.close();

    return 0;
}
