Да се дефинира класа Student во која ќе се чуваат информации за студент кој полагал испит по некој предмет и тоа индекс (стринг), име (стринг), презиме (стринг) и поени освоени на испитот (цел број).

За класата да се дефинираат потребните конструктори , оператор за печатење <<  и метод int grade() (методот ја враќа оценката по предметот по скалата 0-49 (5), 50-59 (6), 60-69 (7), 70-79 (8), 80-89 (9), 90-100 (10)). (10 п.)

Да се дефинира класа Results во која ќе се чуваат листа на студенти кои го положиле испитот по предметот (динамички алоцирана низа од објекти од класата Student и цел број кој ја означува големината на листата).

За класата да се имплементираат:

Потребните конструктори 
Оператор += за додавање на студент (Student) во резултатите (5 п.)
Доколку студентот кој се додава има помалку од 50 поени, односно не го положил испитот, да се фрли исклучок од класата StudentFailedException. (5 п.) Справувањето со исклучокот треба да испечати порака “Student with id {ID} failed the course”. (5 п.)
Оператор за печатење << (5 п.)

Метод Results withGrade(int grade) - кој прима како аргумент оценка (цел број), а враќа нов објект од класата Results во кој во листата на студенти кои го полагале предметот се содржат само студентите со оценка grade. (5 п.)

Дополнете ја main функцијата со следните барања:

Од датотеката input.txt прочитајте ги информациите за сите студенти кои го полагале испитот и тоа во следниот формат:
Информациите за секој студент се дадени во еден ред и тоа во редослед индекс, име, презиме и поени, одделени со празно место.
По читањето на информациите за секој студент, секој студент се додава во објектот results.
Во датотеката output1.txt да се испечатат резултатите за сите студенти.

Во датотеката output2.txt да се испечатат резултатите за сите студенти со оценка grade вчитана во почетниот код. (15 п.)

----

Define a class Student to store information about a student who has taken an exam for a subject, including the index (string), first name (string), last name (string), and points earned on the exam (integer).

For the class, define the necessary constructors, the print operator <<, and the method int grade() (the method returns the grade for the subject based on the scale 0-49 (5), 50-59 (6), 60-69 (7), 70-79 (8), 80-89 (9), 90-100 (10)).

Define a class Results to store a list of students who have passed the exam for the subject (dynamically allocated array of objects from the Student class and an integer indicating the size of the list).

For the class, implement:

The necessary constructors

The operator += for adding a student (Student) to the results.
If the student being added has less than 50 points, meaning they did not pass the exam, throw an exception from the class StudentFailedException. Handling the exception should print the message “Student with id {ID} failed the course”.
The print operator <<

The method Results withGrade(int grade) - which takes a grade (integer) as an argument and returns a new object of the Results class where the list of students who have taken the subject contains only students with the grade grade.

Complete the main function with the following requirements:

Read information about all students who have taken the exam from the file input.txt in the following format:
The information for each student is given in one line in the order of index, first name, last name, and points, separated by a space.
After reading the information for each student, each student is added to the results object.
Print the results for all students to the file output1.txt.

Print the results for all students with the grade read in the initial code to the file output2.txt.


  #include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
using namespace std;

class StudentFailedException : public exception {
    string message;
public:
    StudentFailedException(const string& index) {
        message = "Student with id " + index + " failed the course";
    }
    const char* what() const noexcept override {
        return message.c_str();
    }
};

class Student {
    string index;
    string name;
    string surname;
    int points;

public:
    Student(string index = "", string name = "", string surname = "", int points = 0)
        : index(index), name(name), surname(surname), points(points) {}

    int grade() const {
        if (points < 50) return 5;
        if (points < 60) return 6;
        if (points < 70) return 7;
        if (points < 80) return 8;
        if (points < 90) return 9;
        return 10;
    }

    friend ostream& operator<<(ostream& out, const Student& s) {
        out << s.index << " " << s.name << " " << s.surname << " " << s.points << " Grade: " << s.grade();
        return out;
    }

    friend istream& operator>>(istream& in, Student& s) {
        in >> s.index >> s.name >> s.surname >> s.points;
        return in;
    }

    int getPoints() const {
        return points;
    }

    string getIndex() const {
        return index;
    }
};

class Results {
    Student* students;
    int size;

public:
    Results() {
        students = nullptr;
        size = 0;
    }

    Results(const Results& other) {
        size = other.size;
        students = new Student[size];
        for (int i = 0; i < size; ++i) {
            students[i] = other.students[i];
        }
    }

    Results& operator=(const Results& other) {
        if (this != &other) {
            delete[] students;
            size = other.size;
            students = new Student[size];
            for (int i = 0; i < size; ++i) {
                students[i] = other.students[i];
            }
        }
        return *this;
    }

    ~Results() {
        delete[] students;
    }

    Results& operator+=(const Student& s) {
        if (s.getPoints() < 50) {
            throw StudentFailedException(s.getIndex());
        }
        Student* tmp = new Student[size + 1];
        for (int i = 0; i < size; ++i) {
            tmp[i] = students[i];
        }
        tmp[size] = s;
        delete[] students;
        students = tmp;
        size++;
        return *this;
    }

    Results withGrade(int grade) const {
        Results filtered;
        for (int i = 0; i < size; ++i) {
            if (students[i].grade() == grade) {
                filtered += students[i];
            }
        }
        return filtered;
    }

    friend ostream& operator<<(ostream& out, const Results& r) {
        for (int i = 0; i < r.size; ++i) {
            out << r.students[i] << endl;
        }
        return out;
    }
};


void wtf() {
    ofstream fout("input.txt");
    string line;
    while (getline(std::cin, line)) {
        if (line == "----"){
            break;
        }
        fout << line << endl;
    }
}

void rff(string path) {
    ifstream fin(path);
    string line;
    while (getline(fin, line)) {
        cout << line << endl;
    }
}


int main() {

    wtf();

    Results results;


    ifstream fin("input.txt");
    Student s;
    while (fin >> s) {
        try {
            results += s;
        } catch (StudentFailedException& e) {
            cout << e.what() << endl;
        }
    }
    fin.close();


    int grade;
    cin >> grade;




    ofstream fout1("output1.txt");
    fout1 << results;
    fout1.close();

    Results filtered = results.withGrade(grade);
    ofstream fout2("output2.txt");
    fout2 << filtered;
    fout2.close();

    //DO NOT MODIFY THE CODE BELLOW

    cout << "All students:" << endl;
    rff("output1.txt");
    cout << "Grade report for grade " << grade << ": " << endl;
    rff("output2.txt");

    return 0;
}
