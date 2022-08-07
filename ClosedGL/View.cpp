#include <GLFW/glfw3.h>
#include"imgui.h"
#include"imgui_impl_glfw.h"
#include"imgui_impl_opengl3.h"
#include <gtest/gtest.h>
//#include <UserInfo.h>
#include <GraphicalUser.h>
#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <Windows.h>
#include <Header.h>


TEST(MissedPayments, WarrantsAWarning) {
    drawVertices(true);

}
using namespace std;
MultipleUsers userList;
static bool show_welcome_popup = true,
show_menu_options_popup = true,
show_customer_information_popup = false;
static bool makeGraph = false;
static bool compare_customer_information_popup = false;

/***************************Popup Windows****************************************************/
//Welcome screen
static const char* loginUsers[]{ "Jill","Scott","Tanner","Bill","Megan" };
static int selectedUser = 0;
static int prevSelectedUser = selectedUser;

//Main Menu Options
static const char* menuOptions[]{ "Compare", "View" , "Go Back"};
static int selectedMenuOption = -1;
static int prevSelectedMenuOption = selectedMenuOption;

//Customer history
static const char* customers[]{ "Microsoft","Apple","Facebook","Albacore","Confucious" };
static int selectedCustomer = 0;
static int prevSelectedCustomer = selectedCustomer;


//Customer comparison
/***************************Popup Windows****************************************************/


/***************************Graphical Translation Varialbes************************************************/

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

int Model::actualVals[6][12] = {//make -1. it's being initialized, but not updated
{ 90,90,90,90,90,90,90,90,90,90,90,90 },
{  20,20,20,20,20,20,20,20,20,20,20,20},
{ 20,20,20,20,20,20,20,20,20,20,20,20},
{ 20,20,20,20,20,20,20,20,20,20,20,20 },
{ 20,20,20,20,20,20,20,20,20,20,20,20 },
{ 20,20,20,20,20,20,20,20,20,20,20,20} };

int Model::expectedVals[6][12] = {//make -1. it's being initialized, but not updated
{ -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
{ -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
{ -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
{ -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
{ -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
{ -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1} };

int Model::iDs[20] = { -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1 };

int Model::cnt = 0;
int Model::cnt1 = 0;
/**************************************************************************************************/


void drawVertices(int  selected) {//rename to view history
      
        glLineWidth(3); //set the line width only for plotted points
 
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3, GL_FLOAT, 0, userList.user[selected].expectedPaymentGraphPoints); //use method to recreate
        glColor3f(0.0, 0.0, 1.0); //blue
        glDrawArrays(GL_LINE_STRIP, 0, userList.user[selected].lengthOfMembership);//plots the first x number of points
        glColor3f(1.0, 1.0, 1.0); //white
        glDisableClientState(GL_VERTEX_ARRAY);

        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3, GL_FLOAT, 0, userList.user[selected].actualPaymentGraphPoints);
        glColor3f(0.0, 1.0, 0.0); //green
        glDrawArrays(GL_LINE_STRIP, 0, userList.user[selected].lengthOfMembership);
        glColor3f(1.0, 1.0, 1.0); //white
        glDisableClientState(GL_VERTEX_ARRAY);

        glLineWidth(1); //revert the line width
    return;
}

void compareHistories() {
    //make points for each user
    //make different colors for each user
    //have a legend
}

void createGraph(bool authenticated) {
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
        drawVertices(selectedCustomer);
    } //else, clear the screen
    return;

}

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
        ImGui::ListBox("Chose your user", &selectedUser,
            loginUsers, IM_ARRAYSIZE(loginUsers));
        if (selectedUser != prevSelectedUser) {
            show_menu_options_popup = true;
        }
        ImGui::End();

    }
}


