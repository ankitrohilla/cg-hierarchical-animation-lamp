#include <GL/glut.h>
#include <math.h>
#include <unistd.h>
#include <iostream>
#include <stdio.h>
#include <GL/freeglut.h>
#include "SOIL.h"

int noOfLamps = 0;
int currentLampId;

float eyeX = 0, eyeY = 5, eyeZ = 15;
float lookAtX = 0, lookAtY = 5, lookAtZ = 0;

int shoulderAxisX = 0, shoulderAxisY = 0, shoulderAxisZ = 90.0;
int elbowAxisX = 0, elbowAxisY = 0, elbowAxisZ = 0;
int conicalFrustumAxisX = 0, conicalFrustumAxisY = 0, conicalFrustumAxisZ = 0;

GLfloat lamp1LightPosition[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat lamp1SpotDirection[] = { 1.0, 0.0, 0.0 };
GLfloat light_ambient[] = { 1.0, 1.0, 1.0, 1.0 };

void animate( int i );

int textureBackWall, textureFloor, textureCeiling, textureSideWall, textureFootball;

enum plane     { XYplane, YZplane, XZplane};
enum direction { posX, negX, posZ, negZ };


class lamp
{
    public:

        bool inAir, firstTime = true;

        // elbowAxisX and conicalFrustumAxisZ are responsible for looking left/right in the screen

        float baseAxisX = 0, baseAxisY = 0, baseAxisZ = 0;
        float shoulderAxisX = 0, shoulderAxisY = 0, shoulderAxisZ = 90.0;
        float elbowAxisX = 20, elbowAxisY = 0, elbowAxisZ = 0;
        float conicalFrustumAxisX = 30, conicalFrustumAxisY = 0, conicalFrustumAxisZ = 0;

        float jumpingFromshoulderAxisX = 0, jumpingFromshoulderAxisY = 0, jumpingFromshoulderAxisZ = 90.0;
        float jumpingFromelbowAxisX = 20, jumpingFromelbowAxisY = 0, jumpingFromelbowAxisZ = 0;
        float jumpingFromconicalFrustumAxisX = 30, jumpingFromconicalFrustumAxisY = 0, jumpingFromconicalFrustumAxisZ = 0;

        int lampId;

        float baseX, baseY, baseZ;
        float jumpingFromX, jumpingFromZ;
        float segmentHeight;
        float segmentR, segmentG, segmentB;
        float conicalFrustumR, conicalFrustumG, conicalFrustumB;

        void createLamp();
        void setLampJump( direction whichDirection, float height, float distance, float speed);
        void jump( direction whichDirection, float height, float distance, float speed);


        lamp( float baseX, float baseZ, float segmentHeight, float segmentR, float segmentG, float segmentB, float conicalFrustumR, float conicalFrustumG, float conicalFrustumB)
        {
            inAir = false;
            lampId = noOfLamps++;

            this->baseX = baseX;
            this->baseY = 0.0;
            this->baseZ = baseZ;
            this->segmentHeight = segmentHeight;
            this->segmentR = segmentR;
            this->segmentG = segmentG;
            this->segmentB = segmentB;
            this->conicalFrustumR = conicalFrustumR;
            this->conicalFrustumG = conicalFrustumG;
            this->conicalFrustumB = conicalFrustumB;
            this->jumpingFromX = baseX;
            this->jumpingFromZ = baseZ;

            // set up light
            switch( lampId )
            {
                case 0:
                    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
                    glLightf (GL_LIGHT0, GL_SPOT_CUTOFF, 90.0);
                    glLightf (GL_LIGHT0, GL_SPOT_EXPONENT, 1.0);
                    glLightf (GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.05);
                    glEnable (GL_LIGHT0);
                    break;
                case 1:
                    glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
                    glLightf (GL_LIGHT1, GL_SPOT_CUTOFF, 90.0);
                    glLightf (GL_LIGHT1, GL_SPOT_EXPONENT, 1.0);
                    glLightf (GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.05);
                    glEnable (GL_LIGHT1);
                    break;
                case 2:
                    glLightfv(GL_LIGHT2, GL_AMBIENT, light_ambient);
                    glLightf (GL_LIGHT2, GL_SPOT_CUTOFF, 90.0);
                    glLightf (GL_LIGHT2, GL_SPOT_EXPONENT, 1.0);
                    glLightf (GL_LIGHT2, GL_LINEAR_ATTENUATION, 0.05);
                    glEnable (GL_LIGHT2);
                    break;
                case 3:
                    glLightfv(GL_LIGHT3, GL_AMBIENT, light_ambient);
                    glLightf (GL_LIGHT3, GL_SPOT_CUTOFF, 90.0);
                    glLightf (GL_LIGHT3, GL_SPOT_EXPONENT, 1.0);
                    glLightf (GL_LIGHT3, GL_LINEAR_ATTENUATION, 0.05);
                    glEnable (GL_LIGHT3);
                    break;
                case 4:
                    glLightfv(GL_LIGHT4, GL_AMBIENT, light_ambient);
                    glLightf (GL_LIGHT4, GL_SPOT_CUTOFF, 90.0);
                    glLightf (GL_LIGHT4, GL_SPOT_EXPONENT, 1.0);
                    glLightf (GL_LIGHT4, GL_LINEAR_ATTENUATION, 0.05);
                    glEnable (GL_LIGHT4);
                    break;
                case 5:
                    glLightfv(GL_LIGHT5, GL_AMBIENT, light_ambient);
                    glLightf (GL_LIGHT5, GL_SPOT_CUTOFF, 90.0);
                    glLightf (GL_LIGHT5, GL_SPOT_EXPONENT, 1.0);
                    glLightf (GL_LIGHT5, GL_LINEAR_ATTENUATION, 0.05);
                    glEnable (GL_LIGHT5);
                    break;
                case 6:
                    glLightfv(GL_LIGHT6, GL_AMBIENT, light_ambient);
                    glLightf (GL_LIGHT6, GL_SPOT_CUTOFF, 90.0);
                    glLightf (GL_LIGHT6, GL_SPOT_EXPONENT, 1.0);
                    glLightf (GL_LIGHT6, GL_LINEAR_ATTENUATION, 0.05);
                    glEnable (GL_LIGHT6);
                    break;
                case 7:
                    glLightfv(GL_LIGHT7, GL_AMBIENT, light_ambient);
                    glLightf (GL_LIGHT7, GL_SPOT_CUTOFF, 90.0);
                    glLightf (GL_LIGHT7, GL_SPOT_EXPONENT, 1.0);
                    glLightf (GL_LIGHT7, GL_LINEAR_ATTENUATION, 0.05);
                    glEnable (GL_LIGHT7);
                    break;
            }
        }
}*lampObj[8];


class ball
{
    public:
        float x, y, z, radius;
        float rotX = 0.0, rotY = 0.0, rotZ = 0.0;
        GLUquadricObj *obj;
        void createBall();
        ball(float x, float z, float radius)
        {
            this->x = x;
            this->z = z;
            this->y = radius;
            this->radius = radius;
            obj = gluNewQuadric();
            gluQuadricNormals( obj, GLU_SMOOTH );
            gluQuadricTexture( obj, GL_TRUE);
            gluQuadricDrawStyle( obj, GLU_FILL);
        }
}*balls[10];

void ball::createBall()
{
    glPushMatrix();

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureFootball);

    glTranslatef( x, y, z);
    glRotatef( rotX, 1.0, 0.0, 0.0);
    glRotatef( rotY, 0.0, 1.0, 0.0);
    glRotatef( rotZ, 0.0, 0.0, 1.0);
    gluSphere( obj, radius, 50, 50);

    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}


