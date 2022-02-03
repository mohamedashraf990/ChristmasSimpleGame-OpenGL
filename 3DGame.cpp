#define GL_SILENCE_DEPRECATION
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <string.h>



double camerax = 1.2;
double cameray = 1.2;
double cameraz = 1.2;
double z = 1.2;
double GlobalXTree = -0.3;
double GlobalYTree = -0.1;
double GlobalZTree = 0.3;
double GlobalScaleX = 1.3;
double GlobalScaleY = 2;
double GlobalScaleZ = 1;
double playerX;
double playerZ;
double snow;
double torigateY;

bool present1taken = false;
bool present2taken = false;
bool present3taken = false;
bool animation = false;
double snowmanY ;
double treeY ;
double rotatingangle;
double presentsY;
double colors;

double GlobalTreeFlag = false;
bool TreeFlag = false;
double r=0;
double g=0.4;
double b=0.3;
void drawWall(double thickness) {
    glPushMatrix();
    //0/0.8/0.2
    glColor3f(0, 0.8, 0.2);
    glTranslated(0.5, 0.5 * thickness, 0.5);
    glScaled(1.0, thickness, 1.0);
    glutSolidCube(1);
    glPopMatrix();
}

void drawTableLeg(double thick, double len) {
    glPushMatrix();
    glTranslated(0, len / 2, 0);
    glScaled(thick, len, thick);
    glutSolidCube(1.0);
    glPopMatrix();
}

void drawJackPart() {
    glPushMatrix();
    glScaled(0.2, 0.2, 1.0);
    glutSolidSphere(1, 15, 15);
    glPopMatrix();
    glPushMatrix();
    glTranslated(0, 0, 1.2);
    glutSolidSphere(0.2, 15, 15);
    glTranslated(0, 0, -2.4);
    glutSolidSphere(0.2, 15, 15);
    glPopMatrix();
}


void print(int x, int y, char* string)
{
    int len, i;

    //set the position of the text in the window using the x and y coordinates
    glRasterPos2f(x, y);
    

    //get the length of the string to display
    len = (int)strlen(string);

    //loop to display character by character
    for (i = 0; i < len; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
    }
}


void ToriGate(){
    
    glPushMatrix();
    glColor3f(1, 1, 1);
    glTranslated(0.7, 0.25, 0.25);
    glScaled(0.03, 0.4, 0.05);
    glutSolidCube(1);
    glPopMatrix();
    
    
    glPushMatrix();
    glColor3f(1, 1, 1);
    glTranslated(0.9, 0.25, 0.25);
    glScaled(0.03, 0.4, 0.05);
    glutSolidCube(1);
    glPopMatrix();
    
    glPushMatrix();
    glColor3f(1, 1, 1);
    glTranslated(0.8, 0.35, 0.25);
    glScaled(0.3, 0.03, 0.05);
    glutSolidCube(1);
    glPopMatrix();
    
    
    
    glPushMatrix();
    glColor3f(1, 1, 1);
    glTranslated(0.8, 0.3, 0.25);
    glScaled(0.3, 0.03, 0.05);
    glutSolidCube(1);
    glPopMatrix();
    
    
  
}

void drawJack() {
    glPushMatrix();
    drawJackPart();
    glRotated(90.0, 0, 1, 0);
    drawJackPart();
    glRotated(90.0, 1, 0, 0);
    drawJackPart();
    glPopMatrix();
}



void drawTable(double topWid, double topThick, double legThick, double legLen) {
    glPushMatrix();
    glTranslated(0, legLen, 0);
    glScaled(topWid, topThick, topWid);
    glutSolidCube(1.0);
    glPopMatrix();

    double dist = 0.95 * topWid / 2.0 - legThick / 2.0;
    glPushMatrix();
    glTranslated(dist, 0, dist);
    drawTableLeg(legThick, legLen);
    glTranslated(0, 0, -2 * dist);
    drawTableLeg(legThick, legLen);
    glTranslated(-2 * dist, 0, 2 * dist);
    drawTableLeg(legThick, legLen);
    glTranslated(0, 0, -2 * dist);
    drawTableLeg(legThick, legLen);
    glPopMatrix();
}

