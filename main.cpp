#include <iostream>
#include<windows.h>
#include<Gl/glut.h>
#include<math.h>
using namespace std;
float angle=0;
float pat=0.0;
int avancer=0,scaler=0,cpt=0;
float x=0.2,y=0.8;
float k=0,f=1;
float sTorus;
float xS,yS;
float camx=-65;
float conv(float x);
float col=1.0;
float allume=1.0;
float lumiere=1.0;
float angle_pause=0;
GLfloat ambientColor[3];
float conv(float x){
    const float PI=3.141592654f;
    return x/180*PI;
    }
static void Reshape(int width,int height)
{

    glViewport(0,0,width,height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(14,1,0.1,100);
    gluLookAt(camx,0,32,0,0,0,0,1,0);// Pour la voiture
  // gluLookAt(0,0,50,0,0,0,0,1,0);
}


void animer()
{ if(allume!=1.0)
  {
   if(angle>angle_pause+60)
   {lumiere=0.01;
   ambientColor[0]=0.3f;
     ambientColor[1]=0.3f;
     ambientColor[2]=0.3f;
     glLightModelfv(GL_LIGHT_MODEL_AMBIENT,ambientColor);


   }
   if(angle>360)
       {
         angle=0.0; pat=0;

         //printf("col=%f\n",col);
       }
    angle=angle+0.2;
if(angle<180 ){ avancer=-1;sTorus+=0.0003;}
if(angle>=180){ avancer=1; sTorus-=0.0003;}

k+=0.005;
}
    glutPostRedisplay();

}

void animerVoiture(int key, int x, int y)
{
    switch (key)
   {
       case GLUT_KEY_LEFT : avancer=-1; camx--;  break;
       case GLUT_KEY_RIGHT : avancer=1; camx++;  break;
       case GLUT_KEY_DOWN : scaler=-1; allume=1.0;
lumiere=1.0; angle_pause=angle;
       ambientColor[0]=0.1f;
     ambientColor[1]=0.1f;
     ambientColor[2]=0.1f;
                glLightModelfv(GL_LIGHT_MODEL_AMBIENT,ambientColor);

        break;
       case GLUT_KEY_UP : scaler=1; allume=0.01;


        cpt++; break;
        }
}

void CylindreAndSphere(){



    //Cylindre
      glPushMatrix();
        glColor3f(0.44f,0.44f,0.44f);

        GLUquadricObj * qobj22 = gluNewQuadric();
        glTranslated(10.5, 0.0 , 0.8);
        glScalef(1.0,1.01,1.0);
        glRotatef(180, 1.0f, 0.0f, 1.0f);
        gluCylinder(qobj22, 1.25, 1.25, 6, 35, 1);

        glPopMatrix();

        glPushMatrix();
        glColor3f(0.65,0.165f,0.165f);
                //glColor3f(1.0f,0.0f,0.0f);

        GLUquadricObj * qobj = gluNewQuadric();
        glTranslated(8+xS, 0.0 , 0.8);
        glRotatef(180, 1.0f, 0.0f, 1.0f);
        gluCylinder(qobj, 1.18, 1.18, 5.3, 35, 1);
        glColor3f(1.0f,0.0f,0.0f);
        glPushMatrix();

//Sphere
            //glTranslatef(1.0,0.0,1.0);
            glutSolidSphere(0.2,6,6);
            glPopMatrix();
            gluDeleteQuadric(qobj);
            glPopMatrix();
    }

void genteAlliage(){
    //Lignes à l interieur du torus
glPushMatrix();

glColor3f(1.0,1.0,1.0);
for(int i=0; i<=360; i+=36)
{
glLineWidth(1);
glBegin(GL_LINES);
glVertex3f(0, 0.0, 0.0);
glVertex3f(cos(i+(k))*2, sin(i+(k))*2, 0);
glEnd();
}
glPopMatrix();
    }
void CentreTorus()
{
glPushMatrix();
glColor3f(1.0,0.0,0.0);
glRotatef(angle,0.0,0.0,1.0);
glutSolidSphere(0.2,6,6);
glPopMatrix();
}
void Pedale(){
    //Cylindre qui tourne dans le torus
glPushMatrix();
//(1.0f,1.0f,0.0f);
GLUquadricObj * qobj1 = gluNewQuadric();
glTranslated(0.0, 0.0 , 0.0);
glRotatef(angle,0.0,0.0,1.0);
glColor3f(1.0f,0.0f,0.0f);
glRotatef(90, 0.0f, 1.0f, 0.0f);
glScalef(1.0,1.0,0.9);
gluCylinder(qobj1, 0.1, 0.1, 2.7, 10, 10);
glPopMatrix();


    }
void SphereDansTorus(){
    //Sphere qui tourne sur le torus
            glPushMatrix();
            glRotatef(-90+angle,0.0,0.0,1.0);glTranslatef(0.0,2.5,0.7);
            glColor3f(1.0,0.0,0.0);
            glutSolidSphere(0.2,6,6);
            glPopMatrix();
    }
void Torus(){
    //Grand Torus

genteAlliage();
CentreTorus();
glPushMatrix();
glTranslatef(0.0,0.0,-0.2);
glColor3f(0.0,0.0,1.0);
glRotatef(angle,0.0,0.0,2.0);
glScalef(1.0,1.0,1.0);
glutSolidTorus(0.7+sTorus,2.5+sTorus,12,24);
glPopMatrix();
Pedale();
SphereDansTorus();
    }
void TorCylLine(){
glPushMatrix();
glLineWidth(5);
glColor3f(1.0,0.0,0.0);
glBegin(GL_LINES);

glEnd();
glPopMatrix();

//Ligne entre torus et cylindre

glBegin(GL_LINES);
glLineWidth(7);
glColor3f(1.0,0.0,0.0);
xS=cos(conv(angle))*2.5;
yS=sin(conv(angle))*2.5;
glVertex3f(xS, yS, 0.8);
glVertex3f(8+xS, 0.0, 0.8);
glEnd();
glPopMatrix();

    }
void TorusVersTransfo(){
    glPushMatrix();
        glColor3f(0.5f,0.5f,0.5f);
        GLUquadricObj * qobj22 = gluNewQuadric();
        //gluQuadricDrawStyle(qobj22,GL_LINE);
        glColor3f(0.87,0.72,0.54);
        glTranslatef(0.0,0.0,-6.0);
        glRotatef(angle,0.0,0.0,1.0);
        gluCylinder(qobj22, 0.2, 0.2, 6, 7, 1);
        //gluQuadricDrawStyle(qobj22,GL_FILL);
    glPopMatrix();

    }

void Transfo(){

    glPushMatrix();
        //gluQuadricDrawStyle(GL_FILL);
        glColor3f(1.0,1.0,1.0);
        glTranslatef(0.0,1.0,-6.0);
        glScalef(1.5,3.0,0.5);
        glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
        GLUquadricObj *obj=gluNewQuadric();
        glColor3f(1.0,0.0,0.0);
        glTranslatef(0.0,1.5,-5.74);
        gluDisk(obj,0,0.6,36,2.0);
    glPopMatrix();

    glPushMatrix();
        GLUquadricObj *obj2=gluNewQuadric();
        glColor3f(0.5,0.0,0.0);
        glTranslatef(0.0,1.9,-5.74);
        glRotatef(90,1.0,0.0,0.0);
        //glRotatef(angle,0.0,1.0,0.0);
        gluCylinder(obj2,0.1,0.1,1.0,7,1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0,0.3,0.8);
    glTranslatef(-0.5,2.55,-6.0);
    glutSolidSphere(0.1,6,6);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0,0.3,0.8);
    glTranslatef(0.5,2.55,-6.0);
    glutSolidSphere(0.1,6,6);
    glPopMatrix();

    }

