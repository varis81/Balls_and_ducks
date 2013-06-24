#include <stdio.h>     // - Just for some ASCII messages
#include <string>
#include <cmath>
#include <ctime>
#include <iostream>
#include <fstream>
#include "visuals.h"

#include "GL/glut.h"   // - An interface and windows management library

#define pi 3.14159265358979323846264338327950288
#define g 10.0

using namespace std;


duck d;
balloon b;
static float hflag = 0.0;
static float tx = 0.0;
static float ty = 0.0;
static float zm = 0.0;
static float anglex = 0.0;
static float angley = 0.0;
static float dt = 0.0005;
static float dt1 = 0.003;
static float dt2 = 0.19;
static float start_animation = 0.0;
static float animation = 0.0;
static float v0 = 38.0;                 //arxiki taxitita mpalas
static float a = 0.0;                   //gonia bolis
static float xb = 0.0;                     /////////
static float yb = 0.0;                    // syntetagmenes mpalas
static float zb = 0.0;                    /////////
static float t = 0.0;
static float bcr = 1.0;
static float bcg = 1.0;
static float bcb = 0.0;
static float xcenter;
static float duck_radius = 0.0;
static float sphere_radius = 5.0;
static float xmax = 0.0;
static double starttime = 0.0;
static double endtime = 0.0;
static float cutime = 0.0;
static float dflag[] = {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};
static float vd = 10.0;
static float xd[] = {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};
static float zd[] = {5.0,5.0,5.0,5.0,5.0,5.0,5.0,5.0,5.0,5.0};
static float etime[] = {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};
static float e1time[] = {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};
static float e2time[] = {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};
static float ktime[] = {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};
static float k1time[] = {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};
static float gonia[] = {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};
static float cyrcle_flag[] = {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};
static float c1flag[] = {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};
static float leftflag[] = {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};
static float xdk[] = {0.0,0.0,0.0 ,0.0,0.0,0.0,0.0,0.0,0.0,0.0};
static float zdk[] = {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};
static float apostasi[] = {-2.5,0.0,-7.5,-5.0,2.5,5.0,7.5,10.0,12.3,-10.0};
static float game_over_flag = 0.0;

GLUquadricObj *pObj;

float duckcol[]={1.0,1.0,0.0};


void keimeno(const char *str,float size,int value)
{
   char buffer[10];

   glPushMatrix();
   glScalef(size,size,size);

   if(value == 666)                          //periptosi ektyposis keimenou
   {
      for (int i=0;i<strlen(str);i++)
	     glutStrokeCharacter(GLUT_STROKE_ROMAN,str[i]);
   }
   else                                     //periptosi ektyposis arithmou
   {
	  sprintf(buffer,"%d",value);
      for (int i=0;i<strlen(buffer);i++)
	     glutStrokeCharacter(GLUT_STROKE_ROMAN,buffer[i]);   
   }

   glPopMatrix();
}

void star()
{
   glColor3f(1.0, 0.9, 0.0);
   glPointSize(3);
   glBegin(GL_TRIANGLES);             // Asteri ftiagmeno xrhsimopoiontas 6 shmeia
   glVertex2f(-15.0,-8.0);
   glVertex2f(15.0,-8.0);
   glVertex2f(0.0,17.0);
   glEnd();
}

