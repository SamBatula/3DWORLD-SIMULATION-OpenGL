//  hw4.cpp
//  Graphics
//
//  Created by Samson Batula on 4/2/23.
//
//  Creator: Samson Batula
/******************************************
*
* Official Name:  Samsondeen Batula
*
* Call me: Samson
*
* E-mail:  sobatula@syr.edu
*
* Assignment:  Assignment 4
*
* Environment/Compiler:  Xcode 14.1
*
* Date submitted:  April 10, 2023
*
* References:  list any references you used or write NONE
 Class presentations/ code from class
*
* Interactions:
 
 Required keys:
 D opens/closes the door.
 L turns on/off the ceiling lamp.
 S opens/closes the window shade.

 Required Color picking:
 Click the door to open it.
 Click the light switch to turn on the light.
 Click the window shade to raise the shade.

 Required Collision detection:
 Close to the flashlight, it comes to your hand and turns on.
 Close to the cauldron, it glows.

 Menu:
 Launch orb.
 Select among outcomes.

*
*******************************************/
#define _CRT_SECURE_NO_DEPRECATE

#include <stdio.h>
#include <cmath>
#include <iostream>

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

#define PI 3.14159265358979324



// global variables
static char camerapov = '1'; // point of view of the camera pointing North/South/East/West

// movement with collision
static float meX=6, meY=6.5,meZ=-16;
static float angle=0;  //angle facing
static float stepsize=1;  //step size
static float turnsize=10; //degrees to turn

// door movement
static bool moveDoor = false;  //true for ANIMATION
static int step = 0; // Steps in open/closing box lid.
static float doorAngle = 0;

// shade movement
static bool moveShade = false; //true for ANIMATION
static float shadeAngle = 0;
static int shadestep = 0; // Steps in open/closing box lid.


// ceiling light on/off
static bool clight = false;

void setProjection()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(120, 1, 1, 100);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void drawing(void)
{
    //Clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    //Set Projection
    setProjection();
    
    //Clear Modeview Matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    switch (camerapov){
        case '1':
            // from north view
//                gluLookAt(6,8,-16,
//                          6,5,-6,
//                          0,1,0);
            
            gluLookAt(meX , meY , meZ,
                      meX + sin(angle * PI/180), meY , meZ + cos(angle*PI/180),
                      0, 1, 0);

            break;
        case '2':
            // from south view
                    gluLookAt(6, 7, 5,
                             6, 5, -16,
                              0,1,0);
            break;
        case '3':
           // from east view
                    gluLookAt(13, 6.6, -12,
                              -6 , 2, -9,
                              0,1,0);
            break;
        case '4':
             // from west view
                    gluLookAt(-4, 6.6, -11,
                               6 , 4, -9,
                              0,1,0);
            break;
        case '5':
            //from overhead (from NORTH alignment)
                    gluLookAt(6,15,-16,
                              6,-10,-10,
                              0,1,0);
            break;
    }

