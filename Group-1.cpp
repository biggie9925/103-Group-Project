//
//  main.cpp
//  assignment
//
//  Created by Ellie Kim and David Mackey-Ward on 16/11/21.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void menuFunction() {

    fstream menuItem;
    menuItem.open("menuItem.txt");
    fstream menuPrice;
    menuPrice.open("menuPrice.txt");
    string line;
    string line2;
    int i = 1;

    if (menuItem.is_open() && menuPrice.is_open()) {
        cout << endl;
        while (getline(menuItem, line)) {
            getline(menuPrice, line2);
            if (!line.size()) {
                continue;
            }
            else {
                cout << i << ".   $" << line2 << "   " << line << endl;
                i++;
            }
        }
        cout << endl;
    }
    menuItem.close();
    menuPrice.close();
}


void discountsFunction() {

    ifstream discounts;
    discounts.open("discounts.txt");
    string line;

    if (discounts.is_open()) {
        cout << endl;
        while (getline(discounts, line)) {
            cout << line << endl;
        }
        cout << endl;
    }
    discounts.close();
}


void contactUsFunction() {

    ifstream contactus;
    contactus.open("contactus.txt");
    string line;

    if (contactus.is_open()) {
        cout << endl;
        while (getline(contactus, line)) {
            cout << line << endl;
        }
        cout << endl;
    }
    contactus.close();
}


//Register Function
void registerFunction() {
    string username, password;
    cout << "Enter your username: ";
    cin >> username;
    cout << "Enter your password: ";
    cin >> password;

    ofstream file(username, ios::app);

    string fullName, gender, dob, contact, child, room, visa, expiry;
    int ps;
    cout << "\nWould you like to register as: \n";
    cout << "1. Parent\n";
    cout << "2. Staff\n";
    cout << "Select an option: ";
    cin >> ps;
    if (ps == 1) {
        cin.ignore();
        cout << "\nEnter your personal details:\n";
        cout << "Full Name: ";
        getline(cin, fullName);
        cout << "Gender: ";
        cin >> gender;
        cout << "Date of Birth: ";
        cin >> dob;
        cin.ignore();
        cout << "Contact Number: ";
        getline(cin, contact);
        cout << "Child Name: ";
        getline(cin, child);
        cout << "Child room number: ";
        cin >> room;
        cin.ignore();
        cout << "Visa card number: ";
        getline(cin, visa);
        cout << "Visa card date of expiry: ";
        getline(cin, expiry);

        file << username << endl;
        file << password << endl;
        file << fullName << endl;
        file << contact << endl;
        file << gender << " " << dob << " " << child << " " << room << " " << visa << " " << expiry << endl;

    }
    if (ps == 2) {

        cin.ignore();
        cout << "\nEnter your personal details:\n";
        cout << "Full Name: ";
        getline(cin, fullName);
        cout << "Gender: ";
        cin >> gender;
        cout << "Date of Birth: ";
        cin >> dob;
        cin.ignore();
        cout << "Contact Number: ";
        getline(cin, contact);
        cout << "\tWhere would you like the food delivered: ";
        cin >> room;
        cin.ignore();
        cout << "Visa card number: ";
        getline(cin, visa);
        cout << "Visa card date of expiry: ";
        getline(cin, expiry);

        file << username << endl;
        file << password << endl;
        file << fullName << endl;
        file << contact << endl;
        file << gender << " " << dob << " " << "Staff" << room << " " << visa << " " << expiry << endl;


        cout << "\nSuccessfully registered. Please login\n\n";
    }
    file.close();
}


//Login Function
bool access = false;
void login(string* userAttempt) {
    string passAttempt;

    ifstream loginFile(*userAttempt);
    string username, password, fullName;
    int attempt = 0;
    if (loginFile.is_open()) {
        getline(loginFile, username);
        getline(loginFile, password);
        getline(loginFile, fullName);

        while (attempt < 3) {
            cout << "Password: ";
            cin >> passAttempt;
            if (password == passAttempt) {
                cout << "\nHello " << fullName << ", successfully logged in\n\n";
                access = true;
                break;

            }
            else if (attempt < 2) {
                cout << "Invalid password. Try again.\n";
                attempt++;
            }
            else {
                cout << "Too many failed login attempts. Please try after 30 minutes.\n";
                attempt++;
            }
        }
    }
    else {
        cout << "Invalid username. Going back to the main menu. \n";

    }
    loginFile.close();
}

