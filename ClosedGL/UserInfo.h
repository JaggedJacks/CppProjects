#include <gtest/gtest.h>
#include <graphicalUser.h>
#include <Model.cpp>

using namespace std;

//Names of dummy data that will be gathered from the database at a later date
string names[] = { "Molly" , "Dennis", "Roger", "Dan", "Rayonna","Jacqueline", "Rufus" };

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
    { 100, 100, 105, 100,100, 100, 100, 100,60, 70, 80, 100 },
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
    

    float* expectedPaymentsToPlot;
    float* actualPaymentsToPlot;
    int* paymentLengthToPlot;

    GLfloat* expectedPaymentGraphPoints;
    GLfloat* actualPaymentGraphPoints;
    int largestExpectedPayment;
    int authKey = 3;//0 guest, 1 normal user, 2 admin, 3 invalid

    UserInfo(string name, int* expectedPayments, int* actualPayments, int lengthOfMembership, bool authentication);
    UserInfo();
   
    void setGraphCeiling(int ceiling);
    void setGraphicalData();
    int getGraphCeiling() {
        return graphCeiling;
    }
private:
    void setLargestPayment();
    
    int graphCeiling;
};

//Initial empty constructor
UserInfo::UserInfo() {

}

//Constructor with arguments that initializes the fields
//all of the user info fields should come from the model
UserInfo::UserInfo(string name, int* expectedPayments, int* actualPayments, int lengthOfMembership, bool authentication) {
    name = name;
    this->expectedPayments = expectedPayments;
    this->actualPayments = actualPayments;
    this->lengthOfMembership = lengthOfMembership;
    int authKey = 3;
    totalAmountExpected = 0;
    totalAmountPaid = 0;
    largestExpectedPayment = 0;
    expectedPaymentsToPlot = new float [lengthOfMembership];
    actualPaymentsToPlot = new float[lengthOfMembership];
    const int membLength = lengthOfMembership;


    /***************Translate Graphical Information******************/
    setLargestPayment();
    //cout <<"Largest Expected Payment:" << largestExpectedPayment << "\n";
    setGraphCeiling(largestExpectedPayment+100); //enter a UI element that calls this to change the graph scale
    //cout<<"Graph Ceiling:"<< graphCeiling << "\n";
    setGraphicalData();
    /****************End Translate Graphical Information*************/

    /*******Check Authentication********************************/
    if (authentication) {
        //Calculate the number of missed payments
        underpaymentCount = 0;
        for (int i = 0; i < lengthOfMembership; i++) {
            if (actualPayments[i] < expectedPayments[i])
                underpaymentCount++; //number of missed payments
            totalAmountPaid += actualPayments[i];//accumulate the amount actually paid
            totalAmountExpected += expectedPayments[i]; //accumulate the amount of payments expected each month
        }

        //If the number of payments made is more than the number of payments agreed on, report extra payments
       /* if (sizeof(actualPayments) > lengthOfMembership) {
            status = "Extra Payments Have been made.";
            delinquent = false;
            //make this an elsifstatement with the  rest of the ifs
        }*/
        //If 90 percent or more of the payments are made, the customer is in good standing
        if (underpaymentCount <= lengthOfMembership * .1) {
            status = "This Customer is in good standing";
            delinquent = false;
        }
        //If half or less of the payments are made, notify collections
        else if (underpaymentCount >= lengthOfMembership / 2 || totalAmountExpected / totalAmountPaid >= 2) {
            status = "This Customer has missed " + to_string(underpaymentCount);
            status += " payments. Notifying collections";
            delinquent = true;
        }
        //if less than 2/3 of the payments are made, warn the customer
        else if (underpaymentCount >= lengthOfMembership / 3 || totalAmountPaid / totalAmountExpected <= 2 / 3) {
            status = "This Customer has missed " + to_string(underpaymentCount);
            status += " payments. Please Consult with this customer";
            delinquent = true;
        }
    }
    else
        status = "Authentication failed!";
    //cout << status;
    /*********************************************************End Check Authentication************************************/
    return;
    //test cases, varying lengths of payment histories
    //consider an enum of the reasons a payment is delinquent
}

void UserInfo::setGraphicalData() {
    //Payments
    for (int j = 0; j < lengthOfMembership; j++) {
        expectedPaymentsToPlot[j] = START_Y + ((float)expectedPayments[j] / (float)graphCeiling) * (END_Y - START_Y);
        //cout << "Expected Payments:" << expectedPaymentsToPlot[j] << "\n";
        actualPaymentsToPlot[j] = START_Y + ((float)actualPayments[j] / (float)graphCeiling) * (END_Y - START_Y);
        //cout << "Actual Payments:" << actualPaymentsToPlot[j] << "\n";
    }
    //Graphics
        //verify the output of this
    expectedPaymentGraphPoints = new GLfloat[lengthOfMembership * 3];
    for (int i = 0; i < lengthOfMembership * 3; i += 3) {
        expectedPaymentGraphPoints[i] = START_X + (((GLfloat)(i / 3) / (float)lengthOfMembership) * (END_X - START_X)); //possible divide by zero error
        expectedPaymentGraphPoints[i + 1] = expectedPaymentsToPlot[(i) / 3];
        expectedPaymentGraphPoints[i + 2] = 0;
    }
    //print (x,y) values
    actualPaymentGraphPoints = new GLfloat[lengthOfMembership * 3];
    for (int i = 0; i < lengthOfMembership * 3; i += 3) {
        actualPaymentGraphPoints[i] = START_X + (((GLfloat)(i / 3) / (float)lengthOfMembership) * (END_X - START_X)); //possible divide by zero error
        actualPaymentGraphPoints[i + 1] = actualPaymentsToPlot[(i) / 3];
        actualPaymentGraphPoints[i + 2] = 0;
        /*cout << "Actual Payments:" << actualPaymentGraphPoints[i] << ","
            << actualPaymentGraphPoints[i+1] << ","
            << actualPaymentGraphPoints[i+2] << ","
            << "\n";*/

    }

}


void UserInfo::setLargestPayment() {
    for (int j = 0; j < lengthOfMembership; j++) {
        if (expectedPayments[j] > largestExpectedPayment) {
            //graph x axis based on largest payment
            largestExpectedPayment = expectedPayments[j];
        }
    }
    return;
}

//The user will pick a dollar amount to set the graph ceiling
void UserInfo::setGraphCeiling(int ceiling) {
    //perform calculation, then do comparison
    int translatedGraphCeiling;
    if (ceiling >= largestExpectedPayment)
        graphCeiling = ceiling; //else, return an error
        return;
}
//Create multiple users, useful for testing multiple scenarios
class MultipleUsers {
    Model model;
public:
    UserInfo user[6];
    MultipleUsers() {
        for (int i = 0; i < 6; i++) {
            if (i != 5)
                user[i] = UserInfo(names[i], expected[i], actual[i], membLength[i], true);
            else
                user[i] = UserInfo(names[i], expected[i], actual[i], membLength[i], false);
        }
        return;
    }
};