За потребите на еден приватен банкар кој тргува со акции, потребно е да се направи модул за менаџирање со клиентски портфолија.

За таа цел, треба да се креира класа StockRecord. Класата треба да содржи:

ID, кој означува која е акцијата која се тргува (низа од 12 знаци)
Име на компанијата која ја издала акцијата (низа од 50 знаци)
Цена според која се купени акциите (реален број)
Моментална цена на акцијата (реален број)
Број на акции кои се купени (цел број)
За класата да се дефинираат потребните конструктори и set метода за моменталната цена со потпис void setNewPrice(double c) (10 поени). 
Исто така, да се имплементираат методи double value() и double profit(). Првата треба да ја пресметува вредноста на акциите, а втората треба да го пресметува моменталниот профит од акциите. Пресметката се врши на следниот начин (5 поени):

Вредност = број на акции * моментална цена 
Профит = број на акции * (моментална цена - цена по која се купени)
Дополнително, да се преоптовари операторот << за печатење на објектот во следниот формат (5 поени): Компанија БројНаАкции КуповнаЦена МоменталнаЦена Профит

Да се креира класа Client која содржи:

Име и презиме на клиентот (низа од 60 знаци)
ID на сметка (цел број)
Низа од компании кои ги поседува клиентот (динамичка низа од објекти од класата StockRecord)
Број на објекти во низата (цел број)
За класата Client да се дефинираат потребните конструктори, деструктор и метода double totalValue() која ќе ја пресметува моменталната вредност на акциите кои ги поседува клиентот. Таа се пресметува како збир од вредноста на сите акции од секоја компанија од кои е составено клиентското портфолио (15 поени). Дополнително, за класата да се преоптоварат операторите:

+= за купување на нова компанија во портфолиото (додавање на нов објект од класата StockRecord во низата со компании) (10 поени)

<< за печатење на информации за портфолиото на клиентот така што во првиот ред ќе бидат прикажани ID на сметката и моменталната вредност на портфолиото одделени со празно место, а во секој нареден ред ќе бидат прикажани компаниите од кои е составено портфолиото, секоја во посебен ред (5 поени)

Комплетна функционанлост (5 поени)




#include<iostream>
#include<cstring>
using namespace std;

class StockRecord{
private:
    char id[12];
    char imenakompanija[50];
    double cena;
    double momcena;
    int brojnakacii;
public:
    StockRecord(){}
    StockRecord(char *id,char *imenakompanija,double cena,double momcena,int brojnakacii){
        strcpy(this->id,id);
        strcpy(this->imenakompanija,imenakompanija);
        this->cena=cena;
        this->momcena=momcena;
        this->brojnakacii=brojnakacii;
    }
    StockRecord(const StockRecord &other){
        strcpy(this->id,other.id);
        strcpy(this->imenakompanija,other.imenakompanija);
        this->cena=other.cena;
        this->momcena=other.momcena;
        this->brojnakacii=other.brojnakacii;
    }
    void setNewPrice(double c){
        momcena=c;
    }
    void operator-=(int decrease) {
        brojnakacii -= decrease;
    }
    double const value()const{
        return brojnakacii * momcena;
    }
    double profit()const{
        return brojnakacii *(momcena-cena);
    }
    friend ostream& operator <<(ostream& os,const StockRecord& s){
        os<<s.imenakompanija<<" "<<s.value()<<" "<<s.cena<<" "<<s.momcena<<" "<<s.profit();
        return  os;
    }
    friend class Client;

};
class Client{
private:
    char clientName[60];
    int id;
    StockRecord *niza;
    int brojnaobjekti;
public:
    Client(char *clientName="",int id=0){
        strcpy(this->clientName,clientName);
        this->id=id;
        brojnaobjekti=0;
        niza=new StockRecord[brojnaobjekti+1];
    }
    Client(const Client& other) {
        strcpy(this->clientName, other.clientName);
        this->id = other.id;
        brojnaobjekti = other.brojnaobjekti;
        niza = new StockRecord[brojnaobjekti];
        for (int i = 0; i < brojnaobjekti; ++i) {
            niza[i] = other.niza[i];
        }
    }

    Client& operator=(const Client& other) {
        if (this != &other) {
            strcpy(this->clientName, other.clientName);
            this->id = other.id;
            brojnaobjekti = other.brojnaobjekti;
            delete[] niza;
            niza = new StockRecord[brojnaobjekti];
            for (int i = 0; i < brojnaobjekti; ++i) {
                niza[i] = other.niza[i];
            }
        }
        return *this;
    }

    Client& operator+=( StockRecord& newStock) {
        StockRecord* temp = new StockRecord[brojnaobjekti + 1];
        for (int i = 0; i < brojnaobjekti; ++i) {
            temp[i] = niza[i];
        }
        temp[brojnaobjekti] = newStock;
        delete[] niza;
        niza = temp;
        brojnaobjekti++;
        return *this;
    }


    double totalValue() const{
        double t=0;
        for(int i=0;i<brojnaobjekti;i++){
            t+=niza[i].value();
        }
        return t;
    }

    friend ostream &operator<<(ostream &os, const Client &client) {
        os<<client.id<<" "<<client.totalValue()<<endl;
        for(int i=0;i<client.brojnaobjekti;i++) {
            os << client.niza[i] << endl;
        }
        return os;
    }


};



int main(){

    int test;
    cin >> test;

    if(test == 1){
        double price;
        cout << "=====TEST NA KLASATA StockRecord=====" << endl;
        StockRecord sr("1", "Microsoft", 60.0, 100.0, 10); // Променив го третиот аргумент во 100.0 и додадов последен аргумент 10
        cout << "Konstruktor OK" << endl;
        cin >> price;
        sr.setNewPrice(price);
        cout << "SET metoda OK" << endl;
    }
    else if(test == 2){
        cout << "=====TEST NA METODITE I OPERATOR << OD KLASATA StockRecord=====" << endl;
        char id[12], company[50];
        double price, newPrice;
        int n, shares;
        cin >> n;
        for(int i = 0; i < n; ++i){
            cin >> id;
            cin >> company;
            cin >> price;
            cin >> newPrice;
            cin >> shares;
            StockRecord sr(id, company, price, newPrice, shares); // Променив го третиот аргумент во newPrice
            sr.setNewPrice(newPrice);
            sr -= shares;
            cout << sr.value() << endl;
            cout << sr;
        }
    }
    else if(test == 3){
        cout << "=====TEST NA KLASATA Client=====" << endl;
        char companyID[12], companyName[50], clientName[50];
        int clientID, n, shares;
        double oldPrice, newPrice;
        bool flag = true;
        cin >> clientName;
        cin >> clientID;
        cin >> n;
        Client c(clientName, clientID);
        cout << "Konstruktor OK" << endl;
        for(int i = 0; i < n; ++i){
            cin >> companyID;
            cin >> companyName;
            cin >> oldPrice;
            cin >> newPrice;
            cin >> shares;
            StockRecord sr(companyID, companyName, oldPrice, newPrice, shares); // Променив го третиот аргумент во newPrice
            sr.setNewPrice(newPrice);
            c += sr;
            if(flag){
                cout << "Operator += OK" << endl;
                flag = false;
            }
        }
        cout << c;
        cout << "Operator << OK" << endl;
    }
    return 0;
}