//Parent & Staff Screen Functions

void feedbackFunction() {

    fstream feedbackDoc;
    feedbackDoc.open("feedback.txt", ios::app);
    string username;
    string contactDetails;
    string feedbackDetails;

    if (feedbackDoc.is_open()) {
        cout << "\nPlease provide the details of your feedback: \n";
        cout << "\n\tYour username: ";
        cin >> username;
        cin.ignore();
        cout << "\tContact details: ";
        getline(cin, contactDetails);
        cout << "\tDetails of your feedback: ";
        getline(cin, feedbackDetails);
        feedbackDoc << username << "," << contactDetails << "," << feedbackDetails << "\nStatus - Not Responded\n";
        cout << "\nThank you - Feedback Submitted\n\n";
    }
    feedbackDoc.close();
}

void orderParent(string* user) {
    string date, item, quantity, price, child, classroom, paymentStatus, issuedStatus, dietary;
    ofstream orderFile("orderFile.txt", ios::app);
    int orderNum = rand() % 10000 + 1;
    cout << "Order date (dd/mm/yy): ";
    cin >> date;
    cin.ignore();
    cout << "Item name: ";
    getline(cin, item);
    cout << "quantity(small, large) : ";
    cin >> quantity;
    cout << "price: $";
    cin >> price;
    cin.ignore();
    cout << "Child name: ";
    getline(cin, child);
    cout << "Classroom number: ";
    cin >> classroom;
    cin.ignore();
    cout << "Dietary preference: ";
    getline(cin, dietary);
    issuedStatus = "pending";

    orderFile << orderNum << endl;
    orderFile << date << endl;
    orderFile << item << endl;
    orderFile << quantity << endl;
    orderFile << price << endl;
    orderFile << "Child - " << child << endl;
    orderFile << classroom << endl;
    orderFile << dietary << endl;

    string yn;
    cout << "Proceed payment ? (y/n)";
    cin >> yn;
    if (yn == "y" || yn == "Y") {
        paymentStatus = "Paid";
        orderFile << paymentStatus << endl;
        orderFile << *user << endl;
        orderFile.close();

        cout << "\n----------------------------------------\n";
        cout << "                 BILL                    \n";
        cout << "Order number: " << orderNum << endl;
        cout << "Order date: " << date << endl;
        cout << "Item name : " << item << endl;
        cout << "Price : $" << price << endl;
        cout << "Student name : " << child << endl;
        cout << "Student room number: " << classroom << endl;
        cout << "Dietary preferance: " << dietary << endl;
        cout << "Payment status: " << paymentStatus << endl;
        cout << "Issued status: " << issuedStatus << endl;
        cout << "\n---------------------------------------\n";


    }
    else {
        paymentStatus = "NP";
        cout << "\n No payment received\n";
        orderFile << paymentStatus << endl;
        orderFile << *user << endl;

        ofstream pending("pending.txt", ios::app);
        pending << date << endl;
        pending << item << endl;
        pending << price << endl;
        pending << *user << endl;
        pending.close();

    }
}

