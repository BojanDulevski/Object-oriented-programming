Да се дефинира класа IceCream во која се чуваат податоци за:

име (динамичка низа од знаци),
состав (низа од знаци, најмногу 100)
цена (децимален број),
попуст (цел број, изразен во проценти) иницијална вредност 0.
За потребите на класата да се имплементираат:

соодветни конструктори и деструктор (да се погледнат повиците во функцијата main)
оператор << за печатење на податоците за сладоледот во следниов формат:
име: состав цена [цена на попуст]

делот „цена на попуст“ се печати само ако за сладоледот се нуди попуст (вредноста на попустот е поголема од нула)

оператор ++ во префикс нотација за зголемување на попустот за 5
оператор + - за собирање на објект од класата IceCream со низа од знаци. Собирањето се реализира на начин што името на новиот сладолед се добива со спојување на името на сладоледот и низата од знаци одделени со „ + “. Цената на новиот сладолед се зголемува за 10, а попустот и составот на сладоледот остануваат исти.
метод void setDiscount(int discount) со кој може да се смени вредноста на попустот. Дозволените вредности на попустот се во интервалот [0,100]
метод void setName(char* name) со кој се менува името на сладоледот.
Да се креира класа IceCreamShop во која се чува:

име на продавницата (низа од знаци, најмногу 50)
динамички резервирано поле од објекти од класата IceCream
број на сладоледи во полето (цел број).
За оваа класа да се обезбедат:

соодветни конструктори и деструктор (погледнете ги повиците во main функцијата)
оператор += за додавање нов објект од класата IceCream во полето
оператор << за печатење на листа од сите сладоледи во продавницата. Прво се печати името на продавницата, а потоа се печатат податоците за сите сладоледи одделени со нов ред.





#include<iostream>
#include<cstring>
using namespace std;
class IceCream {
    char *name;
    char sostav[100];
    float price;
    int popust;
public:
    IceCream() {
        name = nullptr;
        price = 0;
        popust = 0;
    }

    IceCream(const char *name, char *sostav, float price, int popust=0) {
        this->name = new char[strlen(name)+1];
        strcpy(this->name, name);
        strcpy(this->sostav, sostav);
        this->price = price;
        this->popust = popust;
    }

    IceCream(const IceCream& ic) {
        this->name = new char[strlen(ic.name)+1];
        strcpy(this->name, ic.name);
        strcpy(this->sostav, ic.sostav);
        this->price = ic.price;
        this->popust = ic.popust;
    }

    IceCream& operator=(const IceCream& c) {
        if (this != &c) {
            delete[] name;
            name = new char[strlen(c.name)+1];
            strcpy(name, c.name);
            strcpy(sostav, c.sostav);
            price = c.price;
            popust = c.popust;
        }
        return *this;
    }

    ~IceCream() {
        delete[] name;
    }

    IceCream& operator++() {
        if (popust + 5 <= 100)
            popust += 5;
        else
            popust = 100;
        return *this;
    }

    IceCream operator+(const char* dodatok) {
        int novaDolzina = strlen(name) + strlen(dodatok) + 4;
        char* novoIme = new char[novaDolzina];
        strcpy(novoIme, name);
        strcat(novoIme, " + ");
        strcat(novoIme, dodatok);

        IceCream nov(novoIme, sostav, price + 10, popust);
        delete[] novoIme;
        return nov;
    }

    void setDiscount(int discount) {
        if (discount >= 0 && discount <= 100)
            popust = discount;
    }

    void setName(char* newName) {
        delete[] name;
        name = new char[strlen(newName)+1];
        strcpy(name, newName);
    }

    friend ostream& operator<<(ostream& o, IceCream& lc) {
        o << lc.name << ":"<<" " << lc.sostav << " " << lc.price<<endl;
        if (lc.popust > 0) {
            float sopopust = lc.price - (lc.price * lc.popust / 100.0);
            o << sopopust << endl;
        }
        return o;
    }
};