// ***************************************************************************************
    
    //Build model
    glEnable(GL_DEPTH_TEST);
   
    //lighting resources
    // Turn on OpenGL lighting.
    glEnable(GL_LIGHTING);
    
    /* CREATING STRUCTURE (GRASSLAND/SUN/TREES) ******************************************************************* */
    
    // sun with lighting
    // Light property vectors.
    float lightAmbsun[] = { 0.0, 0.0, 0.0, 1.0 };
    float lightDifAndSpecsun[] = { 1.0, 1.0, 1.0, 1.0 };
    float lightPos0[] = { 0.0, 1.5, 3.0, 1.0 };
    float sunAmb[] = { 1.0, 0.7, 0.0, 1.0 };
    
    glLightfv(GL_LIGHT0, GL_AMBIENT, sunAmb);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE); // Enable local viewpoint.
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDifAndSpecsun);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightDifAndSpecsun);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
    
    glEnable(GL_LIGHT0); // Enable particular light source.
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, sunAmb);
    
    glPushMatrix();
    glTranslated(6,17,-10);
    glScaled(4, 4, 4);
    glutSolidSphere(1, 360, 360);
    glPopMatrix();
    
    //base - top is at y=0
    //green flat piece (grassland)
    glDisable(GL_LIGHTING);
    glColor3f(0.0,0.9,0.0);
    glPushMatrix();
    glTranslated(6,-.5,-9.01);
    glScaled(50, 10, 50);
    glutSolidCube(1);
    glPopMatrix();
    glEnable(GL_LIGHTING);

    /* CREATING all the TREES ******************************************************************* */
   
    //tree 1 (far left tree in ortho view/ closest tree in frustum view)
    // glColor3f(0,0.3,0);
    float matAmbAndDifuno[] = {0.0, 0.3, 0.0, 1.0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifuno);
    glPushMatrix();
    glTranslated(14,7,-10);
    glScaled(1, 5, 0.5);
    glutSolidCube(1);
    glPopMatrix();
    // cone on top of tree 1
    //glColor3f(0,0.5,0);
    float matAmbAndDiftwo[] = {0.0, 0.5, 0.0, 1.0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDiftwo);
    glPushMatrix();
    glTranslated(14, 9, -10);
    glRotatef(-90, 0, 0, 0);
    glScaled(1, 1, 1);
    glutSolidCone(1, 2, 360, 360);
    glPopMatrix();

    //tree 2 (middle tree in ortho view/ middle tree in frustum view)
   // glColor3f(0.0,0.3,0);
    float matAmbAndDif28[] = {0.0, 0.3, 0.0, 1.0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDif28);
    glPushMatrix();
    glTranslated(9,3.5,-5.9);
    glScaled(1, 7, 0.5);
    glutSolidCube(1);
    glPopMatrix();
    // cone on top of tree 2
    // glColor3f(0.0,0.5,0);
    float matAmbAndDif29[] = {0.0, 0.5, 0.0, 1.0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDif29);
    glPushMatrix();
    glTranslated(9, 6.5, -6);
    glRotatef(-90, 0, 0, 0);
    glScaled(1, 1, 1);
    glutSolidCone(1, 2, 360, 360);
    glPopMatrix();
    
    //tree 3 (far right tree in ortho view/ far right tree in frustum view)
    // glColor3f(0,0.3,0);
    float matAmbAndDif30[] = {0.0, 0.3, 0.0, 1.0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDif30);
    glPushMatrix();
    glTranslated(-4,5.5,-9.2);
    glScaled(0.5, 8, 0.5);
    glutSolidCube(1);
    glPopMatrix();
    // cone on top of tree 3
    // glColor3f(0,0.5,0);
    float matAmbAndDif31[] = {0.0, 0.5, 0.0, 1.0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDif31);
    glPushMatrix();
    glTranslated(-4, 8.2, -9.3);
    glRotatef(-90, 0, 0, 0);
    glScaled(1, 1, 1);
    glutSolidCone(1, 2, 360, 360);
    glPopMatrix();
    
    //tree 4
    // glColor3f(0,0.3,0);
    float matAmbAndDif32[] = {0.0, 0.3, 0.0, 1.0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDif32);
    glPushMatrix();
    glTranslated(-0.5,5.5,-12);
    glScaled(0.5, 8, 0.5);
    glutSolidCube(1);
    glPopMatrix();
    // cone on top of tree 4
   // glColor3f(0,0.5,0);
    float matAmbAndDif33[] = {0.0, 0.5, 0.0, 1.0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDif33);
    glPushMatrix();
    glTranslated(-0.5, 8.2, -12);
    glRotatef(-90, 0, 0, 0);
    glScaled(1, 1, 1);
    glutSolidCone(1, 2, 360, 360);
    glPopMatrix();
    
    //tree 5
    // glColor3f(0,0.3,0);
    float matAmbAndDif34[] = {0.0, 0.3, 0.0, 1.0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDif34);
    glPushMatrix();
    glTranslated(-0.5,4,-10);
    glScaled(0.3, 7, 0.3);
    glutSolidCube(1);
    glPopMatrix();
    // cone on top of tree 5
   // glColor3f(0,0.5,0);
    float matAmbAndDif35[] = {0.0, 0.5, 0.0, 1.0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDif35);
    glPushMatrix();
    glTranslated(-0.5, 7, -10);
    glRotatef(-90, 0, 0, 0);
    glScaled(.5, .5, .5);
    glutSolidCone(1, 2, 360, 360);
    glPopMatrix();
    
    //tree 6
    // glColor3f(0,0.3,0);
    float matAmbAndDif36[] = {0.0, 0.3, 0.0, 1.0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDif36);
    glPushMatrix();
    glTranslated(-0.5,5.5,-7);
    glScaled(0.5, 8, 0.5);
    glutSolidCube(1);
    glPopMatrix();
    // cone on top of tree 6
   // glColor3f(0,0.5,0);
    float matAmbAndDif37[] = {0.0, 0.5, 0.0, 1.0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDif37);
    glPushMatrix();
    glTranslated(-0.5, 8.2, -7);
    glRotatef(-90, 0, 0, 0);
    glScaled(1, 1, 1);
    glutSolidCone(1, 2, 360, 360);
    glPopMatrix();
    
    //tree 7
    // glColor3f(0,0.3,0);
    float matAmbAndDif38[] = {0.0, 0.3, 0.0, 1.0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDif38);
    glPushMatrix();
    glTranslated(-3,5.5,-7);
    glScaled(0.5, 8, 0.5);
    glutSolidCube(1);
    glPopMatrix();
    // cone on top of tree 7
    // glColor3f(0,0.5,0);
    float matAmbAndDif39[] = {0.0, 0.5, 0.0, 1.0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDif39);
    glPushMatrix();
    glTranslated(-3, 8.2, -7);
    glRotatef(-90, 0, 0, 0);
    glScaled(1, 1, 1);
    glutSolidCone(1, 2, 360, 360);
    glPopMatrix();
    
    //tree 8
    // glColor3f(0,0.3,0);
    float matAmbAndDif40[] = {0.0, 0.3, 0.0, 1.0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDif40);
    glPushMatrix();
    glTranslated(3,5.5,-7);
    glScaled(0.5, 8, 0.5);
    glutSolidCube(1);
    glPopMatrix();
    // cone on top of tree 8
    // glColor3f(0,0.5,0);
    float matAmbAndDif41[] = {0.0, 0.5, 0.0, 1.0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDif41);
    glPushMatrix();
    glTranslated(3, 8.2, -7);
    glRotatef(-90, 0, 0, 0);
    glScaled(1, 1, 1);
    glutSolidCone(1, 2, 360, 360);
    glPopMatrix();
    
    //tree 9
    // glColor3f(0,0.3,0);
    float matAmbAndDif42[] = {0.0, 0.3, 0.0, 1.0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDif42);
    glPushMatrix();
    glTranslated(4.5,5.5,-4);
    glScaled(0.5, 8, 0.5);
    glutSolidCube(1);
    glPopMatrix();
    // cone on top of tree 9
    // glColor3f(0,0.5,0);
    float matAmbAndDif43[] = {0.0, 0.5, 0.0, 1.0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDif43);
    glPushMatrix();
    glTranslated(4.5, 8.2, -4);
    glRotatef(-90, 0, 0, 0);
    glScaled(1, 1, 1);
    glutSolidCone(1, 2, 360, 360);
    glPopMatrix();
    
    //tree 9
    // glColor3f(0,0.3,0);
    float matAmbAndDif44[] = {0.0, 0.3, 0.0, 1.0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDif44);
    glPushMatrix();
    glTranslated(8,5.5,-5);
    glScaled(0.5, 8, 0.5);
    glutSolidCube(1);
    glPopMatrix();
    // cone on top of tree 9
   // glColor3f(0,0.5,0);
    float matAmbAndDif45[] = {0.0, 0.5, 0.0, 1.0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDif45);
    glPushMatrix();
    glTranslated(8, 8.2, -5);
    glRotatef(-90, 0, 0, 0);
    glScaled(1, 1, 1);
    glutSolidCone(1, 2, 360, 360);
    glPopMatrix();
    
    //tree 9
    // glColor3f(0,0.3,0);
    float matAmbAndDif46[] = {0.0, 0.3, 0.0, 1.0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDif46);
    glPushMatrix();
    glTranslated(11,5.5,-7);
    glScaled(0.5, 8, 0.5);
    glutSolidCube(1);
    glPopMatrix();
    // cone on top of tree 9
    // glColor3f(0,0.5,0);
    float matAmbAndDif47[] = {0.0, 0.5, 0.0, 1.0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDif47);
    glPushMatrix();
    glTranslated(11, 8.2, -7);
    glRotatef(-90, 0, 0, 0);
    glScaled(1, 1, 1);
    glutSolidCone(1, 2, 360, 360);
    glPopMatrix();
    
    //tree 10
    // glColor3f(0,0.3,0);
    float matAmbAndDif48[] = {0.0, 0.3, 0.0, 1.0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDif48);
    glPushMatrix();
    glTranslated(14,5.5,-5);
    glScaled(0.5, 8, 0.5);
    glutSolidCube(1);
    glPopMatrix();
    // cone on top of tree 10
   // glColor3f(0,0.5,0);
    float matAmbAndDif49[] = {0.0, 0.5, 0.0, 1.0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDif49);
    glPushMatrix();
    glTranslated(14, 8.2, -5);
    glRotatef(-90, 0, 0, 0);
    glScaled(1, 1, 1);
    glutSolidCone(1, 2, 360, 360);
    glPopMatrix();
    
    //tree 11
  //  glColor3f(0,0.3,0);
    float matAmbAndDif50[] = {0.0, 0.3, 0.0, 1.0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDif50);
    glPushMatrix();
    glTranslated(17,5.5,-8);
    glScaled(0.5, 8, 0.5);
    glutSolidCube(1);
    glPopMatrix();
    // cone on top of tree 11
    // glColor3f(0,0.5,0);
    float matAmbAndDif51[] = {0.0, 0.5, 0.0, 1.0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDif51);
    glPushMatrix();
    glTranslated(17, 8.2, -8);
    glRotatef(-90, 0, 0, 0);
    glScaled(1, 1, 1);
    glutSolidCone(1, 2, 360, 360);
    glPopMatrix();
    
    //tree 12
   // glColor3f(0,0.3,0);
    float matAmbAndDif52[] = {0.0, 0.3, 0.0, 1.0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDif52);
    glPushMatrix();
    glTranslated(13,5.5,-8);
    glScaled(0.5, 8, 0.5);
    glutSolidCube(1);
    glPopMatrix();
    // cone on top of tree 12
  //  glColor3f(0,0.5,0);
    float matAmbAndDif53[] = {0.0, 0.5, 0.0, 1.0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDif53);
    glPushMatrix();
    glTranslated(13, 8.2, -8);
    glRotatef(-90, 0, 0, 0);
    glScaled(1, 1, 1);
    glutSolidCone(1, 2, 360, 360);
    glPopMatrix();
    
    //tree 14
    //  glColor3f(0,0.3,0);
    float matAmbAndDif54[] = {0.0, 0.3, 0.0, 1.0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDif54);
    glPushMatrix();
    glTranslated(10,5.5,-12);
    glScaled(0.5, 8, 0.5);
    glutSolidCube(1);
    glPopMatrix();
    // cone on top of tree 14
    // glColor3f(0,0.5,0);
    float matAmbAndDif55[] = {0.0, 0.5, 0.0, 1.0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDif55);
    glPushMatrix();
    glTranslated(10, 8.2, -12);
    glRotatef(-90, 0, 0, 0);
    glScaled(1, 1, 1);
    glutSolidCone(1, 2, 360, 360);
    glPopMatrix();
    
    glDisable(GL_LIGHT0);

}

