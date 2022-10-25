// INIT
#pragma once

#define WIDTH 800
#define HEIGHT 600

#define DUONG_THANG 10
#define TG_VUONG_CAN 11
#define TG_DEU 12
#define HINH_CHU_NHAT 13
#define HINH_VUONG 14
#define HINH_TRON 15
#define ELIP 16
#define NGU_GIAC_DEU 17
#define LUC_GIAC_DEU 18
#define MUI_TEN 19
#define NGOI_SAO 20
#define CONG 21
#define TRU 22
#define NHAN 23
#define CHIA 24

#define XANH 25
#define DO 26
#define VANG 27

#define CHON_HINH 28


static int window;
static int menu_id;
static int tamgiac_id;
static int tugiac_id;
static int oval_id;
static int dagiacdeu_id;
static int hinhkhac_id;
static int dau_id;
static int tomau_id;
static int value = 0;

typedef struct _RGBColor {
	unsigned char r;
	unsigned char g;
	unsigned char b;
}RGBColor;

void myinit(void)
{
	//glClearColor(1.0, 1.0, 1.0, 0.0);
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	////gluOrtho2D(-300, 500.0, -200, 400.0);
	//gluOrtho2D(0, 500, 0, 500);
}
//INIT

// DRAW_OBJECT.H
#pragma once
#include <GL/glut.h>
#include<iostream>
using namespace std;

void myinit(void);
void setPixel(GLint x, GLint y);

// Các hàm cài đặt để vẽ các hình theo yêu cầu 
void lineDDA(float x1, float y1, float x2, float y2);
void lineBresenham(float x1, float y1, float x2, float y2);
void circleMidPoint(float xt, float yt, float r);
void elipMidPoint(float xt, float yt, float a, float b);

void displayLineDDA();
void displayLineBresenham();
void displayCircleMidPoint();
void displayElipMidPoint();
// Các hàm cài đặt để vẽ các hình theo yêu cầu
// DRAW_OBJECT.H

// DRAW_OBJECT.CPP
#include "DrawObject.h"

void setPixel(GLint x, GLint y)
{
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}

// Các hàm cài đặt để vẽ các hình theo yêu cầu 
void lineDDA(float x1, float y1, float x2, float y2) {
	float dy, dx, step, increaseX, increaseY, x, y;
	dx = x2 - x1;
	dy = y2 - y1;

	if (abs(dx) > abs(dy)) {
		step = abs(dx);
	}
	else {
		step = abs(dy);
	}

	increaseX = dx / step;
	increaseY = dy / step;

	// Bắt đầu tại x1, y1
	x = x1;
	y = y1;
	setPixel(x, y);

	for (int i = 0; i < step; i++) {
		x = x + increaseX;
		y = y + increaseY;
		setPixel(x, y);
	}
	glFlush();
}

void lineBresenham(float x1, float y1, float x2, float y2) {
	// dy = y2 - y1; dx = x2 - x1
	// m = dy / dx
	// step: số lần lặp
	float dy, dx, x, y, xTemp, yTemp;
	dx = abs(x2 - x1);
	dy = abs(y2 - y1);

	xTemp = 1, yTemp = 1;

	x = x1, y = y1;

	if (x2 < x1) xTemp = -1;
	if (y2 < y1) yTemp = -1;
	setPixel(x, y);
	int i = 0;
	if (dx > dy) {
		float p = 2 * dy - dx;
		while (i < dx) {
			if (p >= 0) {
				y += yTemp;
				p += 2 * (dy - dx);
			}
			else {
				p += 2 * dy;
			}
			x += xTemp;
			setPixel(x, y);
			i++;
		}
	}
	else {
		float p = 2 * dx - dy;
		while (i < dy) {
			if (p >= 0) {
				x += xTemp;
				p += 2 * (dx - dy);;
			}
			else {
				p += 2 * dx;
			}
			y += yTemp;
			setPixel(x, y);
			i++;
		}
	}
	glFlush();
}

