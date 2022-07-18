#include <GLFW/glfw3.h>
#include"imgui.h"
#include"imgui_impl_glfw.h"
#include"imgui_impl_opengl3.h"
#include <gtest/gtest.h>
#include <UserInfo.h>
#include <GraphicalUser.h>


using namespace std;
MultipleUsers userList;


TEST(MissedPayments, CollectionsNotified) {
    MultipleUsers *usr = new MultipleUsers();
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
    cout << userList.user[4].name <<"\n";

    EXPECT_EQ(0, userList.user[4].underpaymentCount);
    EXPECT_EQ(userList.user[4].status, "This Customer is in good standing");

}

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

TEST(UnauthorizedUser, AuthorizationKeySet) {
    MultipleUsers userList;
    EXPECT_EQ(userList.user[5].authKey, 3);
}

TEST(GraphPoints, GraphPointsTranslated) {
    //MultipleUsers userList;
    MultipleUsers* userList = new MultipleUsers();
    userList->user[0].setGraphicalData();
    bool interfacesTranslated = true;
    for (int i = 0; i < userList->user[0].lengthOfMembership*3; i+=3) {
        if ((userList->user[0].actualPaymentGraphPoints[i] == userList->user[0].actualPaymentsToPlot[i]) ||
            ( userList->user[0].actualPaymentGraphPoints[i+1] == userList->user[0].actualPaymentsToPlot[i+1])||
            (userList->user[0].actualPaymentGraphPoints[i + 2] == userList->user[0].actualPaymentsToPlot[i + 2]))
        {
            interfacesTranslated = false;
            break;
        }
       
    }
    EXPECT_TRUE(interfacesTranslated);
}



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

TEST(GraphPoints, SetGraphBounds) {
    EXPECT_EQ(userList.user[0].largestExpectedPayment+100 , userList.user[0].getGraphCeiling());
}

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


GLfloat pointVertex[] = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
GLfloat pointVertex2[] = { SCREEN_WIDTH * 0.75, SCREEN_HEIGHT * 0.75 };

GLfloat lineVertices[] = {//what do the 3 points mean?
      300,300,
      310,310,
      320, 300,
     330,310,
      340,300
  };

GLfloat lineVerticesUser1[] = {//what do the 3 points mean?
      -.75,-.75,0,
      -.65,0 ,0,
      -.55 , -.75 , 0,
     -.45 ,0 ,0,
      -.35 ,-.75 ,0
};

GLfloat lineVerticesUser2[] = {
    //declare a vertice array of payment length
    //May have to convert DB info to line vertices
    -.75,.5,0,
    -.65,.6 ,0,
    -.55 , .7 , 0,
   -.45 ,.7 ,0,
    -.35 ,.7 ,0
};

GLfloat lineVerticesUser3[3][9] = { //now you can dynamically declare the line vertices and specify each vertex by the d/b info
    //declare a vertice array of payment length
    //May have to convert DB info to line vertices
    -.75,.5,0,
    -.65,.6 ,0,
    -.55 , .7 , 0,
   -.45 ,.7 ,0,
   .75,.5,0,
       .65,.6 ,0,
    .55 , .7 , 0,
   .45 ,.7 ,0,
    -.35 ,.7 ,0
};


void drawVertices(bool revAlert) {
 

    if (revAlert) {    
        glLineWidth(3); //set the line width only for plotted points
        glEnableClientState(GL_VERTEX_ARRAY);

        const GLvoid* pointer = userList.user[0].actualPaymentGraphPoints;

        /*
        for (int i = 0; i < userList.user[0].lengthOfMembership; i++) {
            cout << userList.user[0].actualPaymentGraphPoints[i][0] << ",";
        }
        cout<< "\n";
        for (int i = 0; i < userList.user[0].lengthOfMembership; i++) {
            cout << userList.user[0].actualPaymentGraphPoints[i][1] << ",";
        }
        cout << "\n";
        for (int i = 0; i < userList.user[0].lengthOfMembership; i++) {
            cout << userList.user[0].actualPaymentGraphPoints[i][2] << ",";
        }
        cout << "\n";
        */
        
        
        GLfloat lineVerticesUser[36];
        int k = 0; //do same for actual
        for (int i = 0; i < userList.user[0].lengthOfMembership * 3; i += 3) {
            cout << userList.user[0].expectedPaymentGraphPoints[i] << ",";
            cout << userList.user[0].expectedPaymentGraphPoints[i + 1] << ",";
            cout << userList.user[0].expectedPaymentGraphPoints[i + 2] << "\n";
        }
        cout << "\n";

        glVertexPointer(3, GL_FLOAT, 0, userList.user[0].expectedPaymentGraphPoints); //use method to recreate
        glColor3f(0.0, 0.0, 1.0); //blue
        glDrawArrays(GL_LINE_STRIP, 0, userList.user[0].lengthOfMembership);//plots the first x number of points
        glColor3f(1.0, 1.0, 1.0); //white
        glDisableClientState(GL_VERTEX_ARRAY);

        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3, GL_FLOAT, 0, userList.user[0].actualPaymentGraphPoints);
        glColor3f(0.0, 1.0, 0.0); //green
        glDrawArrays(GL_LINE_STRIP, 0, userList.user[0].lengthOfMembership);
        glColor3f(1.0, 1.0, 1.0); //white
        glDisableClientState(GL_VERTEX_ARRAY);
        glLineWidth(1); //revert the line width

        /*glLineWidth(3); //set the line width only for plotted points
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3, GL_FLOAT, 0, lineVerticesUser1); //use method to recreate
        glColor3f(1.0, 0.0, 0.0); //red
        glDrawArrays(GL_LINE_STRIP, 0, 5);
        glColor3f(1.0, 1.0, 1.0); //white
        glDisableClientState(GL_VERTEX_ARRAY);*/
        
    }
       //glEnd();
    return;
}

