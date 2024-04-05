#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cctype>
#include "PrepCheck.h"

using namespace std;

const int REQUIRED_ID_LENGTH = 9; // This is the required length of a students id
const int MIN_MATH_SCORE = 350, MIN_READING_SCORE = 350, MIN_WRITING_SCORE = 340; // Minimum scores to pass TSI tests

void Student::viewStudentData(fstream& studentData) const {
    /*
    * STUDENT DATA FORMAT
    * # is any number
    * ! is either 1 if a transfer student, 0 if not
    * // add math and reading attempts
    * A0#######,email@islander.tamucc.edu,LASTNAME,FIRSTNAME,!(transfer Status),(ATTEMPTED COLlEGE HOURS)###,##(math tsi attemps), ##(reading tsi attempts),(MATH)###,(READING)###, WRITING(###)
    */
    string studentId;

    // Input student ID with validation
    do {
        cout << "Enter Student ID:";
        cin >> studentId;
    } while (studentId.length() != REQUIRED_ID_LENGTH);

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

            // Parse temporary information from tokens
            string studentEmail = tokens[1],
                    lastName = tokens[2],
                    firstName = tokens[3];
            bool transferStatus = stoi(tokens[4]);
            int attemptedHours = stoi(tokens[5]),
                    mathAttempts = stoi(tokens[6]),
                    readingAttempts = stoi(tokens[7]),
                    mathScore = stoi(tokens[8]),
                    readingScore = stoi(tokens[9]),
                    writingScore = stoi(tokens[10]);

            // Print student information
            cout << "Student " << studentId << " found:" << "\n";
            cout << "\t|STUDENT DETAILS|\n";
            cout << "First Name         : " << firstName << "\n";
            cout << "Last Name          : " << lastName << "\n";
            cout << "Student Email      : " << studentEmail << "\n";
            cout << "Transfer           : " << (transferStatus ? "Yes" : "No") << "\n";
            if(transferStatus)
                cout << "Attempted Hours    : " << attemptedHours << "\n";
            cout << "\n\t|TSI ATTEMPTS|\n";
            cout << "Math Attempts      : " << mathAttempts << "\n";
            cout << "Reading Attempts   : " << readingAttempts << "\n";
            cout << "\n\t|TSI SCORES|\n";
            cout << "Writing Score      : " << writingScore << "\n";
            cout << "Reading Score      : " << readingScore << "\n";
            cout << "Math Score         : " << mathScore << "\n";
            cout << "\n\t|TSI CHECKLIST|\n";
            checkTsiStatus(mathScore, readingScore, writingScore);

            // Clear studentData for next run through
            studentData.clear();
            studentData.seekg(0, ios::beg);
            break; // Exit the loop after finding studentId
        }
    }

    // If no ID was found
    if (!found) {
        cout << "\n\t| Error: Student ID " << studentId << " not found.| \n";
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

void Student::newStudentData(){
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
    }while(contactInfo.studentId.length() < REQUIRED_ID_LENGTH || contactInfo.studentId.length() > REQUIRED_ID_LENGTH);
    // Get & validate names
    do{
        cout << "Last name: ";
        cin >> contactInfo.lastName;
        cout << "First Name: ";
        cin >> contactInfo.firstName;
        if(!inputContainsNumber(contactInfo.lastName) && !inputContainsNumber((contactInfo.firstName))) {
            validStrInput = true;
        } else
            cout << "\n\t| Error: Names cannot contain numbers. |\n";
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
            cout << "\n\t| Error: Invalid Input|\n";
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
    // save data
    fstream studentData("students.txt", std::ios::app);
    saveStudentData(studentData);
}


void Student::editStudentData(fstream& studentData){
    int fieldSelection = 0;
    int lineCounter = 0;
    string studentId;
    // Input student ID with validation
    do {
        cout << "Enter Student ID:";
        cin >> studentId;
    } while (studentId.length() != REQUIRED_ID_LENGTH);

    string line;
    bool found = false;

    // Get each line of studentData
    while (getline(studentData, line)) {
        stringstream ss(line);
        string token;
        vector<string> tokens;

        // Increment line count
        lineCounter++;

        // Tokenize each line of data
        while (getline(ss, token, ',')) {
            tokens.push_back(token);
        }

        // Check if the line contains requested studentId
        if (!tokens.empty() && tokens[0] == studentId) {
            found = true;

            // Parse information from tokens
            contactInfo.studentId = studentId;
            contactInfo.studentEmail = tokens[1];
            contactInfo.lastName = tokens[2];
            contactInfo.firstName = tokens[3];
            status.transferStatus = stoi(tokens[4]);
            attempts.attemptedCollegeHours = stoi(tokens[5]);
            attempts.tsiReadingAttempts = stoi(tokens[6]);
            attempts.tsiMathAttempts= stoi(tokens[7]);
            scores.tsiMathScore = stoi(tokens[8]);
            scores.tsiReadingScore = stoi(tokens[9]);
            scores.tsiWritingScore = stoi(tokens[10]);

            cout << "Found line " << lineCounter << "\n";
            // Print student information
            cout << "| Student " << studentId << " Found |" << "\n";
            cout << "1)  First Name        : " << contactInfo.firstName << "\n";
            cout << "2)  Last Name         : " << contactInfo.lastName << "\n";
            cout << "3)  Student Email     : " << contactInfo.studentEmail << "\n";
            cout << "4)  Transfer          : " << (status.transferStatus ? "Yes" : "No") << "\n";
            if (status.transferStatus) { cout << "5) Attempted Hours   : " << attempts.attemptedCollegeHours << "\n"; }
            cout << "6)  Writing Score     : " << scores.tsiWritingScore << "\n";
            cout << "7)  Reading Score     : " << scores.tsiReadingScore << "\n";
            cout << "8)  Math Score        : " << scores.tsiMathScore << "\n";
            cout << "9)  Reading Attempts  : " << attempts.tsiReadingAttempts << "\n";
            cout << "10) Math Attempts     : " << attempts.tsiMathAttempts << "\n";
            cout << "|       TSI Status        |\n";
            // Check the score eligibility
            checkTsiStatus(scores.tsiMathScore, scores.tsiReadingScore, scores.tsiWritingScore);
            cout << "11) Exit              :\n";
            cout << "Enter a field to edit :\n";

            // Clear studentData for next run through
            studentData.clear();
            studentData.seekg(0, ios::beg);
            break; // Exit the loop after finding studentId
        }
    }
    // Clear input buffer
    cin.clear();
    cin.ignore(100, '\n');

    // Ask user which field theyd like to edit
    cin >> fieldSelection;

    switch (fieldSelection) {
        case 1:
            cout << "Enter a new first name: \n";
            cin >> contactInfo.firstName;
            break;
        case 2:
            cout << "Enter a new last name: \n";
            cin >> contactInfo.lastName;
            break;
        case 3:
            cout << "Enter a new email: \n";
            cin >> contactInfo.studentEmail;
            break;
        case 4:
            cout << "Change Transfer Status (1 or 0): \n";
            cin >> status.transferStatus;
            break;
        case 5:
            cout << "Enter attempted hours:\n";
            cin >> attempts.attemptedCollegeHours;
            break;
        case 6:
            cout << "Change writing score: \n";
            cin >> scores.tsiWritingScore;
            break;
        case 7:
            cout << "Change reading score: \n";
            cin >> scores.tsiReadingScore;
            break;
        case 8:
            cout << "Change math score: \n";
            cin >> scores.tsiReadingScore;
            break;
        case 9:
            cout << "Change reading attempts: \n";
            cin >> attempts.tsiReadingAttempts;
            break;
        case 10:
            cout << "Change math attempts: \n";
            cin >> attempts.tsiMathAttempts;
            break;
        case 12:
            cout << "\n\t| Exiting... |\n";
            break;
        default:
            cout << "\n\t| ERROR: Invalid input. |\n";
    }

    // Copy to new file
    ofstream tempFile("temp.txt");

    string tempLine;
    int lineCounter2 = 0;
    while(studentData >> tempLine){
        lineCounter2++;
        if(lineCounter2 == lineCounter){
            tempFile << contactInfo.studentId << ','
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
        } else
            tempFile << tempLine << "\n";
    }
    // Close the file, delete the original, and rename the temp to the original.
    cout << "\n\t| SAVING FILE |\n";
    tempFile.close();
    studentData.close();
    remove("students.txt");
    rename("temp.txt", "students.txt");

    // If no ID was found
    if (!found) {
        cout << "\n\t| Error: Student ID " << studentId << " not found. |\n";
    }

}

void Student::mergeStudentData(fstream &studentData) {
    string userFileInput;

    do{
    cout << "\nEnter file to merge: ";
    cin >> userFileInput;
    fstream validateFile(userFileInput);

    if(!validateFile.is_open()){
        cout << "\n\t| Error: Couldnt open file, reenter filename and try again. |\n";
        continue;
    }else
        break;
    }while(true);

    vector<string> inputFiles = {"students.txt", userFileInput};


    ofstream mergeFile("mergedtemp.txt");
    if (!mergeFile.is_open()) {
        cout << "\n\t | Error: Failed to open mergedtemp.txt |\n";
        return;
    }

    for (const auto &currentFile: inputFiles) {
        ifstream inputFileStream(currentFile);

        string line;
        while (getline(inputFileStream, line)) {
            mergeFile << line << "\n";
        }
        inputFileStream.close();
    }
    mergeFile.close();
    studentData.close();
    // Remove the original students.txt file
    if (remove("students.txt") != 0) {
        cout << "\n\t| Error: Couldn't delete original file. |\n";
    }

    // Rename mergedtemp.txt to students.txt
    if (rename("mergedtemp.txt", "students.txt") != 0) {
        cout << "\n\t| Error: Couldn't rename file. |\n";
    }

    cout << "\n\t | Files merged successfully. |\n";
}

void Student::checkTsiStatus(int mathScore, int readingScore, int writingScore) const{
    cout << "Math    : " << (mathScore >= MIN_MATH_SCORE ? "Ready" : "Not ready") << "\n";
    cout << "Reading : " << (readingScore >= MIN_READING_SCORE ? "Ready" : "Not ready") << "\n";
    cout << "Writing : " << (writingScore >= MIN_WRITING_SCORE ? "Ready" : "Not ready") << "\n\n";
}

void Student::saveStudentData(fstream& studentData) const {
    if (studentData.is_open()) {
        studentData << contactInfo.studentId << ','
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
    } else {
        cout << "\n\t| Error: Could not write to file! |\n";
    }
}