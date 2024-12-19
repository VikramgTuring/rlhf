#include <iostream>
#include <cstring>
using namespace std;

const int MAX_NAME_LENGTH = 16;

struct Student {
    char name[MAX_NAME_LENGTH];
    int age;
    float grade;
};

void setName(Student* student, const char* name) {
    strncpy(student->name, name, MAX_NAME_LENGTH);
    student->name[MAX_NAME_LENGTH - 1] = '\0';
}

void printStudentInfo(const Student& student) {
    cout << "Name: " << student.name << ", Age: " << student.age << ", Grade: " << student.grade << endl;
}

void trimString(char* str) {
    size_t len = strlen(str);
    while (len > 0 && str[len - 1] == ' ') {
        str[len - 1] = '\0';
        len--;
    }
}

int main() {
    Student student;

    // Inputting name from user (remember to handle invalid inputs properly in a real application)
    char inputName[MAX_NAME_LENGTH];
    cout << "Enter student name: ";
    cin.getline(inputName, MAX_NAME_LENGTH);

    // Copy the input name to the struct, trimming leading and trailing spaces
    setName(&student, inputName);
    trimString(student.name);

    student.age = 16;
    student.grade = 88.5;

    cout << "Student Information:" << endl;
    printStudentInfo(student);

    return 0;
}
