#include <GLFW/glfw3.h>
#include"imgui.h"
#include"imgui_impl_glfw.h"
#include"imgui_impl_opengl3.h"
#include <gtest/gtest.h>
#include <UserInfo.h>

using namespace std;


TEST(MissedPayments, CollectionsNotified) {
    MultipleUsers userList;
    EXPECT_EQ(6, userList.user[0].underpaymentCount);
    EXPECT_EQ(userList.user[0].status, "This Customer has missed 6 payments. Notifying collections");
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
    cout << userList.user[4].name <<"\n";
    cout << "Actual Payments Size: "<< sizeof(userList.user[5].actualPayments) <<"\n";
    cout << "Length Of Membership: " << sizeof(userList.user[5].lengthOfMembership)<<"\n";
    cout << "Total Amount Expected: " << userList.user[5].totalAmountExpected<<"\n";
    EXPECT_EQ(0, userList.user[4].underpaymentCount);
    EXPECT_EQ(userList.user[4].status, "This Customer is in good standing");

}

TEST(UnauthorizedUser, InformationDenied) {
    MultipleUsers userList;
    EXPECT_EQ(userList.user[5].status, "Authentication failed!");
}

void drawLines(bool revAlert) {
    glBegin(GL_LINES);
    if (revAlert) {
        //Customer 1's info
        glColor3f(0.0, 0.0, 1.0); //blue
        glVertex2f(-.5, 0);
        glVertex2f(0, .5);

        //Customer 2's info
        glColor3f(1.0, 0.0, 0.0); //red
        glVertex2f(-.5, 0);
        glVertex2f(0, .3);

        //Customer 3's info
        glColor3f(0.0, 1.0, 0.0); //green
        glVertex2f(-.5, 0);
        glVertex2f(-.1, .5);
    }
        glLineWidth(1);
        glEnd();
    
    return;
}

void createGraph(bool authenticated, bool problemPoint) {
    if (authenticated) {


    //old line
        /*glPushAttrib(GL_ENABLE_BIT);
        glLineStipple(1, 0xAAAA);
        glEnable(GL_LINE_STIPPLE);
        glBegin(GL_LINES);
        glVertex3f(-.5, .5, -.5);
        glVertex3f(.5, .5, -.5);*/

        //new line
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINES);
    glVertex2f(-.5, 0);
    glVertex2f(0, 0);
    glLineWidth(1);
    glEnd();

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINES);
    glVertex2f(-.5, .5);
    glVertex2f(-.5, 0);
    glLineWidth(1);
    glEnd();

    drawLines(problemPoint);
} //else, clear the screen
    return;

}

int main(int argc, char* argv[])
{
    GLFWwindow* window;

    testing::InitGoogleTest(&argc, argv);

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }


    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    bool revAlert = false;

    static const char* items[]{ "Jill","Scott","Tanner" };
    static int selectedItem = 0;


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();

        if (selectedItem != 3) {
            ImGui::NewFrame();
            ImGui::Begin("Welcome to the revenue recovery app!");
            ImGui::Text("Who are you?");
            ImGui::ListBox("ListBox", &selectedItem,
                items, IM_ARRAYSIZE(items));
            ImGui::End();
        }

        if (selectedItem == 1) {
            ImGui::Begin("What would you like to do?");
            ImGui::Checkbox("View customer history?", &revAlert);
            ImGui::End();
        }
        

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());      
 
        
        createGraph(selectedItem==1, revAlert);        

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    RUN_ALL_TESTS();
    return 0;
}

