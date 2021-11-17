//
//  main.cpp
//  assignment
//
//  Created by Ellie Kim on 1/11/21.
//

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//Register Function
void parentRegister(){
    string username, password;
    string fullName, gender, dob, contact, child, room, visa, expiry;
    cout << "Enter your username: ";
    cin >> username;
    cout << "Enter your password: ";
    cin >> password;
    
    ofstream file (username , ios::app);
    cin.ignore();
    cout << "Enter your personal details:\n";
    cout << "Full Name: ";
    getline(cin,fullName);
    cout << "Gender: ";
    cin >> gender;
    cout << "Date of Birth: ";
    cin >> dob;
    cin.ignore();
    cout << "Contact Number: ";
    getline (cin, contact);
    cout << "Child Name: ";
    getline( cin, child);
    cout << "Child room number: ";
    cin >> room;
    cin.ignore();
    cout << "Visa card number: ";
    getline (cin, visa);
    cout << "Visa card date of expiry: ";
    getline (cin, expiry);

    file << username << endl;
    file << password << endl;
    file << fullName << endl;
    file << contact << endl;
    file << gender << " " << dob << " " << child << " " << room << " " << visa << " " << expiry << endl;

    file.close();

    cout << "\nSuccessfully registered. Please login\n\n";
}

void staffRegister(){
    string username, password;
    string fullName, gender, dob, contact, child, room, visa, expiry;
    cout << "Enter your username: ";
    cin >> username;
    cout << "Enter your password: ";
    cin >> password;
    
    ofstream file (username , ios::app);
    cin.ignore();
    cout << "Enter your personal details:\n";
    cout << "Full Name: ";
    getline(cin,fullName);
    cout << "Gender: ";
    cin >> gender;
    cout << "Date of Birth: ";
    cin >> dob;
    cin.ignore();
    cout << "Visa card number: ";
    getline (cin, visa);
    cout << "Visa card date of expiry: ";
    getline (cin, expiry);

    file << username << endl;
    file << password << endl;
    file << fullName << endl;
    file << gender << endl;
    file << dob << " " << visa << " " << expiry << endl;

    file.close();

    cout << "\nSuccessfully registered. Please login\n\n";
}

//Login Function
bool access = false;
void login(string *userAttempt) {
    string passAttempt;

    ifstream loginFile (*userAttempt);
    string username, password;
    int attempt =0;
    if(loginFile.is_open()){
        getline(loginFile, username);
        getline(loginFile,password);

        while (attempt<3){
            cout << "Password: ";
            cin >> passAttempt;
            if (password == passAttempt){
                cout << "\nsuccessfully logged in\n\n";
                access = true;
                break;
                
            }else if (attempt <2){
                cout << "Invalid password. Try again.\n";
                attempt++;
            }else{
                cout << "Too many failed login attempts. Please try after 30 minutes.\n";
                attempt++;
            }
        }
    }else {
        cout << "Invalid username. Going back to the main menu. \n";
        
    }
    loginFile.close();
}

//Parent & Staff Screen Functions

void weeklyMenu(){
    ifstream menuFile("weeklyMenu.txt");
    
    if(!menuFile){
        cout << "\nNo data found...\n";
    }
    
    string line;
    while (getline(menuFile,line)){
        cout << line << endl;
    }
    menuFile.close();
}

void complaint(){
    string fullName, date, item, complaint, contact, email, action;
    ofstream complainFile("complaint.txt", ios::app);
    int complaintNum = rand()%10000+1;
    cin.ignore();
    cout << "Full name: ";
    getline(cin, fullName);
    cout << "Date of order: ";
    cin >> date;
    cin.ignore();
    cout << "Item ordered: ";
    getline(cin, item);
    cout << "Complaint description: ";
    getline (cin,complaint);
    cout << "Contact number: ";
    cin >> contact;
    cout <<"Email address: ";
    cin >> email;
    action = "pending";
    
    complainFile << "Complaint number : " << complaintNum << endl;
    complainFile << "Full name: " << fullName << endl;
    complainFile << "Date of order: " << date << endl;
    complainFile << "Item ordered: " << item << endl;
    complainFile << "Complaint description: " << complaint << endl;
    complainFile << "Contact number: " << contact << endl;
    complainFile << "Email address: " << email <<endl;
    complainFile << "\n\n";
    
    cout << "\n******************************\n";
    cout << "Complaint number : " << complaintNum << endl;
    cout << "Full name: " << fullName << endl;
    cout << "Date of order: " << date << endl;
    cout << "Item ordered: " << item << endl;
    cout << "Complaint description: " << complaint << endl;
    cout << "Contact number: " << contact << endl;
    cout << "Email address: " << email <<endl;
    cout << "Action status: " << action << endl;
    cout << "\n******************************\n";
    
    complainFile.close();

}

