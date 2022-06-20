#include <gtest/gtest.h>

using namespace std;

//Names of dummy data that will be gathered from the database at a later date
string names [] = {"Molly" , "Dennis", "Roger", "Dan", "Rayonna","Jacqueline", "Rufus"};

//committed payment schedule, showing the amount in dollars of each expected payment for the next 12 months
int expected[6][12] = { 
{ 100, 100, 100, 100, 100, 100, 100, 100,100, 100, 100, 100 },
{ 100, 100, 100, 100, 100, 100, 100, 100,100, 100, 100, 100 },
{ 100, 100, 100, 100, 100, 100, 100, 100,100, 100, 100, 100 },
{ 100, 100, 100, 100, 100, 100, 100, 100,100, 100, 100, 100 },
{ 100, 100, 100, 100, 100, 100, 100, 100,100, 100, 100, 100 },
{ 100, 100, 100, 100, 100, 100, 100, 100,100, 100, 100, 100 } };

//an array of monthly payments in dollar amounts of what the customer actually paid
int actual[6][12] = { { 50, 100, 30, 100,90, 100, 100, 85,100, 100, 95, 90 },
    { 100, 100, 100, 100,100, 100, 100, 100,60, 70, 80, 100 },
{ 100, 100, 100, 100,100, 100, 100, 100,100, 100, 100, 100 } ,
{ 100, 100, 100, 100,100, 100, 100, 100,100, 100, 100, 90 } ,
{ 100, 100, 100, 100,100, 100, 100, 100,100, 100, 100, 100 } ,
{ 100, 100, 100, 100,100, 100, 100, 100,100, 100, 100, 100 } };

//length of membership in months for each member. There are 6 users that are members in total.
int membLength[6] = { 12,12,12,12,10,12 };

//The initial class that contains all of the attributes of a user that will be included in a database at a later point
class UserInfo {
public:
    string name;    
    int* expectedPayments;
    int* actualPayments;
    int underpaymentCount;
    bool delinquent = false;
    string specialMessage;
    string status;
    int totalAmountPaid;
    int totalAmountExpected;
    int lengthOfMembership;
    UserInfo(string name, int* expectedPayments, int* actualPayments, int lengthOfMembership);
    UserInfo();
};

//Initial empty constructor
UserInfo::UserInfo() {

}

//Constructor with arguments that initializes the fields
UserInfo::UserInfo(string name, int* expectedPayments, int* actualPayments, int lengthOfMembership ) {
    name = name;
    this->expectedPayments = expectedPayments;
    this->actualPayments = actualPayments;
    this->lengthOfMembership = lengthOfMembership;
    totalAmountExpected = 0;
    totalAmountPaid = 0;

    //Calculate the number of missed payments
    underpaymentCount = 0;
    for (int i = 0; i < lengthOfMembership; i++) {
        if (actualPayments[i] < expectedPayments[i])
            underpaymentCount++; //number of missed payments
        totalAmountPaid += actualPayments[i];//accumulate the amount actually paid
        totalAmountExpected += expectedPayments[i]; //accumulate the amount of payments expected each month
    }
    
    //If the number of payments made is more than the number of payments agreed on, report extra payments
    if (sizeof(actualPayments) > lengthOfMembership) {
        status = "Extra Payments Have been made.";
        delinquent = false;
    }
    //If 90 percent or more of the payments are made, the customer is in good standing
    else if (underpaymentCount <= lengthOfMembership * .1 ) {
        status = "This Customer is in good standing";
       delinquent = false;
    }
    //If half or less of the payments are made, notify collections
    else if (underpaymentCount >= lengthOfMembership/2 || totalAmountExpected/totalAmountPaid >= 2) {
        status = "This Customer has missed " + to_string(underpaymentCount);
       status += " payments. Notifying collections";
        delinquent = true;
    }
    //if less than 2/3 of the payments are made, warn the customer
    else if (underpaymentCount >= lengthOfMembership / 3 || totalAmountPaid / totalAmountExpected <= 2/3) {
        status = "This Customer has missed " + to_string(underpaymentCount);
            status += " payments. Please Consult with this customer";
        delinquent = true;
    }   
    //cout << status;
    return;
    //test cases, varying lengths of payment histories
    //consider an enum of the reasons a payment is delinquent
}

//Create multiple users, useful for testing multiple scenarios
class MultipleUsers {
public:
    UserInfo user[6];
    MultipleUsers() {
        for (int i = 0; i < 6; i++) {
            user[i] = UserInfo(names[i], expected[i], actual[i], membLength[i]);
        }
        return;
    }

};