#pragma once
#include <gtest/gtest.h>


#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 800
#define START_X -.75
#define START_Y -.3
#define END_X .15
#define END_Y .8

using namespace std;

class GraphicalUser {
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
    GraphicalUser(int one, int two);

};

GraphicalUser::GraphicalUser(int screenHeight, int screenWidth) {

}