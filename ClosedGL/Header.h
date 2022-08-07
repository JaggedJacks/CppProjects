#include <gtest/gtest.h>
#include <UserInfo.h>
#include <Windows.h>

TEST(MissedPayments, CollectionsNotified) {
    MultipleUsers* usr = new MultipleUsers();
    EXPECT_EQ(6, usr->user[0].underpaymentCount);
    EXPECT_EQ(usr->user[0].status, "This Customer has missed 6 payments. Notifying collections");
}

TEST(MissedPayments, WarrantsAWarning) {
    MultipleUsers userList;
    EXPECT_EQ(3, userList.user[1].underpaymentCount);
    EXPECT_EQ(userList.user[1].status, "This Customer has missed 3 payments. Please Consult with this customer");
}

TEST(TimelyPayments, PerfectHistory) {
    MultipleUsers userList;
    EXPECT_EQ(0, userList.user[2].underpaymentCount);
    EXPECT_EQ(userList.user[2].status, "This Customer is in good standing");

}

TEST(TimelyPayments, AFewMissedPayments) {
    MultipleUsers userList;
    EXPECT_EQ(1, userList.user[3].underpaymentCount);
    EXPECT_EQ(userList.user[3].status, "This Customer is in good standing");

}

TEST(TimelyPayments, ExtraPaymentsMade) {
    MultipleUsers userList;
    cout << userList.user[4].name << "\n";

    EXPECT_EQ(0, userList.user[4].underpaymentCount);
    EXPECT_EQ(userList.user[4].status, "This Customer is in good standing");

}

//NEW
TEST(TimelyPayments, UserInfoCollected) {
    MultipleUsers userList;
    cout << userList.user[4].name << "\n";

    EXPECT_TRUE(sizeof(userList.user[4].actualPayments) >= sizeof(userList.user[5].lengthOfMembership)); //Length of membership should always expect a set amount of payments from the user
    EXPECT_EQ(10, userList.user[4].lengthOfMembership); //Membership length was preset, so expect that value
}


TEST(UnauthorizedUser, InformationDenied) {
    MultipleUsers userList;
    EXPECT_EQ(userList.user[5].status, "Authentication failed!");
}

//TC1
TEST(UnauthorizedUser, AuthorizationKeySet) {
    MultipleUsers userList;
    EXPECT_EQ(userList.user[5].authKey, 3);
}

//NEW
TEST(GraphPoints, GraphPointsTranslated) {
    //MultipleUsers userList;
    MultipleUsers* userList = new MultipleUsers();
    userList->user[0].setGraphicalData();
    bool interfacesTranslated = true;
    for (int i = 0; i < userList->user[0].lengthOfMembership * 3; i += 3) {
        if ((userList->user[0].actualPaymentGraphPoints[i] == userList->user[0].actualPaymentsToPlot[i]) ||
            (userList->user[0].actualPaymentGraphPoints[i + 1] == userList->user[0].actualPaymentsToPlot[i + 1]) ||
            (userList->user[0].actualPaymentGraphPoints[i + 2] == userList->user[0].actualPaymentsToPlot[i + 2]))
        {
            interfacesTranslated = false;
            break;
        }

    }
    EXPECT_TRUE(interfacesTranslated);
}


//TC 12
TEST(GraphPoints, PrepareExpectedPaymentGraphPoints) {
    MultipleUsers userList;
    bool allEqual = true;
    for (int i = 0; i < 12; i++) {
        if (userList.user[0].expectedPaymentsToPlot[i] - 100.0 > 10.0) {
            allEqual = false;
            break;
        }
    }
    EXPECT_TRUE(allEqual);
}

//TC12
TEST(GraphPoints, SetGraphBounds) {
   // EXPECT_EQ(userList.user[0].largestExpectedPayment + 100, userList.user[0].getGraphCeiling());
}

//TC12
TEST(GraphPoints, PrepareActualPaymentGraphPoints) {
    MultipleUsers userList;
    bool allEqual = true;
    for (int i = 0; i < 12; i++) {
        if (userList.user[0].actualPaymentsToPlot[i] - 100.0 > 10.0) {
            allEqual = false;
            break;
        }
    }
    EXPECT_TRUE(allEqual);
}

//TC 6
TEST(Database, createDatabase) {
    Model modelo;
    Sleep(2);
    EXPECT_EQ(modelo.rc, SQLITE_OK);
}

//TC 6
TEST(Database, readFromDatabase) {
    Model modelo;
    Sleep(2);
    modelo.readAll();
    EXPECT_EQ(modelo.rc, SQLITE_OK);
}

//TC4
TEST(Database, expectedValues) {
    Model modelo;
    modelo.read();
    bool arrsEqual = true;
    for (int a = 0; a < 6; a++) {
        for (int b = 0; b < 12; b++) {
            if (modelo.expectedVals[a][b] != 100) {
                arrsEqual = false;
            }
        }
    }
    EXPECT_TRUE(arrsEqual);
}

//TC4
TEST(Database, actualValues) {
    Model modelo;
    modelo.read();
    bool arrsEqual = true;
    int testVals[] = { 10,50,120,90,0,70,90,90,90,100,50,50 };
    for (int a = 0; a < 1; a++) {
        for (int b = 0; b < 12; b++) {
            if (modelo.actualVals[a][b] != testVals[b]) {
                arrsEqual = false;
            }
        }
    }
    EXPECT_TRUE(arrsEqual);
}
//TC4
TEST(Database, idValues) {
    Model modelo;
    modelo.read();
    bool arrsEqual = true;
    int testVals[] = { 0,1,2,3,4,5,6 };
    for (int a = 0; a < 3; a++) {
        if (modelo.iDs[a] != testVals[a]) {
            cout << "modelo: " << modelo.iDs[a] << "\n";
            cout << "testvals: " << testVals[a] << "\n";

            arrsEqual = false;
        }
    }
    EXPECT_TRUE(arrsEqual);
}