void setupLights() {
    GLfloat ambient[] = { 0.7f, 0.7f, 0.7, 1.0f };
    GLfloat diffuse[] = { 0.6f, 0.6f, 0.6, 1.0f };
    GLfloat specular[] = { 1.0f, 1.0f, 1.0, 1.0f };
    GLfloat shininess[] = { 50 };
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, shininess);

    GLfloat lightIntensity[] = { 0.7f, 0.7f, 1, 1.0f };
    GLfloat lightPosition[] = { -7.0f, 6.0f, 3.0f, 0.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, lightIntensity);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity);
}

void setupCamera() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // glOrtho(-0.5, 0.5, -0.5, 0.5, -1, 1);
    gluPerspective(60, 640 / 480, 0.001, 100);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(camerax, cameray, cameraz, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}



void Keyboard(unsigned char key, int x, int y) {

    switch (key) {
    case 'm':
        animation = !animation;
        break;
    case 'w':
        cameray += 0.1;
        break;
    case 's':
        cameray -= 0.1;
        break;
    case 'a':
        camerax += 0.1;
        break;
    case 'd':
        camerax -= 0.1;
        break;
    case 'q':
        cameraz += 0.1;
        break;
    case 'e':
        cameraz -= 0.1;
        break;

    case 'i':
    camerax=2.5;
    cameray=2;
    break;
       
    
    case 'o':
    cameray=4;
    break;
           
    case 'p':
    camerax=-2.5;
    cameray=2.5;
    break;
           
    case 'g':
        if (TreeFlag == false) {
            TreeFlag = true;
        }
        else {
            TreeFlag = false;
        }
        break;
    }



    //    if(key=='w'){
    //        cameray+=0.1;
    //    }
    int scoreY =cameray;
    int scoreX=camerax;
    int scoreZ=cameraz;
  
    glColor3f(0, 0, 0);
    char* p0y[20];
 
    sprintf((char*)p0y, "Your Y %d", scoreY);
    print(150, 480, (char*)p0y);
    
    
    glColor3f(0, 0, 0);
    char* p0x[20];
    sprintf((char*)p0x, "Your X %d", scoreX);
    print(250, 480, (char*)p0y);
    
    
    
    glColor3f(0, 0, 0);
    char* p0z[20];
    sprintf((char*)p0z, "Your Z %d", scoreZ);
    print(250, 480, (char*)p0z);
    glutPostRedisplay();

}
void fence() {
    //0.3/0/0

    glPushMatrix();
    glColor3f(0.3, 0, 0);
    glTranslated(0.07, 0.25, 0);
    glScaled(0.2, 0.5, 0.05);
    glutSolidCube(1);
    glPopMatrix();
}



void ChristmasTree() {
    //0.2/0.4/0
    glPushMatrix();
    glColor3f(0.2, 0.4, 0);
    glTranslated(0.5, 0.3, 0.5);
    glRotated(270, 0, 0, 0);
    glScaled(GlobalScaleX, GlobalScaleY, GlobalScaleZ);
    glutSolidCone(0.05, 0.02, 500, 500);
    glPopMatrix();


    // glColor3f(0.2, 0.9, 0.0);

    glPushMatrix();
    glColor3f(0.2, 0.6, 0.3);
    glTranslated(0.5, 0.27, 0.5);
    glRotated(270, 0, 0, 0);
    glScaled(1.3, 2, 1);
    glutSolidCone(0.05, 0.02, 500, 500);
    glPopMatrix();



    glPushMatrix();
    glColor3f(0.2, 0.6, 0.3);
    glTranslated(0.5, 0.24, 0.5);
    glRotated(270, 0, 0, 0);
    glScaled(1.3, 2, 1);
    glutSolidCone(0.05, 0.02, 500, 500);
    glPopMatrix();





    glPushMatrix();
    glScaled(0.05, 0.2, 0.05);
    glColor3f(0.2, 0, 0);
    glTranslated(10, 1, 10);
    glutSolidCube(1);
    glPopMatrix();


}