int applyTexture( char* file)
{
    return SOIL_load_OGL_texture // load an image file directly as a new OpenGL texture
    (
        file,
        SOIL_LOAD_RGBA,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_TEXTURE_REPEATS | SOIL_FLAG_COMPRESS_TO_DXT
    );
}

void draw_rect_with_tex( float l, float r, float b, float t, plane whichPlane, int texture)
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);
    glBegin(GL_QUADS);
    if( whichPlane == XYplane )
    {
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f( l, b,  0.0);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f( r, b,  0.0);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f( r, t,  0.0);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f( l, t,  0.0);
    }
    else if( whichPlane == YZplane)
    {
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f( 0.0, l,  b);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f( 0.0, r,  b);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f( 0.0, r,  t);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f( 0.0, l,  t);
    }
    else if( whichPlane == XZplane )
    {
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f( l, 0.0,  b);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f( r, 0.0,  b);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f( r, 0.0,  t);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f( l, 0.0,  t);
    }
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void init(void)
{
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 10.0 };
	
    glClearColor (0.0, 0.0, 0.0, 0.0);

    textureFootball = applyTexture("Football.png");
    textureBackWall = applyTexture("backwall.jpg");
    textureSideWall = applyTexture("sidewall.jpg");
    textureFloor    = applyTexture("floor.jpg");
    textureCeiling  = applyTexture("ceiling.jpg");

    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    
    lampObj[0] = new lamp( -5.0, 0.0, 3.0, 1.0, 1.0, 1.0, 0.8, 0.7, 0.6);
    lampObj[1] = new lamp(  5.0, 1.0, 1.0, 1.0, 0.5, 0.5, 1.0, 0.7, 0.7);
    lampObj[2] = new lamp(  3.0, 95.0,  1.5,  1.0, 1.0, 0.3, 1.0, 1.0, 0.8);

    lampObj[2]->elbowAxisX = -20;
    lampObj[2]->conicalFrustumAxisX = -30;
//    lampObj[2]->baseAxisX = 0;
//    lampObj[2]->baseAxisY = 70;

    balls[0] = new ball( 0.0, 100.0, 0.5);
    balls[1] = new ball( 0.0, 70.0, 2.0);

    glEnable(GL_LIGHTING);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_BLEND);

    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel  (GL_SMOOTH);
    glLightModeli (GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
}

// filled cylinder
void createCylinder( float radius, float height )
{
	glPushMatrix();
	glTranslatef(height/2, 0.0, 0.0);
	glRotatef (90.0, 0.0, 1.0, 0.0);
	glTranslatef(0.0, 0.0, -height/2);
	glutSolidCylinder(radius, height, 100, 100);
	glPopMatrix();
}

