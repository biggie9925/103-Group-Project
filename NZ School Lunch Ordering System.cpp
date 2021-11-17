// NZ School Lunch Ordering System.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>
#include <limits>
#include <vector>
#include <sstream>
#include <limits>
#include <iomanip>
#include <algorithm>
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


void orderFunction(string username, string staffName, string child, string classroom, string visaCardNo, string visaCardExp, string contactNo) {

    fstream orders;
    fstream menuItem;
    fstream menuPrice;
    fstream totalDate;
    fstream totalAmount;
    orders.open("orders.txt", ios::app);
    menuItem.open("menuItem.txt");
    menuPrice.open("menuPrice.txt");
    totalDate.open("totalDate.txt", ios::app);
    totalAmount.open("totalAmount.txt", ios::app);
    int itemNumber;
    int itemNumber1;
    vector <string> menuVector;
    vector <double> menu1Vector;
    string line;
    double line1;
    int i = 0;
    int k = 0;
    bool loop = true;
    char input;
    string itemDate;
    double billTotal = 0;



    while (!menuPrice.eof()) {
        menuPrice >> line1;
        menu1Vector.push_back(line1);
    }

    while (!menuItem.eof()) {
        getline(menuItem, line);
        menuVector.push_back(line);
    }


    if (orders.is_open()) {
        menuFunction();

        cout << "\tPlease enter the date you would like this order for (DD/MM) : ";
        cin >> itemDate;

        orders << itemDate << ",     " << staffName << child << "    Location: " << classroom << "     Username:" << username << "    Contact:" << contactNo << "    Credit Card:" << visaCardNo << "    " << visaCardExp << endl;

        while (loop) {

            cout << "\tPlease enter the item number you would like to order or press 0 to return to Main Menu: ";
            cin >> itemNumber;
            itemNumber1 = itemNumber;

            if (itemNumber == 0) {
                break;
            }

            orders << menuVector[itemNumber - 1] << "    $" << menu1Vector[itemNumber1 - 1] << "    ";
            billTotal = billTotal + menu1Vector[itemNumber1 - 1];

            cout << "\tItem added - Would you like to order another item? (Y/N) : ";
            cin >> input;

            if (input == 'y' || input == 'Y') {
                continue;
            }

            else {
                cout << "\nYour total comes to: $" << fixed << setprecision(2) << billTotal << " which will be charged automatically to your credit card.\n\n";
                orders << "\n" << billTotal << "\nIncomplete" << "\nUnpaid\n";

                if (totalDate.is_open()) {
                    totalDate << itemDate << endl;
                }

                if (totalAmount.is_open()) {
                    totalAmount << billTotal << endl;
                }

                loop = false;

            }
        }
    }


    orders.close();
    menuItem.close();
    menuPrice.close();
    totalDate.close();
    totalAmount.close();
}

vector <string> parseCommaDelimitedString(string line) {
    vector <string> result;
    stringstream s_stream(line);

    while (s_stream.good()) {
        string substr;
        getline(s_stream, substr, ',');
        result.push_back(substr);
    }
    return result;
}


void loginFunction() {

    fstream users;
    string username1;
    string line;
    users.open("users.txt", ios::in);
    bool login;

    if (users.is_open()) {

        cout << "\n\tPlease enter your username: ";
        cin >> username1;
        const char* username2 = username1.c_str();

        while (getline(users, line)) {

            vector<string> parsedLine = parseCommaDelimitedString(line);
            const char* username = parsedLine.at(0).c_str();

            if (strcmp(username, username2) == 0) {
                const char* password = parsedLine.at(1).c_str();
                string password1;
                const char* password2 = password1.c_str();

                for (int i = 0; i < 4; i++) {

                    if (i < 3) {
                        cout << "\tPlease enter your password: ";
                        cin >> password1;

                        if (strcmp(password, password2) == 0) {
                            cout << "\n\tLogin Successful - Hello " << parsedLine.at(0).c_str() << ", please see menu below:\n";
                            orderFunction(parsedLine.at(0).c_str(), parsedLine.at(2).c_str(), parsedLine.at(3).c_str(), parsedLine.at(4).c_str(), parsedLine.at(5).c_str(), parsedLine.at(6).c_str(), parsedLine.at(7).c_str());
                            login = true;
                            break;
                        }

                        else {
                            cout << "\n\t\tIncorrect password\n\n";
                        }
                    }

                    else {
                        cout << "\t\tMaximum 3 attempts exceeded - Returning to Main Menu\n\n";
                    }
                }
            }

            else {
                cout << "\n\t\tUsername not found - Returning to Main Menu\n\n";
            }
        }
    }
    users.close();
}