void createGraph(bool authenticated, bool problemPoint) {
    if (authenticated) {
        //x axis
        glBegin(GL_LINES);
        glVertex2f(START_X, START_Y);
        glVertex2f(START_X, END_Y);
        glLineWidth(1);
        glEnd();

        //y axis
        glBegin(GL_LINES);
        glVertex2f(START_X, START_Y);
        glVertex2f(END_X, START_Y);
        glLineWidth(1);
        glEnd();

    drawVertices(problemPoint);
    } //else, clear the screen
    return;

}

/***************************Popup Windows****************************************************/
static const char* items[]{ "Jill","Scott","Tanner" };
static int selectedItem = 0;

//Welcome Screen
void showWelcomePopup(bool* p_open)
{
    //The window gets created here. Passing the bool to ImGui::Begin causes the "x" button to show in the top right of the window. Pressing the "x" button toggles the bool passed to it as "true" or "false"
    //If the window cannot get created, it will call ImGui::End
    if (!ImGui::Begin("Welcome to the revenue recovery app!", p_open))
    {
        ImGui::End();
    }
    else
    {
        ImGui::Text("Welcome to the revenue recovery app!");
        ImGui::Text("Who are you?");
        ImGui::ListBox("Chose your user", &selectedItem,
            items, IM_ARRAYSIZE(items));
        ImGui::End();

    }
}

bool revAlert = false;
void showMenuOptionsPopup(bool* p_open) {
    //The window gets created here. Passing the bool to ImGui::Begin causes the "x" button to show in the top right of the window. Pressing the "x" button toggles the bool passed to it as "true" or "false"
    //If the window cannot get created, it will call ImGui::End
    if (!ImGui::Begin("What would you like to do?"))
    {
        ImGui::End();
    }
    else
    {
        static float sliderFloat = 0.f;
        static int sliderInt = 0;
        ImGui::SliderFloat("GraphHeight", &sliderFloat, (float) userList.user[0].largestExpectedPayment, (float)userList.user[0].largestExpectedPayment*2);
        ImGui::Text("What would you like to do?");
        ImGui::Checkbox("View customer history?", &revAlert);
        ImGui::End();
        userList.user[0].setGraphCeiling(sliderFloat);
        userList.user[0].setGraphicalData(); //May be repetitive
    }
}


int main(int argc, char* argv[])
{
    GLFWwindow* window;

    //MultipleUsers userList;//each user list currently has 6 users

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

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
    
    glViewport(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT); //specifies the part of the window to which OpenGL will draw (in pixels), convert from normalised to pixels
    glMatrixMode(GL_PROJECTION);// projection matrix defines the properties of the camera that views the objects in the world coordinate frame. Here you typically set the zoom factor, aspect ration and the near and far clipping planes
    glLoadIdentity(); // replace the current matrix with the identity matrix and starts us a fresh becausematrix transformations such as glOrpho and glRotate cumulate, basically puts us at (0,0,0)
    //glOrtho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, 0, 1); //essentially set coordinate system
    glMatrixMode(GL_MODELVIEW); // (default matrix mode) modelview matrix defines how your objects are transformed (meaning translation, rotation and scaling) in your world
    glLoadIdentity(); //same as above comment
    
    static bool show_welcome_popup = true, 
                show_menu_options_popup = true;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
                
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();

        if (selectedItem != 3) {
            ImGui::NewFrame();
            if (show_welcome_popup)
            {
                showWelcomePopup(&show_welcome_popup);
            }
        }

        if (selectedItem == 1) {            
            show_welcome_popup = false;
            userList.user[0].authKey=1;
            if (show_menu_options_popup)
            {
                showMenuOptionsPopup(&show_menu_options_popup);
            }
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