void circleMidPoint(float xt, float yt, float r) {
	r = (r < 0) ? -r : r;
	float x, y;
	x = 0;
	y = r;
	setPixel(x + xt, y + yt);
	setPixel(x + xt, -y + yt);
	setPixel(y + xt, x + yt);
	setPixel(-y + xt, x + yt);

	float p = 1 - r;

	while (x < y) {

		x++;
		if (p < 0) {
			p = p + 2 * x + 1;
		}
		else {
			y = y - 1;
			p = p + 2 * x + 1 - 2 * y;
		}

		setPixel(x + xt, y + yt);
		setPixel(-x + xt, y + yt);
		setPixel(x + xt, -y + yt);
		setPixel(-x + xt, -y + yt);

		setPixel(y + xt, x + yt);
		setPixel(-y + xt, x + yt);
		setPixel(y + xt, -x + yt);
		setPixel(-y + xt, -x + yt);
	}
	glFlush();
}

void elipMidPoint(float xt, float yt, float a, float b) {
	a = (a < 0) ? -a : a;
	b = (b < 0) ? -b : b;

	float d1, d2, x, y;
	x = 0;
	y = b;

	setPixel(xt + x, yt + y);
	setPixel(xt - x, yt + y);

	d1 = (b * b) - (a * a * b) + (0.25 * a * a);
	while (2 * b * b * x < 2 * a * a * y) {

		if (d1 < 0) {
			x++;
			d1 = d1 + 2 * b * b * x + (b * b);
		}
		else {
			x++;
			y--;
			d1 = d1 + 2 * b * b * x - 2 * a * a * y + (b * b);
		}
		setPixel(xt + x, yt + y);
		setPixel(xt - x, yt + y);
		setPixel(xt + x, yt - y);
		setPixel(xt - x, yt - y);
	}
	glFlush();

	d2 = ((b * b) * ((x + 0.5) * (x + 0.5))) + ((a * a) * ((y - 1) * (y - 1))) - (a * a * b * b);
	while (y >= 0) {
		if (d2 > 0)
		{
			y--;
			d2 = d2 - 2 * a * a * y + (a * a);
		}
		else
		{
			x++;
			y--;
			d2 = d2 + 2 * b * b * x - 2 * a * a * y + (a * a);
		}
		setPixel(xt + x, yt + y);
		setPixel(xt - x, yt + y);
		setPixel(xt + x, yt - y);
		setPixel(xt - x, yt - y);
	}
	glFlush();
}

void displayLineDDA()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	glPointSize(2.0);
	//lineDDA(params[0], params[1], params[2], params[3]);
	lineDDA(50, 50, 200, 203);
	glFlush();
}
void displayLineBresenham()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 1.0, 0.0);
	glPointSize(2.0);
	//lineBresenham(params[0], params[1], params[2], params[3]);
	lineBresenham(50, 50, 200,203);
	glFlush();
}
void displayCircleMidPoint()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.3, 0.7, 1.0);
	glPointSize(2.0);
	//circleMidPoint(params[0], params[1], params[2]);
	circleMidPoint(200,200,100);
	glFlush();
}
void displayElipMidPoint()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.2, 0.4);
	glPointSize(2.0);
	//elipMidPoint(params[0], params[1], params[2], params[3]);
	elipMidPoint(50,50,120,180);
	glFlush();
}
// Các hàm cài đặt để vẽ các hình theo yêu cầu
// DRAW_OBJECT.CPP

// MAIN.CPP
#include <windows.h>
#include <GL/glut.h> 
#include <iostream>
#include "init.h"
#include "DrawObject.h"
using namespace std;

