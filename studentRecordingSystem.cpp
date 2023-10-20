#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

struct Student {
    string name;
    int id;
    vector<int> grades;
};

void printMenu() {
    cout << "Menu:\n";
    cout << "1. Add a student record\n";
    cout << "2. Update a student record\n";
    cout << "3. Delete a student record\n";
    cout << "4. Display all student records\n";
    cout << "5. Calculate average grade\n";
    cout << "6. Save student records to file\n";
    cout << "7. Load student records from file\n";
    cout << "8. Exit\n";
    cout << "Choose an option: ";
}

void addStudentRecord(vector<Student>& students) {
    Student newStudent;
    cout << "Enter student name: ";
    cin.ignore();
    getline(cin, newStudent.name);

    cout << "Enter student ID: ";
    cin >> newStudent.id;

    int numGrades;
    cout << "Enter the number of grades: ";
    cin >> numGrades;

    cout << "Enter " << numGrades << " grades: ";
    for (int i = 0; i < numGrades; i++) {
        int grade;
        cin >> grade;
        newStudent.grades.push_back(grade);
    }

    students.push_back(newStudent);
    cout << "Student record added successfully!\n";
}

void updateStudentRecord(vector<Student>& students) {
    int id;
    cout << "Enter the ID of the student to update: ";
    cin >> id;

    for (Student& student : students) {
        if (student.id == id) {
            cout << "Enter the new name for the student: ";
            cin.ignore();
            getline(cin, student.name);

            int numGrades;
            cout << "Enter the number of grades: ";
            cin >> numGrades;

            cout << "Enter " << numGrades << " grades: ";
            student.grades.clear();
            for (int i = 0; i < numGrades; i++) {
                int grade;
                cin >> grade;
                student.grades.push_back(grade);
            }

            cout << "Student record updated successfully!\n";
            return;
        }
    }

    cout << "Student not found!\n";
}

void deleteStudentRecord(vector<Student>& students) {
    int id;
    cout << "Enter the ID of the student to delete: ";
    cin >> id;

    for (auto it = students.begin(); it != students.end(); it++) {
        if (it->id == id) {
            students.erase(it);
            cout << "Student record deleted successfully!\n";
            return;
        }
    }

    cout << "Student not found!\n";
}

void displayStudentRecords(const vector<Student>& students) {
    cout << "Student records:\n";
    cout << "-----------------------------" << endl;
    cout << "ID\tName\tGrades" << endl;

    for (const Student& student : students) {
        cout << student.id << "\t" << student.name << "\t";
        for (int grade : student.grades) {
            cout << grade << " ";
        }
        cout << endl;
    }
    cout << endl;
}

float calculateAverageGrade(const vector<Student>& students) {
    float total = 0;
    int count = 0;

    for (const Student& student : students) {
        for (int grade : student.grades) {
            total += grade;
            count++;
        }
    }

    if (count > 0) {
        return total / count;
    }
    else {
        return 0;
    }
}

void saveStudentRecordsToFile(const vector<Student>& students) {
    string fileName;
    cout << "Enter the file name to save student records: ";
    cin >> fileName;

    ofstream outFile(fileName);

    if (outFile.is_open()) {
        for (const Student& student : students) {
            outFile << student.id << "," << student.name << ",";
            for (int grade : student.grades) {
                outFile << grade << " ";
            }
            outFile << endl;
        }

        cout << "Student records saved to file successfully!\n";
    }
    else {
        cout << "Error: Unable to open file\n";
    }
}

void loadStudentRecordsFromFile(vector<Student>& students) {
    string fileName;
    cout << "Enter the file name to load student records: ";
    cin >> fileName;
     ifstream inFile(fileName);

    if (inFile.is_open()) {
        students.clear();
        string line;
        while (getline(inFile, line)) {
            Student newStudent;
            string gradeStr;

            size_t pos = line.find(",");
            newStudent.id = stoi(line.substr(0, pos));

            size_t pos2 = line.find(",", pos + 1);
            newStudent.name = line.substr(pos + 1, pos2 - pos - 1);

            size_t pos3 = pos2 + 1;
            pos = line.find(" ", pos3);
            while (pos != string::npos) {
                gradeStr = line.substr(pos3, pos - pos3);
                newStudent.grades.push_back(stoi(gradeStr));
                pos3 = pos + 1;
                pos = line.find(" ", pos3);
            }

            students.push_back(newStudent);
        }

        cout << "Student records loaded from file successfully!\n";
    }
    else {
        cout << "Error: Unable to open file\n";
    }
}

int main() {
    vector<Student> students;
    int choice;
    do {
        printMenu();
        cin >> choice;
        cout << endl;

        switch (choice) {
            case 1:
                addStudentRecord(students);
                break;
            case 2:
                updateStudentRecord(students);
                break;
            case 3:
                deleteStudentRecord(students);
                break;
            case 4:
                displayStudentRecords(students);
                break;
            case 5: {
                float averageGrade = calculateAverageGrade(students);
                cout << "Average Grade of all students: " << averageGrade << endl;
                break;
            }
            case 6:
                saveStudentRecordsToFile(students);
                break;
            case 7:
                loadStudentRecordsFromFile(students);
                break;
            case 8:
                cout << "Goodbye!\n";
                break;
            default:
                cout << "Invalid choice!\n";
                break;
        }

        cout << endl;
    } while (choice != 8);

    return 0;
}
