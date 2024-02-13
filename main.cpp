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
    int tsiMathScore;
    int tsiEnglScore;
    bool tsiMathStatus;
    bool tsiReadingStatus;
    bool tsiWritingStatus;

    // Construct data
    Student(const string& _studentId = "", const string& _lastName = "",
            const string& _firstName = "", const string& _studentEmail = "",
            const int& _tsiMathScore = 0, const int& _tsiEnglScore = 0,
            bool _tsiMathStatus = false, bool _tsiReadingStatus = false, bool _tsiWritingStatus = false)
            : studentId(_studentId), lastName(_lastName), firstName(_firstName), studentEmail(_studentEmail),
            tsiMathScore(_tsiMathScore), tsiEnglScore(_tsiEnglScore),
            tsiMathStatus(_tsiMathStatus), tsiReadingStatus(_tsiReadingStatus), tsiWritingStatus(_tsiWritingStatus) {}

    void readStudentData(){
        cout << "Enter ID: ";
        cin >> studentId;
        cout << "Last name: ";
        cin >> lastName;
        cout << "First Name: ";
        cin >> firstName;
        cout << "Student email: ";
        cin >> studentEmail;
        cout << "Tsi Math Score: ";
        cin >> tsiMathScore;
        cout << "Tsi English Score: ";
        cin >> tsiEnglScore;

        // put this tsi readiness check somewhere else, 
        // im guessing math & engl count is the students score for each, but how
        // do we determine if engl is ready since we have to factor both reading and writing?
        const int minMathScore = 950, minEnglScore = 945;
        tsiMathScore >= minMathScore ? tsiMathStatus = true : tsiMathStatus = false; // Check if the students score meet min math score.
        // tsiEnglScore >= minEnglScore ? tsiWritingStatus = true : tsiWritingStatus = false;

    }

    void saveStudentData(ofstream& file) const{
        file <<  studentId << ',' << lastName << ',' << firstName << ',' << studentEmail << '\n';
    }
};

int main() {
    ofstream studentData("students.txt");

    if(!studentData){
        cout << "Error opening file\n";
        return 1;
    }

    int studentBodySize;
    cout << "How many students?: ";
    cin >> studentBodySize;

    for(int i = 0; i < studentBodySize; i++){
        Student student; // var and type
        cout << "\nEnter data for student " << (i + 1) << " :\n";
        student.readStudentData(); // Get input from user
        student.saveStudentData(studentData); // Save input to students.txt
    }

    studentData.close();
    cout << "Data written to file\n";
    return 0;
}