void menu(int num) {
    if (num == 0) {
        glutDestroyWindow(window);
        exit(0);
    }
    else {
        value = num;
    }
    glutPostRedisplay();
}
void createMenu(void) {
    tamgiac_id = glutCreateMenu(menu);
    glutAddMenuEntry("Vuong can", TG_VUONG_CAN);
    glutAddMenuEntry("Deu", TG_DEU);

    tugiac_id = glutCreateMenu(menu);
    glutAddMenuEntry("Hinh chu nhat", HINH_CHU_NHAT);
    glutAddMenuEntry("Hinh vuong", HINH_VUONG);

    oval_id = glutCreateMenu(menu);
    glutAddMenuEntry("Hinh tron", HINH_TRON);
    glutAddMenuEntry("Elip", ELIP);

    dagiacdeu_id = glutCreateMenu(menu);
    glutAddMenuEntry("Ngu giac deu", NGU_GIAC_DEU);
    glutAddMenuEntry("Luc giac deu", LUC_GIAC_DEU);


    hinhkhac_id = glutCreateMenu(menu);
    glutAddMenuEntry("Mui ten", MUI_TEN);
    glutAddMenuEntry("Ngoi sao", NGOI_SAO);

    dau_id = glutCreateMenu(menu);
    glutAddMenuEntry("Cong", CONG);
    glutAddMenuEntry("Tru", TRU);
    glutAddMenuEntry("Nhan", NHAN);
    glutAddMenuEntry("Chia", CHIA);

    tomau_id = glutCreateMenu(menu);
    glutAddMenuEntry("Xanh", XANH);
    glutAddMenuEntry("Do", DO);
    glutAddMenuEntry("Vang", VANG);

    menu_id = glutCreateMenu(menu);
    glutAddMenuEntry("Clear", 1);
    glutAddMenuEntry("Duong thang", 10);
    glutAddSubMenu("Tam giac", tamgiac_id);
    glutAddSubMenu("Tu giac", tugiac_id);
    glutAddSubMenu("Oval", oval_id);
    glutAddSubMenu("Da giac deu", dagiacdeu_id);
    glutAddSubMenu("Hinh khac", hinhkhac_id);
    glutAddSubMenu("Dau", dau_id);
    glutAddSubMenu("To mau", tomau_id);
    glutAddMenuEntry("Chon hinh", CHON_HINH);
    glutAddMenuEntry("Quit", 0);     
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}
void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);   
    if (value == 1) {
        //glutPostRedisplay();
        return; 
    }
    else if (value == DUONG_THANG) {
        glPushMatrix();
        glColor3d(1.0, 0.0, 0.0);
        glutWireSphere(0.5, 50, 50);
        glPopMatrix();
    }
    else if (value == TG_VUONG_CAN) {
        glPushMatrix();
        glColor3d(0.0, 1.0, 0.0);
        glRotated(65, -1.0, 0.0, 0.0);
        glutWireCone(0.5, 1.0, 50, 50);
        glPopMatrix();
    }
    else if (value == TG_DEU) {
        glPushMatrix();
        glColor3d(0.0, 0.0, 1.0);
        glutWireTorus(0.3, 0.6, 100, 100);
        glPopMatrix();
    }
    else if (value == HINH_CHU_NHAT) {
        glPushMatrix();
        glColor3d(1.0, 0.0, 1.0);
        glutSolidTeapot(0.5);
        glPopMatrix();
    }
    else if (value == HINH_VUONG) {
        glPushMatrix();
        glColor3d(1.0, 0.0, 0.0);
        glutWireSphere(0.5, 50, 50);
        glPopMatrix();
    }
    else if (value == HINH_TRON) {
        glPushMatrix();
        glColor3d(1.0, 0.0, 0.0);
        float xt = 100, yt = 100, r = 0.5;
        r = (r < 0) ? -r : r;
        float x, y;
        x = 0;
        y = r;
        setPixel(x + xt, y + yt);
        setPixel(x + xt, -y + yt);
        setPixel(y + xt, x + yt);
        setPixel(-y + xt, x + yt);

        float p = 1 - r;

        while (x < y) {

            x++;
            if (p < 0) {
                p = p + 2 * x + 1;
            }
            else {
                y = y - 1;
                p = p + 2 * x + 1 - 2 * y;
            }

            setPixel(x + xt, y + yt);
            setPixel(-x + xt, y + yt);
            setPixel(x + xt, -y + yt);
            setPixel(-x + xt, -y + yt);

            setPixel(y + xt, x + yt);
            setPixel(-y + xt, x + yt);
            setPixel(y + xt, -x + yt);
            setPixel(-y + xt, -x + yt);
        }
        glPopMatrix();
    }
    else if (value == ELIP) {
        glPushMatrix();
        glColor3d(0.0, 0.0, 1.0);
        glutWireTorus(0.3, 0.6, 100, 100);
        glPopMatrix();
    }
    else if (value == NGU_GIAC_DEU) {
        glPushMatrix();
        glColor3d(1.0, 0.0, 1.0);
        glutSolidTeapot(0.5);
        glPopMatrix();
    }
    else if (value == LUC_GIAC_DEU) {
        glPushMatrix();
        glColor3d(0.0, 0.0, 1.0);
        glutWireTorus(0.3, 0.6, 100, 100);
        glPopMatrix();
    }
    else if (value == MUI_TEN) {
        glPushMatrix();
        glColor3d(1.0, 0.0, 1.0);
        glutSolidTeapot(0.5);
        glPopMatrix();
    }
    else if (value == NGOI_SAO) {
        glPushMatrix();
        glColor3d(1.0, 0.0, 0.0);
        glutWireSphere(0.5, 50, 50);
        glPopMatrix();
    }
    else if (value == CONG) {
        glPushMatrix();
        glColor3d(0.0, 1.0, 0.0);
        glRotated(65, -1.0, 0.0, 0.0);
        glutWireCone(0.5, 1.0, 50, 50);
        glPopMatrix();
    }
    else if (value == TRU) {
        glPushMatrix();
        glColor3d(0.0, 0.0, 1.0);
        glutWireTorus(0.3, 0.6, 100, 100);
        glPopMatrix();
    }
    else if (value == NHAN) {
        glPushMatrix();
        glColor3d(1.0, 0.0, 1.0);
        glutSolidTeapot(0.5);
        glPopMatrix();
    }
    else if (value == CHIA) {
        glPushMatrix();
        glColor3d(1.0, 0.0, 1.0);
        glutSolidTeapot(0.5);
        glPopMatrix();
    }
    glFlush();
}