void orderParent(string *user){
    string date, item, quantity, price, child, classroom, paymentStatus, issuedStatus, dietary;
    ofstream orderFile("orderFile.txt",ios::app);
    int orderNum = rand()%10000+1;
    cout << "Order date (dd/mm/yy): ";
    cin >> date;
    cin.ignore();
    cout << "Item name: ";
    getline(cin,item);
    cout << "quantity(small, large) : ";
    cin >> quantity;
    cout << "price: $";
    cin >> price;
    cin.ignore();
    cout << "Child name: ";
    getline(cin,child);
    cout << "Classroom number: ";
    cin >> classroom;
    cin.ignore();
    cout << "Dietary preference: ";
    getline(cin,dietary);
    issuedStatus = "pending";
    
    orderFile << orderNum << endl;
    orderFile << date << endl;
    orderFile << item << endl;
    orderFile << quantity << endl;
    orderFile << price << endl;
    orderFile << child << endl;
    orderFile << classroom << endl;
    orderFile << dietary << endl;
    
    string yn;
    cout << "Proceed payment ? (y/n)";
    cin >> yn;
    if (yn == "y" || yn == "Y"){
        paymentStatus = "Paid";
        orderFile << paymentStatus <<endl;
        orderFile << *user << endl;
        orderFile.close();
        
        cout << "\n----------------------------------------\n";
        cout << "                 BILL                    \n";
        cout << "Order number: "<< orderNum << endl;
        cout << "Order date: " << date << endl;
        cout << "Item name : " << item << endl;
        cout << "Price : $" << price << endl;
        cout << "Student name : " <<child << endl;
        cout << "Student room number: " << classroom << endl;
        cout << "Dietary preferance: " << dietary << endl;
        cout << "Payment status: " << paymentStatus <<endl;
        cout << "Issued status: " << issuedStatus << endl;
        cout << "\n---------------------------------------\n";
        
        
    }else {
        paymentStatus = "NP";
        cout << "\n No payment received\n";
        orderFile << paymentStatus <<endl;
        orderFile << *user << endl;
        
        ofstream pending("pending.txt",ios::app);
        pending << date << endl;
        pending << item << endl;
        pending << price << endl;
        pending << *user << endl;
        pending.close();

    }
}

void orderStaff(string *user){
    string date, item, quantity, price, delivery, paymentStatus, issuedStatus, dietary;
    ofstream orderFile("orderFile.txt",ios::app);
    int orderNum = rand()%10000+1;
    cout << "Order date (dd/mm/yy): ";
    cin >> date;
    cin.ignore();
    cout << "Item name: ";
    getline(cin,item);
    cout << "quantity(small, large) : ";
    cin >> quantity;
    cout << "price: $";
    cin >> price;
    cin.ignore();
    cout << "Delivery address: ";
    cin >> delivery;
    cout << "Dietary preference: ";
    getline(cin,dietary);
    issuedStatus = "pending";

    orderFile << orderNum << endl;
    orderFile << date << endl;
    orderFile << item << endl;
    orderFile << quantity << endl;
    orderFile << price << endl;
    orderFile << "Staff" <<endl;
    orderFile << delivery << endl;
    orderFile << dietary << endl;
    
    string yn;
    cout << "Proceed payment ? (y/n)";
    cin >> yn;
    if (yn == "y" || yn == "Y"){
        paymentStatus = "Paid";
        orderFile << paymentStatus <<endl;
        orderFile << *user << endl;
        orderFile.close();
        
        cout << "\n----------------------------------------\n";
        cout << "              BILL (Staff)                 \n";
        cout << "Order number: "<< orderNum << endl;
        cout << "Order date: " << date << endl;
        cout << "Item name : " << item << endl;
        cout << "Price : $" << price << endl;
        cout << "Delivery Address : " << delivery << endl;
        cout << "Dietary preferance: " << dietary << endl;
        cout << "Payment status: " << paymentStatus <<endl;
        cout << "Issued status: " << issuedStatus << endl;
        cout << "\n---------------------------------------\n";
        
        
    }else {
        paymentStatus = "NP";
        cout << "\n No payment received\n";
        orderFile << paymentStatus <<endl;
        orderFile << *user << endl;
        
        ofstream pending("pending.txt",ios::app);
        pending << date << endl;
        pending << item << endl;
        pending << price << endl;
        pending << *user << endl;
        pending.close();

    }
}