void house(void){
    glDisable(GL_LIGHTING);

    // cone on top of house
    // dark brown
    glColor3ub(160,82,45);
    glPushMatrix();
    glTranslated(6,8.35,-10);
    glRotatef(-90, 0, 0, 0);
    glScaled(2.7, 2.7, 2.7);
    glutSolidCone(1.3, 1, 360, 360);
    glPopMatrix();
  
    // pavement to house
    // dark grey
    glColor3ub(75,75,75);
    glPushMatrix();
    glTranslated(6,4.5,-11.5);
    glScaled(5.3, 0.5, 7.6);
    glutSolidCube(1);
    glPopMatrix();
    
    
    // front door knob
    // dark grey
    glColor3ub(75,75,75);
    glPushMatrix();
    glTranslated(6.3, 6, -12.2);
    glScaled(0.3, 0.3, 0.3);
    glutSolidSphere(0.5, 360, 360);
    glPopMatrix();
    
    
    // front door on house
    // brown
    glColor3ub(160,82,45);
    glPushMatrix();
    glTranslated(6,6,-12.2);
    glScaled(1, 3, 0.2);
    glutSolidCube(1);
    glPopMatrix();
    
    // table top
    // red wine color
    glColor3ub(255,87,51);
    glPushMatrix();
    glTranslated(6,5.5,-11.7);
    glScaled(1, 0.25, 0.2);
    glutSolidSphere(1, 360, 360);
    glPopMatrix();
    // table legs
    glColor3ub(114,47,55);
    glPushMatrix();
    glTranslated(5.5,5.0,-11.7);
    glScaled(0.1, 0.7, 0.2);
    glutSolidCube(1);
    glPopMatrix();
    // table legs
    glColor3ub(114,47,55);
    glPushMatrix();
    glTranslated(6.5,5.0,-11.7);
    glScaled(0.1, 0.7, 0.2);
    glutSolidCube(1);
    glPopMatrix();
    
    glEnable(GL_LIGHTING);
}

