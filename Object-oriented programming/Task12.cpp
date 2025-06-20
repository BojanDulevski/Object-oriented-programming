Да се дефинира класа Product во која ќе се чуваат информации за производ во една продавница и тоа име (стринг), категорија (стринг) и цена (цел број) и достапна количина (цел број).

За класата да се дефинираат потребните конструктори, оператор за печатење << и метод int totalPrice() - методот ја враќа вкупната вредност на производот пресметана како производ на цената и достапната количина. (10 п.)

Да се дефинира класа Store во која ќе се чуваат листа на производи (динамички алоцирана низа од објекти од класата Product и цел број кој ја означува големината на листата).

За класата да се имплементираат:

Потребните конструктори
Оператор += за додавање на производ (Product) во продавницата (5 п.)
Оператор за печатење << (5 п.)
Метод Store fromCategory (string & category) - кој прима како аргумент категорија (стринг), а враќа нов објект од класата Store во кој во листата на производи се сместени само производи од категоријата category. (5 п.)
Доколку нема ниту еден таков продукт да се фрли исклучок од класата NoProductFoundException. (5 п.) Справувањето со исклучокот треба да испечати порака “No products from category {category} were found in the store”. (5 п.)
Дополнете ја main функцијата со следните барања:

Од датотеката input.txt прочитајте ги информациите за сите производи:
За секој производ во 4 реда се дадени информациите за името, категоријата, цената и количината.
По читањето на информациите за секој производ, секој производ се додава во објектот store.
Во датотеката output1.txt да се испечатат информациите за продавницата.
Во датотеката output2.txt да се испечати резултатот од методот fromCategory за категоријата category вчитана во почетниот код. (15 п.)

----


Define a class Product to store information about a product in a store, including the name (string), category (string), price (integer), and available quantity (integer).

For the class, define the necessary constructors, the print operator <<, and the method int totalPrice() - the method returns the total value of the product calculated as the product of the price and available quantity.

Define a class Store to store a list of products (dynamically allocated array of objects from the Product class and an integer indicating the size of the list).

For the class, implement:

The necessary constructors
The operator += for adding a product (Product) to the store
The print operator <<
The method Store fromCategory(string &category) - which takes a category (string) as an argument and returns a new object of the Store class where the list of products contains only products from the specified category.
If there is no such product, throw an exception of the class NoProductFoundException. Handling the exception should print the message “No products from category {category} were found in the store”.

Complete the main function with the following requirements:

Read information about all products from the file input.txt
For each product, the information for the name, category, price, and quantity is given in 4 lines.
After reading the information about each product, each product is added to the store object.
Print the store information to the file output1.txt.
Print the result of the fromCategory method for the read category in the initial code to the file output2.txt.



  #include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
using namespace std;

class NoProductFoundException : public exception {
    string message;
public:
    NoProductFoundException(string category) {
        message = "No products from category " + category + " were found in the store";
    }
    const char* what() const noexcept override {
        return message.c_str();
    }
};

class Product {
    string name;
    string category;
    int price;
    int quantity;

public:
    Product(string name = "", string category = "", int price = 0, int quantity = 0)
        : name(name), category(category), price(price), quantity(quantity) {}

    int totalPrice() const {
        return price * quantity;
    }

    friend ostream& operator<<(ostream& out, const Product& p) {
        out << p.name << " (" << p.category << ") " 
            << p.quantity << " x " << p.price 
            << " = " << p.totalPrice() << endl;
        return out;
    }

    friend istream& operator>>(istream& in, Product& p) {
        getline(in, p.name);
        if (p.name.empty()) getline(in, p.name);
        getline(in, p.category);
        in >> p.price >> p.quantity;
        in.ignore();
        return in;
    }

    string getCategory() const {
        return category;
    }
};

class Store {
    Product* products;
    int size;

public:
    Store() {
        products = nullptr;
        size = 0;
    }

    Store(const Store& other) {
        size = other.size;
        products = new Product[size];
        for (int i = 0; i < size; ++i) {
            products[i] = other.products[i];
        }
    }

    Store& operator=(const Store& other) {
        if (this != &other) {
            delete[] products;
            size = other.size;
            products = new Product[size];
            for (int i = 0; i < size; ++i) {
                products[i] = other.products[i];
            }
        }
        return *this;
    }

    ~Store() {
        delete[] products;
    }

    Store& operator+=(const Product& p) {
        Product* temp = new Product[size + 1];
        for (int i = 0; i < size; ++i) {
            temp[i] = products[i];
        }
        temp[size] = p;
        delete[] products;
        products = temp;
        size++;
        return *this;
    }

    Store fromCategory(string& category) {
        Store filtered;
        for (int i = 0; i < size; ++i) {
            if (products[i].getCategory() == category) {
                filtered += products[i];
            }
        }
        if (filtered.size == 0) {
            throw NoProductFoundException(category);
        }
        return filtered;
    }

    friend ostream& operator<<(ostream& out, const Store& s) {
        for (int i = 0; i < s.size; ++i) {
            out << s.products[i];
        }
        return out;
    }
};


void wtf() {
    ofstream fout("input.txt");
    string line;
    while (getline(std::cin, line)) {
        if (line == "----") {
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

    Store s;


    ifstream fin("input.txt");
    Product p;
    while (fin.peek() != EOF) {
        fin >> p;
        s += p;
    }
    fin.close();



    string category;
    cin >> category;



    ofstream fout1("output1.txt");
    fout1 << s;
    fout1.close();

    try {
        Store filtered = s.fromCategory(category);
        ofstream fout2("output2.txt");
        fout2 << filtered;
        fout2.close();
    } catch (NoProductFoundException& e) {
        ofstream fout2("output2.txt");
        fout2 << e.what() << endl;
        fout2.close();
    }



    cout << "All products:" << endl;
    rff("output1.txt");
    cout << "Products from category " << category << ": " << endl;
    rff("output2.txt");

    return 0;
}
