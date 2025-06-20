Дефинирајте апстрактна класа Museum со следниве спецификации (5 поени):

Име на музејот (низа од максимум 50 знаци/стринг)
Град во кој се наоѓа (низа од максимум 50 знаци/стринг)
Основна цена на билет (реален број)
Број на работни часови во неделата (цел број)

Дополнително, класата треба да содржи двe чисто виртуелни функции-членови на класaта:

void printDetails() - функција која ги печати информациите за објектот
double calculateTicketCost() - функција која враќа цена на билет за посета на музеј
Да се дефинираат две класи, ScientificMuseum и ArtMuseum, кои наследуваат од класата Museum (5 поени).

За класата ScientificMuseum дополнително се чува информација за интерактивни поставки во рамки на музејот (Boolean променлива), како и информација за број на мултимедијални презентации кои може да се посетат во музејот (целобројна променлива).

Цената на билет (функција double calculateTicketCost()) за ScientificMuseum се пресметува на следниот начин:

Ако музејот нуди интерактивни поставки, тогаш цената се зголемува за 12%.
Дополнително, секоја мултимедијална презентација ја зголемува цената за $6.

Функцијата void printDetail() ги печати карактеристиките за музејот во следниот формат:

[Ime na muzej] - (Scientific) [Grad] [Broj na mult. prezentacii] [Cena na karta] (10 поени)

За класата ArtMuseum дополнително се чува информација за тоа дали музејот нуди опции за аматерски изложби (Boolean променлива), како и информација за бројот на оригинални не-реставрирани уметнички дела (цел број).

Цената на билет (функција double calculateTicketCost()) за  ArtMuseum се пресметува на следниот начин:

Ако музејот нуди опција за аматерски изложби, тогаш цената се намалува за 18%.
Дополнително, секое оригинално не-реставрирано дело ја зголемува цената за $3.

Функцијата void printDetail() ги печати карактеристиките за музејот во следниот формат:

[Ime na muzej] - (Art) [Grad] [Amaterski izlozbi] [Cena na karta] (10 поени)

Да се дефинира следната глобална функција:

int findCheapestScientificMuseum(Museum **m, int n) која како аргумент прима низа од покажувачи кон музеи и големина на низата, а како резултат го враќа индексот на научниот музеј (ScientificMuseum) кој има најниска цена на карта во низата. Доколку не постои таков објект во низата, функцијата враќа -1. Ако повеќе музеи имаат иста цена на картата, се избира тој со повеќе работни часови во неделата (последниот таков). (20 поени)
----------------------------------------------
Define an abstract class Museum with the following specifications (5 points):

Name of the museum (string)
City where the museum is located (string)
Base ticket price (floating-point number)
Number of working hours in the week (integer)
Additionally, the class should contain two pure virtual member functions:

void printDetails() - function that prints the object's information
double calculateTicketCost() - function that returns the ticket price for visiting the museum
Define two classes, ScientificMuseum and ArtMuseum, which inherit from the Museum class (5 points).

For the ScientificMuseum class, additionally store information about:

Interactive exhibits within the museum (Boolean variable)
Number of multimedia presentations available in the museum (integer variable)
The ticket price (function double calculateTicketCost()) for ScientificMuseum is calculated as follows:

If the museum offers interactive exhibits, the price increases by 12%.
Additionally, each multimedia presentation increases the price by $6.
The function void printDetail() prints the characteristics of the museum in the following format:

[Museum Name] - (Scientific) [City] [Number of multimedia presentations] [Ticket price] (10 points)

For the ArtMuseum class, additionally store information about:

Whether the museum offers options for amateur exhibitions (Boolean variable)
Number of original non-restored artworks (integer variable)
The ticket price (function double calculateTicketCost()) for ArtMuseum is calculated as follows:

If the museum offers options for amateur exhibitions, the price decreases by 18%.
Additionally, each original non-restored artwork increases the price by $3.
The function void printDetail() prints the characteristics of the museum in the following format:

[Museum Name] - (Art) [City] [Amateur exhibitions] [Ticket price] (10 points)

Define the following global function:

int findCheapestScientificMuseum(Museum **m, int n) which takes as an argument an array of pointers to museums and the size of the array, and returns the index of the scientific museum (ScientificMuseum) with the lowest ticket price in the array. If no such object exists in the array, the function returns -1. If multiple museums have the same ticket price, the one with more working hours in the week is chosen (the last one found). (20 points)

#include <iostream>
#include <cstring>
#include <string>
using namespace std;