void frontsideofhouse (void){
    
    // window with blinds (left window)
    glDisable(GL_LIGHTING);
    glColor3ub(164, 164, 164); // light gray color
    glPushMatrix();
    glTranslated(7,6.9,-12.2);
    glScaled(1.1, 1.1, 0.2);
    glutSolidCube(1);
    glPopMatrix();
    glEnable(GL_LIGHTING);
    // black color
    float matAmbAndDif8[] = {0.0, 0.0, 0.0, 1.0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDif8);

    glPushMatrix();
    glTranslated(7,6.9,-12.3);
    glScaled(0.1, 1, 0.1);
    glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
    glTranslated(7,6.9,-12.3);
    glScaled(1, 0.1, 0.1);
    glutSolidCube(1);
    glPopMatrix();

    // window with blinds (right window)
    glDisable(GL_LIGHTING);
    glColor3ub(164, 164, 164); // light gray color
    glPushMatrix();
    glTranslated(5,6.9,-12.2);
    glScaled(1.1, 1.1, 0.2);
    glutSolidCube(1);
    glPopMatrix();
    glEnable(GL_LIGHTING);

    // black color
    float matAmbAndDif10[] = {0.0, 0.0, 0.0, 1.0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDif10);
    glPushMatrix();
    glTranslated(5,6.9,-12.3);
    glScaled(0.1, 1, 0.1);
    glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
    glTranslated(5,6.9,-12.3);
    glScaled(1, 0.1, 0.1);
    glutSolidCube(1);
    glPopMatrix();
    
    // tan
    // front face of house (LEFT SIDE)
    glDisable(GL_LIGHTING);
    glColor3f(0.82,0.71,0.55);
    glPushMatrix();
    glTranslated(7.5,5.5,-12.2);
    glScaled(2, 1.7, 0.1);
    glutSolidCube(1);
    glPopMatrix();
    glColor3ub(222, 184, 135);
    glPushMatrix();
    glTranslated(7.5,8,-12.2);
    glScaled(2, 1, 0.1);
    glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
    glTranslated(8,6,-12.2);
    glScaled(1, 3, 0.1);
    glutSolidCube(1);
    glPopMatrix();
    // front face of house (RIGHT SIDE)
    glPushMatrix();
    glTranslated(4.5,5.5,-12.2);
    glScaled(2, 1.7, 0.1);
    glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
    glTranslated(4.5,8,-12.2);
    glScaled(2, 1, 0.1);
    glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
    glTranslated(4,6,-12.2);
    glScaled(1, 3, 0.1);
    glutSolidCube(1);
    glPopMatrix();
    // top middle piece on door
    glPushMatrix();
    glTranslated(6,8,-12.2);
    glScaled(1, 1, 0.1);
    glutSolidCube(1);
    glPopMatrix();
    glEnable(GL_LIGHTING);
}

