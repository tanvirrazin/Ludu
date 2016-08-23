
#include<windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <stdio.h>

static GLfloat spin = 0;
static GLfloat l = 0;
static GLfloat r = 0;
static GLfloat t= 0;
static GLfloat b = 0;
static int c = 0;
static int now_P = -1;
static int chhokka = 0;
static boolean game_end = false;

class person{
public:
    int cur_sec;
    int cur_g;
    int sv_g;
    boolean start;
    int ghor_count;
};

class ghor{
public:
    float L;
    float R;
    float T;
    float B;
    int C;
    int def_C;

    /*ghor(float l, float r, float t, float b, int c){
        L = l;
        R = r;
        T = t;
        B = b;
        C = c;
    }*/


    void draw(){
        if(C == 0)
            glColor3f(1.0, 0.0, 0.0);
        else if(C == 1)
            glColor3f(0.0, 1.0, 0.0);
        else if(C == 2)
            glColor3f(0.0, 0.0, 1.0);
        else if(C == 3)
            glColor3f(1.0, 1.0, 0.0);
        else if(C == 4)
            glColor3f(0.411765, 0.411765, 0.411765);
        else
            glColor3f(1.0, 1.0, 1.0);

        glBegin(GL_POLYGON);
            glVertex2f(L,B);
            glVertex2f(R,B);
            glVertex2f(R,T);
            glVertex2f(L,T);
        glEnd();
    }
};


ghor g[4][13];
ghor safe_g[4][5];
person P[4];


void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    glPushMatrix();
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_POLYGON);
        glVertex2f(14.5,14.5);
        glVertex2f(-14.5,14.5);
        glVertex2f(0,0);
    glEnd();
    glBegin(GL_POLYGON);
        glVertex2f(15,15);
        glVertex2f(75,15);
        glVertex2f(75,75);
        glVertex2f(15,75);
    glEnd();



    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
        glVertex2f(-14.5,14.5);
        glVertex2f(-14.5,-14.5);
        glVertex2f(0,0);
    glEnd();
    glBegin(GL_POLYGON);
        glVertex2f(-15,15);
        glVertex2f(-15,75);
        glVertex2f(-75,75);
        glVertex2f(-75,15);
    glEnd();



    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
        glVertex2f(-14.5,-14.5);
        glVertex2f(14.5,-14.5);
        glVertex2f(0,0);
    glEnd();
    glBegin(GL_POLYGON);
        glVertex2f(-15,-15);
        glVertex2f(-75,-15);
        glVertex2f(-75,-75);
        glVertex2f(-15,-75);
    glEnd();



    glColor3f(1.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
        glVertex2f(14.5,-14.5);
        glVertex2f(15,15);
        glVertex2f(0,0);
    glEnd();
    glBegin(GL_POLYGON);
        glVertex2f(15,-15);
        glVertex2f(15,-75);
        glVertex2f(75,-75);
        glVertex2f(75,-15);
    glEnd();
    glPopMatrix();




        for(int j=0;j<4;j++){
            glPushMatrix();
            glRotatef(-j*90, 0.0, 0.0, 1.0);
            for(int i=0;i<13;i++)
                g[j][i].draw();
            for(int i=0;i<5;i++)
                safe_g[j][i].draw();
            glPopMatrix();
        }



    glFlush();
}



void init(void)
{
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glOrtho(-75.0, 75.0, -75.0, 75.0, -1.0, 1.0);

    for(int j=0;j<4;j++){
        l = -14.5;
        r = -5;
        t = -55;
        b = -64.5;

        int i =0;
        for(i=0;i<5;i++){
            g[j][i].L = l;
            g[j][i].R = r;
            g[j][i].B = b;
            g[j][i].T = t;
            g[j][i].C = 5;
            g[j][i].def_C = 5;

            safe_g[j][i].L = l+10;
            safe_g[j][i].R = r+10;
            safe_g[j][i].B = b;
            safe_g[j][i].T = t;
            safe_g[j][i].C = j;
            safe_g[j][i].def_C = j;
            t+=10;
            b+=10;

        }
        l-=10;
        r-=10;

        for(;i<11;i++){
            g[j][i].L = l;
            g[j][i].R = r;
            g[j][i].B = b;
            g[j][i].T = t;
            g[j][i].C = 5;
            g[j][i].def_C = 5;
            l-=10;
            r-=10;

        }
        l+=10;
        r+=10;
        t+=10;
        b+=10;
        for(;i<13;i++){
            g[j][i].L = l;
            g[j][i].R = r;
            g[j][i].B = b;
            g[j][i].T = t;
            g[j][i].C = 5;
            g[j][i].def_C = 5;
            t+=10;
            b+=10;

        }
        g[j][0].def_C = j;
        g[j][0].C = j;
    }

    for(int i=0;i<4;i++){
        P[i].cur_sec = i;
        P[i].cur_g = 0;
        P[i].sv_g = 0;
        P[i].start = false;
        P[i].ghor_count = 0;

    }
}


void spe_key(int key, int x, int y)
{

	switch ((char)key) {


        case GLUT_KEY_F1:
            if(game_end == false){
                now_P++;
                if(now_P > 3)
                    now_P = 0;
                chhokka = (rand() % 6)+1;
                printf("chaal hoilo ... %d\n\n",chhokka);
                g[P[now_P].cur_sec][P[now_P].cur_g].C = g[P[now_P].cur_sec][P[now_P].cur_g].def_C;
                //safe_g[P[now_P].cur_sec][P[now_P].cur_g].C = safe_g[P[now_P].cur_sec][P[now_P].cur_g].def_C;

                P[now_P].ghor_count += chhokka;
                if(P[now_P].ghor_count <51){
                    P[now_P].cur_g += chhokka;
                    if(P[now_P].cur_g >=13){
                        P[now_P].cur_g -= 13;
                        P[now_P].cur_sec += 1;
                        if(P[now_P].cur_sec > 3)
                            P[now_P].cur_sec = 0;
                    }

                    g[P[now_P].cur_sec][P[now_P].cur_g].C = now_P;
                } else {
                    safe_g[now_P][P[now_P].sv_g].C = safe_g[now_P][P[now_P].sv_g].def_C;
                    if(P[now_P].ghor_count<56){
                        P[now_P].sv_g = P[now_P].ghor_count - 51;
                        safe_g[now_P][P[now_P].sv_g].C = 4;
                    } else {
                        printf("\n\n\n%d won\n\n\n",now_P+1);
                        game_end = true;
                    }

                }
                if(!game_end)
                    printf("Now chance of player: ...%d...\n",(now_P+2)<5 ? (now_P+2) : 1);
                glutPostRedisplay();
            }
			break;




	  default:
			break;
	}
}


/*
 *
 *  Register mouse input callback functions
 */


int main()
{
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize (700, 700);
	glutInitWindowPosition (100, 100);
	glutCreateWindow ("Ludu");
	init();
	glutDisplayFunc(display);

	glutSpecialFunc(spe_key);
	printf("Now chance of player: ...1...\n");

	glutMainLoop();
	return 0;   /* ANSI C requires main to return int. */
}