void orderStaff(string* user) {
    string date, item, quantity, price, delivery, paymentStatus, issuedStatus, dietary;
    ofstream orderFile("orderFile.txt", ios::app);
    int orderNum = rand() % 10000 + 1;
    cout << "Order date (dd/mm/yy): ";
    cin >> date;
    cin.ignore();
    cout << "Item name: ";
    getline(cin, item);
    cout << "quantity(small, large) : ";
    cin >> quantity;
    cout << "price: $";
    cin >> price;
    cin.ignore();
    cout << "Delivery address: ";
    cin >> delivery;
    cin.ignore();
    cout << "Dietary preference: ";
    getline(cin, dietary);
    issuedStatus = "pending";

    orderFile << orderNum << endl;
    orderFile << date << endl;
    orderFile << item << endl;
    orderFile << quantity << endl;
    orderFile << price << endl;
    orderFile << "Staff" << endl;
    orderFile << delivery << endl;
    orderFile << dietary << endl;

    string yn;
    cout << "Proceed payment ? (y/n)";
    cin >> yn;
    if (yn == "y" || yn == "Y") {
        paymentStatus = "Paid";
        orderFile << paymentStatus << endl;
        orderFile << *user << endl;
        orderFile.close();

        cout << "\n----------------------------------------\n";
        cout << "              BILL (Staff)                 \n";
        cout << "Order number: " << orderNum << endl;
        cout << "Order date: " << date << endl;
        cout << "Item name : " << item << endl;
        cout << "Price : $" << price << endl;
        cout << "Delivery Address : " << delivery << endl;
        cout << "Dietary preferance: " << dietary << endl;
        cout << "Payment status: " << paymentStatus << endl;
        cout << "Issued status: " << issuedStatus << endl;
        cout << "\n---------------------------------------\n";


    }
    else {
        paymentStatus = "NP";
        cout << "\n Payment not received\n";
        orderFile << paymentStatus << endl;
        orderFile << *user << endl;

        ofstream pending("pending.txt", ios::app);
        pending << date << endl;
        pending << item << endl;
        pending << price << endl;
        pending << *user << endl;
        pending.close();

    }
}


//Admin Screen Functions

void adminMenuFunction() {

    //need to update this


    int option1;

    cout << "Would you like to:\n";
    cout << "\n\t1. Update a particular menu item";
    cout << "\n\t2. Reset full menu";
    cout << "\n\t3. Return to Admin Menu";
    cout << "\n\nSelect option: ";
    cin >> option1;
    cout << endl;

    if (cin.fail())
    {
        cout << "\nIncorrect input, please try again\n\n";
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }


    else if (option1 == 1) {

        fstream menuItem;
        fstream menuPrice;
        menuItem.open("menuItem.txt");
        menuPrice.open("menuPrice.txt");

        vector <string> menuItemVector;
        vector <double> menuPriceVector;

        string newMenuItem;
        double newMenuPrice;
        string line;
        double line1;

        int updateMenu;



        if (menuItem.is_open()) {

            while (!menuPrice.eof()) {
                menuPrice >> line1;
                menuPriceVector.push_back(line1);
            }

            while (!menuItem.eof()) {
                getline(menuItem, line);
                menuItemVector.push_back(line);
            }

        }

        menuFunction();

        //for (int i = 0; i < menuPriceVector.size(); i++) {
        //    cout << "$" << menuPriceVector[i] << "    " << menuItemVector[i] << endl;
        //}


        menuItem.close();
        menuPrice.close();

        cout << "\nEnter the line you would like to update or press 0 to return to Admin Menu: ";
        cin >> updateMenu;

        if (updateMenu == 0) {

        }

        else {
            cout << "\n\tEnter new menu item: ";
            cin.ignore();
            getline(cin, newMenuItem);
            menuItemVector[updateMenu - 1] = newMenuItem;

            menuItem.open("menuItem.txt", ios::out);

            for (size_t l = 0; l < menuItemVector.size(); l++) {
                menuItem << menuItemVector[l] << endl;
            }

            cout << "\tEnter new menu price (No $ Symbol Necessary) : ";
            cin >> newMenuPrice;
            menuPriceVector[updateMenu - 1] = newMenuPrice;

            menuPrice.open("menuPrice.txt", ios::out);

            for (size_t m = 0; m < menuPriceVector.size(); m++) {
                menuPrice << menuPriceVector[m] << endl;
            }

            cout << "\nYou entered:   " << newMenuItem << "   $" << newMenuPrice;
            cout << "\n\nUpdate Successful\n";
            menuItem.close();
            menuPrice.close();
        }
    }


    else if (option1 == 2) {

        fstream menu;
        string newMenu;
        bool menuLoop = true;
        menu.open("menu.txt", ios::out);
        cout << "Menu has been reset\n";
        cout << "\nPlease enter new menu item and price - once finished type 'exit' : \n";
        cin.ignore();
        if (menu.is_open()) {
            while (menuLoop) {
                getline(cin, newMenu);
                if (newMenu == "exit") {
                    break;
                }
                menu << newMenu << endl;
            }
        }
        menu.close();
    }

    else if (option1 == 3) {
        cout << "\nReturning to Admin Menu...\n";
    }

    else {
        cout << "\nIncorrect input - Returning to Admin Menu...\n";
    }
}