void leftsideofhouse (void){
    glDisable(GL_LIGHTING);
    glColor3ub(222, 184, 135); // tan
    glPushMatrix();
    glTranslated(8.5,5.3,-10);
    glRotated(90, 0, 1, 0);
    glScaled(4.5, 1, 0.1);
    glutSolidCube(1);
    glPopMatrix();
    
    //top piece
    glPushMatrix();
    glTranslated(8.5,8,-10);
    glRotated(90, 0, 1, 0);
    glScaled(4.5, 1, 0.1);
    glutSolidCube(1);
    glPopMatrix();
    glEnable(GL_LIGHTING);

}

void rightsideofhouse (void){
    
    // tan
    glDisable(GL_LIGHTING);
    glColor3ub(222, 184, 135);

    glPushMatrix();
    glTranslated(3.5,5.3,-10);
    glRotated(90, 0, 1, 0);
    glScaled(4.5, 1, 0.1);
    glutSolidCube(1);
    glPopMatrix();
    
    glPushMatrix();
    glTranslated(3.5,8,-10);
    glRotated(90, 0, 1, 0);
    glScaled(4.5, 1, 0.1);
    glutSolidCube(1);
    glPopMatrix();
    glEnable(GL_LIGHTING);
}

void shades (void){
    
    // right side
    // glColor3ub(25, 25, 25);
    // black
    float matAmbAndDif14[] = {0.0, 0.0, 0.0, 1.0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDif14);
     glPushMatrix();
     glTranslated(3.5,6.6,-10);
     glRotatef(90, 0, 1, 0);
     glRotatef(shadeAngle, 1, 0, 0);
     glScaled(4.35, 1.75, 0.05);
     glutSolidCube(1);
     glPopMatrix();
    
    // left side
     // glColor3ub(25, 25, 25);
     glPushMatrix();
     glTranslated(8.5,6.6,-10);
     glRotatef(90, 0, 1, 0);
     glRotatef(shadeAngle, 1, 0, 0);
     glScaled(4.35, 1.75, 0.05);
     glutSolidCube(1);
     glPopMatrix();
    
    // window with blinds (back right)
    // glColor3ub(25, 25, 25);
    glPushMatrix();
    glTranslated(7.53,6.8,-7.75);
    glRotatef(shadeAngle, 1, 0, 0);
    glScaled(0.85, 1.78, 0.05);
    glutSolidCube(1);
    glPopMatrix();
    
    // window with blinds (back left)
    // glColor3ub(25, 25, 25);
    glPushMatrix();
    glTranslated(4.45,6.8,-7.75);
    glRotatef(shadeAngle, 1, 0, 0);
    glScaled(0.9, 1.78, 0.05);
    glutSolidCube(1);
    glPopMatrix();
}

