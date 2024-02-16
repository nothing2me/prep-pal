#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Student {
public:
    string studentId;
    string lastName;
    string firstName;
    string studentEmail;
    // Maybe put these in private
    int tsiMathScore;
    int tsiWritingScore;
    int tsiReadingScore;
    bool transferStatus; // 1 for transfer 0 for newly enrolled
    bool tsiMathStatus;
    bool tsiReadingStatus;
    bool tsiWritingStatus;

    // Construct data
    Student(const string& _studentId = "", const string& _lastName = "",
            const string& _firstName = "", const string& _studentEmail = "",
            const int& _tsiMathScore = 0, const int& _tsiWritingScore = 0, const int& _tsiReadingScore = 0,
            const bool& _transferStatus = false, const bool& _tsiMathStatus = false,
            bool _tsiReadingStatus = false, bool _tsiWritingStatus = false)
            : studentId(_studentId), lastName(_lastName), firstName(_firstName), studentEmail(_studentEmail),
              tsiMathScore(_tsiMathScore), tsiWritingScore(_tsiWritingScore), tsiReadingScore(_tsiReadingScore),
              transferStatus(_transferStatus), tsiMathStatus(_tsiMathStatus),
              tsiReadingStatus(_tsiReadingStatus), tsiWritingStatus(_tsiWritingStatus) {
    }

    void viewStudentData(fstream& studentData){
        /*
         * STUDENT DATA FORMAT
         * # is any number
         * ! is either 1 if a transfer student, 0 if not
         * A0#######,email@islander.tamucc.edu,LASTNAME,FIRSTNAME,!,(ATTEMPTED HOURS)###,(MATH)###,(READING)###, WRITING(###)
         */
        cout << "Enter Student ID: ";
        cin >> studentId;
        string searchId;
        bool found = false;
        // Read each line in students.txt
        while (getline(studentData, searchId)) {
            size_t delimPos = searchId.find(studentId); // Check if the line contains the student ID
            // Condition if found
            if (delimPos != string::npos) {
                found = true;
                //Get delimiter position of each
                size_t writingPosition = searchId.find_last_of(',');
                size_t readingPosition = searchId.find_last_of(',', writingPosition - 1);
                size_t mathPosition = searchId.find_last_of(',', readingPosition - 1);
                // Use positions to parse into strings
                string writingScoreString = searchId.substr(writingPosition + 1);
                string readingScoreString = searchId.substr(readingPosition + 1, writingPosition - readingPosition - 1);
                string mathScoreString = searchId.substr(mathPosition + 1, readingPosition - mathPosition - 1);
                // Convert string to integer using  string to int function
                int writingScore = stoi(writingScoreString);
                int readingScore = stoi(readingScoreString);
                int mathScore = stoi(mathScoreString);
                // Output data and end loop
                cout << "Student found: " << "\n";
                cout << "Writing Score: " << writingScore << "\n";
                cout << "Reading Score: " << readingScore << "\n";
                cout << "Math Score: " << mathScore << "\n";
                checkTsiStatus(tsiMathScore, tsiReadingScore, tsiWritingScore);
                break;
            }
        }
        // If no id was found
        if (!found) {
            cout << "Error, student Id not found." << "\n";
        }
    }

    void checkTsiStatus(int mathscore, int readingscore, int writingscore){

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
        /*
        cout << "Transfer student? (y/N): ";
        cin >> transferStatus;
        //checks if the input by the user is and variation of 'yes' and returns true if yes. if no input from user, default is false.
        transferStatus = transferStatus == "Yes" || "yes" || "Y" || "y" ? true : false;
        cout << "Tsi Math Score: ";
        cin >> tsiMathScore;
        cout << "Tsi English Score: ";
        cin >> tsiWritingScore;

        // put this tsi readiness check somewhere else,
        // im guessing math & engl count is the students score for each, but how
        // do we determine if engl is ready since we have to factor both reading and writing?
         const int minMathScore = 950, minEnglScore = 945;
         tsiMathScore >= minMathScore ? tsiMathStatus = true : tsiMathStatus = false; // Check if the students score meet min math score
         tsiWritingScore >= minEnglScore ? tsiWritingStatus = true : tsiWritingStatus = false;
        */
    }


    void saveStudentData(fstream& file) const{
        file <<  studentId << ',' << lastName << ',' << firstName << ',' << studentEmail << '\n';
    }
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
