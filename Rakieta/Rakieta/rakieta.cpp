#include "glm.h"

static float ykot = 0, zkot = 0, xkot=0, bkot=0;

#define PI 3.1415f
int xd, yd;
float rx, ry, tz=-3;
int ldown, rdown;
GLMmodel* rak = 0;
GLMmodel* podl = 0;
GLMmodel* sceneria = 0;
GLMmodel* igloo = 0;
GLMmodel* wieza = 0;
GLMmodel* start = 0;
double px=3,py=0,pz=0,jas_sw=0.1;

void init(void) 
{
   glClearColor (0.0, 0.0, 0.0, 0.0);   
   glEnable(GL_DEPTH_TEST);
   glShadeModel (GL_SMOOTH);
}

GLfloat a,b,c,y,i,m,j,k=0;
int u=1;
GLfloat xa=0.0f;
GLfloat xb=4.0f;
GLfloat xm=2.0f;
GLfloat ym=5.0f;

//parametry swiat³a
GLfloat swiatlo_otaczajace[4] = {0.05f, 0.0f, 0.0f, 1.0f};
GLfloat swiatlo_rozproszone[4] = {0.1f, 0.0f, 0.0f, 1.0f};
GLfloat swiatlo_odbite[4] = {0.99f, 0.0f, 0.0f, 1.0f}; 
GLfloat pozycja_swiatla[4] = {10, 50, 50, 0.0f};
GLfloat odblaskowosc[4] = {1.0f, 0.0f, 0.0f, 0.0f};
GLfloat kierunek[3]={10.0f,0.0f,-1.0f};

void trajektoria(void)
{
	a= -1/(-xb*xa+xb*xm+xm*xa-xm*xm)*ym;
	b= (xa+xb)/(-xb*xa+xb*xm+xm*xa-xm*xm)*ym;
	c= -xb*xa/(-xb*xa+xb*xm+xm*xa-xm*xm)*ym;
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_LINES);
	for(i=0; i<=xb; i+=(xb/50))
	{
		y=(a*i*i)+(b*i)+c;
		glVertex2f(i,y); 
	}
	glEnd();
}

void podloze(void)
{
    if (!podl) 
	{
        podl = glmReadOBJ((char*)"podloze.obj", 0);	
        if (!podl) exit(0);
        glmUnitize(podl);
        glmFacetNormals(podl);        
		glmVertexNormals(podl, 90.0);
    }
    glmDraw(podl, GLM_SMOOTH|GLM_TEXTURE);
}

void wiezyczka(void)
{
    if (!wieza) 
	{
        wieza = glmReadOBJ((char*)"wieza2.obj", 0);
        if (!wieza) exit(0);
        glmUnitize(wieza);
        glmFacetNormals(wieza);        
		glmVertexNormals(wieza, 90.0);
    }
    glmDraw(wieza, GLM_SMOOTH|GLM_TEXTURE);
}

void scena(void)
{
    if (!sceneria) 
	{
        sceneria = glmReadOBJ((char*)"sceneria.obj", 0);


        if (!sceneria) exit(0);
        glmUnitize(sceneria);
        glmFacetNormals(sceneria);        
		glmVertexNormals(sceneria, 90.0);
    }
    glmDraw(sceneria, GLM_SMOOTH|GLM_TEXTURE);
}

void starter(void)
{
    if (!start) 
	{
        start = glmReadOBJ((char*)"start.obj", 0);
        if (!start) exit(0);
        glmUnitize(start);
        glmFacetNormals(start);        
		glmVertexNormals(start, 90.0);
    }
    glmDraw(start, GLM_SMOOTH|GLM_TEXTURE);
}
void iglo(void)
{
    if (!igloo) 
	{
        igloo = glmReadOBJ((char*)"igloo.obj", 0);
        if (!igloo) exit(0);
        glmUnitize(igloo);
        glmFacetNormals(igloo);        
		glmVertexNormals(igloo, 90.0);
    }
    glmDraw(igloo, GLM_SMOOTH|GLM_COLOR);
}
void rakieta(void)
{
    if (!rak) 
	{
        rak = glmReadOBJ((char*)"rakieta2.obj", 0);
        if (!rak) exit(0);
        glmUnitize(rak);
        glmFacetNormals(rak);        
		glmVertexNormals(rak, 90.0);
		glmScale(rak,0.5);
    }
    glmDraw(rak, GLM_SMOOTH| GLM_COLOR);
}