void drawCharacter() {
    glPushMatrix();
   
    glColor3f(0.2, 1, 1);
    glTranslated(0, 0.1, 0);
    glScaled(0.1, 0.1, 0.05);
    glutSolidCube(1);
    glPopMatrix();



    glPushMatrix();
    glColor3f(0.2, 1, 1);
    glTranslated(0, 0.20, -0.03);
    glutSolidSphere(0.03, 500, 500);
    glPopMatrix();




    glPushMatrix();
    glColor3f(0.2, 1, 1);
    glTranslated(-0.04, 0.04, 0.02);
    glScaled(0.01, 0.05, 0.01);
    glutSolidCube(1);
    glPopMatrix();



    glPushMatrix();
    glColor3f(0.2, 1, 1);
    glTranslated(0.04, 0.04, 0.02);
    glScaled(0.01, 0.05, 0.01);
    glutSolidCube(1);
    glPopMatrix();
}

void fencer(double red, double green, double blue) {
    //0.3/0/0

    glPushMatrix();
    //0/0.4/0.7
    
    

    glColor3f(red, green, blue);
    glTranslated(0.07, 0.25, 0);
    glScaled(0.15, 0.3, 0.05);
    glutSolidCube(1);
    glPopMatrix();
}


void fencerRight(double red, double green, double blue) {
    //0.3/0/0

    glPushMatrix();
    //0/0.4/0.7

    glColor3f(red, green, blue);
    glTranslated(0.07, 0.25, 0);
    glScaled(0.05, 0.3, 0.15);
    glutSolidCube(1);
    glPopMatrix();
}

void DrawXFences() {


    //First Fence
    glPushMatrix();
    glTranslated(0, -0.1, 0);
    fencer(r, g, b);
    glPopMatrix();


    //Second Fence
    glPushMatrix();
    glTranslated(0.15, -0.1, 0);
    fencer(g, r, b);
    glPopMatrix();

    //Third Fence
    glPushMatrix();
    glTranslated(0.3, -0.1, 0);
    fencer(g, b, r);
    glPopMatrix();




    //Fourth Fence
    glPushMatrix();
    glTranslated(0.45, -0.1, 0);
    fencer(b, g, r);
    glPopMatrix();



    //Sixth Fence
    glPushMatrix();
    glTranslated(0.6, -0.1, 0);
    fencer(r, b, g);
    glPopMatrix();


    //7th Fence
    glPushMatrix();
    glTranslated(0.75, -0.1, 0);
    fencer(g, g, r);
    glPopMatrix();

    
    //8th Fence
    glPushMatrix();
    glTranslated(0.9, -0.1, 0);
    fencer(r, r, g);
    glPopMatrix();


}



void DrawYFences() {

    //9th Fence
    glPushMatrix();


    glTranslated(0.95, -0.1, 0.1);
    fencerRight(r, g, b);
    glPopMatrix();




    //10th Fence
    glPushMatrix();
    glTranslated(0.95, -0.1, 0.25);
    fencerRight(r, b, g);
    glPopMatrix();



    //11th Fence
    glPushMatrix();
    glTranslated(0.95, -0.1, 0.4);
    fencerRight(b, r, g);
    glPopMatrix();


    //12th Fence
    glPushMatrix();
    glTranslated(0.95, -0.1, 0.55);
    fencerRight(b, g, r);
    glPopMatrix();


    //13th Fence
    glPushMatrix();
    glTranslated(0.95, -0.1, 0.7);
    fencerRight(g, r, b);
    glPopMatrix();


    //14th Fence
    glPushMatrix();
    glTranslated(0.95, -0.1, 0.85);
    fencerRight(g, b, r);
    glPopMatrix();





    glPushMatrix();
    glTranslated(-0.1, -0.1, 0.1);
    fencerRight(r, g, b);
    glPopMatrix();


    glPushMatrix();
    glTranslated(-0.1, -0.1, 0.25);
    fencerRight(r, b, g);
    glPopMatrix();


    glPushMatrix();
    glTranslated(-0.1, -0.1, 0.4);
    fencerRight(b, g, r);
    glPopMatrix();


    glPushMatrix();
    glTranslated(-0.1, -0.1, 0.55);
    fencerRight(b, r, g);
    glPopMatrix();



    glPushMatrix();
    glTranslated(-0.1, -0.1, 0.7);
    fencerRight(g, r, b);
    glPopMatrix();


    glPushMatrix();
    glTranslated(-0.1, -0.1, 0.85);
    fencerRight(g, b, r);
    glPopMatrix();



}