void Render()
{       
     
  //CLEARS FRAME BUFFER ie COLOR BUFFER& DEPTH BUFFER (1.0)
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // Clean up the colour of the window
													   // and the depth buffer
  glMatrixMode(GL_MODELVIEW); 
  glLoadIdentity();
  
  glTranslatef(0,-25,-120);
  glTranslatef(tx,ty,zm);
  glRotatef(anglex,1,0,0);   
  glRotatef(angley,0,1,0); 

  glPushMatrix();

  glPushMatrix();
  glTranslatef(0,0,-0.65);
  
  glPushMatrix();           //pano aristera podi
  glColor3f(0.0, 0.0, 1.0);
  glTranslatef(-50,-40,-65);
  glScalef(0.5,4.0,0.5);
  glutSolidCube(12);
  glPopMatrix();
  
  glPushMatrix();             //pano dexia podi
  glColor3f(0.0, 0.0, 1.0);
  glTranslatef(50,-40,-65);
  glScalef(0.5,4.0,0.5);
  glutSolidCube(12);
  glPopMatrix();
  
  glPushMatrix();           //piso eutheia pista
  glColor3f(0.18, 0.18, 0.18);
  glTranslatef(0.0,-16,-65);
  glScalef(13.5,0.1,0.55);
  glutSolidCube(12);
  glPopMatrix();
  
  glPopMatrix();      
  
  glPushMatrix();              //kato aristera podi
  glColor3f(0.0, 0.0, 1.0);
  glTranslatef(-50,-40,-20);
  glScalef(0.5,4.0,0.5);
  glutSolidCube(12);
  glPopMatrix();
  
  glPushMatrix();            //kato dexia podi
  glColor3f(0.0, 0.0, 1.0);
  glTranslatef(50,-40,-20);
  glScalef(0.5,4.0,0.5);
  glutSolidCube(12);
  glPopMatrix();
  
  glPushMatrix();           //mprostini eutheia pista
  glColor3f(0.18,0.18,0.18);
  glTranslatef(0.0,-16,-20);
  glScalef(13.5,0.1,0.5);
  glutSolidCube(12);
  glPopMatrix();
  
  glPushMatrix();               //dexi imikiklio
  glColor3f(1.0, 1.0, 1.0);
  glRotatef(-90.0,1.0,0.0,0.0);
  glTranslatef(80.0,43.0,-16.0);
  glScalef(15,13,3);
  pObj = gluNewQuadric();
  gluPartialDisk(pObj, 1.5f, 2.0f, 20, 30, 0.0f, 180.0f);
  glPopMatrix();
  
  
   glPushMatrix();               //aristero imikiklio
   glColor3f(1.0, 1.0, 1.0);
   glRotatef(-90.0,1.0,0.0,0.0);
   glRotatef(180.0,0.0,0.0,1.0);
   glTranslatef(80.0,-43.0,-16.0);
   glScalef(15,13,3);
   pObj = gluNewQuadric();
   gluPartialDisk(pObj, 1.5f, 2.0f, 20, 30, 0.0f, 180.0f);
   glPopMatrix();


  glPushMatrix();
  glColor3f(0.81, 0.36, 0.36);
  glTranslatef(0,25,-40);
  glScalef(75,50,0.5);             // pinakas
  glutSolidCube(1.0);
  glPopMatrix();


 if(!dflag[2])
 {
  glPushMatrix();       //papia
  glRotatef(180.0,0.0,1.0,0.0);
  glScalef(6,5,4);
  glColor3f(duckcol[0], duckcol[1], duckcol[2]);
  glTranslatef(apostasi[2],0.0,0.0 );
  glTranslatef(xdk[2]+xd[2],-2.8,zdk[2]+zd[2]);
  if(cyrcle_flag[2])
	  glRotatef(gonia[2],0.0,1.0,0.0);
  DisplayDuck(d);
  glPopMatrix();
 }

 if(!dflag[3])
 {
  glPushMatrix();       //papia
  glRotatef(180.0,0.0,1.0,0.0);
  glScalef(6,5,4);
  glColor3f(duckcol[0], duckcol[1], duckcol[2]);
  glTranslatef(apostasi[3],0.0,0.0 );
  glTranslatef(xdk[3]+xd[3],-2.8,zdk[3]+zd[3]);
  if(cyrcle_flag[3])
	  glRotatef(gonia[3],0.0,1.0,0.0);
  DisplayDuck(d);
  glPopMatrix();
 }

 if(!dflag[0])
 {
  glPushMatrix();       //papia
  glRotatef(180.0,0.0,1.0,0.0);
  glScalef(6,5,4);
  glColor3f(duckcol[0], duckcol[1], duckcol[2]);
  glTranslatef(apostasi[0],0.0,0.0 );
  glTranslatef(xdk[0]+xd[0],-2.8,zdk[0]+zd[0]);
  if(cyrcle_flag[0])
	  glRotatef(gonia[0],0.0,1.0,0.0);
  DisplayDuck(d);
  glPopMatrix();
 }
  if(!dflag[1])
  {
     glPushMatrix();       //papia
     glRotatef(180,0.0,1.0,0.0);
     glScalef(6,5,4);
     glColor3f(duckcol[0], duckcol[1], duckcol[2]);
	 glTranslatef(xdk[1]+xd[1],-2.8,zdk[1]+zd[1]);
	 glTranslatef(apostasi[1],0.0,0.0 );
	 if(cyrcle_flag[1])
	    glRotatef(gonia[1],0.0,1.0,0.0);
     DisplayDuck(d);
     glColor3f(0.4,0.3,0.2);
     glPopMatrix();
  }

 if(!dflag[4])
 {
  glPushMatrix();       //papia
  glRotatef(180.0,0.0,1.0,0.0);
  glScalef(6,5,4);
  glColor3f(duckcol[0], duckcol[1], duckcol[2]);
  glTranslatef(apostasi[4],0.0,0.0 );
  glTranslatef(xdk[4]+xd[4],-2.8,zdk[4]+zd[4]);
  if(cyrcle_flag[4])
	  glRotatef(gonia[4],0.0,1.0,0.0);
  DisplayDuck(d);
  glPopMatrix();
 }

 if(!dflag[5])
 {
  glPushMatrix();       //papia
  glRotatef(180.0,0.0,1.0,0.0);
  glScalef(6,5,4);
  glColor3f(duckcol[0], duckcol[1], duckcol[2]);
  glTranslatef(apostasi[5],0.0,0.0 );
  glTranslatef(xdk[5]+xd[5],-2.8,zdk[5]+zd[5]);
  if(cyrcle_flag[5])
	  glRotatef(gonia[5],0.0,1.0,0.0);
  DisplayDuck(d);
  glPopMatrix();
 }

 if(!dflag[6])
 {
  glPushMatrix();       //papia
  glRotatef(180.0,0.0,1.0,0.0);
  glScalef(6,5,4);
  glColor3f(duckcol[0], duckcol[1], duckcol[2]);
  glTranslatef(apostasi[6],0.0,0.0 );
  glTranslatef(xdk[6]+xd[6],-2.8,zdk[6]+zd[6]);
  if(cyrcle_flag[6])
	  glRotatef(gonia[6],0.0,1.0,0.0);
  DisplayDuck(d);
  glPopMatrix();
 }
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 if(!dflag[7])
 {
    glPushMatrix();       //papia
  glRotatef(180.0,0.0,1.0,0.0);
  glScalef(6,5,4);
  glColor3f(duckcol[0], duckcol[1], duckcol[2]);
  glTranslatef(apostasi[7],0.0,0.0 );
  glTranslatef(xdk[7]+xd[7],-2.8,zdk[7]+zd[7]);
  if(cyrcle_flag[7])
	  glRotatef(gonia[7],0.0,1.0,0.0);
  DisplayDuck(d);
  glPopMatrix();
 }

 if(!dflag[8])
 {
    glPushMatrix();       //papia
  glRotatef(180.0,0.0,1.0,0.0);
  glScalef(6,5,4);
  glColor3f(duckcol[0], duckcol[1], duckcol[2]);
  glTranslatef(apostasi[8],0.0,0.0 );
  glTranslatef(xdk[8]+xd[8],-2.8,zdk[8]+zd[8]);
  if(cyrcle_flag[8])
	  glRotatef(gonia[8],0.0,1.0,0.0);
  DisplayDuck(d);
  glPopMatrix();
 }

 if(!dflag[9])
 {
    glPushMatrix();       //papia
  glRotatef(180.0,0.0,1.0,0.0);
  glScalef(6,5,4);
  glColor3f(duckcol[0], duckcol[1], duckcol[2]);
  glTranslatef(apostasi[9],0.0,0.0 );
  glTranslatef(xdk[9]+xd[9],-2.8,zdk[9]+zd[9]);
  if(cyrcle_flag[9])
	  glRotatef(gonia[9],0.0,1.0,0.0);
  DisplayDuck(d);
  glPopMatrix();
 }
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  glPushMatrix();             //balloon
  glColor3f(1.0, 0.35, 0.0);
  glTranslatef(-50.0,-2.8,-40);
  glScalef(30,30,30);
  DisplayBalloon(b);
  glPopMatrix();
  
  glPushMatrix();             //balloon
  glColor3f(1.0, 0.35, 0.0);
  glTranslatef(50.0,-2.8,-40);
  glScalef(30,30,25);
  DisplayBalloon(b);
  glPopMatrix();
  
  glPushMatrix();          //mpala
  glColor3f(bcr, bcg, bcb);
  glTranslatef(0.0,8.0,60.0);
  glTranslatef(xb,yb,zb);
  glutSolidSphere(sphere_radius,120,120);
  glPopMatrix();

  glPushMatrix();
  glColor3f(1.0, 1.0, 1.0);
  glTranslatef(-22.5,45,-38.5);
  keimeno("~~~Mpalakia kai Papakia~~~",0.025f,666);
  glTranslatef(8.0,-5.0,0.0);
  keimeno("press 'm' to start",0.025f,666);
  glTranslatef(0.0,-5.0,0.0);
  keimeno("press 'h' to shoot",0.025f,666);
  glTranslatef(0.0,-5.0,0.0);
  keimeno("w/s/a/d to change view",0.025f,666);
  glTranslatef(0.0,-5.0,0.0);
  keimeno("(+/-) to zoom in/out",0.025f,666);
  glTranslatef(0.0,-5.0,0.0);
  keimeno("Shooting Angle (u/b):",0.025f,666);
  glTranslatef(35.0,0.0,0.0);
  keimeno(" ",0.025f,a);
  glTranslatef(-35.0,-5.0,0.0);
  keimeno("Ball position in X-Axis:",0.025f,666);
  glTranslatef(38.0,0.0,0.0);
  keimeno(" ",0.025f,xb);
  glTranslatef(-38.0,-5.0,0.0);
  keimeno("Ball Velocity (y/v):",0.025f,666);
  glTranslatef(30.0,0.0,0.0);
  keimeno(" ",0.025f,v0);
  glTranslatef(-30.0,-5.0,0.0);
  keimeno("Duck Velocity:",0.025f,666);
  glTranslatef(22.0,0.0,0.0);
  keimeno(" ",0.025f,vd);
  glPopMatrix();

  if(hflag)
  {
     glPushMatrix();                      //asteri
     glTranslatef(0.0,-40.0,-10.0);  
     star();
     glRotatef(45.0,0,0,1);
     star();
     glRotatef(-90.0,0,0,1);
     star();
     glColor3f(1.0, 0.0, 0.1);
     glTranslatef(-1.8,-7.0,1.0);              // emfanish mhnymatos otan xtyphthei papaki
	 glRotatef(45.0,0,0,1);
     keimeno("Hit!",0.08f,666);
     glPopMatrix();
  }

  if(game_over_flag)                        //GAME OVER
  { 
     glPushMatrix();
	 glColor3f(1.0,0.0,0.0);
	 glTranslatef(-35.0,55.0,-30.0);
	 keimeno("GAME OVER",0.10f,666);
	 glPopMatrix();
  }
  glPopMatrix();

 
  glutSwapBuffers();             // All drawing commands applied to the 
                                 // hidden buffer, so now, bring forward
                                 // the hidden buffer and hide the visible one
}