void siatka(void)
{
	float linia;
	for(linia = -500; linia < 500; linia+=5){

		GLfloat linia1[3]={ linia, 500.0f, -4.0f};
		GLfloat linia2[3]={ linia, -500.0f, -4.0f};
		glColor3f(1.0f, 1.0f, 1.0f);
		glPushMatrix();
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		glTranslatef(0.0f,0.0f,6.0f);
		glBegin(GL_LINES); 
		glVertex3fv(linia1); 
		glVertex3fv(linia2); 
		glEnd();
		glPopMatrix();
	}

	for(linia = -500; linia < 500; linia+=5){

		GLfloat linia1[3]={ 500, linia, -4.0f};
		GLfloat linia2[3]={ -500, linia, -4.0f};
		glColor3f(1.0f, 1.0f, 1.0f);
		glPushMatrix();
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f); 
		glTranslatef(0.0f,0.0f,6.0f);
		glBegin(GL_LINES); 
		glVertex3fv(linia1); 
		glVertex3fv(linia2); 
		glEnd();
		glPopMatrix();
	}

}

void laser()
{
	//funkcje œwiat³a
	glLightfv(GL_LIGHT1,GL_AMBIENT,swiatlo_otaczajace); 
	glLightfv(GL_LIGHT1,GL_DIFFUSE,swiatlo_rozproszone); 
	glLightfv(GL_LIGHT1,GL_SPECULAR,swiatlo_odbite); 
	glLightfv(GL_LIGHT1,GL_POSITION,pozycja_swiatla);
	glLightfv(GL_LIGHT1,GL_SPOT_DIRECTION,kierunek);
	glEnable(GL_COLOR_MATERIAL); 
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE); 
	glMaterialfv(GL_FRONT, GL_SPECULAR,odblaskowosc);
	glMateriali(GL_FRONT,GL_SHININESS,128);
}

void glowna()
{
	glPushMatrix();
	glTranslatef(0,-3,0);
	siatka();
	glPopMatrix();

	glPushMatrix();
	glScalef(100,100,100);
	glTranslatef(0,-0.02,0);
	podloze();
	glPopMatrix();

	glPushMatrix();
	glScalef(3,3,3);
	glRotatef(90.0f,0.0f,1.0f,0.0f);
	glTranslatef(3,0,-1.5);
	for(int x=2;x>=-3;x-=2)
	{
		iglo();
		glTranslatef(x,0,0);
	}
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-6,3,-1);
	glScalef(3.5,3.5,3.5);
	wiezyczka();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-3.0,-1.1,-1.0);
	trajektoria();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-3,-1.1,-1);
	glScalef(0.3,0.3,0.3);
	starter();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0,0.0,0.0);
	glScalef(100,100,100);
	scena();
	glPopMatrix();

	glTranslatef(px,py-1.5,pz);
	glRotatef(xkot,1,0,0);
	glRotatef(ykot,0,1,0);
	glRotatef(zkot,0,0,1);
}

void glowna2()
{
	glTranslatef(0,0,tz-7);	
	glRotatef(rx, 1.0, 0.0, 0.0);
	glRotatef(ry, 0.0, 1.0, 0.0);
}

void display(void)
{
	// czyszczenie buforow
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	GLfloat ambiencik[4]={jas_sw,jas_sw,jas_sw,1.0f};
	GLfloat position[4]={10.0f, 10.0f, 100.0f, 0.0f};
	laser();
	glLightfv(GL_LIGHT2, GL_POSITION, position);
	glLightfv(GL_LIGHT2, GL_AMBIENT, ambiencik);
	
	
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	glEnable(GL_LIGHTING);

	
	// flagi czynnosci pomocniczych

    glEnable( GL_DEPTH_TEST );
    
	//glEnable(GL_CULL_FACE);
	glEnable(GL_COLOR_MATERIAL);

	//auxInitDisplayMode(AUX_SINGLE|AUX_RGBA);
	
	// transformacja obserwacji
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

	glPushMatrix();
		glPushMatrix();
			if(u%2==0)
			{
				
				glPushMatrix();
				for(j=0; j<=xb; j+=(xb/50))
				{
					glPushMatrix();

						glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
				
						glowna2();

						k=(a*j*j)+(b*j)+c;
						GLfloat p=(2*a*j)+b;
						GLfloat poch=atan(p)*180/PI;
				
						glowna();

						glPushMatrix();
							glTranslatef(j-6,k+1.0,-1);
							glRotatef(270+poch,0,0,1);
							rakieta();
						
							Sleep(5);
							glutSwapBuffers();
						glPopMatrix();

					u++;
					glPopMatrix();
				}
				glPopMatrix();
			}
			else
			{
				glowna2();
				
				glowna();
				
				glPushMatrix();
				glTranslatef(-6.0,1.0,-1);
				rakieta();
				glPopMatrix();
			}
		glPopMatrix();

	glPopMatrix();
		Sleep(5);
		glutSwapBuffers();
}

