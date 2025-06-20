Дефинирајте апстрактна класа Library со следниве спецификации (5 поени):

Име на библиотеката (низа од максимум 50 знаци/стринг)
Град во кој се наоѓа (низа од максимум 50 знаци/стринг)
Основна цена на месечна членарина (реален број)
Информација дали работи за викенд (Boolean променлива)
Дополнително, класата треба да содржи двe чисто виртуелни функции-членови на класта:

void printDetail() - функција која ги печати информациите за објектот
double calculateMembershipCardCost() - функција која враќа цена на чинење на членарина во библиотеката
Да се дефинираат две класи, AcademicLibrary и NationalLibrary, кои наследуваат од класата Library (5 поени).

За класата AcademicLibrary дополнително се чува информација за отворени можности за истражување (Boolean променлива), како и информација за број на специјализирани колекции од списанија во рамки на библиотеката (целобројна променлива).

Цената на членарина (функција double calculateMembershipCardCost()) за AcademicLibrary се пресметува на следниот начин:

Ако библиотеката нуди отворени можности за истражување, тогаш цената се зголемува за 24%.
Дополнително, секоја специјализирани колекции од списанија ја зголемува цената за $6.

Функцијата void printDetail() ги печати карактеристиките за библиотеката во следниот формат:

[Ime na biblioteka] - (Academic) [Grad] [Broj na spec. kolekcii] [Cena na clenarina] (10 поени)

За класата NationalLibrary дополнително се чува информација за тоа дали библиотеката нуди едукативни програми за културното наследство (Boolean променлива), како и информација за бројот на сочувани оригинални ракописи од национално значење (цел број).

Цената на членарина (функција double calculateMembershipCardCost()) за NationalLibrary се пресметува на следниот начин:

Ако библиотеката нуди едукативни програми, тогаш цената се намалува за 7%.
Дополнително, секој сочуван оригинален ракопис ја зголемува цената за $15.

Функцијата void printDetail() ги печати карактеристиките за библиотеката во следниот формат:

[Ime na biblioteka] - (National) [Grad] [Broj na rakopisi] [Cena na clenarina] (10 поени)

Да се дефинира следната глобална функција:

int findMostExpensiveNationalLibrary(Library **l, int n) која како аргумент прима низа од покажувачи кон библиотеки и големина на низата, а како резултат го враќа индексот во низата на националната библиотека (NationalLibrary) која има најскапата членарина. Доколку не постои таков објект во низата, функцијата враќа -1. Ако повеќе национални библиотеки имаат иста цена на членарина, се избира таа која работи за викенд (последниот најден). (20 поени)

--------------------------------------------
Define an abstract class Library with the following specifications (5 points):

Name of the library (string)
City where the library is located (string)
Base monthly membership fee (floating-point number)
Information on whether it operates on weekends (Boolean variable)
Additionally, the class should contain two pure virtual member functions:

void printDetails() - function that prints the object's information
double calculateMembershipCardCost() - function that returns the membership fee for the library
Define two classes, AcademicLibrary and NationalLibrary, which inherit from the Library class (5 points).

For the AcademicLibrary class, additionally store information about:

Open research opportunities (Boolean variable)
Number of specialized journal collections within the library (integer variable)
The membership fee (function double calculateMembershipCardCost()) for AcademicLibrary is calculated as follows:

If the library offers open research opportunities, the fee increases by 24%.
Additionally, each specialized journal collection increases the fee by $6.
The function void printDetail() prints the characteristics of the library in the following format:

[Library Name] - (Academic) [City] [Number of specialized collections] [Membership fee] (10 points)

For the NationalLibrary class, additionally store information about:

Whether the library offers educational programs on cultural heritage (Boolean variable)
Number of preserved original manuscripts of national significance (integer variable)
The membership fee (function double calculateMembershipCardCost()) for NationalLibrary is calculated as follows:

If the library offers educational programs, the fee decreases by 7%.
Additionally, each preserved original manuscript increases the fee by $15.
The function void printDetail() prints the characteristics of the library in the following format:

[Library Name] - (National) [City] [Number of manuscripts] [Membership fee] (10 points)

Define the following global function:

int findMostExpensiveNationalLibrary(Library **l, int n) which takes as an argument an array of pointers to libraries and the size of the array, 
and returns the index in the array of the national library (NationalLibrary) with the highest membership fee. If no such object exists in the array, 
the function returns -1. If multiple national libraries have the same membership fee, the one that operates on weekends is chosen (the last one found). (20 points)



