За потребите на еден приватен банкар кој тргува со акции, потребно е да се направи модул за менаџирање со клиентски портфолија.

За таа цел, треба да се креира класа StockRecord. Класата треба да содржи:

ID, кој означува која е акцијата која се тргува (низа од 12 знаци)
Име на компанијата која ја издала акцијата (низа од 50 знаци)
Цена според која се купени акциите (реален број)
Моментална цена на акцијата (реален број)
Број на акции кои се купени (цел број)
За класата да се дефинираат потребните конструктори и set метода за моменталната цена со потпис void setNewPrice(double c) (10 поени). Исто така, да се имплементираат методи double value() и double profit(). Првата треба да ја пресметува вредноста на акциите, а втората треба да го пресметува моменталниот профит од акциите. Пресметката се врши на следниот начин (5 поени):

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

class StockRecord {
	char id[13];
	char name[51];
	double buy_actions;
	double now_cena;
	int num_action;

public:
	StockRecord() {}

	StockRecord(char *id, char *name, double buy_actions,  int num_action) {
		strcpy(this->id, id);
		strcpy(this->name, name);
		this->buy_actions = buy_actions;
		
		this->num_action = num_action;
	}

	void setNewPrice(double c) {
		this->now_cena = c;
	}

	double value() {
		return num_action * now_cena;
	}

	double profit() {
		return num_action * (now_cena - buy_actions);
	}

	friend ostream &operator<<(ostream &o, StockRecord &st) {
		o << st.name << " " << st.num_action << " " << st.buy_actions << " "
		  << st.now_cena << " " << st.profit() << endl;
		return o;
	}
};



	class Client {
    char name_surrname[62];
    int ID;
    StockRecord *cliente;
    int num;

public:

    Client(char *name_surrname, int ID) {
        strcpy(this->name_surrname, name_surrname);
        this->ID = ID;
        this->num = 0;
        this->cliente = nullptr;
    }


    Client(const Client &c) {
        strcpy(this->name_surrname, c.name_surrname);
        this->ID = c.ID;
        this->num = c.num;
        this->cliente = new StockRecord[num];

        for (int i = 0; i < num; i++) {
            this->cliente[i] = c.cliente[i];
        }
    }


    Client &operator=(const Client &ce) {
        if (this == &ce) return *this;


        delete[] this->cliente;

        strcpy(this->name_surrname, ce.name_surrname);
        this->ID = ce.ID;
        this->num = ce.num;
        this->cliente = new StockRecord[num];

        for (int i = 0; i < num; i++) {
            this->cliente[i] = ce.cliente[i];
        }

        return *this;
    }


    Client &operator+=(const StockRecord &newStock) {
        StockRecord *temp = new StockRecord[num + 1];

        for (int i = 0; i < num; i++) {
            temp[i] = cliente[i];
        }

        temp[num] = newStock;
        delete[] cliente;
        cliente = temp;
        num++;

        return *this;
    }


		double totalValue() const {
    	double sum = 0;
    	for (int i = 0; i < num; i++) {
    		sum += cliente[i].value();
    	}
    	return sum;
    }

		friend ostream &operator<<(ostream &o, const Client &c) {
    	o << c.ID << " " << c.totalValue() << endl;
    	for (int i = 0; i < c.num; i++) {
    		o << c.cliente[i];
    	}
    	return o;
    }


    ~Client() {
        delete[] cliente;
    }
};




// ne menuvaj vo main-ot

int main(){

	int test;
	cin >> test;

	if(test == 1){
		double price;
		cout << "=====TEST NA KLASATA StockRecord=====" << endl;
		StockRecord sr("1", "Microsoft", 60.0, 100);
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
			StockRecord sr(id, company, price, shares);
			sr.setNewPrice(newPrice);
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
			StockRecord sr(companyID, companyName, oldPrice, shares);
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