// filled cone
void createCone( float radius, float height )
{
	glPushMatrix();
	glTranslatef( height/2, 0.0, 0.0);
	glRotatef( 90.0, 0.0, 1.0, 0.0);
	glTranslatef( 0.0, 0.0, -height/2);
	glutSolidCone( radius, height, 50, 50);
	glPopMatrix();
}

// hollow connical frustum
void createHollowConicalFrustum( float radiusBase, float radiusTop, float height)
{
    GLUquadricObj *obj = gluNewQuadric();
    gluQuadricNormals( obj, GLU_SMOOTH );
    gluQuadricTexture( obj, GL_TRUE);
    gluQuadricDrawStyle( obj, GLU_FILL);

	glPushMatrix();
    glTranslatef(height/2, 0.0, 0.0);
	glRotatef( -90, 0.0, 1.0, 0.0);
	glTranslatef(0.0, 0.0, -height/2);
	gluCylinder( obj, radiusTop, radiusBase, height, 100, 100);
    glPopMatrix();
}

void lamp::createLamp()
{
    glPushMatrix();

    // This translate moves the base
    glTranslatef ( baseX, baseY, baseZ);
    glColor3f( segmentR, segmentG, segmentB);
    glPushMatrix();
    glRotatef ((GLfloat) 90.0, 0.0, 0.0, 1.0);

    glRotatef ((GLfloat) baseAxisX, 1.0, 0.0, 0.0);
    glRotatef ((GLfloat) baseAxisY, 0.0, 1.0, 0.0);
    glRotatef ((GLfloat) baseAxisZ, 0.0, 0.0, 1.0);

    createCone( segmentHeight/2, segmentHeight/6);
    glPopMatrix();

    // This rotate rotates the shoulder but not the base
    glRotatef ((GLfloat) shoulderAxisX, 1.0, 0.0, 0.0);
    glRotatef ((GLfloat) shoulderAxisY, 0.0, 1.0, 0.0);
    glRotatef ((GLfloat) shoulderAxisZ, 0.0, 0.0, 1.0);



    // This is the shoulder
    glPushMatrix();
    glPushMatrix();
    glTranslatef(0.0, 0.0, -segmentHeight/15);
    createCylinder(segmentHeight/30, segmentHeight);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.0, segmentHeight/15, segmentHeight/15);
    createCylinder(segmentHeight/30, segmentHeight);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.0, -segmentHeight/15, segmentHeight/15);
    createCylinder(segmentHeight/30, segmentHeight);
    glPopMatrix();
    glPopMatrix();

    // This translate moves the first joint
    glTranslatef ( segmentHeight, 0.0, 0.0);
    // This rotate rotates the first joint
    glRotatef ((GLfloat) elbowAxisX, 0.0,-1.0, 0.0);
    glRotatef ((GLfloat) elbowAxisY, 1.0, 0.0, 0.0);
    glRotatef ((GLfloat) elbowAxisZ, 0.0, 0.0, 1.0);

    // this is the joint between shoulder and elbow
    glutSolidSphere( segmentHeight/7.5, 100, 100);

    // This is the elbow
    glPushMatrix();
    glPushMatrix();
    glTranslatef(0.0, 0.0, -segmentHeight/15);
    createCylinder(segmentHeight/30, segmentHeight);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.0, segmentHeight/15, segmentHeight/15);
    createCylinder(segmentHeight/30, segmentHeight);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.0, -segmentHeight/15, segmentHeight/15);
    createCylinder(segmentHeight/30, segmentHeight);
    glPopMatrix();
    glPopMatrix();
    // This translate moves the lamp conicalFrustum and the light
    glTranslatef ( segmentHeight, 0.0, 0.0);
    // This rotate rotates the lamp conicalFrustum and the light
    glRotatef ((GLfloat) conicalFrustumAxisX, 0.0,-1.0, 0.0);
    glRotatef ((GLfloat) conicalFrustumAxisY, 1.0, 0.0, 0.0);
    glRotatef ((GLfloat) conicalFrustumAxisZ, 0.0, 0.0, 1.0);

    // joint between elbow and conical frustum
    glutSolidSphere( segmentHeight/7.5, 100, 100);

    glPushMatrix();
    glTranslatef(segmentHeight*3/10.0, 0.0, 0.0);
    glColor3f( 1.0, 1.0, 0.6);
    // this is the bulb
    glutSolidSphere(segmentHeight*7/30.0, 100, 100);
    glPopMatrix();

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glColor3f( conicalFrustumR/4, conicalFrustumG/4, conicalFrustumB/4 );
    createHollowConicalFrustum( segmentHeight/6, segmentHeight/1.5, segmentHeight/1.5);
    glCullFace(GL_FRONT);
    glColor3f( conicalFrustumR, conicalFrustumG, conicalFrustumB );
    createHollowConicalFrustum( segmentHeight/6, segmentHeight/1.5, segmentHeight/1.5);
    glDisable(GL_CULL_FACE);

    // This is the color of the lamp-light
    glColor3f( 1.0, 1.0, 1.0);