void registerFunction() {

    fstream users;
    users.open("users.txt", ios::app);

    string username;
    string password;
    string parentName;
    string gender;
    string dob;
    string contactNo;
    string childName;
    string childRoomNo;
    string visaCardNo;
    string visaCardExp;
    int staffOrParent;

    if (users.is_open()) {
        cout << "\nWould you like to register as: \n";
        cout << "\n\t1. Parent";
        cout << "\n\t2. Staff";
        cout << "\n\nSelect option: ";
        cin >> staffOrParent;

        if (cin.fail())
        {
            cout << "\nIncorrect input, please try again\n\n";
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        else if (staffOrParent == 1) {

            cout << "\nPlease complete the following:\n\n";
            cout << "\tUsername: ";
            cin >> username;
            cout << "\tPassword: ";
            cin >> password;
            cout << "\tParent Full Name: ";
            cin.ignore();
            getline(cin, parentName);
            cout << "\tGender: ";
            getline(cin, gender);
            cout << "\tDate of birth: ";
            getline(cin, dob);
            cout << "\tContact number: ";
            getline(cin, contactNo);
            cout << "\tChild Full Name: ";
            getline(cin, childName);
            cout << "\tChild room number: ";
            getline(cin, childRoomNo);
            cout << "\tVisa card number: ";
            getline(cin, visaCardNo);
            cout << "\tVisa card expiry (MM/YY) : ";
            getline(cin, visaCardExp);
            cout << "\n\tRegistration Successful\n\n";

            users << username << "," << password << "," << " Child    -  " << "," << childName << "," << childRoomNo << "," << visaCardNo << "," << visaCardExp << "," << contactNo << "," << parentName << "," << gender << "," << dob << "," << "\n";
        }

        else if (staffOrParent == 2) {

            cout << "\nPlease complete the following:\n\n";
            cout << "\tUsername: ";
            cin >> username;
            cout << "\tPassword: ";
            cin >> password;
            cout << "\tStaff Full Name: ";
            cin.ignore();
            getline(cin, childName);
            cout << "\tGender: ";
            getline(cin, gender);
            cout << "\tDate of birth: ";
            getline(cin, dob);
            cout << "\tContact number: ";
            getline(cin, contactNo);
            cout << "\tWhere would you like the food delivered: ";
            getline(cin, childRoomNo);
            cout << "\tVisa card number: ";
            getline(cin, visaCardNo);
            cout << "\tVisa card expiry (MM/YY) : ";
            getline(cin, visaCardExp);
            cout << "\n\tRegistration Successful\n\n";

            users << username << "," << password << "," << " Staff   -    " << "," << childName << "," << childRoomNo << "," << visaCardNo << "," << visaCardExp << "," << contactNo << "," << gender << "," << dob << "," << "\n";

        }

        else {
            cout << "\nIncorrect input - Returning to Main Menu...\n";
        }
    }
    users.close();
}


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
        int j = 0;
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

        cout << "\nEnter the line you would like to update: ";
        cin >> updateDiscounts;
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
        int j = 0;
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

        cout << "\nEnter the line you would like to update: ";
        cin >> updateContact;
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

bool find_substring(const string& word_to_find, const string& target) {
    size_t found = target.find(word_to_find);
    if (found == string::npos)
        return false;
    else
        return true;
}

void adminOrderFunction() {

    fstream orders;
    int option1;
    string newline;
    vector <string> ordersVector;
    string date;
    string datesearch;
    int j = 0;
    int k = 0;


    cout << "Would you like to:\n";
    cout << "\n\t1. Search for orders by date";
    cout << "\n\t2. Show all orders and update status";
    cout << "\n\t3. Clear orders";
    cout << "\n\t4. Return to Admin Menu";
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

        cout << "Enter the date you would like to search for: ";
        cin >> date;

        orders.open("orders.txt");
        if (orders.is_open()) {

            while (!orders.eof()) {

                orders >> datesearch;
                getline(orders, newline);

                if (find_substring(date, datesearch)) {
                    cout << date << newline;
                    cout << endl;
                }
            }
        }
        orders.close();
    }


    else if (option1 == 2) {

        orders.open("orders.txt");
        int updateOrder;
        string newOrder;

        if (orders.is_open()) {
            while (!orders.eof()) {
                getline(orders, newline);
                ordersVector.push_back(newline);
            }

            for (string j : ordersVector) {
                k = k + 1;
                cout << "Line: " << k << " - " << j << "\n";
            }
        }

        orders.close();

        cout << "\nEnter the line you would like to update or press 0 to return to Admin Menu: ";
        cin >> updateOrder;


        if (updateOrder == 0) {

        }


        else {
            cout << "\nEnter new status: ";
            cin.ignore();
            getline(cin, newOrder);
            ordersVector[updateOrder - 1] = newOrder;
            orders.open("orders.txt", ios::out);

            for (size_t l = 0; l < ordersVector.size(); l++) {
                orders << ordersVector[l] << endl;
            }

            cout << "\nYou entered: " << newOrder;
            cout << "\n\nUpdate Successful\n";
            orders.close();
        }


    }

    else if (option1 == 3) {
        fstream orders;
        orders.open("orders.txt", ios::out);
        if (orders.is_open()) {
            cout << "Orders have been reset\n";
        }
        orders.close();
    }

    else if (option1 == 4) {
        cout << "\nReturning to Admin Menu...\n";
    }

    else {
        cout << "\nIncorrect input - Returning to Admin Menu...\n";
    }
}

