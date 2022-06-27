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

    bool revAlert = true;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Welcome to the revenue recovery app!");
        ImGui::Text("Please Select a customer");
       // ImGui::Checkbox("Payment Overdue?", NULL);
        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        

 
        //old line
        /*glPushAttrib(GL_ENABLE_BIT);
        glLineStipple(1, 0xAAAA);
        glEnable(GL_LINE_STIPPLE);
        glBegin(GL_LINES);
        glVertex3f(-.5, .5, -.5);
        glVertex3f(.5, .5, -.5);*/

        //new line
        glBegin(GL_LINES);
        glVertex2f(-.5, 0);
        glVertex2f(0,0 );
        glLineWidth(1);
        glEnd();

        glBegin(GL_LINES);
        glVertex2f(-.5, .5);
        glVertex2f(-.5, 0);
        glLineWidth(1);
        glEnd();

        glBegin(GL_LINES);
        if (revAlert)
            glColor3f(1.0, 0.0, 0.0);
        glVertex2f(-.5, 0);
        glVertex2f(0, .5);
        glLineWidth(1);
        glEnd();

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