//    This one is between the 2 glLights below -> glTranslatef(10.0, 0.0, 0.0);
    switch(lampId)
    {
        case 0:
            glLightfv(GL_LIGHT0, GL_POSITION, lamp1LightPosition);
            glTranslatef(10.0, 0.0, 0.0);
            glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, lamp1SpotDirection);
        break;
        case 1:
            glLightfv(GL_LIGHT1, GL_POSITION, lamp1LightPosition);
            glTranslatef(10.0, 0.0, 0.0);
            glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, lamp1SpotDirection);
        break;
        case 2:
            glLightfv(GL_LIGHT2, GL_POSITION, lamp1LightPosition);
            glTranslatef(10.0, 0.0, 0.0);
            glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, lamp1SpotDirection);
        break;
        case 3:
            glLightfv(GL_LIGHT3, GL_POSITION, lamp1LightPosition);
            glTranslatef(10.0, 0.0, 0.0);
            glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, lamp1SpotDirection);
        break;
        case 4:
            glLightfv(GL_LIGHT4, GL_POSITION, lamp1LightPosition);
            glTranslatef(10.0, 0.0, 0.0);
            glLightfv(GL_LIGHT4, GL_SPOT_DIRECTION, lamp1SpotDirection);
        break;
        case 5:
            glLightfv(GL_LIGHT5, GL_POSITION, lamp1LightPosition);
            glTranslatef(10.0, 0.0, 0.0);
            glLightfv(GL_LIGHT5, GL_SPOT_DIRECTION, lamp1SpotDirection);
        break;
        case 6:
            glLightfv(GL_LIGHT6, GL_POSITION, lamp1LightPosition);
            glTranslatef(10.0, 0.0, 0.0);
            glLightfv(GL_LIGHT6, GL_SPOT_DIRECTION, lamp1SpotDirection);
        break;
        case 7:
            glLightfv(GL_LIGHT7, GL_POSITION, lamp1LightPosition);
            glTranslatef(10.0, 0.0, 0.0);
            glLightfv(GL_LIGHT7, GL_SPOT_DIRECTION, lamp1SpotDirection);
        break;
    }
    glPopMatrix();

}

// traverse the equation whichDirection ^ 2 = -4 * height * y
void lamp::jump( direction whichDirection, float height, float distance, float speed)
{
    if( !inAir || baseY > 0.0 )
    {
        switch( whichDirection )
        {
            case posX:
                baseX += 0.1 * speed;
                if( (jumpingFromX + distance/2) > baseX )
                {
                    shoulderAxisZ -= 1 * speed;
                    elbowAxisZ -= 2 * speed;
//                  conicalFrustumAxisZ -= 2 * speed;
                }
                else
                {
                    shoulderAxisZ += 1 * speed;
                    elbowAxisZ += 2 * speed;
//                  conicalFrustumAxisZ += 2 * speed;
                }
                baseY = (height/4)*( distance/4 + pow(baseX - jumpingFromX  - distance/2 , 2) / -distance);
                break;
            case negX:
                baseX -= 0.1;
                if( (jumpingFromX - distance/2) > baseX )
                {
                    shoulderAxisZ -= 0.5;
                    elbowAxisZ -= 1;
                    conicalFrustumAxisZ -= 1;
                }
                else
                {
                    shoulderAxisZ += 0.5;
                    elbowAxisZ += 1;
                    conicalFrustumAxisZ += 1;
                }
                baseY =(height/4)*( distance/4 + pow(jumpingFromX - baseX  - distance/2 , 2) / -distance);
                break;
            case posZ:
                baseZ += 0.1 * speed;
                if( (jumpingFromZ + distance/2) > baseZ )
                {
                    shoulderAxisX -= 0.5 * speed;
                    elbowAxisX += 1.2 * speed;
                    conicalFrustumAxisX -= 0.25 * speed;
                }
                else
                {
                    shoulderAxisX += 0.5 * speed;
                    elbowAxisX -= 1.2 * speed;
                    conicalFrustumAxisX += 0.25 * speed;
                }
                baseY =(height/4)*( distance/4 + pow(baseZ - jumpingFromZ  - distance/2 , 2) / -distance);
                break;
            case negZ:
                baseZ -= 0.1 * speed;
                if( (jumpingFromZ - distance/2) > baseZ )
                {
                    shoulderAxisX += 0.5 * speed;
                    elbowAxisX += 1 * speed;
                    conicalFrustumAxisX += 1 * speed;
                }
                else
                {
                    shoulderAxisX -= 0.5 * speed;
                    elbowAxisX -= 1 * speed;
                    conicalFrustumAxisX -= 1 * speed;
                }
                baseY =(height/4)*( distance/4 + pow(jumpingFromZ - baseZ  - distance/2 , 2) / -distance);
                break;
        }
        inAir = true;
    }
}