//Admin Screen Functions

void menuUpdate(){
    ofstream menuFile("weeklyMenu.txt", ios::out);
    string startDate;
    cout << "Enter Start date: ";
    cin >> startDate;
    string endDate;
    cout << "Enter End date: ";
    cin >> endDate;
    int menuNum;
    cout << "How many menu options? ";
    cin >> menuNum;
    string menu[menuNum];
    string priceSmall[menuNum];
    string priceLarge[menuNum];
    
    for (int i =0; i <menuNum; i ++){
        cin.ignore();
        cout << "Enter menu "<< i+1 << " : ";
        getline(cin, menu[i]);
        cout << "Enter price (small) : $";
        cin >> priceSmall[i];
        cout << "Enter price (large) : $";
        cin >> priceLarge[i];
    }
    
    menuFile << "Menu from " << startDate << " to " << endDate << "\n\n";
    menuFile << "\t\t\t Small    Large\n";
    for (int i =0; i<menuNum; i++){
        menuFile <<  i+1 << ". " << menu[i] << "\t  $" << priceSmall[i] << "   $" << priceLarge[i] <<endl;
    }
    
    cout << "\nSuccessfully updated.\n\n";
}

void dailyOrder(){
    string date;
    ifstream file("orderFile.txt");
    if(!file){
        cout << "--------------------------------------\n\n";
        cout << "\t\tNo data found...\n";
        cout << "\n--------------------------------------\n";
    }
    if(file.is_open()){
        cout << "Enter the date (dd/mm/yy) : ";
        cin >> date;
    
        cout << "--------------------------------------\n\n";
        cout << "Daily order report - " << date << "\n\n";
        string line;
        int count = 1;
        while (getline(file,line)){
            if (line == date){
                string s1,s2,s3;
                getline(file,s1);
                getline(file,s2);
                getline(file,s3);
                cout << count << ". " << s1 << " " << s2 << " $" << s3 << endl;
                count ++;
            }
        }
        cout << "\nTotal " << count - 1 << " Orders\n";
        cout << "\n--------------------------------------\n\n";
    }
}

void salesReport(){
    cout << "\n----------------------------------\n";
    cout << "\t\t Sales Report\n";
    ifstream file("orderFile.txt");
    if(file.is_open()){
        int count = 0;
        int sum = 0;
        string s[10];
        for(int i=0; i<10;i ++){
            getline(file,s[i]);
        }
        while (!file.eof()){
            cout << "Date: " << s[1] << endl;
            cout << "Item: " << s[2] << endl;
            cout << "Price: " << s[4] << endl;
            cout <<"----------------------------------\n\n";
            count++;
            sum += stoi(s[4]);
            for(int i=0; i<10;i ++){
                getline(file,s[i]);
            }
        }
        cout << "Total order: " << count <<endl;
        cout << "Amount Received: $" << sum <<"\n\n";
        }else{
        cout << "\nNo data found...\n";
        cout << "\n----------------------------------\n";
        }
}

void pending(){
    ifstream file("pending.txt");
    if(file.is_open()){
        string line;
        string info[4];
        cout << "\t\tPending Payment:\n";
        cout << "------------------------------------\n";
        for (int i =0; i<4; i++){
            getline(file,info[i]);
        }
        while(!file.eof()){
                cout << "Date : " << info[0] << endl;
                cout << "Item : " << info[1] << endl;
                cout << "Price : " << info[2] << endl;
                ifstream userfile(info[3]);
                string user,pass,fullName,contact;
                getline(userfile,user);
                getline(userfile,pass);
                getline(userfile,fullName);
                getline(userfile,contact);
                cout << "Full name: " << fullName << endl;
                cout << "Contact: " << contact << endl;
                for (int i =0; i<4; i++){
                    getline(file,info[i]);
                }
                userfile.close();
                cout << "------------------------------------\n\n";
                }
        file.close();
    }else{
        cout << "\nNo data found...\n\n";
    }
}