void adminFeedbackFunction() {

    int option1;
    fstream feedback;
    string line;
    vector <string> feedbackVector;
    int j = 0;
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

        cout << "\nEnter the line you would like to update: ";
        cin >> updateFeedback;
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



void adminReportFunction() {
    int option1;
    string newline;
    fstream orders;
    string date;
    string datesearch;
    double sales = 0;
    double salesTotal = 0;
    vector <double> salesTotalVector;
    vector <string> totalDateVector;
    double line1 = 0;
    string line;
    double dailyTotal = 0;

    cout << "Would you like to:\n";
    cout << "\n\t1. Show Sales by Date";
    cout << "\n\t2. Show Total Sales";
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

        cout << "Enter the date you would like to search for: ";
        cin >> date;
        cout << "\n";

        fstream totalDate;
        fstream totalAmount;
        totalDate.open("totalDate.txt");
        totalAmount.open("totalAmount.txt");

        if (totalAmount.is_open()) {
            while (!totalAmount.eof()) {
                totalAmount >> line1;
                salesTotalVector.push_back(line1);
            }
        }

        if (totalDate.is_open()) {
            while (!totalDate.eof()) {
                getline(totalDate, line);
                totalDateVector.push_back(line);
            }
        }

        for (int i = 0; i < totalDateVector.size(); i++) {
            if (date == totalDateVector[i]) {
                cout << "Date:   " << totalDateVector[i] << "     Bill Total:   $" << salesTotalVector[i] << endl;
                dailyTotal = dailyTotal + salesTotalVector[i];
            }
        }
        cout << "\t\t Daily Total:   $" << dailyTotal << endl;

        //if (find(totalDateVector.begin(), totalDateVector.end(), date) != totalDateVector.end()) {
        //    cout << "Date:   " << totalDateVector[i] << "   Bill Total   $" << salesTotalVector[i] << endl;
        //    i++;
        //}

    }

    else if (option1 == 2) {
        fstream totalAmount;
        totalAmount.open("totalAmount.txt");

        if (totalAmount.is_open()) {

            while (totalAmount >> sales) {
                salesTotal = salesTotal + sales;
            }

        }

        cout << "Total Sales is: $" << fixed << setprecision(2) << salesTotal << endl;

        totalAmount.close();
    }

    else if (option1 == 3) {
        cout << "\nReturning to Admin Menu...\n";
    }

    else {
        cout << "\nIncorrect input - Returning to Admin Menu...\n";
    }
}