#include <iostream>
#include <string>
using namespace std;

class Library {
protected:
    string name;
    string city;
    double base_price;
    bool weekend_working;

public:
    Library(string name, string city, double base_price, bool weekend_working)
        : name(name), city(city), base_price(base_price), weekend_working(weekend_working) {}

    virtual void printDetail() const = 0;
    virtual double calculateMembershipCardCost() const = 0;
    bool isWeekendWorking() const { return weekend_working; }
    virtual ~Library() {}
};

class AcademicLibrary : public Library {
private:
    bool open_cooperation;
    int specialized_articles;

public:
    AcademicLibrary(string name, string city, double base_price, bool weekend_working,
                    bool open_cooperation, int specialized_articles)
        : Library(name, city, base_price, weekend_working),
          open_cooperation(open_cooperation), specialized_articles(specialized_articles) {}

    double calculateMembershipCardCost() const override {
        double cost = base_price;
        if (open_cooperation) {
            cost += base_price * 0.24;
        }
        cost += specialized_articles * 6;
        return cost;
    }

    void printDetail() const override {
        cout << name << " - (Academic) " << city << " " << specialized_articles
             << " " << calculateMembershipCardCost() << endl;
    }
};

class NationalLibrary : public Library {
private:
    bool cultural_program;
    int national_articles;

public:
    NationalLibrary(string name, string city, double base_price, bool weekend_working,
                    bool cultural_program, int national_articles)
        : Library(name, city, base_price, weekend_working),
          cultural_program(cultural_program), national_articles(national_articles) {}

    double calculateMembershipCardCost() const override {
        double cost = base_price;
        if (cultural_program) {
            cost -= base_price * 0.07;
        }
        cost += national_articles * 15;
        return cost;
    }

    void printDetail() const override {
        cout << name << " - (National) " << city << " " << national_articles
             << " " << calculateMembershipCardCost() << endl;
    }
};

int findMostExpensiveNationalLibrary(Library **l, int n) {
    int index = -1;
    double max_cost = 0;
    for (int i = 0; i < n; ++i) {
        NationalLibrary *nl = dynamic_cast<NationalLibrary *>(l[i]);
        if (nl) {
            double cost = nl->calculateMembershipCardCost();
            if (cost > max_cost || (cost == max_cost && nl->isWeekendWorking())) {
                max_cost = cost;
                index = i;
            }
        }
    }
    return index;
}

int main() {
    int n, testCase, type;
    cin >> testCase >> n;
    cin.ignore();

    Library** m = new Library*[n];

    for (int i = 0; i < n; ++i) {
        string name;
        string city;
        float base_price;
        bool weekend_working;

        cin >> type;
        cin.ignore();
        getline(cin, name);
        getline(cin, city);
        cin >> base_price;
        cin.ignore();
        cin >> weekend_working;
        cin.ignore();

        if (type == 1) {
            bool open_cooperation;
            int specialized_articles;

            cin >> open_cooperation >> specialized_articles;
            cin.ignore();

            m[i] = new AcademicLibrary(name, city, base_price, weekend_working, open_cooperation, specialized_articles);
        } else {
            bool cultural_program;
            int national_articles;

            cin >> cultural_program >> national_articles;
            cin.ignore();

            m[i] = new NationalLibrary(name, city, base_price, weekend_working, cultural_program, national_articles);
        }
    }

    if(testCase == 1){
        cout << "Abstract and child classes OK" << endl;
    }
    else if(testCase == 2){
        for(int i = 0; i < n; i++){
            cout << m[i]->calculateMembershipCardCost() << endl;
        }
        cout << "calculateMembershipCardCost method OK" << endl;
    }
    else if(testCase == 3){
        for(int i = 0; i < n; i++){
            m[i]->printDetail();
        }
        cout << "printDetail method OK" << endl;
    }
    else if(testCase == 4){
        int most_expensive_nat_lib_index = findMostExpensiveNationalLibrary(m, n);
        if(most_expensive_nat_lib_index>=0){
            m[most_expensive_nat_lib_index]->printDetail();
        }else{
            cout << "National Library not found in the array!"<<endl;
        }
        cout << "findMostExpensiveNationalLibrary method OK" << endl;
    }


    for (int i = 0; i < n; ++i) {
        delete m[i];
    }

    delete[] m;

    return 0;
}