void Setup()
{ 
	ReadFile(&d,&b);

	//Parameter handling
	glShadeModel (GL_SMOOTH);
	
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);  //renders a fragment if its z value is less or equal of the stored value
	glClearDepth(1);
    
	// polygon rendering mode
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial( GL_FRONT, GL_AMBIENT_AND_DIFFUSE );
  
	//Set up light source
	GLfloat light_position[] = { 0.0, 30.0, 50.0, 0.0 };
	glLightfv( GL_LIGHT0, GL_POSITION, light_position);

	GLfloat ambientLight[] = { 0.3, 0.3, 0.3, 1.0 };
	GLfloat diffuseLight[] = { 0.8, 0.8, 0.8, 1.0 };
	GLfloat specularLight[] = { 1.0, 1.0, 1.0, 1.0 };

	   
	glLightfv( GL_LIGHT0, GL_AMBIENT, ambientLight );
	glLightfv( GL_LIGHT0, GL_DIFFUSE, diffuseLight );
	

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);

	//01
	glFrontFace(GL_CCW);
 

	// Black background
	glClearColor(0.0f,0.0f,0.0f,1.0f);

}

void Resize(int w, int h)
{ 
  // define the visible area of the window ( in pixels )
  if (h==0) h=1;
  glViewport(0,0,w,h); 

  // Setup viewing volume

  glMatrixMode(GL_PROJECTION); 
  glLoadIdentity();
 //glOrtho (-100.0, 100.0, -100.0, 100.0, 100.0,-100.0);
  gluPerspective(60.0, (float)w/(float)h, 1.0, 500.0);
}