void lamp::setLampJump( direction whichDirection, float height, float distance, float speed)
{
    bool pos = (whichDirection == posX || whichDirection == posZ )&&(( baseZ - jumpingFromZ < distance - 0.01 && baseX - jumpingFromX < 0.01) ||( baseX - jumpingFromX < distance - 0.01 && baseZ - jumpingFromZ < 0.01));
    bool neg = (whichDirection == negX || whichDirection == negZ )&&(( jumpingFromZ - baseZ < distance - 0.01 && jumpingFromX - baseX < 0.01) ||( jumpingFromX - baseX < distance - 0.01 && jumpingFromZ - baseZ < 0.01));

    if( pos || neg || firstTime )
    {
        if( firstTime )
        {
//            std::cout << "Right if beginning";
            fflush(stdout);;
            firstTime = false;
            jumpingFromX = baseX;
            jumpingFromZ = baseZ;
            jumpingFromshoulderAxisX = shoulderAxisX;
            jumpingFromshoulderAxisY = shoulderAxisY;
            jumpingFromshoulderAxisZ = shoulderAxisZ;
            jumpingFromelbowAxisX = elbowAxisX;
            jumpingFromelbowAxisY = elbowAxisY;
            jumpingFromelbowAxisZ = elbowAxisZ;
            jumpingFromconicalFrustumAxisX = conicalFrustumAxisX;
            jumpingFromconicalFrustumAxisY = conicalFrustumAxisY;
            jumpingFromconicalFrustumAxisZ = conicalFrustumAxisZ;
        }
        jump(whichDirection, height, distance, speed);
    }
    else if( !firstTime )
    {
        std::cout << "Wrong if beginning";
        fflush(stdout);;
        firstTime = true;
        switch (whichDirection)
        {
        case posX:
            baseX = jumpingFromX + distance;
            shoulderAxisZ = jumpingFromshoulderAxisZ;
            elbowAxisZ = jumpingFromelbowAxisZ;
            conicalFrustumAxisZ = jumpingFromconicalFrustumAxisZ;
                    baseY = 0.0;
            break;
        case negX:
            baseX = jumpingFromX - distance;
            shoulderAxisZ = jumpingFromshoulderAxisZ;
            elbowAxisZ = jumpingFromelbowAxisZ;
            conicalFrustumAxisZ = jumpingFromconicalFrustumAxisZ;
                    baseY = 0.0;
            break;
        case posZ:
            baseZ = jumpingFromZ + distance;
            shoulderAxisX = jumpingFromshoulderAxisX;
            elbowAxisX = jumpingFromelbowAxisX;
            conicalFrustumAxisX = jumpingFromconicalFrustumAxisX;
                    baseY = 0.0;
            break;
        case negZ:
            baseZ = jumpingFromZ - distance;
            shoulderAxisX = jumpingFromshoulderAxisX;
            elbowAxisX = jumpingFromelbowAxisX;
            conicalFrustumAxisX = jumpingFromconicalFrustumAxisX;
            baseY = 0.9;
            break;
        }
        inAir = false;
        jumpingFromX = baseX;
        jumpingFromZ = baseZ;
        firstTime = true;
    }

}

