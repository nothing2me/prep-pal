#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Student {
public:
    // Maybe put these in private or a data structure
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


    // Construct data
    Student(const string& _studentId = "", const string& _lastName = "",
            const string& _firstName = "", const string& _studentEmail = "",
            const int& _tsiMathScore = 0, const int& _tsiWritingScore = 0,
            const int& _tsiReadingScore = 0, const int& _attemptedCollegeHours = 0,
            const int& _tsiMathAttempts = 0, const int& _tsiReadingAttempts = 0,
            const bool& _transferStatus = false)
            : studentId(_studentId), lastName(_lastName),
              firstName(_firstName), studentEmail(_studentEmail),
              tsiMathScore(_tsiMathScore), tsiWritingScore(_tsiWritingScore),
              tsiReadingScore(_tsiReadingScore), tsiMathAttempts(_tsiMathAttempts),
              tsiReadingAttempts(_tsiReadingAttempts),transferStatus(_transferStatus),
              attemptedCollegeHours(_attemptedCollegeHours){
    }

    void viewStudentData(fstream& studentData){
        /*
         * STUDENT DATA FORMAT
         * # is any number
         * ! is either 1 if a transfer student, 0 if not
         * // add math and reading attempts
         * A0#######,email@islander.tamucc.edu,LASTNAME,FIRSTNAME,!(transfer Status),(ATTEMPTED COLlEGE HOURS)###,##(math tsi attemps), ##(reading tsi attempts),(MATH)###,(READING)###, WRITING(###)
         */
        cout << "Enter Student ID:";
        cin >> studentId;
        string searchId;
        bool found = false;
        // Read each line in students.txt
        while (getline(studentData, searchId)) {
            size_t delimPos = searchId.find(studentId); // Check if the line contains the student ID
            // Condition if a matching student id found
            if (delimPos != string::npos) {
                found = true;

                // Get delimiter position of each variable in the format
                // Need this to parse data.
                size_t writingPosition = searchId.find_last_of(','),
                        readingPosition = searchId.find_last_of(',', writingPosition - 1),
                        mathPosition = searchId.find_last_of(',', readingPosition - 1),
                        readingAttemptsPosition = searchId.find_last_of(',', mathPosition - 1),
                        mathAttemptsPosition = searchId.find_last_of(',', readingAttemptsPosition - 1),
                        attemptedCollegeHoursPosition = searchId.find_last_of(',', mathAttemptsPosition - 1),
                        transferStatusPosition = searchId.find_last_of(',', attemptedCollegeHoursPosition - 1),
                        firstNamePosition = searchId.find_last_of(',', transferStatusPosition - 1),
                        lastNamePosition = searchId.find_last_of(',', firstNamePosition - 1),
                        studentEmailPosition = searchId.find_last_of(',', lastNamePosition - 1);

                // Use positions to parse each element into strings
                string writingScoreStr_conversion = searchId.substr(writingPosition + 1),
                        readingScoreStr_conversion = searchId.substr(readingPosition + 1, writingPosition - readingPosition - 1),
                        mathScoreStr_conversion = searchId.substr(mathPosition + 1, readingPosition - mathPosition - 1),
                        readingAttemptsStr_conversion = searchId.substr(readingAttemptsPosition + 1, mathPosition - readingAttemptsPosition - 1),
                        mathAttemptsStr_conversion = searchId.substr(mathAttemptsPosition + 1, readingAttemptsPosition - mathAttemptsPosition - 1),
                        attemptedCollegeHoursStr_conversion = searchId.substr(attemptedCollegeHoursPosition + 1, mathAttemptsPosition - attemptedCollegeHoursPosition - 1),
                        transferStatusStr_conversion = searchId.substr(transferStatusPosition + 1, attemptedCollegeHoursPosition - transferStatusPosition - 1),
                        firstNameStr_conversion = searchId.substr(firstNamePosition + 1, transferStatusPosition - firstNamePosition - 1),
                        lastNameStr_conversion = searchId.substr(lastNamePosition + 1, firstNamePosition - lastNamePosition - 1),
                        studentEmailStr_conversion = searchId.substr(studentEmailPosition + 1, lastNamePosition - studentEmailPosition - 1);


                // Convert string to integer for needed comparisions
                int parsed_WritingScore = stoi(writingScoreStr_conversion),
                        parsed_ReadingScore = stoi(readingScoreStr_conversion),
                        parsed_MathScore = stoi(mathScoreStr_conversion),
                        parsed_ReadingAttempts = stoi(readingAttemptsStr_conversion),
                        parsed_MathAttempts = stoi(mathAttemptsStr_conversion),
                        parsed_transferStatus = stoi(transferStatusStr_conversion);

                // Print the transferstatus in terms other than 1 and 0
                string transferStatusYN;
                if(parsed_transferStatus == 1){
                    transferStatusYN = "Yes";
                } else
                    transferStatusYN = "No";

                // Output data and end loop
                cout << "Student " << studentId << " found: " << "\n";
                cout << "First Name         : " << firstNameStr_conversion << "\n";
                cout << "Last Name          : " << lastNameStr_conversion << "\n";
                cout << "Student Email      : " << studentEmailStr_conversion << "\n";
                cout << "Transfer           : " << transferStatusYN           << "\n";
                cout << "Writing Score      : " << parsed_WritingScore        << "\n";
                cout << "Reading Score      : " << parsed_ReadingScore        << "\n";
                cout << "Math Score         : " << parsed_MathScore           << "\n";
                cout << "Reading Attempts   : " << parsed_ReadingAttempts     << "\n";
                cout << "Math Attempts      : " << parsed_MathAttempts        << "\n";
                cout << "TSI Status:\n";
                checkTsiStatus(parsed_MathScore, parsed_ReadingScore, parsed_WritingScore);
                break;
            }
        }
        // If no id was found
        if (!found) {
            cout << "Error, student Id not found." << "\n";
        }
    }

    void checkTsiStatus(int mathScore, int readingScore, int writingScore){
        const int minMathScore = 350, minReadingScore = 351, minWritingScore = 340;
        cout << "Math    : " << (mathScore >= minMathScore ? "Ready" : "Not ready") << "\n";
        cout << "Reading : " << (readingScore >= minReadingScore ? "Ready" : "Not ready") << "\n";
        cout << "Writing : " << (writingScore >= minWritingScore ? "Ready" : "Not ready") << "\n";
    }

    void newStudentData(){
        cout << "Enter ID: ";
        cin >> studentId;
        cout << "Last name: ";
        cin >> lastName;
        cout << "First Name: ";
        cin >> firstName;
        cout << "Student email: ";
        cin >> studentEmail;
        cout << "Transfer status (1 for transfer, 0 for new student): ";
        cin >> transferStatus;
        if(transferStatus == 1){
            cout << "Attempted College Credits: ";
            cin >> attemptedCollegeHours;
        } else
            attemptedCollegeHours = 0;
        cout << "Math Tsi Attempts: ";
        cin >> tsiMathAttempts;
        cout << "Reading Tsi Attempts: ";
        cin >> tsiReadingAttempts;
        if(tsiMathAttempts > 0){
            cout << "Enter the highest attempted score: ";
            cin >> tsiMathScore;
        } else
            tsiMathScore = 0;
        if(tsiReadingAttempts > 0){
            cout << "Enter the highest attempted score: ";
            cin >> tsiReadingScore;
            cout << "Enter the highest attempted score: ";
            cin >> tsiWritingScore;
        } else {
            tsiReadingScore = 0;
            tsiWritingScore = 0;
        }
    }

    void saveStudentData(fstream& file) const{
        file <<  studentId << ',' << studentEmail << ',' << lastName << ',' << firstName << ',' << transferStatus
             << ',' << attemptedCollegeHours << ',' << tsiMathAttempts << ',' << tsiReadingAttempts
             << ',' << tsiMathScore << ',' << tsiReadingScore << ',' << tsiWritingScore << "\n";
    }

    // TODO add function to merge a new student database file to students.txt
    // TODO add function to edit student data
    // TODO void mergeNewStudentData, this will append new lines and not overwrite the file
};

void mainMenu(fstream& studentData){
    int menuChoice;
    Student student; // class and var type

    cout << "(1) Add to\n(2) search database\n";
    cin >> menuChoice;
    switch(menuChoice){
        case 1:
            int studentBodySize;
            cout << "\nHow many students?: ";
            cin >> studentBodySize;

            for(int i = 0; i < studentBodySize; i++){
                cout << "\nEnter data for student " << (i + 1) << " :\n";
                student.newStudentData(); // Get input from user
                student.saveStudentData(studentData); // Save input to students.txt
            }
            break;
        case 2:
            student.viewStudentData(studentData);
            break;
        default:
            cout << "error";
    }
}

int main() {
    const char fileName[] = "students.txt";
    fstream studentData(fileName);

    if(!studentData){
        cout << "Error opening file\n";
        return 1;
    }

    mainMenu(studentData);

    studentData.close();
    return 0;
}