class IceCreamShop {
    char name[50];
    IceCream* iceCreams;
    int count;

public:
    IceCreamShop(){}
    IceCreamShop(const char* name = "") {
        strncpy(this->name, name, 49);
        this->name[49] = '\0';
        iceCreams = nullptr;
        count = 0;
    }

    IceCreamShop(const IceCreamShop& other) {
        strcpy(this->name, other.name);
        count = other.count;
        iceCreams = new IceCream[count];
        for (int i = 0; i < count; ++i) {
            iceCreams[i] = other.iceCreams[i];
        }
    }

    IceCreamShop& operator=(const IceCreamShop& other) {
        if (this != &other) {
            delete[] iceCreams;
            strcpy(this->name, other.name);
            count = other.count;
            iceCreams = new IceCream[count];
            for (int i = 0; i < count; ++i) {
                iceCreams[i] = other.iceCreams[i];
            }
        }
        return *this;
    }

    ~IceCreamShop() {
        delete[] iceCreams;
    }

    IceCreamShop& operator+=( IceCream& ic) {
        IceCream* tmp = new IceCream[count + 1];
        for (int i = 0; i < count; ++i) {
            tmp[i] = iceCreams[i];
        }
        tmp[count] = ic;
        delete[] iceCreams;
        iceCreams = tmp;
        count++;
        return *this;
    }

    friend ostream& operator<<(ostream& out, const IceCreamShop& shop) {
        out << shop.name<<endl;
        for (int i = 0; i < shop.count; ++i) {
            out << shop.iceCreams[i];
        }
        return out;
    }
};












int main() {
    char name[100];
    char ingr[100];
    float price;
    int discount;

    int testCase;

    cin >> testCase;
	cin.get();
    if(testCase == 1) {
        cout << "====== TESTING IceCream CLASS ======" << endl;
        cin.getline(name,100);
        cin.getline(ingr,100);
        cin >> price;
        cin >> discount;
        cout << "CONSTRUCTOR" << endl;
        IceCream ic1(name, ingr, price);
        ic1.setDiscount(discount);
        cin.get();
        cin.getline(name,100);
        cin.getline(ingr,100);
        cin >> price;
        cin >> discount;
        IceCream ic2(name, ingr, price);
        ic2.setDiscount(discount);
        cout << "OPERATOR <<" << endl;
        cout << ic1 << endl;
        cout << ic2 << endl;
        cout << "OPERATOR ++" << endl;
        ++ic1;
        cout << ic1 << endl;
        cout << "OPERATOR +" << endl;
        IceCream ic3 = ic2 + "chocolate";
        cout << ic3 << endl;
    } else if(testCase == 2) {
        cout << "====== TESTING IceCream CONSTRUCTORS ======" << endl;
        cin.getline(name,100);
        cin.getline(ingr,100);
        cin >> price;
        //cin >> discount;
        cout << "CONSTRUCTOR" << endl;
        IceCream ic1(name, ingr, price);
        cout << ic1 << endl;
        cout << "COPY CONSTRUCTOR" << endl;
        IceCream ic2(ic1);
        cin.get();
        cin.getline(name,100);
        ic2.setName(name);
        cout << ic1 << endl;
        cout << ic2 << endl;
        cout << "OPERATOR =" << endl;
        ic1 = ic2;
        cin.getline(name,100);
        ic2.setName(name);
        cout << ic1 << endl;
        cout << ic2 << endl;

        cin >> discount;
        ic1.setDiscount(discount);


    } else if(testCase == 3) {
        cout << "====== TESTING IceCreamShop ======" << endl;
        char icsName[50];
        cin.getline(icsName,100);
        cout << "CONSTRUCTOR" << endl;
        IceCreamShop ics(icsName);
        int n;
        cin >> n;
        cout << "OPERATOR +=" << endl;
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,100);
        	cin.getline(ingr,100);
            cin >> price;
            IceCream ic(name, ingr, price);
            ics += ic;
        }
        cout << ics;
    } else if(testCase == 4) {
        cout << "====== TESTING IceCreamShop CONSTRUCTORS ======" << endl;
        char icsName[50];
        cin.getline(icsName,100);
        IceCreamShop ics(icsName);
        int n;
        cin >> n;
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,100);
        	cin.getline(ingr,100);
            cin >> price;
            IceCream ic(name, ingr, price);
            ics += ic;
        }
        IceCream x("FINKI fruits", "strawberry ice cream, raspberry ice cream, blueberry ice cream", 60);
        IceCreamShop icp = ics;
        ics+=x;
        cout << ics << endl;
        cout << icp << endl;
    }


    return 0;
}