void createPresents() {

    if (present3taken == false)
    {
        glPushMatrix();
        glColor3f(0.7, 0, 0);
        glTranslated(0.05, 0.25, 0.5);
        glScaled(0.1, 0.1, 0.1);
        glutSolidCube(1);
        glPopMatrix();



        glPushMatrix();
        glColor3f(0.2, 0.7, 0.2);
        glTranslated(0.05, 0.3, 0.5);
        glScaled(0.1, 0.02, 0.1);
        glutSolidCube(1);
        glPopMatrix();



        glPushMatrix();
        glColor3f(0.7, 0, 0);
        glTranslated(0.05, 0.31, 0.5);
        glScaled(0.08, 0.01, 0.01);
        glutSolidCube(1);
        glPopMatrix();


        glPushMatrix();
        glColor3f(0.7, 0, 0);
        glTranslated(0.05, 0.31, 0.5);
        glScaled(0.01, 0.01, 0.08);
        glutSolidCube(1);
        glPopMatrix();

    }
    if (present1taken == false)
    {


        glPushMatrix();
        glColor3f(0.7, 0, 0);
        glTranslated(0.5, 0.25, 0.5);
        glScaled(0.1, 0.1, 0.1);
        glutSolidCube(1);
        glPopMatrix();


        glPushMatrix();
        glColor3f(0.2, 0.7, 0.2);
        glTranslated(0.5, 0.3, 0.5);
        glScaled(0.1, 0.02, 0.1);
        glutSolidCube(1);
        glPopMatrix();



        glPushMatrix();
        glColor3f(0.7, 0, 0);
        glTranslated(0.5, 0.31, 0.5);
        glScaled(0.08, 0.01, 0.01);
        glutSolidCube(1);
        glPopMatrix();


        glPushMatrix();
        glColor3f(0.7, 0, 0);
        glTranslated(0.5, 0.31, 0.5);
        glScaled(0.01, 0.01, 0.08);
        glutSolidCube(1);
        glPopMatrix();

    }













    if (present2taken == false)
    {
        glPushMatrix();
        //0/0.4/0.7

        glColor3f(0.7, 0, 0);
        glTranslated(0.8, 0.25, 0.5);
        glScaled(0.1, 0.1, 0.1);
        glutSolidCube(1);
        glPopMatrix();


        glPushMatrix();

        //0/0.4/0.7
        glColor3f(0.2, 0.7, 0.2);
        glTranslated(0.8, 0.3, 0.5);
        glScaled(0.1, 0.02, 0.1);
        glutSolidCube(1);
        glPopMatrix();




        glPushMatrix();
        glColor3f(0.7, 0, 0);
        glTranslated(0.8, 0.31, 0.5);
        glScaled(0.08, 0.01, 0.01);
        glutSolidCube(1);
        glPopMatrix();


        glPushMatrix();
        glColor3f(0.7, 0, 0);
        glTranslated(0.8, 0.31, 0.5);
        glScaled(0.01, 0.01, 0.08);
        glutSolidCube(1);
        glPopMatrix();
    }


}

