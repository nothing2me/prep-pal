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
    * A0#######,email@islander.tamucc.edu,LASTNAME,FIRSTNAME,!(transfer Status),
    * (ATTEMPTED COLlEGE HOURS)###,##(math tsi attemps), ##(reading tsi attempts),
    * (MATH)###,(READING)###, WRITING(###)
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
                    writingScore = stoi(tokens[10]),
                    violations = stoi(tokens[11]);

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
            cout << "\t|VIOLATIONS|\n";
            if(!transferStatus) {
                cout << "FTIC Violations : " << violations << "\n";
            } else
                cout << "Transfer Violations : " << violations << "\n";

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
        if(!isdigit(i) && i != ','){
            return true;
        }
    }
    return false;
}

bool inputContainsComma(string &line) {
    return line.find(',') != string::npos;
}

bool isCharAndComma( string& line) {
    return inputContainsChar(line) || inputContainsComma(line);
}


void Student::newStudentData() {
    bool validStrInput = false;
    string mathAttemptsStr, readingAttemptsStr, mathScoreStr, readingScoreStr, writingScoreStr, attemptedHoursStr;

    // Validate student ID
    do {
        cout << "Enter ID: ";
        cin >> contactInfo.studentId;

        if (inputContainsComma(contactInfo.studentId)) {
            cout << "\n\t| Error: IDs cannot contain commas. |\n";
        } else if (contactInfo.studentId.length() != REQUIRED_ID_LENGTH) {
            cout << "\n\t| Error: ID length is invalid. |\n";
        } else {
            validStrInput = true;
        }
    } while (!validStrInput);

    // Validate last and first names
    validStrInput = false;
    do {
        cout << "Last name: ";
        cin >> contactInfo.lastName;
        cout << "First Name: ";
        cin >> contactInfo.firstName;

        if (inputContainsNumber(contactInfo.lastName) || inputContainsNumber(contactInfo.firstName)) {
            cout << "\n\t| Error: Names cannot contain numbers. |\n";
        } else if (inputContainsComma(contactInfo.lastName) || inputContainsComma(contactInfo.firstName)) {
            cout << "\n\t| Error: Names cannot contain commas. |\n";
        } else {
            validStrInput = true;
        }
    } while (!validStrInput);

    // Validate student email
    validStrInput = false;
    do {
        cout << "Student email: ";
        cin >> contactInfo.studentEmail;

        if (inputContainsComma(contactInfo.studentEmail)) {
            cout << "\n\t| Error: Emails cannot contain commas. |\n";
        } else {
            validStrInput = true;
        }
    } while (!validStrInput);

    // Validate transfer status
    int transferInput;
    string tempInput;
    do {
        cout << "Transfer status (1 for transfer, 0 for FTIC): ";
        cin >> tempInput;

        if (!inputContainsChar(tempInput) && !inputContainsComma(tempInput)) {
            stringstream ss(tempInput);
            ss >> transferInput;
            if (transferInput >= 0 && transferInput <= 1) {
                // Input is valid
                break;
            } else {
                cout << "\n\t| Error: Input must be either 0 or 1 |\n";
            }
        } else {
            cout << "\n\t| Error: Invalid Input|\n";
        }
    } while (true);

    if (transferInput == 1) {
        status.transferStatus = true;
        do {
            cout << "Attempted College Credits: ";
            cin >> attemptedHoursStr;
            if (inputContainsChar(attemptedHoursStr) || inputContainsComma(attemptedHoursStr)) {
                cout << "\n\t| Error: Invalid Input. Please enter a number without commas. |\n";
            } else {
                attempts.attemptedCollegeHours = stoi(attemptedHoursStr);
                break;
            }
        } while(true);
    } else {
        status.transferStatus = false;
        attempts.attemptedCollegeHours = 0;
    }

    // Validate academic violations
    validStrInput = false;
    do {
        cout << "Academic Violations: ";
        cin >> status.violations;
        string violations = to_string(status.violations);
        if (isCharAndComma(violations)) {
            cout << "\n\t| Error: Violations cannot contain characters or commas. |\n";
            validStrInput = false;
        } else {
            validStrInput = true;
        }
    } while (!validStrInput);

    do {
        cout << "Math Tsi Attempts: ";
        cin >> mathAttemptsStr;
        cout << "Reading Tsi Attempts: ";
        cin >> readingAttemptsStr;
        if((inputContainsChar(mathAttemptsStr) || inputContainsComma(mathAttemptsStr)) ||
             (inputContainsChar(readingAttemptsStr) || inputContainsComma(readingAttemptsStr))) {
            validStrInput = false;
            cout << "\n\t| Error: Scores cannot contain commas or characters. |\n";
             } else {
                 validStrInput = true;
             }
    } while (!validStrInput);
    attempts.tsiMathAttempts = stoi(mathAttemptsStr);
    attempts.tsiReadingAttempts = stoi(readingAttemptsStr);

    if (attempts.tsiMathAttempts > 0) {
        do {
            cout << "Enter the highest attempted math score: ";
            cin >> mathScoreStr;
        } while (inputContainsChar(mathScoreStr) || inputContainsComma(mathScoreStr));
        scores.tsiMathScore = stoi(mathScoreStr); // Assign the math score
    } else {
        scores.tsiMathScore = 0;
    }

    if (attempts.tsiReadingAttempts > 0) {
        bool validStrInput = false;
        do {
            cout << "Enter the highest attempted reading score: ";
            cin >> readingScoreStr;
            cout << "Enter the highest attempted writing score: ";
            cin >> writingScoreStr;

            if (inputContainsComma(readingScoreStr) || inputContainsChar(readingScoreStr) ||
                inputContainsComma(writingScoreStr) || inputContainsChar(writingScoreStr)) {
                cout << "\n\t| Error: Scores cannot contain commas or characters. |\n";
                validStrInput = false;
                } else {
                    validStrInput = true;
                    scores.tsiReadingScore = stoi(readingScoreStr); // Assign the reading score
                    scores.tsiWritingScore = stoi(writingScoreStr); // Assign the writing score
                }
        } while (!validStrInput);
    } else {
        scores.tsiReadingScore = 0;
        scores.tsiWritingScore = 0;
    }


    // Save data
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
        case 11:
            cout << "Change violations: \n";
            cin >> status.violations;
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
                     << scores.tsiWritingScore << ','
                    << status.violations << "\n"; // Use '\n' for correct newline
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

void Student::collegeReadinessFilter(fstream &studentData) {
    string line;
    int lineCounter = 0; // Counter to track current line number

    while (getline(studentData, line)) {
        stringstream ss(line);
        string token;
        vector<string> tokens;

        // Tokenize each line of data
        while (getline(ss, token, ',')) {
            tokens.push_back(token);
        }

        if (!tokens.empty()) {
            // Parse information from tokens
            contactInfo.studentId = tokens[0];
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
            status.violations = stoi(tokens[11]);
            // Filter based on TSI scores (assuming scores are at indices)
            if (scores.tsiMathScore >= MIN_MATH_SCORE &&
                scores.tsiReadingScore >= MIN_READING_SCORE &&
                scores.tsiWritingScore >= MIN_WRITING_SCORE) {
                // Save student data to collegeReady.txt
                fstream tempReadyFile("collegeReady.txt", ios::app); // Open in append mode
                saveStudentData(tempReadyFile);
                tempReadyFile.close();
            } else {
                    // Save student data to notCollegeReady.txt
                    fstream tempNotReadyFile("notCollegeReady.txt", ios::app); // Open in append mode
                    saveStudentData(tempNotReadyFile);
                    tempNotReadyFile.close();
                }
        }
        lineCounter++; // Increment line counter for filtering in temp file
    }
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
                    << scores.tsiWritingScore << ','
                    << status.violations << "\n"; // Use '\n' for correct newline
    } else {
        cout << "\n\t| Error: Could not write to file! |\n";
    }
}