void display(void)
{
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glColor3f( 1.0, 1.0, 1.0);
    // Back Side Wall
    glPushMatrix();
    glTranslatef(0.0, 0.0, -10.0);
    draw_rect_with_tex( -15.0, 15.0, 0.0, 20.0, XYplane, textureBackWall);
    glPopMatrix();

    // build corridor
    for( int i = 0; i < 100; i++ )
    {
        // Right Side Wall
        glPushMatrix();
        glTranslatef(15.0, 0.0, 0.0);
        draw_rect_with_tex( 20.0, 0.0, -10.0 + i*10, 0.0 + i*10, YZplane, textureSideWall);
        glPopMatrix();

        // Left Side Wall
        glPushMatrix();
        glTranslatef(-15.0, .0, 0.0);
        draw_rect_with_tex( 20.0, 0.0, 0.0 + i*10, -10.0 + i*10, YZplane, textureSideWall);
        glPopMatrix();

        // Floor
        glPushMatrix();
        draw_rect_with_tex( -15.0, 15.0, 0.0 + i*10, -10.0 + i*10, XZplane, textureFloor);
        glPopMatrix();
        \
        // Ceiling
        glPushMatrix();
        glTranslatef(0.0, 20.0, 0.0);
        draw_rect_with_tex( 15.0, -15.0, 0.0 + i*10, -10.0 + i*10, XZplane, textureCeiling);
        glPopMatrix();
    }

    lampObj[0]->createLamp();
    lampObj[1]->createLamp();

    glPushMatrix();
    //glRotatef()
    lampObj[2]->createLamp();
    glPopMatrix();


    balls[0]->createBall();
    //balls[1]->createBall();

    glLoadIdentity();
    gluLookAt(eyeX, eyeY, eyeZ, lookAtX, lookAtY, lookAtZ, 0.0, 1.0, 0.0);

	glutSwapBuffers();
}
void reshape (int w, int h)
{
	glViewport (0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
    glFrustum(-8.0, 8.0, -4.5, 4.5, 5.0, 200.0);
	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eyeX, eyeY, eyeZ, lookAtX, lookAtY, lookAtZ, 0.0, 1.0, 0.0);
}
void keyboard (unsigned char key, int x, int y)
{
    if( key >= 48 && key <= 55 )
    {
        currentLampId = key - 48;
    }
	switch (key)
	{
        case 'q':
            lampObj[currentLampId]->shoulderAxisX = (int)(lampObj[currentLampId]->shoulderAxisX + 5) % 360;
			glutPostRedisplay();
			break;
		case 'w':
            lampObj[currentLampId]->shoulderAxisY = (int)(lampObj[currentLampId]->shoulderAxisY + 5) % 360;
			glutPostRedisplay();
			break;
        case 'e':
            lampObj[currentLampId]->shoulderAxisZ = (int)(lampObj[currentLampId]->shoulderAxisZ + 5) % 360;
			glutPostRedisplay();
			break;
		case 'a':
            lampObj[currentLampId]->elbowAxisX = (int)(lampObj[currentLampId]->elbowAxisX + 5) % 360;
			glutPostRedisplay();
			break;
		case 's':
            lampObj[currentLampId]->elbowAxisY = (int)(lampObj[currentLampId]->elbowAxisY + 5) % 360;
			glutPostRedisplay();
			break;
		case 'd':
            lampObj[currentLampId]->elbowAxisZ = (int)(lampObj[currentLampId]->elbowAxisZ + 5) % 360;
			glutPostRedisplay();
			break;
		case 'z':
            lampObj[currentLampId]->conicalFrustumAxisX = (int)(lampObj[currentLampId]->conicalFrustumAxisX + 5) % 360;
			glutPostRedisplay();
			break;
		case 'x':
            lampObj[currentLampId]->conicalFrustumAxisY = (int)(lampObj[currentLampId]->conicalFrustumAxisY + 5) % 360;
			glutPostRedisplay();
			break;
		case 'c':
            lampObj[currentLampId]->conicalFrustumAxisZ = (int)(lampObj[currentLampId]->conicalFrustumAxisZ + 5) % 360;
			glutPostRedisplay();
			break;
        case 'r':
            lampObj[currentLampId]->shoulderAxisX = (int)(lampObj[currentLampId]->shoulderAxisX - 5) % 360;
            glutPostRedisplay();
            break;
        case 't':
            lampObj[currentLampId]->shoulderAxisY = (int)(lampObj[currentLampId]->shoulderAxisY - 5) % 360;
            glutPostRedisplay();
            break;
        case 'y':
            lampObj[currentLampId]->shoulderAxisZ = (int)(lampObj[currentLampId]->shoulderAxisZ - 5) % 360;
            glutPostRedisplay();
            break;
        case 'f':
            lampObj[currentLampId]->elbowAxisX = (int)(lampObj[currentLampId]->elbowAxisX - 5) % 360;
            glutPostRedisplay();
            break;
        case 'g':
            lampObj[currentLampId]->elbowAxisY = (int)(lampObj[currentLampId]->elbowAxisY - 5) % 360;
            glutPostRedisplay();
            break;
        case 'h':
            lampObj[currentLampId]->elbowAxisZ = (int)(lampObj[currentLampId]->elbowAxisZ - 5) % 360;
            glutPostRedisplay();
            break;
        case 'v':
            lampObj[currentLampId]->conicalFrustumAxisX = (int)(lampObj[currentLampId]->conicalFrustumAxisX - 5) % 360;
            glutPostRedisplay();
            break;
        case 'b':
            lampObj[currentLampId]->conicalFrustumAxisY = (int)(lampObj[currentLampId]->conicalFrustumAxisY - 5) % 360;
            glutPostRedisplay();
            break;
        case 'n':
            lampObj[currentLampId]->conicalFrustumAxisZ = (int)(lampObj[currentLampId]->conicalFrustumAxisZ - 5) % 360;
            glutPostRedisplay();
            break;
        case 'o':
            lampObj[currentLampId]->baseAxisX = (int)(lampObj[currentLampId]->baseAxisX - 5) % 360;
            glutPostRedisplay();
            break;
        case 'p':
            lampObj[currentLampId]->baseAxisY = (int)(lampObj[currentLampId]->baseAxisY - 5) % 360;
            glutPostRedisplay();
            break;
        case '[':
            lampObj[currentLampId]->baseAxisZ = (int)(lampObj[currentLampId]->baseAxisZ - 5) % 360;
            glutPostRedisplay();
            break;
        case 'u':
            balls[0]->x += 0.1;
            balls[0]->rotX  = 0.0;
            balls[0]->rotZ -= 7.5;
            glutPostRedisplay();
            break;
        case 'i':
            balls[0]->z += 0.1;
            balls[0]->rotZ  = 0.0;
            balls[0]->rotX += 7.5;
            glutPostRedisplay();
            break;
        case 'j':
            balls[0]->x -= 0.1;
            balls[0]->rotX  = 0.0;
            balls[0]->rotZ += 7.5;
            glutPostRedisplay();
            break;
        case 'k':
            balls[0]->z -= 0.1;
            balls[0]->rotZ  = 0.0;
            balls[0]->rotX -= 7.5;
            glutPostRedisplay();
//      case 'j':
//            lampObj[currentLampId]->jump( toX)
		default:
			break;
	}
}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize (1600, 900);
	glutInitWindowPosition (0, 0);
	glutCreateWindow (argv[0]);
	glutFullScreen();
	init ();
    glutTimerFunc( 1000, animate, 5);
    glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}