void backsideofhouse (void){
    // back face of house (right SIDE) when you're on the back side of the house
    glDisable(GL_LIGHTING);
    glColor3ub(222, 184, 135);
    glPushMatrix();
    glTranslated(7.8,5.3,-7.75);
    glScaled(1.4, 1.2, 0.1);
    glutSolidCube(1);
    glPopMatrix();
    glColor3ub(222, 184, 135);
    glPushMatrix();
    glTranslated(7.8,8.08,-7.75);
    glScaled(1.4, 0.7, 0.1);
    glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
    glTranslated(8.24,6.2,-7.75);
    glScaled(0.5, 3, 0.1);
    glutSolidCube(1);
    glPopMatrix();
    
    // back face of house (left SIDE) when you're on the back side of the house
    glPushMatrix();
    glTranslated(4.2,5.3,-7.75);
    glScaled(1.4, 1.2, 0.1);
    glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
    glTranslated(4.2,8.08,-7.75);
    glScaled(1.4, 0.7, 0.1);
    glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
    glTranslated(3.76,6.2,-7.75);
    glScaled(0.5, 3, 0.1);
    glutSolidCube(1);
    glPopMatrix();
    // top middle piece on door
    glPushMatrix();
    glTranslated(6,8.08,-7.75);
    glScaled(2.3, 0.7, 0.1);
    glutSolidCube(1);
    glPopMatrix();
    glEnable(GL_LIGHTING);
}

void backdoor (void){
    
    glDisable(GL_LIGHTING);
    // back door knob
    glColor3ub(108, 108, 108);
    glPushMatrix();
    glTranslated(6.3, 6, -7.75);
    glRotatef(doorAngle, 0.0, 1.0, 0.0);
    glScaled(0.3, 0.3, 0.3);
    glutSolidSphere(0.5, 360, 360);
    glPopMatrix();

    // back door on house
    glColor3ub(160,82,45);
    glPushMatrix();
    glTranslated(6,6.25,-7.75);
    glRotatef(doorAngle, 0.0, 1.0, 0.0);
    glScaled(2.2, 2.9, 0.2);
    glutSolidCube(1);
    glPopMatrix();
    
    glEnable(GL_LIGHTING);
}