class Museum {
protected:
    string name;
    string city;
    float base_price;
    int working_hours;

public:
    Museum(string name = "", string city = "", float base_price = 0.0, int working_hours = 0) {
        this->name = name;
        this->city = city;
        this->base_price = base_price;
        this->working_hours = working_hours;
    }

    virtual ~Museum() {}

    virtual void printDetail() const = 0;
    virtual double calculateTicketCost() const = 0;
    int getWorkingHours() const {
        return working_hours;
    }
};


class ScientificMuseum : public Museum {
private:
    bool interactive_shows;
    int multimedia_presentations;

public:
    ScientificMuseum(string name, string city, float base_price, int working_hours,
                     bool interactive_shows, int multimedia_presentations)
        : Museum(name, city, base_price, working_hours) {
        this->interactive_shows = interactive_shows;
        this->multimedia_presentations = multimedia_presentations;
    }

    double calculateTicketCost() const override {
        double price = base_price;
        if (interactive_shows) {
            price *= 1.12;
        }
        price += multimedia_presentations * 6;
        return price;
    }

    void printDetail() const override {
        cout << name << " - (Scientific) " << city << " " << multimedia_presentations
             << " " << calculateTicketCost() << endl;
    }
};


class ArtMuseum : public Museum {
private:
    bool amateur_exhibitions;
    int original_artworks;

public:
    ArtMuseum(string name, string city, float base_price, int working_hours,
              bool amateur_exhibitions, int original_artworks)
        : Museum(name, city, base_price, working_hours) {
        this->amateur_exhibitions = amateur_exhibitions;
        this->original_artworks = original_artworks;
    }

    double calculateTicketCost() const override {
        double price = base_price;
        if (amateur_exhibitions) {
            price *= 0.82;
        }
        price += original_artworks * 3;
        return price;
    }

    void printDetail() const override {
        cout << name << " - (Art) " << city << " " << (amateur_exhibitions ? "true" : "false")
             << " " << calculateTicketCost() << endl;
    }
};


int findCheapestScientificMuseum(Museum **m, int n) {
    int minIndex = -1;
    double minPrice = 1e9;

    for (int i = 0; i < n; ++i) {
        ScientificMuseum* sci = dynamic_cast<ScientificMuseum*>(m[i]);
        if (sci) {
            double currentPrice = sci->calculateTicketCost();
            if (currentPrice < minPrice) {
                minPrice = currentPrice;
                minIndex = i;
            } else if (currentPrice == minPrice) {

                if (m[i]->getWorkingHours() > m[minIndex]->getWorkingHours()) {
                    minIndex = i;
                }
            }
        }
    }

    return minIndex;
}


int main() {
    int n, testCase, type;
    cin >> testCase >> n;
    cin.ignore();

    Museum** m = new Museum*[n];

    for (int i = 0; i < n; ++i) {
        string name;
        string city;
        float base_price;
        int working_hours;

        cin >> type;
        cin.ignore();
        getline(cin, name);
        getline(cin, city);
        cin >> base_price;
        cin.ignore();
        cin >> working_hours;
        cin.ignore();

        if (type == 1) {
            bool interactive_shows;
            int multimedia_pres;

            cin >> interactive_shows >> multimedia_pres;
            cin.ignore();

            m[i] = new ScientificMuseum(name, city, base_price, working_hours, interactive_shows, multimedia_pres);
        } else {
            bool amateur_shows;
            int original_artwork;

            cin >> amateur_shows >> original_artwork;
            cin.ignore();

            m[i] = new ArtMuseum(name, city, base_price, working_hours, amateur_shows, original_artwork);
        }
    }

    if(testCase == 1){
        cout << "Abstract and child classes OK" << endl;
    }
    else if(testCase == 2){
        for(int i = 0; i < n; i++){
            cout << m[i]->calculateTicketCost() << endl;
        }
        cout << "calculateTicketCost method OK" << endl;
    }
    else if(testCase == 3){
        for(int i = 0; i < n; i++){
            m[i]->printDetail();
        }
        cout << "printDetail method OK" << endl;
    }
    else if(testCase == 4){
        int cheapest_sci_museum_index = findCheapestScientificMuseum(m, n);
        if(cheapest_sci_museum_index>=0){
            m[cheapest_sci_museum_index]->printDetail();
        }else{
            cout << "Scientific Museum not found in the array!"<<endl;
        }
        cout << "findCheapestOnlineOrder method OK" << endl;
    }


    for (int i = 0; i < n; ++i) {
        delete m[i];
    }

    delete[] m;

    return 0;
}
