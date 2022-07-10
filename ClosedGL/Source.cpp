#include <GLFW/glfw3.h>
#include"imgui.h"
#include"imgui_impl_glfw.h"
#include"imgui_impl_opengl3.h"
#include <gtest/gtest.h>
#include <UserInfo.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

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

        RUN_ALL_TESTS();
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
    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Hello World", NULL, NULL);//determines how big your screen is

    if (!window)
    {
        glfwTerminate();
        return -1;
    }


    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    float vertices[] =
    {
        0 ,300, //top left
        300, 300, //top right
        300, 0, //bottom right
        0, 0 // bottom left
    };

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    bool revAlert = false;

    static const char* items[]{ "Jill","Scott","Tanner" };
    static int selectedItem = 0;

    glViewport(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT); //specifies the part of the window to which OpenGL will draw (in pixels), convert from normalised to pixels
    glMatrixMode(GL_PROJECTION);// projection matrix defines the properties of the camera that views the objects in the world coordinate frame. Here you typically set the zoom factor, aspect ration and the near and far clipping planes
    glLoadIdentity(); // replace the current matrix with the identity matrix and starts us a fresh becausematrix transformations such as glOrpho and glRotate cumulate, basically puts us at (0,0,0)
    glOrtho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, 0, 1); //essentially set coordinate system
    glMatrixMode(GL_MODELVIEW); // (default matrix mode) modelview matrix defines how your objects are transformed (meaning translation, rotation and scaling) in your world
    glLoadIdentity(); //same as above comment

    GLfloat pointVertex[] = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
    GLfloat pointVertex2[] = { SCREEN_WIDTH * 0.75, SCREEN_HEIGHT * 0.75};

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        // Render OpenGL here
        glEnable(GL_POINT_SMOOTH);
        glEnableClientState(GL_VERTEX_ARRAY);
        glPointSize(50);//anywhere before drawarrays
        glVertexPointer(2, GL_FLOAT, 0, pointVertex);
        glDrawArrays(GL_POINTS, 0, 1);
        glDisableClientState(GL_VERTEX_ARRAY);
        glDisable(GL_POINT_SMOOTH);

        glEnableClientState(GL_VERTEX_ARRAY);
        glPointSize(10);//anywhere before drawarrays
        glVertexPointer(2, GL_FLOAT, 0, pointVertex2);
        glDrawArrays(GL_POINTS, 0, 1);
        glDisableClientState(GL_VERTEX_ARRAY);

        
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();

        if (selectedItem != 3) {
            ImGui::NewFrame();
            ImGui::Begin("Welcome to the revenue recovery app!");
            ImGui::Text("Who are you?");
            ImGui::ListBox("Chose your user", &selectedItem,
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

    return 0;
}

