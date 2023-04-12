#include <iostream>
#include <string>
using namespace std;
//Function headings
bool authenticate(string, int);
bool changePin(string*);
void checkBalance(int, string);
void exitProgram();
bool isNumeric(string);
void sendMoney(double*, string );
bool checkNumber(string);
bool isNumeric(string);
void toContinue();

//To hold the user pin, default is 0000
string pin = "0000";
//use balance
double balance = 1000;
//Control program running execution
bool run = true;



int main() {
int choice = 0;

while(run) {
cout << endl;
 cout << "1 \t Send Money\n2 \t Check Balance \n3 \t Change Pin\n4 \t Exit" << endl;
 cin >> choice;
 switch(choice) {
    case 1:
        sendMoney(&balance, pin);
        break;
    case 2:
        checkBalance(balance, pin);
        break;
    case 3:
        if (changePin(&pin)) {
            cout << "Pin changed successfully"<<endl;
        } else {
            cout << "Operation aborted successfully"<<endl;
        }
        break;
    case 4:
        exitProgram();
    default:
        break;
 }

}

}



void exitProgram() {
    /*
    exitProgram: Quit the program
    */
 run = false;
}

void toContinue() {
    /*
    toContinue: Ask if the use want to perfrom another operation after an operation is done.
    return: void;
    */
    cout << "Would you like to perform another operation \n1 \t Yes\n2  \t No Quit the program" << endl;
    int choice = 0; 
    cin >> choice;
    if (choice == 2){
        exitProgram();
    }
}
bool authenticate(string savedpin, int tries=3) {
    /*
    checkPin : Verifies users pin 
    param:
        savepin: user saved pin
        pin: pin to compare to savepin
    return:
      1. true : if user pin is verify
      2. flase: if user fails to enter correct pin 3 times
    */
    string pin;
    cout << "Enter pin :";
    cin >> pin;
    if (pin == savedpin)
        return true;
    while (tries > 1) {
        cout << "Wrong pin. enter pin again. tries left " << --tries << endl;
        cin >> pin;
    if (pin == savedpin)
        return true;
    }
    return false;
}
void checkBalance(int balance, string savedpin) {
    /*
    checkBalance : Display user balance
    param:
        balance : User balance to display
        pin : user saved pin
    return:
        returns void
    */
    bool verify = authenticate(savedpin);
    if (verify) {
     cout<<"Your balance is "<< balance << endl;
     toContinue();
    }
    else {
        cout << "Limit reached";
        exitProgram();
    }
    
}
bool changePin(string* savedpin) {
    /*
    changepin : Changes user pin
    param:
        pin : reference to user pin
    return:
      1. true : if pin was change succesfully, false otherwise
    */
    int option;
    cout<< "Are you sure you want to change pin.\n1 \t Yes \n2 \t No"<<endl;
    cin >> option;
    if (option == 1){
        string oldpin, newpin;
        cout << "Verify by entering old pin" << endl;
        bool verify = authenticate(*savedpin);
        if (verify)
        {
        cout << "Enter new pin: "<<endl;
        cin >> newpin;
        *savedpin = newpin;
        return true;
        }
        else {
            cout << "Limit reached" << endl;
            exitProgram();
        }    
    }
    return false;
}

void sendMoney(double *balance, string savedpin){
    string number;
    string confirm_number;
    string ref_id;
    double amount;
     cout<<"Enter mobile Number"<<endl;
     cin >> number;
     while ( !checkNumber(number) ) {
        cout << "Invalid number try number again"<<endl;
        cin >> number;
     }
    cout << "confirm number" << endl;
    cin >> confirm_number;

    if (number != confirm_number) {
        cout << "Numbers mismatched";
        return;
    }
    cout << "Enter Amount "<<endl;
    cin >> amount;
    while (amount <= 0) {
         cout << "cant send 0 or negative amount, enter amount again " << endl;
         cin >>amount; 
    }
    if(amount > *balance) {
    cout << "Not enough funds to perform transaction"<<endl<<endl;
        return;
    }
    cout << "Enter reference id"<<endl;
    cin >> ref_id;
    cout << "You are about to send "<<amount<<" to "<<number 
    << " with reference id " << ref_id << "\nEnter pin to to confirm\n";
    bool verify = authenticate(savedpin);
    if (verify){
        *balance -= amount;
        cout << "Transaction Successful"<<endl<<endl;
        toContinue();
    }
    else {
        cout << "Limit reached"<<endl;
        exitProgram();
        }
}

bool checkNumber(string number) {
    /*
    CheckNumber : returns true if a number is 10 digits
    param:
        number : number to check condition
    return:
        true if number meet requirement else false;
    */
    if (number.length() != 10 || !isNumeric(number))
        return false;
    return true;  
}

bool isNumeric(string value) {
    /*
    isNumberic: checks if a string contains only numbers by using ascii valu comparison
    param:
        value: String to check condition
    return:
        true: if string contains only numbers false other wise
    */
    for(int i = 0; i < value.length(); i++) {
        if ( !(value[i] >= '0' && value[i] <= '9') )
            return false;
    }
    return true;
}