void Cables(){

    glPushMatrix();
        GLUquadricObj *obj2=gluNewQuadric();
        glColor3f(1.0,0.0,0.0);
        glTranslatef(0.5,5.55,-6.0);
        glRotatef(90,1.0,0.0,0.0);
        //glRotatef(angle,0.0,1.0,0.0);
        gluCylinder(obj2,0.03,0.03,3.0,25,1);
    glPopMatrix();

        glPushMatrix();
        GLUquadricObj *obj23=gluNewQuadric();
        glColor3f(0.0,0.0,1.0);
        glTranslatef(-0.5,6.05,-6.0);
        glRotatef(90,1.0,0.0,0.0);
        //glRotatef(angle,0.0,1.0,0.0);
        gluCylinder(obj23,0.03,0.03,3.5,25,1);
    glPopMatrix();

    glPushMatrix();
        GLUquadricObj *obj26=gluNewQuadric();
        glColor3f(1.0,0.0,0.0);
        glTranslatef(0.5,5.55,-6.0);

        gluCylinder(obj26,0.03,0.03,3.0,25,1);
    glPopMatrix();

        glPushMatrix();
        GLUquadricObj *obj236=gluNewQuadric();
        glColor3f(0.0,0.0,1.0);
        glTranslatef(-0.5,6.05,-6.0);

        gluCylinder(obj236,0.03,0.03,3.5,25,1);
    glPopMatrix();




    }