void Idle()
{
   int i,j;

   if(game_over_flag)
   {
	  bcr = 0.5;
	  bcg = 0.5;
	  bcb = 0.5;
   }
   if(start_animation)
   {
   for(i=0; i < 10;i++)
   {
      if((xd[i] + xdk[i]) > -12.2 - apostasi[i] && (zd[i] + zdk[i]) == 5.0 )
	  {
	     xd[i] = -vd*etime[i];                   // x = u*t
		 etime[i] = etime[i] + dt1;
		 gonia[i] = 180.0;
	  }
	  else if((zd[i]+zdk[i]) <= 16.399999 && (xd[i] + xdk[i]) > -17.999999 - apostasi[i] && !c1flag[i])
	  {
	     xdk[i] = -5.7*sin((pi/180)*(vd*ktime[i])/(5.7));
		 zdk[i]= -5.7*cos(pi*(vd*ktime[i])/(180*5.7)) +5.7;
		 cyrcle_flag[i] = 1;
		 gonia[i] = (vd*ktime[i])/5.7;
		 ktime[i] = ktime[i] + dt2;
	  }
	  else if(zdk[i] + zd[i] > 16.399999 && (xd[i] + xdk[i]) <= 12.2 -apostasi[i])
	  {
		  xdk[i] = vd*e1time[i];
          e1time[i] = e1time[i] + dt1;
	  }
	  else if((zd[i]+zdk[i]) >= 5.001 && (xd[i] +xdk[i]) < 17.999999 - apostasi[i]  )
	  {
		  c1flag[i] = 1.0;
         if(!leftflag[i])
		 {
		     zd[i] = zd[i] + zdk[i];
		     xd[i] = xd[i] + xdk[i];
			 leftflag[i] = 1.0;
		 }
	     xdk[i] = 5.7*sin((pi/180)*(vd*k1time[i])/(5.7));
		 zdk[i] = 5.7*cos(pi*(vd*k1time[i])/(180*5.7)) -5.7;
		 cyrcle_flag[i] = 1;
		 gonia[i] = 180 + (vd*k1time[i])/5.7;
		 k1time[i] = k1time[i] + dt2;		  

	  }
	  else if((xd[i]+xdk[i]) > -0.0 && (zd[i] + zdk[i]) <= 5.001  )
	  {
		  xdk[i] = -vd*e2time[i];
		  e2time[i] = e2time[i] + dt1;
		  if(xd[i] + xdk[i] < 0.0)
		  {
		     xd[i] = 0.0;
			 xdk[i] = 0.0;
			 zd[i] = 5.0;
			 zdk[i] = 0.0;
			 c1flag[i] = 0.0;
			 leftflag[i] = 0.0;
			 cyrcle_flag[i] = 0.0;
			 gonia[i] = 180.0;
			 etime[i] = 0.0;
			 e1time[i] = 0.0;
			 e2time[i] = 0.0;
			 ktime[i] = 0.0;
			 k1time[i] = 0.0;
		  }
	  }
      if(animation)
	  {
		  if(yb > -40.0)                 //epilogi katofliou
		  {
		     yb = v0*sin(pi*(a/180))*t - (g*t*t)/2;     //synarthseis bolis
			 zb = -v0*cos(pi*(a/180))*t;                //h bolh ginetai stous aksones y,z
			 t = t + dt;
			 if(sqrt((xb - (-6*(xd[i]+xdk[i]+apostasi[i])))*(xb - (-6*(xd[i]+xdk[i]+apostasi[i]))) + ((8+yb) -(-14))*((8+yb) -(-14)) + ((60+zb) -(-4*(zd[i]+zdk[i])))*((60+zb) -(-4*(zd[i]+zdk[i])))) < 6*duck_radius + sphere_radius)
			 {
				 hflag = 1.0;
				 zd[i] = 999;
				 dflag[i] = 1.0;
			 }
		  }
		  else
		  {
		     xb = 0.0;
		     yb = 0.0;
			 zb = 0.0;
             t = 0.0;
             animation = 0.0;

		  }
	   }
	  }
   }
   if(hflag)
   {
	  if(cutime < 50)
	  {
	     cutime = cutime + 0.08;
		 start_animation = 0.0;
		 animation = 0.0;
	  }
	  else
	  {
		 hflag = 0.0;
		 xb = 0.0;
		 yb = 0.0;
	     zb = 0.0;
		 t=0.0;
		 cutime = 0.0;
		 start_animation = 1.0;
	  }
   }
   if(dflag[0] &&  dflag[1] && dflag[2] &&  dflag[3] && dflag[4] &&  dflag[5] && dflag[6] &&  dflag[7] && dflag[8] &&  dflag[9])                    //game over
   { 
      start_animation = 0.0;
	  game_over_flag = 1.0;
   }
	glutPostRedisplay();
}

