#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cctype>

using namespace std;

class Student {
public:
    const int requiredLength = 9; // This is the required length of a students id
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
        studentId = " ";
        do{
            cout << "Enter Student ID:";
            cin >> studentId;
        }while(studentId.length() < requiredLength || studentId.length() > requiredLength);
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
                // Clear student data for next run through
                studentData.clear();
                studentData.seekg(0, ios::beg);
                break;
            }
        }
        // If no id was found
        if (!found) {
            cout << "Error: student Id" << studentId << "not found." << "\n";
        }
    }

    void checkTsiStatus(int mathScore, int readingScore, int writingScore){
        const int minMathScore = 350, minReadingScore = 351, minWritingScore = 340;
        cout << "Math    : " << (mathScore >= minMathScore ? "Ready" : "Not ready") << "\n";
        cout << "Reading : " << (readingScore >= minReadingScore ? "Ready" : "Not ready") << "\n";
        cout << "Writing : " << (writingScore >= minWritingScore ? "Ready" : "Not ready") << "\n\n";
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
            cin >> studentId;
        }while(studentId.length() < requiredLength || studentId.length() > requiredLength);
        // Get & validate names
        do{
            cout << "Last name: ";
            cin >> lastName;
            cout << "First Name: ";
            cin >> firstName;
            if(!inputContainsNumber(lastName) && !inputContainsNumber((firstName))) {
                validStrInput = true;
            } else
                cout << "\nError: Names cannot contain numbers.\n";
        }while(!validStrInput);
        // Doesnt need validation due to variance
        cout << "Student email: ";
        cin >> studentEmail;

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
            transferStatus = true;
            do {
                cout << "Attempted College Credits: ";
                cin >> attemptedHoursStr;
            }while(inputContainsChar(attemptedHoursStr));
            // Convert str to int
            attemptedCollegeHours = stoi(attemptedHoursStr);
        } else {
            transferStatus = false;
            attemptedCollegeHours = 0;
        }
        // Get & validate tsi Attempts
        do {
            cout << "Math Tsi Attempts: ";
            cin >> mathAttemptsStr;
            cout << "Reading Tsi Attempts: ";
            cin >> readingAttemptsStr;
        }while(inputContainsChar(mathAttemptsStr) && inputContainsChar(readingAttemptsStr));
        // Convert string to int after validation
        tsiMathAttempts = stoi(mathAttemptsStr);
        tsiReadingAttempts = stoi(readingAttemptsStr);
        // If the attempts is greater than 0, ask for the highest score
        if(tsiMathAttempts > 0){
            do {
                cout << "Enter the highest attempted math score: ";
                cin >> mathScoreStr;
            }while(inputContainsChar(mathScoreStr));
        } else
            tsiMathScore = 0;
        if(tsiReadingAttempts > 0){
            do {
                cout << "Enter the highest attempted reading score: ";
                cin >> tsiReadingScore;
                cout << "Enter the highest attempted writing score: ";
                cin >> tsiWritingScore;
            }while(inputContainsChar(readingScoreStr) && inputContainsChar(writingScoreStr));
        } else {
            tsiReadingScore = 0;
            tsiWritingScore = 0;
        }
    }

    void saveStudentData(fstream& file) const{
        file <<  studentId << ',' << studentEmail << ',' << lastName << ',' << firstName << ',' << transferStatus
             << ',' << attemptedCollegeHours << ',' << tsiMathAttempts << ',' << tsiReadingAttempts
             << ',' << tsiMathScore << ',' << tsiReadingScore << ',' << tsiWritingScore << "\n";
        file.flush();
    }

    /*void newStudentDataFromFile(string& fileName){
        vector<Student> students;
        ifstream file(fileName);

        if(file.is_open()){
            string line;
            while(getLine(file, line)) {
                istringstream ss(line);
                string first, last, id, email;

                getLine(ss, first, ' , ');
                getLine(ss, last, ' , ');
                getLine(ss, id, ' , ');
                getLine(ss, email, ' , ');

                students.emplace_back(first, last, id, email);
            }
            file.close();
        } else {
            cout<<"Unable to open file: "<<fileName<<endl;
        }
    }*/

    // TODO INPUT VALIDATION FOR EVERY INPUT (done, but just need menuchoice)
    // TODO add function to merge a new student database file to students.txt
    // TODO add function to edit student data
    // TODO void mergeNewStudentData, this will append new lines and not overwrite the file
};

void mainMenu(fstream& studentData, int &menuChoice){
    Student student; // class and var type
    // TODO Input validation for menuChoice
    cout << "\n(1) Add to\n(2) Search database\n(3) Edit User\n(4) Merge file to DB\n(5) Exit Program\n";
    cin >> menuChoice;

    switch(menuChoice){
        case 1:
            int studentBodySize;
            cout << "\nHow many students?: ";
            cin >> studentBodySize;

            if (!studentData.is_open()) {
                cout << "Error opening file\n";
                return;
            }

            for(int i = 0; i < studentBodySize; i++){
                cout << "\nEnter data for student " << (i + 1) << " :\n";
                student.newStudentData(); // Get input from user
                student.saveStudentData(studentData); // Save input to students.txt
            }
            break;
        case 2:
            // Call function to view the student data
            // of a specified id entered within the function
            student.viewStudentData(studentData);
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

    mainMenu(studentData, menuChoice);

    studentData.close();

    return 0;
}