void showMenuOptionsPopup(bool* p_open) {
    //selectedUser = 0;
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
        //ImGui::SliderFloat("GraphHeight", &sliderFloat, (float) userList.user[selectedCustomer].largestExpectedPayment*2, (float)userList.user[selectedCustomer].largestExpectedPayment);
        ImGui::Text("What would you like to do?");
        ImGui::ListBox("Here are your options", &selectedMenuOption,
            menuOptions, IM_ARRAYSIZE(menuOptions));

        if (selectedMenuOption == 2) {
            selectedMenuOption = -1;
            cout << "line 209 reached. Selected Menu Option: "<<selectedMenuOption;
            show_menu_options_popup = false;
            show_customer_information_popup = false;
            show_welcome_popup = true;
            compare_customer_information_popup = false;

        }
        //else if (selectedMenuOption == 0) {
           // compare_customer_information_popup = true;
         // show_menu_options_popup = false;
        //}
        else{
            compare_customer_information_popup = false;

            if (selectedMenuOption == 1 && showMenuOptionsPopup) {
                makeGraph = true;
            }
            else {
                makeGraph = false;
            }
            show_customer_information_popup = true;
            //show_menu_options_popup = false;
        }
            
        ImGui::End();
       // userList.user[selectedCustomer].setGraphCeiling(sliderFloat);
        //userList.user[selectedCustomer].setGraphicalData(); //May be repetitive
    }
}

void showCustomerInformationPopup(bool* p_open) {
    if (!ImGui::Begin("Here are your customers: "))
    {
        ImGui::End();
    }
    else
    {
        static float sliderFloat = 0.f;
        static int sliderInt = 0;
        ImGui::SliderFloat("GraphHeight", &sliderFloat, (float) userList.user[selectedCustomer].largestExpectedPayment*2, (float)userList.user[selectedCustomer].largestExpectedPayment);
        ImGui::Text("Here are your customers. Select One");
        ImGui::ListBox("Chose your customer", &selectedCustomer,
            customers, IM_ARRAYSIZE(customers));
        ImGui::Checkbox("Go back", &show_menu_options_popup);
        ImGui::End();
        userList.user[selectedCustomer].setGraphCeiling(sliderFloat);
        userList.user[selectedCustomer].setGraphicalData(); //May be repetitive
    }
}

void compareCustomerInformationPopup(bool* p_open) {
    if (!ImGui::Begin("Here are your customers: "))
    {
        ImGui::End();
    }
    else
    {
        ImGui::Text("Select Customers to Compare Info");

        ImGui::Text(customers[0]); //show delinquent payments
        ImGui::Text(customers[1]);
        ImGui::Text(customers[2]);
        ImGui::Text(customers[3]);
        ImGui::Text(customers[4]);

        ImGui::Checkbox("Go back", &show_menu_options_popup);
        ImGui::End();

    }
}



int main(int argc, char* argv[]){
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
    
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
                
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
                
        ImGui::NewFrame();

        /*Welcome popup logic*/
        if (show_welcome_popup)
         {
                prevSelectedUser = selectedUser;
                showWelcomePopup(&show_welcome_popup);   //show_welcome_popup boolean in checkbox
        }

        /* Main menu logic*/
        if (prevSelectedUser != selectedUser) { //cureently, the options do nothing. Ideally, close this window and open compare history
            
            show_welcome_popup = false;
            userList.user[0].authKey=1;
            if (show_menu_options_popup)
            {
                makeGraph = false;
                prevSelectedMenuOption = selectedMenuOption;
               showMenuOptionsPopup(&show_menu_options_popup); // where is this boolean? your checkbox is now a list box so you need a different check
            }      
        }

        /* Show History Logic*/
        if (prevSelectedMenuOption != selectedMenuOption) {
            
            if (show_customer_information_popup)
            {
                show_menu_options_popup = false;
                showCustomerInformationPopup(&show_customer_information_popup);
            }  
           /* else if (compare_customer_information_popup)
            {
                show_menu_options_popup = false;
                compareCustomerInformationPopup(&compare_customer_information_popup);
            }*/
            else
                show_menu_options_popup = true;
        }

        /* Compare Customers*/
      /*  if (prevSelectedMenuOption != selectedMenuOption) {

            if (compare_customer_information_popup)
            {
                show_menu_options_popup = false;
                compareCustomerInformationPopup(&compare_customer_information_popup);
            }
            else
                show_menu_options_popup = true;
        }*/
   
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());      
 
       createGraph(makeGraph);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    //RUN_ALL_TESTS();
    return 0;
}