void weeklyComplaint(){
    ifstream weeklyComplaint ("complaint.txt");
    if(!weeklyComplaint){
        cout << "\nNo data found...\n\n";
    }
    string line;
    cout << "\n------------------------------\n";
        while (getline(weeklyComplaint,line)){
        cout << line << endl;
        }
    cout << "-------------------------------\n";
    weeklyComplaint.close();
}

int main(int argc, const char * argv[]) {
    
    srand(time(NULL));

    instruction:
    cout << "\n-----------------------------\n";
    cout << "School Lunch Order System\n";
    cout << "-----------------------------\n";
    cout << "1. Weekly Menu\n";
    cout << "2. Discounts for bulk booking\n";
    cout << "3. Contacts details and office locations\n";
    cout << "4. Register\n";
    cout << "5. Login\n";
    cout << "6. Exit\n";
    int input;
    cout << "\nSelect an option: ";
    cin >> input;
    
    int ps;
    string userAttempt;
    string *ptr_user = &userAttempt;

    switch(input){
        case 1 :
            weeklyMenu();
            cout << "\nPress any key to go back: ";
            cin.ignore();
            cin.get();
            goto instruction;
        case 2 :
            cout << "discount\n";
            cout << "Press any key to go back: ";
            cin.ignore();
            cin.get();
            goto instruction;
        case 3 :
            cout << "business\n";
            cout << "Press any key to go back: ";
            cin.ignore();
            cin.get();
            goto instruction;
        case 4 :
            cout << "\n1. Parent\n";
            cout << "2. Staff\n";
            cout << "Select an option: ";
            cin >> ps;
            if (ps == 1){
                parentRegister();
                goto instruction;
            }
            if (ps==2) {
                staffRegister();
                goto instruction;
            }
         case 5 :
            cout << "\n1. Parent\n";
            cout << "2. Staff\n";
            cout << "3. Admin\n";
            cout << "Select an option: ";
            cin >> ps;
            
            if (ps == 1 || ps == 2){
                cout << "Username: ";
                cin >> userAttempt;
                login(ptr_user);
                if(!access){
                    goto instruction;
                }
                while (access){
                    int option;
                    cout << "\n1.Weekly menu list\n";
                    cout << "2.Make Complaint\n";
                    cout << "3.Lunch Order\n";
                    cout << "4.Back to main menu\n\n";
                    cout << "Select an option: ";
                    cin >> option;
                
                    if (option == 1){
                        weeklyMenu();
                    }else if (option ==2){
                        complaint();
                    }else if (option ==3){
                        if(ps == 1){
                            orderParent(ptr_user);
                        }else if(ps==2){
                            orderStaff(ptr_user);
                        }
                    }else if (ps == 4){
                        
                    }else{
                        access = false;
                        goto instruction;
                    }
                    }
                }
            
            if (ps ==3){
                string adminPassword;
                cout << "Admin password? ";
                cin >> adminPassword;
                if(adminPassword!="admin"){
                    cout <<"\nWrong password. Going back to the main menu\n";
                    goto instruction;
                }
                while(adminPassword == "admin"){
                    int option;
                    cout << "\n1.Menu update\n";
                    cout << "2.Daily order report\n";
                    cout << "3.Sales report\n";
                    cout << "4.Pending payment\n";
                    cout << "5.Customer complaint\n";
                    cout << "6.Back to main menu\n\n";
                    cout << "Select an option: ";
                    cin >> option;
                
                    if (option ==1){
                        menuUpdate();
                    }else if (option==2){
                        dailyOrder();
                    }else if (option ==3){
                        salesReport();
                    }else if (option ==4){
                        pending();
                    }else if (option ==5){
                        weeklyComplaint();
                    }else{
                        access= false;
                        goto instruction;
                    }
                    }
                }
        }
    }