void createSnowMan() {
    glPushMatrix();
    glColor3f(1, 1, 1);
    glTranslated(0.2, 0.3, 0.2);
    glutSolidSphere(0.08, 500, 500);
    glPopMatrix();







    glPushMatrix();
    glColor3f(1, 1, 1);
    glTranslated(0.2, 0.43, 0.2);
    glutSolidSphere(0.05, 500, 500);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0, 0, 0);
    glTranslated(0.18, 0.45, 0.25);
    glutSolidSphere(0.008, 500, 500);
    glPopMatrix();



    glPushMatrix();
    glColor3f(0, 0, 0);
    glTranslated(0.23, 0.45, 0.25);
    glutSolidSphere(0.008, 500, 500);
    glPopMatrix();
}
void fcollision() {
    if (playerZ <= 0)
        playerZ = 0;
    if (playerZ >= 0.85) {
        playerZ = 0.85;
    }
    if (playerX <= -0.3) {
        playerX = -0.3;
    }
    if (playerX <= -0.3) {
        playerX = -0.3;
    }
    if (playerX >= 0.5) {
        playerX = 0.5;
    }




}
void pcollision() {

    if (playerX >= 0.05 & playerX <= 0.15 & playerZ >= 0.35 & playerZ <= 0.45)
        present1taken = true;

    if (playerX >= 0.35 & playerX <= 0.45 & playerZ >= 0.35 & playerZ <= 0.45)
        present2taken = true;

    if (playerX <= -0.25 & playerX >=- 0.35 & playerZ >= 0.35 & playerZ <= 0.45)
        present3taken = true;

}
void Special(int key, int x, int y) {
    float a = 1.0;

    switch (key) {
    case GLUT_KEY_UP:

            playerZ += 0.1;  rotatingangle = 180;

        break;
    case GLUT_KEY_DOWN:

            playerZ -= 0.1;rotatingangle = 0;
        break;
    case GLUT_KEY_LEFT:
            playerX -= 0.1;rotatingangle = 90;
        break;
    case GLUT_KEY_RIGHT:
            playerX += 0.1;rotatingangle = -90;
        break;
    }

    glutPostRedisplay();
}
void TimerTimeIsUp(int value) {
    if (present1taken == false || present2taken == false || present3taken == false) {
        glClearColor(1, 0, 0, 0);
        //lost
    }
    else
    {
        //won
        glClearColor(0, 0, 1, 0);
    }

}
void Colors(int value){
    if(colors==0){
        r=0.5;g=0.8;
        
        
    }
    if(colors==1){
        b=1;r=0.3;
        
    }
    if(colors==2){
        r=1;g=0.3;
        
    }
    if(colors==3){
        g=1;b=0.6;
        
    }
    if(colors==4){
        
        r=0.3;g=0.7;b=0.4;
        
    }
 
    
    
    
    
    
    colors++;
    
    if(colors ==4){
        colors=0;
    }
    
    
    
    glutTimerFunc(1000, Colors, 0);
    
}

void Display() {
    setupLights();
    setupCamera();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            //Drawing a wall

    glPushMatrix();
    drawWall(0.02);
    glPopMatrix();

    glPushMatrix();
    DrawXFences();
    glPopMatrix();

    glPushMatrix();
    DrawYFences();
    
    glPopMatrix();


    glPushMatrix();
    glTranslated(playerX, 0, playerZ);
    glTranslated(0.4,0,0.1);
    glRotated(rotatingangle,0,1,0);
    drawCharacter();
    glPopMatrix();


    if (TreeFlag == true) {
        //        GlobalXTree+=0.001;
        GlobalScaleX += 0.01;
        GlobalScaleY += 0.01;
        GlobalScaleZ += 0.01;

    }








    //    glPushMatrix();
    //    glRotated(90, 0, 0, 1.0);
    //    drawWall(0.02);
    //    glPopMatrix();
    //
    //    glPushMatrix();
    //    glRotated(-90, 1.0, 0.0, 0.0);
    //    drawWall(0.02);
    //    glPopMatrix();
    glPushMatrix();
    glTranslated(0.3,treeY -0.1, 0.3);
    ChristmasTree();
    glPopMatrix();



    glPushMatrix();
    glTranslated(GlobalXTree, treeY+ GlobalYTree, GlobalZTree);

    ChristmasTree();
    glPopMatrix();

   


       // glPushMatrix();
        //glTranslated(0, presentsY - 0.2, 0);
        //createPresents();
        //glPopMatrix();
    


  

        glPushMatrix();
        glTranslated(0, presentsY - 0.2, 0);
        createPresents();
        glPopMatrix();
    
    glPushMatrix();
    glTranslated(0, torigateY, 0);
    ToriGate();
    glPopMatrix();


    glPushMatrix();
    glTranslated(0,snowmanY -0.2, 0);
    createSnowMan();
    glPopMatrix();

    fcollision();
    pcollision();

    glutPostRedisplay();

    if (animation == true) {
        snowmanY += 0.005;
        presentsY += 0.005;
        treeY += 0.005;
        torigateY +=0.005;

        if (snowmanY == 0.4) {
            snowmanY = 0;
            presentsY = 0;
            treeY = 0;
            torigateY = 0;
        }
    }
    else
    {
        presentsY = 0;
    }

    
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);

    glutInitWindowSize(640, 480);
    glutInitWindowPosition(50, 50);

    glutCreateWindow("Lab 5");
    glutDisplayFunc(Display);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);

    glShadeModel(GL_SMOOTH);
    glutKeyboardFunc(Keyboard);
    glutSpecialFunc(Special);
    glutTimerFunc(10000, TimerTimeIsUp, 0);
    glutTimerFunc(1000, Colors, 0);
    glutMainLoop();
}