void Keyboard(unsigned char key,int x,int y)
{
	int i;

   switch(key)
   {
      case 'q': 
		       exit(0);
		       break;
	  case 'm':
	           if(start_animation == 0.0)
	           start_animation = 1.0;
			   else
				   start_animation = 0.0;
			   break;
	  case 'h':
		       if(start_animation)
			   {
			      if(!animation)
				  {
			         if(animation == 0.0)
			            animation = 1.0;
			         else
				        animation = 0.0;
				   }  
			   }
			   break;
	  case 'w':
		       anglex = anglex + 2;
		       //ty = ty + 2;
		       break;
	  case 's':
		       anglex = anglex - 2;
		      // ty = ty -2;
			   break;
	  case 'a':
		       angley = angley - 2;
		      // tx = tx - 2;
			   break;
	  case 'd':
		       angley = angley + 2;
		       //tx = tx + 2;
			   break;
	  case 'u':
	           if((start_animation == 0 && animation == 0) || (start_animation == 1 && animation == 0))     //gonia volis ++
			   {
			      if(a<90)
				     a++;
			   }
		       break;
	  case 'b':
		       if((start_animation == 0 && animation == 0) || (start_animation == 1 && animation == 0))     //gonia volis --
			   {
			      if(a>-90)
				     a--;
			   }
		       break;
	  case 'y':if((start_animation == 0 && animation == 0) || (start_animation == 1 && animation == 0))
			   {
			      if(v0 < 100)
				     v0++;
			   }
		       break;
	  case 'v':if((start_animation == 0 && animation == 0) || (start_animation == 1 && animation == 0))
			   {
			      if(v0 > 0)
				     v0--;
			   }
		       break;
	  case '-':
	           zm = zm--;
			   break;
	  case '+':
	           zm = zm++;
			   break;
   }
   glutPostRedisplay();
}