void BoundaryFill(int x, int y, RGBColor F_Color, RGBColor B_Color);
bool IsSameColor(RGBColor currentColor, RGBColor otherColor);
RGBColor GetPixel(int x, int y);
void PutPixel(int x, int y, RGBColor color);
void XuLyMouse(int button, int state, int x, int y);

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    window = glutCreateWindow("Paint");
    createMenu();     
    myinit();
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glutDisplayFunc(display);
    glutMouseFunc(XuLyMouse);
    glutMainLoop();
    return EXIT_SUCCESS;
}

void BoundaryFill(int x, int y, RGBColor F_Color, RGBColor B_Color) {
    RGBColor currentColor;
    currentColor = GetPixel(x, y);

    if (!IsSameColor(currentColor, B_Color) && !IsSameColor(currentColor, F_Color)) {
        PutPixel(x, y, F_Color);
        BoundaryFill(x - 1, y, F_Color, B_Color);
        BoundaryFill(x, y + 1, F_Color, B_Color);
        BoundaryFill(x + 1, y, F_Color, B_Color);
        BoundaryFill(x, y - 1, F_Color, B_Color);
    }
}
bool IsSameColor(RGBColor a, RGBColor b) {
    if (a.r == b.r && a.g == b.g && a.b == b.b) {
        return true;
    }
    return false;
}
RGBColor GetPixel(int x, int y) {
    cout << "Pos " << x << " " << y << endl;
    unsigned char* ptr = new unsigned char[3];

    glReadPixels(x, y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, ptr);


    for (int i = 0; i < 3; i++) {
        cout << int(ptr[i]) << " ";
    }

    RGBColor color;
    color.r = ptr[0];
    color.g = ptr[1];
    color.b = ptr[2];

    return color;
}
void PutPixel(int x, int y, RGBColor color) {
    unsigned char* ptr = new unsigned char[3];
    ptr[0] = color.r;
    ptr[1] = color.g;
    ptr[2] = color.b;

    glRasterPos2i(x, y);
    glDrawPixels(1, 1, GL_RGB, GL_UNSIGNED_BYTE, ptr);
    
    glFlush();
}
void XuLyMouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        RGBColor B_Color = GetPixel(x, y);
        RGBColor F_Color = GetPixel(150, 50);
        cout << "Get color: ";
        cout << B_Color.r << B_Color.g << B_Color.b << endl;
        cout << "Get color: ";
        cout << F_Color.r << F_Color.g << F_Color.b << endl;
        //BoundaryFill(x, y, F_color, B_Color);
    }
}
// MAIN.CPP