void adminDiscountFunction() {

    int option1;

    cout << "Would you like to:\n";
    cout << "\n\t1. Update a particular discount";
    cout << "\n\t2. Reset all discounts";
    cout << "\n\t3. Return to Admin Menu";
    cout << "\n\nSelect option: ";
    cin >> option1;
    cout << endl;

    if (cin.fail())
    {
        cout << "\nIncorrect input, please try again\n\n";
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    else if (option1 == 1) {

        fstream discounts;
        discounts.open("discounts.txt");

        vector <string> discountsVector;

        string newDiscount;
        string line;

        int updateDiscounts;
        int k = 0;

        if (discounts.is_open()) {
            while (!discounts.eof()) {
                getline(discounts, line);
                discountsVector.push_back(line);
            }

            for (string j : discountsVector) {
                k = k + 1;
                cout << "Line: " << k << " - " << j << "\n";
            }
        }

        discounts.close();


        cout << "\nEnter the line you would like to update or press 0 to return to Admin Menu: ";
        cin >> updateDiscounts;

        if (updateDiscounts == 0) {

        }

        else {
            cout << "\nEnter new menu item: ";
            cin.ignore();
            getline(cin, newDiscount);
            discountsVector[updateDiscounts - 1] = newDiscount;


            discounts.open("discounts.txt", ios::out);

            for (size_t l = 0; l < discountsVector.size(); l++) {
                discounts << discountsVector[l] << endl;
            }

            cout << "\nYou entered: " << newDiscount;
            cout << "\n\nUpdate Successful\n";
            discounts.close();
        }
    }


    else if (option1 == 2) {

        fstream discounts;
        string newDiscount;
        bool discountLoop = true;
        discounts.open("discounts.txt", ios::out);
        cout << "Discounts have been reset\n";
        cout << "\nPlease enter new discounts and type 'exit' when finished: \n";
        cin.ignore();
        if (discounts.is_open()) {
            while (discountLoop) {
                getline(cin, newDiscount);
                if (newDiscount == "exit") {
                    break;
                }
                discounts << newDiscount << endl;
            }
        }
        discounts.close();
    }

    else if (option1 == 3) {
        cout << "\nReturning to Admin Menu...\n";
    }

    else {
        cout << "\nIncorrect input - Returning to Admin Menu...\n";
    }
}


void adminContactusFunction() {

    int option1;

    cout << "Would you like to:\n";
    cout << "\n\t1. Update a particular Contact Us line";
    cout << "\n\t2. Reset Contact Us document";
    cout << "\n\t3. Return to Admin Menu";
    cout << "\n\nSelect option: ";
    cin >> option1;
    cout << endl;

    if (cin.fail())
    {
        cout << "\nIncorrect input, please try again\n\n";
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    else if (option1 == 1) {

        fstream contactus;
        contactus.open("contactus.txt");

        vector <string> contactusVector;

        string newContact;
        string line;

        int updateContact;
        int k = 0;

        if (contactus.is_open()) {
            while (!contactus.eof()) {
                getline(contactus, line);
                contactusVector.push_back(line);
            }

            for (string j : contactusVector) {
                k = k + 1;
                cout << "Line: " << k << " - " << j << "\n";
            }
        }

        contactus.close();

        cout << "\nEnter the line you would like to update or press 0 to return to Admin Menu: ";
        cin >> updateContact;

        if (updateContact == 0) {

        }

        else {
            cout << "\nEnter new menu item: ";
            cin.ignore();
            getline(cin, newContact);
            contactusVector[updateContact - 1] = newContact;


            contactus.open("contactus.txt", ios::out);

            for (size_t l = 0; l < contactusVector.size(); l++) {
                contactus << contactusVector[l] << endl;
            }

            cout << "\nYou entered: " << newContact;
            cout << "\n\nUpdate Successful\n";
            contactus.close();
        }

    }


    else if (option1 == 2) {

        fstream contactus;
        string newContact;
        bool contactLoop = true;
        contactus.open("contactus.txt", ios::out);
        cout << "Contact Us has been reset\n";
        cout << "\nPlease enter new Contact Us details and type 'exit' when finished: \n";
        cin.ignore();
        if (contactus.is_open()) {
            while (contactLoop) {
                getline(cin, newContact);
                if (newContact == "exit") {
                    break;
                }
                contactus << newContact << endl;
            }
        }
        contactus.close();
    }

    else if (option1 == 3) {
        cout << "\nReturning to Admin Menu...\n";
    }

    else {
        cout << "\nIncorrect input - Returning to Admin Menu...\n";
    }
}


void adminDailyOrder() {
    string date;
    ifstream file("orderFile.txt");
    if (!file) {
        cout << "--------------------------------------\n\n";
        cout << "\t\tNo data found...\n";
        cout << "\n--------------------------------------\n";
    }
    if (file.is_open()) {
        cout << "Enter the date (dd/mm/yy) : ";
        cin >> date;

        cout << "--------------------------------------\n\n";
        cout << "Daily order report - " << date << "\n\n";
        string line;
        int count = 1;
        while (getline(file, line)) {
            if (line == date) {
                string info[5];
                for (int i = 0; i < 5; i++) {
                    getline(file, info[i]);
                }
                cout << count << ". " << info[0] << " " << info[1] << " $" << info[2] << endl;
                cout << "\t" << info[3] << endl;
                cout << "\tDeliver to - " << info[4] << endl;
                count++;
            }
        }
        cout << "\nTotal " << count - 1 << " Orders\n";
        cout << "\n--------------------------------------\n\n";
    }
}

void adminSalesReport() {
    cout << "\n----------------------------------\n";
    cout << "\t\t Sales Report\n";
    ifstream file("orderFile.txt");
    if (file.is_open()) {
        int count = 0;
        int sum = 0;
        string s[10];
        for (int i = 0; i < 10; i++) {
            getline(file, s[i]);
        }
        while (!file.eof()) {
            cout << "Date: " << s[1] << endl;
            cout << "Item: " << s[2] << endl;
            cout << "Price: " << s[4] << endl;
            cout << "----------------------------------\n\n";
            count++;
            sum += stoi(s[4]);
            for (int i = 0; i < 10; i++) {
                getline(file, s[i]);
            }
        }
        cout << "Total order: " << count << endl;
        cout << "Amount Received: $" << sum << "\n\n";
    }
    else {
        cout << "\nNo data found...\n";
        cout << "\n----------------------------------\n";
    }
}

void adminPendingPayment() {
    ifstream file("pending.txt");
    if (file.is_open()) {
        string line;
        string info[4];
        cout << "\t\tPending Payment:\n";
        cout << "------------------------------------\n";
        for (int i = 0; i < 4; i++) {
            getline(file, info[i]);
        }
        while (!file.eof()) {
            cout << "Date : " << info[0] << endl;
            cout << "Item : " << info[1] << endl;
            cout << "Price : " << info[2] << endl;
            ifstream userfile(info[3]);
            string user, pass, fullName, contact;
            getline(userfile, user);
            getline(userfile, pass);
            getline(userfile, fullName);
            getline(userfile, contact);
            cout << "Full name: " << fullName << endl;
            cout << "Contact: " << contact << endl;
            for (int i = 0; i < 4; i++) {
                getline(file, info[i]);
            }
            userfile.close();
            cout << "------------------------------------\n\n";
        }
        file.close();
    }
    else {
        cout << "\nNo data found...\n\n";
    }
}

void adminFeedbackFunction() {

    int option1;
    fstream feedback;
    string line;
    vector <string> feedbackVector;
    int k = 0;

    cout << "Would you like to:\n";
    cout << "\n\t1. Show feedback and update status";
    cout << "\n\t2. Clear all feedback";
    cout << "\n\t3. Return to Admin Menu";
    cout << "\n\nSelect option: ";
    cin >> option1;
    cout << endl;

    if (cin.fail())
    {
        cout << "\nIncorrect input, please try again\n\n";
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    else if (option1 == 1) {

        int updateFeedback;
        string newFeedback;
        feedback.open("feedback.txt");

        if (feedback.is_open()) {
            while (!feedback.eof()) {
                getline(feedback, line);
                feedbackVector.push_back(line);
            }

            for (string j : feedbackVector) {
                k = k + 1;
                cout << "Line: " << k << " - " << j << "\n";
            }
        }

        feedback.close();

        cout << "\nEnter the line you would like to update or press 0 to return to Admin Menu: ";
        cin >> updateFeedback;

        if (updateFeedback == 0) {

        }

        else {
            cout << "\nEnter new status: ";
            cin.ignore();
            getline(cin, newFeedback);
            feedbackVector[updateFeedback - 1] = newFeedback;


            feedback.open("feedback.txt", ios::out);

            for (size_t l = 0; l < feedbackVector.size(); l++) {
                feedback << feedbackVector[l] << endl;
            }

            cout << "\nYou entered: " << newFeedback;
            cout << "\n\nUpdate Successful\n";
            feedback.close();
        }
    }


    else if (option1 == 2) {

        feedback.open("feedback.txt", ios::out);
        if (feedback.is_open()) {
            cout << "Feedback has been cleared\n";
        }
        feedback.close();

    }

    else if (option1 == 3) {
        cout << "\nReturning to Admin Menu...\n";
    }

    else {
        cout << "\nIncorrect input - Returning to Admin Menu...\n";
    }
}





int main(int argc, const char* argv[]) {

    srand(time(NULL));

mainMenu:
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
    string* ptr_user = &userAttempt;

    if (cin.fail())
    {
        cout << "\nIncorrect input, please try again\n\n";
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    switch (input) {
    case 1:
        menuFunction();
        cout << "\nPress Enter key to go back: ";
        cin.ignore();
        cin.get();
        goto mainMenu;
    case 2:
        discountsFunction();
        cout << "Press Enter key to go back: ";
        cin.ignore();
        cin.get();
        goto mainMenu;
    case 3:
        contactUsFunction();
        cout << "Press Enter key to go back: ";
        cin.ignore();
        cin.get();
        goto mainMenu;
    case 4:
        registerFunction();
        goto mainMenu;
    case 5:
        cout << "\n1. Parent\n";
        cout << "2. Staff\n";
        cout << "3. Admin\n";
        cout << "\nSelect an option: ";
        cin >> ps;

        if (cin.fail())
        {
            cout << "\nIncorrect input, please try again\n";
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            goto mainMenu;
        }

        if (ps == 1 || ps == 2) {
            cout << "Username: ";
            cin >> userAttempt;
            login(ptr_user);
            if (!access) {
                goto mainMenu;
            }
            while (access) {
                int option;
                cout << "1.Weekly menu list\n";
                cout << "2.Make Complaint\n";
                cout << "3.Lunch Order\n";
                cout << "4.Return to main menu\n\n";
                cout << "Select an option: ";
                cin >> option;

                if (option == 1) {
                    menuFunction();
                }
                else if (option == 2) {
                    feedbackFunction();
                }
                else if (option == 3) {
                    if (ps == 1) {
                        orderParent(ptr_user);
                    }
                    else if (ps == 2) {
                        orderStaff(ptr_user);
                    }
                }
                else {
                    access = false;
                    goto mainMenu;
                }
            }
        }

        if (ps == 3) {
            string adminPassword;
            cout << "Admin password? ";
            cin >> adminPassword;
            if (adminPassword != "admin") {
                cout << "\nWrong password. Returning to the main menu\n";
                goto mainMenu;
            }
            while (adminPassword == "admin") {
                int option;
                cout << "\n1. Update Menu\n";
                cout << "2. Update Discounts\n";
                cout << "3. Update Contact Details\n";
                cout << "4. View Daily Order Report\n";
                cout << "5. View Sales Report\n";
                cout << "6. View Pending Payment\n";
                cout << "7. View Feedback\n";
                cout << "8. Return to main menu\n\n";
                cout << "Select an option: ";
                cin >> option;

                if (cin.fail())
                {
                    cout << "\nIncorrect input, please try again\n\n";
                    cin.clear();
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
                else if (option == 1) {
                    adminMenuFunction();
                }
                else if (option == 2) {
                    adminDiscountFunction();
                }
                else if (option == 3) {
                    adminContactusFunction();
                }
                else if (option == 4) {
                    adminDailyOrder();
                }
                else if (option == 5) {
                    adminSalesReport();
                }
                else if (option == 6) {
                    adminPendingPayment();
                }
                else if (option == 7) {
                    adminFeedbackFunction();
                }
                else {
                    access = false;
                    goto mainMenu;
                }
            }
        }
    }
}