void adminFunction() {
    int option1;
    bool admin = true;
    
    while (admin) {
        cout << "\nWelcome Admin, would you like to:\n";
        cout << "\n\t1. Update Menu";
        cout << "\n\t2. Update Discounts";
        cout << "\n\t3. Update Contact Details";
        cout << "\n\t4. View Orders";
        cout << "\n\t5. View Feedback";
        cout << "\n\t6. View Report";
        cout << "\n\t7. Return to Main Menu";
        cout << "\n\nSelect option: ";
        cin >> option1;
        cout << "\n";

        if (cin.fail())
        {
            cout << "\nIncorrect input, please try again\n\n";
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        else if (option1 == 1) {
            adminMenuFunction();
        }

        else if (option1 == 2) {
            adminDiscountFunction();
        }

        else if (option1 == 3) {
            adminContactusFunction();
        }

        else if (option1 == 4) {
            adminOrderFunction();
        }

        else if (option1 == 5) {
            adminFeedbackFunction();
        }

        else if (option1 == 6) {
            adminReportFunction();
        }

        else if (option1 == 7) {
            admin = false;
        }

        else {
            cout << "\nIncorrect input, please try again\n";
            continue;
        }

    }
    cout << endl;
}





int main()
{
    bool intro = true;
    int option1;
    string username;
    string password;
    string adminPassword;

    while (intro) {
        cout << "School Lunch Order System - Main Menu\n\n";
        cout << "\t1. Weekly menu\n";
        cout << "\t2. Discounts for bulk orders\n";
        cout << "\t3. Contact details\n";
        cout << "\t4. Login and order\n";
        cout << "\t5. Registration for parents and staff\n";
        cout << "\t6. Feedback\n";
        cout << "\t7. Admin access\n";
        cout << "\t8. Exit\n\n";
        cout << "Select option: ";
        cin >> option1;

        if (cin.fail())
        {
            cout << "\nIncorrect input, please try again\n\n";
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        else if (option1 == 1) {
            menuFunction();
            continue;
        }

        else if (option1 == 2) {
            discountsFunction();
            continue;
        }

        else if (option1 == 3) {
            contactUsFunction();
            continue;
        }

        else if (option1 == 4) {
            loginFunction();
            continue;
        }

        else if (option1 == 5) {
            registerFunction();
            continue;
        }

        else if (option1 == 6) {
            feedbackFunction();
            continue;
        }

        else if (option1 == 7) {
            cout << "\nAdmin Password: ";
            cin >> adminPassword;
            if (adminPassword == "admin") {
                adminFunction();
                continue;
            }

            else {
                cout << "\nIncorrect password\n\n";
                continue;
            }
        }

        else if (option1 == 8) {
            cout << "\nExiting application...\n";
            intro = false;
            break;
        }

        else {
            cout << "\nIncorrect input, please try again\n";
            continue;
        }
    }
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
