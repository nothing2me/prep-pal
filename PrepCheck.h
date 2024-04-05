#ifndef CAPSTONE_PROJECT_PREPCHECK_H
#define CAPSTONE_PROJECT_PREPCHECK_H

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

    // Construct default data for errors
    Student(const string &_studentId = "DEFAULT",
            const string &_lastName = "DEFAULT", const string &_firstName = "DEFAULT",
            const string &_studentEmail = "DEFAULT",
            const int &_tsiMathScore = 0, const int &_tsiWritingScore = 0,
            const int &_tsiReadingScore = 0, const int &_attemptedCollegeHours = 0,
            const int &_tsiMathAttempts = 0, const int &_tsiReadingAttempts = 0,
            const bool &_transferStatus = false)
            :
            contactInfo({_studentId,_studentEmail,_lastName,_firstName}),
            scores({_tsiMathScore, _tsiWritingScore, _tsiReadingScore}), // Initialize Scores struct
            attempts({_tsiMathAttempts, _tsiReadingAttempts,_attemptedCollegeHours}),  // Initialize Attempts struct
            status({_transferStatus}){
    }
    void checkTsiStatus(int mathScore, int readingScore, int writingScore) const;
    void viewStudentData(fstream& studentData) const;
    void newStudentData();
    void editStudentData(fstream& studentData);
    void saveStudentData(fstream& studentData) const;
    void mergeStudentData(fstream& studentData);
};

#endif //CAPSTONE_PROJECT_PREPCHECK_H