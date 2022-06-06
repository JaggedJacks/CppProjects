#include <string>
#include <iostream>
using namespace std;

//This class is the initial utility class used to track the payments of customers
//currently, this class tracks the payments of a single customer
class MyRevenue{
	public:
	//committed payment schedule, showing the amount in dollars of each expected payment for the next 12 months
	int expectedPayments [12] = {100, 100, 100, 100,100, 100, 100, 100,100, 100, 100, 100};
	int underpaymentCount;
	std::string myString;
	bool delinquent = false;
	void myMethod(){
	}
	
};

int main(){
	MyRevenue myObj;
	myObj.myMethod();
	//an array of monthly payments in dollar amounts of what the customer actually paid
	int actual [12] = {50, 100, 70, 100,0, 100, 80, 100,90 , 100, 100, 100};
	myObj.underpaymentCount = 0;
	for (int i = 0; i < 12; i++){
		if (actual[i] < myObj.expectedPayments[i])
			myObj.underpaymentCount++;
	}
	
	if (myObj.underpaymentCount > 3){
		cout << "This Customer has missed "<< myObj.underpaymentCount <<" payments. Please Consult with this customer";
		myObj.delinquent = true;
	}
	return 0;
}