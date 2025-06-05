#include <iostream>
#include <fstream>
#include <sstream>
#include <windows.h>
#include <iomanip>

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

void addItem(Bill &b){
    bool close = false;
    while(!close) {
        int choice;
        
        cout << "\n\t1. Add Item" << endl;
        cout << "\t2. Close" << endl;
        cout << "\tEnter Choice: ";
        cin >> choice;

        if(choice == 1) {
            system("cls");
            string item;
            int rate, quant;

            cout << "\tEnter Item Name: ";
            cin.ignore();
            getline(cin, item);
            b.setItem(item);

            cout << "\tEnter Rate of Item: ";
            cin >> rate;
            b.setRate(rate);

            cout << "\tEnter Quantity of Item: ";
            cin >> quant;
            b.setQuant(quant);

            ofstream out("Bill.txt", ios::app);
            if(!out) {
                cout << "\tError: Could not open file." << endl;
            } else {
                out << b.getItem() << ":" << b.getRate() << ":" << b.getQuant() << endl;
                out.close();
                cout << "\tItem Added Successfully." << endl;
            }
            Sleep(1500);
        }
        else if(choice == 2) {
            system("cls");
            close = true;
            cout << "\tClosing..." << endl;
            Sleep(1500);
        }
        else {
            cout << "\tInvalid choice! Please select 1 or 2." << endl;
            Sleep(1500);
        }
        system("cls");
    }
}

void printBill(){
    system("cls");
    int totalAmount = 0;
    bool close = false;

    while(!close) {
        system("cls");
        int choice;
        cout << "\n\t1. Add Item to Bill" << endl;
        cout << "\t2. Close Session" << endl;
        cout << "\tEnter Choice: ";
        cin >> choice;

        if(choice == 1) {
            string item;
            int quant;
            cout << "\tEnter Item Name: ";
            cin.ignore();
            getline(cin, item);
            cout << "\tEnter Quantity: ";
            cin >> quant;

            ifstream in("Bill.txt");
            ofstream out("Bill_Temp.txt");

            if(!in || !out) {
                cout << "\tError: Could not open files." << endl;
                continue;
            }

            string line;
            bool found = false;

            while(getline(in, line)) {
                stringstream ss(line);
                string itemName;
                int itemRate, itemQuant;
                
                getline(ss, itemName, ':');
                ss >> itemRate;
                ss.ignore();
                ss >> itemQuant;

                if(item == itemName) {
                    found = true;
                    if(quant <= itemQuant) {
                        int amount = itemRate * quant;
                        cout << "\n\tItem | Rate | Quantity | Amount" << endl;
                        cout << "\t" << setw(10) << itemName << " | " 
                             << setw(4) << itemRate << " | " 
                             << setw(8) << quant << " | " 
                             << setw(6) << amount << endl;
                        totalAmount += amount;
                        itemQuant -= quant;
                        
                        out << itemName << ":" << itemRate << ":" << itemQuant << endl;
                    } else {
                        cout << "\tSorry, " << itemName << " is not available in sufficient quantity." << endl;
                        out << line << endl;
                    }
                } else {
                    out << line << endl;
                }
            }

            if(!found) {
                cout << "\tItem not available." << endl;
            }

            out.close();
            in.close();
            remove("Bill.txt");
            rename("Bill_Temp.txt", "Bill.txt");
            Sleep(1500);
        }
        else if(choice == 2) {
            close = true;
            cout << "\tCalculating Total Amount..." << endl;
            Sleep(1000);
        }
    }
    
    system("cls");
    cout << "\n\n\t=================================" << endl;
    cout << "\tTotal Bill Amount: " << totalAmount << endl;
    cout << "\t=================================" << endl;
    cout << "\n\tThank you for shopping with us!" << endl;
    Sleep(3000);
}

int main() {
    Bill b;
    bool exit = false;

    while(!exit) {
        system("cls");
        int val;

        cout << "\n\tWelcome to Supermarket Billing System" << endl;
        cout << "\t*************************************" << endl;
        cout << "\t1. Add Item" << endl;
        cout << "\t2. Print Bill" << endl;
        cout << "\t3. Exit" << endl;
        cout << "\tEnter Choice: ";
        cin >> val;

        if(val == 1) {
            system("cls");
            addItem(b);
        }
        else if(val == 2) {
            printBill();
        }
        else if(val == 3) {
            system("cls");
            exit = true;
            cout << "\tThank you for using our system!" << endl;
            Sleep(3000);
        }
        else {
            cout << "\tInvalid choice! Please try again." << endl;
            Sleep(1500);
        }
    }
    return 0;
}