void SpecialKeyboard(int key,int x,int y)
{
    switch(key)
	{
	   case GLUT_KEY_RIGHT :
		                    if((start_animation == 0 && animation == 0) || (start_animation == 1 && animation == 0))
							{
							   if(xb < 108)         //(L+R)/2
							      xb++;
							}
							break;
	   case GLUT_KEY_LEFT :
		                    if((start_animation == 0 && animation == 0) || (start_animation == 1 && animation == 0))
							{
							   if(xb > -108)         //(L+R)/2
							      xb--;
							}
							break;

	}
	glutPostRedisplay();
}

void cdr()
{
	int i;

	for (i = 0; i < d.vertices; i++)
       xcenter = xcenter + d.obj_points[i].x;
	xcenter = xcenter/d.vertices;
	for (i = 0; i < d.vertices; i++)
	{
         if(d.obj_points[i].x - xcenter > xmax)
		 {
	        xmax = (d.obj_points[i].x - xcenter);
		 }
    }
	duck_radius = xmax - abs(xcenter);
}

void ReadFile(duck *d,balloon *b)
{    
     int  i;
     string         str,st;
     ifstream duck;    // Create an input file stream.
     ifstream balloon;    // Create an input file stream.
     
     duck.open("duck.obj");   // Use it to read from file balloon.obj.
     balloon.open("balloon.obj");  // Use it to read from file balloon.obj.
     
     if (duck.fail() || balloon.fail()) 
		exit(1);

     
     for(i=0;i<9;i++){
       getline(duck,str);
       getline(balloon,str);
     }
     
     d->vertices=427;
     b->vertices=447;

     for(i=0;i<(d->vertices);i++){
       duck >> st;
       duck >> d->obj_points[i].x;
       duck >> d->obj_points[i].y;
       duck >> d->obj_points[i].z;
     }
     
     for(i=0;i<(b->vertices);i++){
       balloon >> st;
       balloon >> b->obj_points[i].x;
       balloon >> b->obj_points[i].y;
       balloon >> b->obj_points[i].z;
     }

     do
     {
     duck >> st;
     }
     while ( st!="f" );
     
     do
     {
     balloon >> st;
     }
     while ( st!="f" );

     d->faces=824;
     b->faces=1398;
     
     i=0;
     while (!duck.eof())     
     {
      duck >> d->obj_faces[i].vtx[0];                  //reading x  (from x//y)
      duck >> st;                             //reading //y (from x//y)
      duck >> d->obj_faces[i].vtx[1];
      duck >> st;
      duck >> d->obj_faces[i].vtx[2];
      duck >> st;
      duck >> st;
      i++;                               //reading f
     }    

     duck.close();
     cdr();
     i=0;
     while (!balloon.eof())     
     {
      balloon >> b->obj_faces[i].vtx[0];                  //reading x  (from x//y)
      balloon >> st;                             //reading //y (from x//y)
      balloon >> b->obj_faces[i].vtx[1];
      balloon >> st;
      balloon >> b->obj_faces[i].vtx[2];
      balloon >> st;
      balloon >> st;
      i++;                               //reading f
     }    

     balloon.close();

}
     