//STARTER
/*#include <iostream>
#include <cstring>
using namespace std;


// vashiot kod ovde

// zabraneto e menuvanje na main funkcijata

int main() {
    char name[100];
    char ingr[100];
    float price;
    int discount;

    int testCase;

    cin >> testCase;
	cin.get();
    if(testCase == 1) {
        cout << "====== TESTING IceCream CLASS ======" << endl;
        cin.getline(name,100);
        cin.getline(ingr,100);
        cin >> price;
        cin >> discount;
        cout << "CONSTRUCTOR" << endl;
        IceCream ic1(name, ingr, price);
        ic1.setDiscount(discount);
        cin.get();
        cin.getline(name,100);
        cin.getline(ingr,100);
        cin >> price;
        cin >> discount;
        IceCream ic2(name, ingr, price);
        ic2.setDiscount(discount);
        cout << "OPERATOR <<" << endl;
        cout << ic1 << endl;
        cout << ic2 << endl;
        cout << "OPERATOR ++" << endl;
        ++ic1;
        cout << ic1 << endl;
        cout << "OPERATOR +" << endl;
        IceCream ic3 = ic2 + "chocolate";
        cout << ic3 << endl;
    } else if(testCase == 2) {
        cout << "====== TESTING IceCream CONSTRUCTORS ======" << endl;
        cin.getline(name,100);
        cin.getline(ingr,100);
        cin >> price;
        cout << "CONSTRUCTOR" << endl;
        IceCream ic1(name, ingr, price);
        cout << ic1 << endl;
        cout << "COPY CONSTRUCTOR" << endl;
        IceCream ic2(ic1);
        cin.get();
        cin.getline(name,100);
        ic2.setName(name);
        cout << ic1 << endl;
        cout << ic2 << endl;
        cout << "OPERATOR =" << endl;
        ic1 = ic2;
        cin.getline(name,100);
        ic2.setName(name);
        cout << ic1 << endl;
        cout << ic2 << endl;

        cin >> discount;
        ic1.setDiscount(discount);


    } else if(testCase == 3) {
        cout << "====== TESTING IceCreamShop ======" << endl;
        char icsName[50];
        cin.getline(icsName,100);
        cout << "CONSTRUCTOR" << endl;
        IceCreamShop ics(icsName);
        int n;
        cin >> n;
        cout << "OPERATOR +=" << endl;
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,100);
        	cin.getline(ingr,100);
            cin >> price;
            IceCream ic(name, ingr, price);
            ics += ic;
        }
        cout << ics;
    } else if(testCase == 4) {
        cout << "====== TESTING IceCreamShop CONSTRUCTORS ======" << endl;
        char icsName[50];
        cin.getline(icsName,100);
        IceCreamShop ics(icsName);
        int n;
        cin >> n;
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,100);
        	cin.getline(ingr,100);
            cin >> price;
            IceCream ic(name, ingr, price);
            ics += ic;
        }
        IceCream x("FINKI fruits", "strawberry ice cream, raspberry ice cream, blueberry ice cream", 60);
        IceCreamShop icp = ics;
        ics+=x;
        cout << ics << endl;
        cout << icp << endl;
    }


    return 0;
}
*/