void lampe(){
    glPushMatrix();
        glColor3f(0.5,0.5,0.5);
        glTranslatef(-5,5.3,0.5);
        glScalef(0.5,1.0,0.5);
        glRotatef(90,0.0,0.0,1.0);
        glutSolidCube(1.0);
    glPopMatrix();

        glPushMatrix();
            GLfloat lightPos5[]={-2.9, 5.4, 0.0, -4.0};
            GLfloat light_specular5[] = { 1.0, 0.01, 0.01, 0.1 };
   // glLightfv(GL_LIGHT1,GL_SPECULAR,light_specular5);

    glColor3f(col,col,lumiere);
    glTranslatef(-2.9,5.4,0.8);
    glutSolidSphere(1.0,10,25);
    glPopMatrix();



    }
void Scene()
{

glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
glTranslated(-5.0,0.0,0.0);
//GRANDE CYLINDRE+petite sphere pour le faire bouger
CylindreAndSphere();


Torus();
TorCylLine();


//Piston(petite sphere au centre du torus)
glPushMatrix();
 glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
glLineWidth(10);
int k=0;
float X=-9,Y=-0.43;
glColor3f(0.4,0.3,1.0);
/*if(allume!=1.0 && lumiere!=1.0)
while(k<7)
{    glBegin(GL_LINES);
    glVertex3f(X,Y,0);
    Y-=0.3;

    if((int) X%2==0) X-=rand()%2+0.01;
    else X+=rand()%2+0.01;
    glVertex3f(X,Y,0);
    glEnd();

    k++;
}*/
TorusVersTransfo();
Transfo();
Cables();
lampe();


cout <<  allume << endl;
cout <<  lumiere << endl;

glutSwapBuffers();





}
void initRendering(){
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_SMOOTH);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_NORMALIZE);

    }
void Lightt(){
        initRendering();
    	glShadeModel(GL_SMOOTH);
		glMaterialf(GL_FRONT, GL_SHININESS, 1.0);
float s[1]={50};
glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,s);
    //Add ambient Light
     ambientColor[0]=0.1f;
     ambientColor[1]=0.1f;
     ambientColor[2]=0.1f;

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,ambientColor);

    //Add positionned light
    GLfloat lightColor0[]={0.5f,0.5f,0.5f,1.0f};
    GLfloat lightPos0[]={0.0f,2.0f,8.0f,1.0f};
    glLightfv(GL_LIGHT0,GL_DIFFUSE,lightColor0);
    glLightfv(GL_LIGHT0,GL_POSITION,lightPos0);

    //Add directed light
    GLfloat lightColor1[]={0.5f,0.2f,0.2f,1.0f};

    //Comming from the direction (-1,0.5,0.5)
    GLfloat lightPos1[]={-1.0f,0.5f,0.5f,0.0f};
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    glLightfv(GL_LIGHT1,GL_SPECULAR,light_specular);
    glLightfv(GL_LIGHT0,GL_SPECULAR,light_specular);

    glLightfv(GL_LIGHT1,GL_DIFFUSE,lightColor1);
    glLightfv(GL_LIGHT1,GL_POSITION,lightPos1);




    }
int main()
{
glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);


    glutInitWindowSize(920,720);
    glutInitWindowPosition(100,100);
    glutCreateWindow("OpenGl TP");
   // glutKeyboardFunc(keyPressed);
//   glutKeyboardUpFunc(keyUp);
   glutSpecialFunc(animerVoiture);
    Lightt();
  // glutMouseFunc(mousePressed);
glutDisplayFunc(Scene);

    glutReshapeFunc(Reshape);

    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);






   glutIdleFunc(animer);
    glutMainLoop();
return 0;

}