void DisplayDuck(duck b)
{

	glPushMatrix();
	glBegin(GL_TRIANGLES);

	for (int i = 0; i < b.faces; i++)
	{
		glVertex3f(b.obj_points[b.obj_faces[i].vtx[0]-1].x,b.obj_points[b.obj_faces[i].vtx[0]-1].y,b.obj_points[b.obj_faces[i].vtx[0]-1].z);
		glVertex3f(b.obj_points[b.obj_faces[i].vtx[1]-1].x,b.obj_points[b.obj_faces[i].vtx[1]-1].y,b.obj_points[b.obj_faces[i].vtx[1]-1].z);
		glVertex3f(b.obj_points[b.obj_faces[i].vtx[2]-1].x,b.obj_points[b.obj_faces[i].vtx[2]-1].y,b.obj_points[b.obj_faces[i].vtx[2]-1].z);
	}

	glEnd();
	glPopMatrix();

}     
  
void DisplayBalloon(balloon b)
{

	glPushMatrix();
	glBegin(GL_TRIANGLES);

	for (int i = 0; i < b.faces; i++)
	{
		glVertex3f(b.obj_points[b.obj_faces[i].vtx[0]-1].x,b.obj_points[b.obj_faces[i].vtx[0]-1].y,b.obj_points[b.obj_faces[i].vtx[0]-1].z);
		glVertex3f(b.obj_points[b.obj_faces[i].vtx[1]-1].x,b.obj_points[b.obj_faces[i].vtx[1]-1].y,b.obj_points[b.obj_faces[i].vtx[1]-1].z);
		glVertex3f(b.obj_points[b.obj_faces[i].vtx[2]-1].x,b.obj_points[b.obj_faces[i].vtx[2]-1].y,b.obj_points[b.obj_faces[i].vtx[2]-1].z);
	}

	glEnd();
	glPopMatrix();

}  
