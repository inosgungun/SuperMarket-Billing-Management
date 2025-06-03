#include <iostream>
#include <fstream>
#include <sstream>
#include <windows.h>

using namespace std;

class Bill{
private:
    string Item;
    int Rate;
    int Quantity;

public:
    Bill():Item(""), Rate(0), Quantity(0) {

    }

    void setItem(string item){
        Item = item;
    }

    void setRate(int rate){
        Rate = rate;
    }

    void setQuant(int quant){
        Quantity = quant;
    }

    string getItem(){
        return Item;
    }

    int getRate(){
        return Rate;
    }

    int getQuant(){
        return Quantity;
    }
};

void addItem(Bill b){
    bool close = false;
    while(!close) {
        int choice;
        
        cout<<"\t1.Add."<<endl;
        cout<<"\t2.close."<<endl;
        cout<<"\tEnter Choice: ";
        cin>>choice;

        if(choice == 1){
            system("cls");
            string item;
            int rate, quant;

            cout<<"\tEnter Item Name: ";
            cin>>item;
            b.setItem(item);

            cout<<"\tEnter Rate of Item: ";
            cin>>rate;
            b.setRate(rate);

            cout<<"\tEnter Quantity of Item: ";
            cin>>quant;
            b.setQuant(quant);

            ofstream out("Bill.txt", ios::app);

            if(!out) {
                cout <<"\tError: Could not open file."<<endl;
            } else {
                out<<"\t"<<b.getItem()<<" : "<<b.getRate()<<" : "<<b.getQuant()<<endl;  
            }
            out.close();
            cout<<"\tItem Added Successfully."<<endl;
            Sleep(3000);
        }

        else if(choice == 2){
            system("cls");
            close = true;
            cout<<"\tClosing..."<<endl;
            Sleep(3000);
        }
    }
}

void printBill(){
    system("cls");
    int count = 0;
    bool close = false;

    while(!close){
        system("cls");
        int choice;
        cout<<"\t1.Add Bill."<<endl;
        cout<<"\t2.Close Session."<<endl;
        cout<<"\tEnter Choice: ";
        cin>>choice;

        if(choice == 1){
            string item;
            int quant;
            cout<<"\tEnter Item:";
            cin>>item;
            cout<<"\tEnter Quantity: ";
            cin>>quant;

            ifstream in("Bill.txt");
            ofstream out("Bill Temp.txt");

            string line;
            bool found = false;

            while(getline(in, line)){
                stringstream ss;
                ss<<line;
                string itemName;
                int itemRate, itemQuant;
                char delimiter;
                ss>>itemName>>delimiter>>itemRate>>delimiter>>itemQuant;

                if(item == itemName){
                    found = true;
                    if(quant <= itemQuant){
                        int amount = itemRate * quant;
                        cout<<"\t Item | Rate | Quantity | Amount"<<endl;
                        cout<<"\t"<<itemName<<"\t "<<itemRate<<"\t "<<quant<<"\t "<<amount<<endl;
                        count += amount;
                        itemQuant -= quant;
                        
                        out<<"\t"<<itemName<<" : "<<itemRate<<" : "<<itemQuant<<endl;
                    } 
                    else {
                        cout<<"\tSorry, "<<itemName<<" is not available in sufficient quantity."<<endl;
                    }
                } 
                else {
                    out<<line<<endl;
                }
            }
            if(!found) {
                cout<<"\tItem not available."<<endl;
            }

            out.close();
            in.close();
            remove("Bill.txt");
            rename("Bill Temp.txt", "Bill.txt");
        }
        else if(choice == 2){
            close = true;
            cout<<"\tCounting Total Amount..."<<endl;
        }
        Sleep(3000);
    }
    system("cls");
    cout<<endl<<endl;
    cout<<"\tTotal Bill ---------------- : "<<count<<endl<<endl;
    cout<<"\tThank you for shopping with us!"<<endl;
    Sleep(5000);
}

int main() {
    Bill b;
    bool exit = false;

    while(!exit){
        system("cls");
        int val;

        cout<<"\tWelcome to Supermarket Billing System"<<endl;
        cout<<"\t*************************************"<<endl;
        cout<<"\t\t1.Add Item."<<endl;
        cout<<"\t\t2.Print Bill."<<endl;
        cout<<"\t\t3.Exit."<<endl;
        cout<<"\t\tEnter Choice: "<<endl;

        cin>>val;

        if(val==1){
            system("cls");
            addItem(b);
            Sleep(3000);
        }

        else if(val == 2){
            printBill();
            Sleep(3000);
        }
        
        else if(val == 3){
            system("cls");
            exit = true;
            cout<<"\tGood Luck!"<<endl;
            Sleep(3000);
        }
    }

}