void lightswitch (void){
    
    glDisable(GL_LIGHTING);
    // light switch base
    glColor3ub(30,30,30);
    glPushMatrix();
    glTranslated(4.7,5.5,-7.9);
    glScaled(0.2, 0.5, 0.2);
    glutSolidCube(1);
    glPopMatrix();
    
    if (clight){
        // light switch (on)
        glColor3ub(200,200,200);
        glPushMatrix();
        glTranslated(4.7,5.5,-8);
        glRotatef(40, 0, 0, 0);
        glScaled(0.1, 0.1, 0.2);
        glutSolidCube(1);
        glPopMatrix();
    }
    else{
        // light switch (off)
        glColor3ub(200,200,200);
        glPushMatrix();
        glTranslated(4.7,5.5,-8);
        glRotatef(-40, 0, 0, 0);
        glScaled(0.1, 0.1, 0.2);
        glutSolidCube(1);
        glPopMatrix();
    }
    
    glEnable(GL_LIGHTING);

}
void ceilinglight (void){
    
    // light properties
    float ceilingAmb[] = { 0.0, 0.6, 1.0, 1.0 }; // bluish color
    float lightDifAndSpec[] = { 1.0, 1.0, 1.0, 1.0 };
    float lightPos1[] = { 6.0, 9, -10.0, 1.0 }; // position the light to the lightbulb
    float lightAmb[] = { 0.0, 0.0, 0.0, 1.0 };

    // Light properties.
    glLightfv(GL_LIGHT1, GL_AMBIENT, lightAmb);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDifAndSpec);
    glLightfv(GL_LIGHT1, GL_SPECULAR, lightDifAndSpec);
    glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);
    
    // Global ambient light.
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ceilingAmb); // global amb light
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE); // Enable local viewpoint.
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE); // Enable two-sided lighting.

    
    glDisable(GL_LIGHTING);
    // ceiling light base
    glColor3ub(80,80,80);
    glPushMatrix();
    glTranslated(6,9,-10);
    glScaled(0.1, 0.7, 0.2);
    glutSolidCube(1);
    glPopMatrix();
    
    // bulb base (black part)
    glColor3ub(80,80,80);
    glPushMatrix();
    glTranslated(6,8.5,-10);
    glRotatef(-90, 0, 0, 0);
    glScaled(0.1, 0.1, 0.2);
    glutSolidCone(3, 3, 360, 360);
    glPopMatrix();

  
    if (clight){
        glEnable(GL_LIGHT1);
        glEnable(GL_LIGHTING);

        // flashlight bulb (lighting part)
        float matAmbAndDif19[] = {1, 1, 1, 1.0};
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDif19);
        glPushMatrix();
        glTranslated(6,8.55,-10);
        glRotatef(-90, 0, 0, 0);
        glScaled(0.1, 0.1, 0.2);
        glutSolidCone(1, 1, 360, 360);
        glPopMatrix();
    } else{
        glDisable(GL_LIGHT1);
    }
}

void flashlight(void){
    
    // light properties
    float flashAmb[] = { 1.0, 0.0, 3.0, 1.0 }; // purplish color
    float lightDifAndSpec2[] = { 1.0, 1.0, 1.0, 1.0 };
    float lightPos2[] = { meX, meY, meZ, 1.0 };
    float lightAmb2[] = { 0.0, 0.0, 0.0, 1.0 };

    // Light properties.
    glLightfv(GL_LIGHT2, GL_AMBIENT, lightAmb2);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, lightDifAndSpec2);
    glLightfv(GL_LIGHT2, GL_SPECULAR, lightDifAndSpec2);
    glLightfv(GL_LIGHT2, GL_POSITION, lightPos2);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, flashAmb);
    
    glDisable(GL_LIGHTING);
    // flashlight handle
    glColor3ub(30,30,30);
    glPushMatrix();
    glTranslated(6,5.8,-11.4);
    glScaled(0.1, 0.1, 0.33);
    glutSolidCube(1);
    glPopMatrix();
    // bulb base (black part)
    glColor3ub(30,30,30);
    glPushMatrix();
    glTranslated(6,5.8,-11.6);
    glScaled(0.1, 0.1, 0.2);
    glutSolidCone(1, 1, 360, 360);
    glPopMatrix();
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT2);
    // flashlight bulb (white part)
    float matAmbAndDif22[] = {1, 1, 1, 1.0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDif22);
    glPushMatrix();
    glTranslated(6,5.8,-11.65);
    glScaled(0.1, 0.1, 0.2);
    glutSolidCone(0.5, 0.5, 360, 360);
    glPopMatrix();
    
    
}

// door ANIMATION
void animateDoor(int someValue)
{
    if (moveDoor){
        if(doorAngle <= 150){
            doorAngle +- 1;
        }
    }
    
glutTimerFunc(100, animateDoor, 1);
}