void animate( int i)
{
    static int angleCounter = 0;
    static bool firstTime = true;
    static bool lamp1Begin = false;
    static bool xGoingRight = true;

    if( eyeZ < 95 && angleCounter < 1000 )
        eyeZ += 0.01 * ( 95 - eyeZ );


    switch (angleCounter)
    {
        case 40:
            balls[0]->x = -2;
            firstTime = true;
            break;
        case 150:
            firstTime = true;
            break;
        case 320:
            firstTime = true;
            break;
        case 490:
            firstTime = true;
            break;
        case 900:
            firstTime = true;
            break;
        case 1120:
            firstTime = true;
            break;
        case 1700:
            firstTime = true;
        case 2060:
            firstTime = true;
            break;
        case 2800:
            firstTime = true;
        default:
            break;
    }

    // for ball
    if( angleCounter >= 160 && !lamp1Begin )
    {
        balls[0]->x += 0.002;
        balls[0]->z -= 0.003 * balls[0]->z;
        balls[0]->rotX -= 0.225 * balls[0]->z;
    }
    else if( lamp1Begin && angleCounter < 800 )
    {
        balls[0]->x -= 0.02;
        balls[0]->z += 0.2 ;
        balls[0]->rotX += 15.0 ;
    }

    // for lamps
    if( lampObj[0]->baseZ < 80.0 )
    {
        lampObj[0]->setLampJump( posZ, 5.0, 20.0, 2.0);
        glutTimerFunc( 2 , animate, 5 );
    }
 else   if( angleCounter < 40 )
    {
        angleCounter++;
        if( firstTime )
        {
            sleep( 1 );
            firstTime = false;
        }
        lampObj[0]->shoulderAxisY += 1;
        lampObj[0]->elbowAxisX += 2;
        lampObj[0]->elbowAxisZ -= 1;
        lampObj[0]->conicalFrustumAxisZ += 1;
        lampObj[0]->conicalFrustumAxisX -= 1;
        glutTimerFunc( 5, animate, 5 );
    }
    else if( angleCounter >= 40 && angleCounter < 150 )
    {
        angleCounter++;
        if( firstTime )
        {
//            sleep( 1 );
            firstTime = false;
        }
        lampObj[0]->baseX -= 0.01;
        lampObj[0]->jumpingFromX = lampObj[0]->baseX;
        lampObj[0]->shoulderAxisZ -= 0.3;
        lampObj[0]->elbowAxisX -= 0.5;
        lampObj[0]->conicalFrustumAxisX += 1;
        glutTimerFunc( 5, animate, 5 );
    }
    else if( angleCounter >= 150 && angleCounter < 320 )
    {
        angleCounter++;
        if( firstTime )
        {
  //          sleep( 1 );
            firstTime = false;
        }

            lampObj[0]->conicalFrustumAxisZ -= 1.0;

        glutTimerFunc( 5, animate, 5 );
    }
    else if( angleCounter >= 320 && angleCounter < 490 )
    {
        angleCounter++;
        if( firstTime )
        {
            sleep( 2 );
            firstTime = false;
        }
        lampObj[0]->shoulderAxisZ += 0.1;
        if( angleCounter < 405 )
            lampObj[0]->conicalFrustumAxisZ += 2.0;
        glutTimerFunc( 5, animate, 5 );
        fflush(stdout);
    }
    else if( (lampObj[0]->baseX < 0.01 || lampObj[0]->baseY < 0.001) && !lamp1Begin )
    {
        lampObj[0]->elbowAxisY += 0.5;
        lampObj[0]->jumpingFromelbowAxisY += 0.5;
        lampObj[0]->conicalFrustumAxisZ -= 2.0;
        lampObj[0]->conicalFrustumAxisX -= 2.0;
        lampObj[0]->jumpingFromconicalFrustumAxisZ -= 1.5;
        lampObj[0]->jumpingFromconicalFrustumAxisX -= 2.0;
        lampObj[0]->setLampJump( posX, 10.0, 3.15, 1.0);
        glutTimerFunc( 5, animate, 5 );
        fflush(stdout);
    }
    else if( lampObj[1]->baseZ < 85.0 )
    {
        lamp1Begin = true;
        lampObj[0]->baseX = 0.0;
        lampObj[0]->baseY = 0.0;

        lampObj[0]->shoulderAxisY += 0.001 * lampObj[1]->baseZ;
        lampObj[0]->shoulderAxisZ += 0.001 * lampObj[1]->baseZ;
        lampObj[0]->elbowAxisY += 0.006 * lampObj[1]->baseZ;
        lampObj[0]->elbowAxisZ -= 0.004 * lampObj[1]->baseZ;
        lampObj[0]->conicalFrustumAxisY += 0.003 * lampObj[1]->baseZ;

        lampObj[1]->baseX -= 0.05;
        lampObj[1]->jumpingFromX -= 0.04;
        lampObj[1]->setLampJump( posZ, 5.0, 5.0, 3.0);
        glutTimerFunc( 5, animate, 5 );
    }
    else if( angleCounter >= 490 && angleCounter < 540 )
    {
        angleCounter++;
        lampObj[0]->shoulderAxisY += 0.01 * lampObj[1]->baseZ;
        glutTimerFunc( 5, animate, 5);
    }
    if( angleCounter >= 540 && angleCounter < 900 )
    {
        if( firstTime )
        {
            sleep( 1 );
            firstTime = false;
        }
        angleCounter++;
        lampObj[0]->shoulderAxisY -= 0.0007 * (900-angleCounter);
        lampObj[1]->shoulderAxisY += (900-angleCounter) * 0.002;
        lampObj[1]->conicalFrustumAxisY += 0.4;
        glutTimerFunc( 5, animate, 5 );
    }
    else if( angleCounter >= 900 && balls[0]->z > 82.0 && angleCounter < 1120 )
    {
        if( firstTime )
        {
            balls[0]->x = -7.96;
            balls[0]->z = 103.0;
            firstTime = false;
        }
        lampObj[1]->shoulderAxisX -= 0.03 * (balls[0]->z - 82.0);
        lampObj[1]->shoulderAxisZ += 0.01 * (balls[0]->z - 82.0);
        lampObj[1]->elbowAxisX += 0.03 * (balls[0]->z - 82.0);
        lampObj[1]->conicalFrustumAxisX += 0.03 * (balls[0]->z - 82.0);

        balls[0]->z -= 0.01 * (balls[0]->z - 82.0);
        balls[0]->rotX -= 0.75 * (balls[0]->z - 82.0);

        if( balls[0]->z < 82.01 )
            balls[0]->z = 81.99;

        angleCounter++;

        glutTimerFunc( 5, animate, 5 );
    }
    else if( angleCounter >= 1120 && angleCounter < 1700 )
    {
        if( firstTime )
        {
            balls[0]->rotX = 0.0;
            firstTime = false;
            sleep( 1 );
        }

        if( angleCounter < 1200 )
        {
            lampObj[1]->shoulderAxisX += 0.03 * (1200 - angleCounter);
            lampObj[1]->shoulderAxisZ -= 0.01 * (1200 - angleCounter);
            lampObj[1]->elbowAxisX -= 0.03 * (1200 - angleCounter);
            lampObj[1]->conicalFrustumAxisX -= 0.03 * (1200 - angleCounter);
        }
        else if( angleCounter < 1260 )
        {
            lampObj[1]->shoulderAxisX -= 0.9;
            lampObj[1]->shoulderAxisZ += 0.3;
            lampObj[1]->elbowAxisX += 0.9;
            lampObj[1]->conicalFrustumAxisX += 0.9;
        }

        static bool isGoingRight = true;

        if( balls[0]->x < 14.5 && isGoingRight )
        {
            lampObj[0]->shoulderAxisY += 0.5;

            balls[0]->x += 0.0002 * (1700 - angleCounter);
            balls[0]->rotZ -= 0.015 * (1700 - angleCounter);
            if( balls[0]->x > 14.3 )
            {
                balls[0]->x = 14.5;
                isGoingRight = false;
            }
            std::cout << angleCounter;
        }
        else if( balls[0]->x > -14.5 && !isGoingRight )
        {
            lampObj[0]->shoulderAxisY -= 0.5;

            balls[0]->x -= 0.0002 * (1700 - angleCounter);
            balls[0]->rotZ += 0.015 * (1700 - angleCounter);
            if( balls[0]->x < -14.3 )
            {
                balls[0]->x = -14.5;
                isGoingRight = true;
            }
        }

//        if( balls[0]->z < 84.21 )
  //          balls[0]->z = 84.19;

        angleCounter++;

        glutTimerFunc( 5, animate, 5 );
    }
    else if( angleCounter >= 1700 && angleCounter < 2060 )
    {
        if( firstTime )
        {
            firstTime = false;
        }

        eyeX += 0.013;
        eyeZ -= 0.06;
        lookAtZ += 2.0;
        lampObj[2]->setLampJump(negZ, 7, 5.0, 0.28);
        lampObj[2]->baseAxisY -= 0.2;
        lampObj[2]->baseY = 0.9;
        angleCounter++;
        glutTimerFunc( 5, animate, 5 );
    }
    else if( angleCounter >= 2060 && angleCounter < 2800 )
    {
        if( firstTime )
        {
            lampObj[2]->baseY = 0.9;
            firstTime = false;
        }

        if( lampObj[2]->baseY > 0 )
        {
            lampObj[2]->baseY -= 0.1;
            lampObj[2]->baseAxisY += 3.0;
        }
        else
        {
            lampObj[2]->baseY = 0.0;
            lampObj[2]->baseAxisY = 0;
        }

        if( angleCounter < 2460 )
        {
            lampObj[0]->shoulderAxisY -= 0.23;
            lampObj[0]->shoulderAxisX += 0.05;
            lampObj[1]->shoulderAxisY += 0.1;
            lampObj[2]->conicalFrustumAxisX -= 0.1;
        }
        balls[0]->z -= 0.0002 * (2800 - angleCounter);
        balls[0]->rotX -= 0.015 * (2800 - angleCounter);
        eyeZ -= 0.0002 * (2800 - angleCounter);;
        glutTimerFunc( 5, animate, 5 );
        angleCounter++;
    }
    else if( angleCounter >= 2800 )
    {
        static int diff;
        if( firstTime )
        {
            balls[0]->rotZ = 0;
            diff = balls[0]->z - eyeZ;
        }
        balls[0]->z += eyeZ / 220;
        balls[0]->rotX += 50 * eyeZ / 220;
        eyeZ += eyeZ /200;
        lookAtZ -= 2.5;
        glutTimerFunc( 5, animate, 5 );
    }

   glutPostRedisplay();
}