void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1.0, 1000.0);
   glMatrixMode (GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y)
{
   switch (key) {
      case 27:
         exit(0);
         break;
	  case 'x':         
		  xkot+=5;
		  if (xkot>360) xkot=0;
         glutPostRedisplay();
         break;
	 case 'z':         
		 xkot-=5;
		 if (xkot>360) xkot=0;
         glutPostRedisplay();
         break;
	case 'c':         
		  ykot+=5;
		  if (ykot>360) ykot=0;
         glutPostRedisplay();
         break;
	 case 'v':         
		 ykot-=5;
		 if (ykot>360) ykot=0;
         glutPostRedisplay();
         break;
	 case 'b':         
		zkot -=5;
		 if (zkot>360) zkot=0;
         glutPostRedisplay();
         break;
	 case 'n':         
		 zkot+=5;
		 if (zkot>360) zkot=0;
         glutPostRedisplay();
         break;
	 case 'a':
		 px-=0.25;
		 if(px<-10.0)  px=-2.5;
		 glutPostRedisplay();
		 break;
	 case 's':
		 px+=0.25;
		 if(px>10.0)  px=0;
		 glutPostRedisplay();
		 break;
	 case 'd':
		 py-=0.25;
		 if(py<0)  py=0;
		 glutPostRedisplay();
		 break;
	 case 'f':
		 py+=0.25;
		 glutPostRedisplay();
		 break;
	 case 'g':
		 pz-=0.25;
		 glutPostRedisplay();
		 break;
	 case 'h':
		 pz+=0.25;
		 glutPostRedisplay();
		 break;
	 case 32:
		 u++;
		 glutPostRedisplay();
		 break;
	case '1':         
		 xa+=0.1;
         glutPostRedisplay();
         break;
	case '2':         
		 xa-=0.1;
         glutPostRedisplay();
         break;
	case '3':         
		 xb+=0.1;
         glutPostRedisplay();
         break;
	case '4':         
		 xb-=0.1;
         glutPostRedisplay();
         break;
	case '5':         
		 xm+=0.1;
         glutPostRedisplay();
         break;
	case '6':         
		 xm-=0.1;
         glutPostRedisplay();
         break;
	case '7':         
		 ym+=0.1;
         glutPostRedisplay();
         break;
	case '8':         
		 ym-=0.1;
         glutPostRedisplay();
         break;
	case '9':         
		 jas_sw+=0.1;
         glutPostRedisplay();
         break;
	case '0':         
		 jas_sw-=0.1;
         glutPostRedisplay();
         break;
	case 'q':         
		 ry+=0.5;
         glutPostRedisplay();
         break;
	case 'w':         
		 ry-=0.5;
         glutPostRedisplay();
         break;
	case 'e':         
		 rx+=0.5;
         glutPostRedisplay();
         break;
	case 'r':         
		 rx-=0.5;
         glutPostRedisplay();
         break;
	case 't':         
		 tz+=0.1;
         glutPostRedisplay();
         break;
	case 'y':         
		 tz-=0.1;
         glutPostRedisplay();
         break;
   }
}

static void mouse(int button, int state, int x, int y)
{
	xd = x; yd = y;
	if(state == GLUT_DOWN) {
		if(button == GLUT_LEFT_BUTTON) {
			ldown = 1;
		}
		if(button == GLUT_RIGHT_BUTTON) {
			rdown = 1;
		}
	} else if(state == GLUT_UP) {				
		if(button == GLUT_LEFT_BUTTON) {
			ldown = 0;
		}
		if(button == GLUT_RIGHT_BUTTON) {
			rdown = 0;
		}
	}
}
static void motion(int x, int y)
{
	if(ldown) {
		ry += (x - xd);
		rx += (y - yd);
		if(rx + (y - yd)>90) rx=90;
		if(rx + (y - yd)<0) rx=0;
	}
	if(rdown) {
		tz += (y - yd);
	}

	xd = x;
	yd = y;
	glutPostRedisplay();
}


int main(int argc, char** argv)
{
   int wys=1000;
   int szer=500;
   ldown=rdown=0;

   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
   glutInitWindowSize (wys, szer);
   glutInitWindowPosition (0, 0);
   glutCreateWindow (argv[0]);
   init ();
   glutDisplayFunc(display); 
   glutKeyboardFunc(keyboard);
   glutMouseFunc(mouse);
   glutMotionFunc(motion);
   glutReshapeFunc(reshape);
   glutMainLoop();
   return 0;
}