// shade ANIMATION
void animateShade(int someValue)
{
    if (moveShade){
        if(shadeAngle <= 150)
            shadeAngle += 1;
    }
 
    
glutTimerFunc(100, animateShade, 1);
}


// Drawing (display) routine.
void drawScene(void)
{
   //Clear buffers
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
   //Set Projection
   setProjection();
    
    //Clear Modeview Matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    drawing();
    house();
    frontsideofhouse();
    backsideofhouse();
    rightsideofhouse();
    leftsideofhouse();
    shades();
    flashlight();
    ceilinglight();
    backdoor();
    lightswitch();
    
    glutSwapBuffers();
}

// Initialization routine.
void setup(void)
{
    // create sky color here light blue
    glClearColor(0.1, 0.5, 1.0, 0.0);
    glEnable(GL_DEPTH_TEST); // Enable depth testing.
}


void resize(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    setProjection();
}

// Callback Special Keys for non-ASCII key entries
void specialkeyInput(int key, int x, int y)
{
    switch(key){
        
        case GLUT_KEY_UP: //forward
            std::cout << meX << " " << meZ << std::endl;
            meZ += stepsize*cos(angle*PI/180);
            meX += stepsize*sin(angle*PI/180);
            break;
        case GLUT_KEY_DOWN: //back
            meZ -= stepsize*cos(angle*PI/180);
            meX -= stepsize*sin(angle*PI/180);
            break;
        case GLUT_KEY_RIGHT: //turn right
            angle -= turnsize;
            break;
        case GLUT_KEY_LEFT: //turn left
             angle += turnsize;
            break;
    }//end switch
    
    glutPostRedisplay();
    
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
   switch(key)
   {
      // Press escape to exit.
      case 27:
         exit(0);
         break;
       case '1':
           camerapov = '1';
           std:: cout << "North POV enabled" << std::endl;
           glutPostRedisplay();
           break;
       case '2':
           camerapov = '2';
           std::cout << "south POV enabled" << std::endl;
           glutPostRedisplay();
           break;
       case '3':
           camerapov = '3';
           std::cout << "East POV enabled" << std::endl;
           glutPostRedisplay();
           break;
       case '4':
           camerapov = '4';
           std::cout << "West POV enabled" << std::endl;
           glutPostRedisplay();
           break;
       case '5':
           camerapov = '5';
           std::cout << "Overview (north) POV enabled" << std::endl;
           glutPostRedisplay();
           break;
       case 'd':
          // if (step < 180) step++; // angle in which the box moves..
           moveDoor =! moveDoor;
           std::cout << "door opened" << std::endl;
           glutPostRedisplay();
           break;
       case 'l':
           clight =! clight;
           std::cout << "light switch pressed" << std::endl;
           glutPostRedisplay();
           break;
       case 's':
           // if (step < 180) step++; // angle in which the box moves..
           moveShade =! moveShade;
           std::cout << "shades opened" << std::endl;
           glutPostRedisplay();
           break;
      default:
         break;
   }
}

// Routine to output interaction instructions to the C++ window.
void printInteraction(void)
{
    std::cout << "Program launches with North View in frustum Point of View" << std::endl;
    std::cout << "Interaction:" << std::endl;
    std::cout << "l to switch lights on/off" << std::endl
        << "d to open/close door" << std::endl
        << "s to open/close shade" << std::endl
        << "1 to change to North view" << std::endl
        << "2 to change to South View" << std::endl
        << "3 to change to East View" << std::endl
        << "4 to change to West View" << std::endl
        << "5 to change to OverView (Top View)" << std::endl
        << "(UP) ARROW KEY to move forward " << std::endl
        << "(DOWN) to move backwards "  << std::endl
        << "(RIGHT) ARROW KEY to rotate right" << std::endl
        << "(LEFT) ARROW KEY to rotate left " << std::endl;
}


int main(int argc, char **argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize(500, 500);
   glutInitWindowPosition(300, 100);
   glutCreateWindow("HW4.cpp");
   setup();
   printInteraction();
   glutDisplayFunc(drawScene);
   glutReshapeFunc(resize);
   glutKeyboardFunc(keyInput);
   glutSpecialFunc(specialkeyInput);
   glutTimerFunc(5, animateDoor, 1); // door movement
   glutTimerFunc(5, animateShade, 1); // shade movement
   glutMainLoop();
   return 0;
}
