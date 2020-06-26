#include <iostream>
#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h> 
#include <glm/glm.hpp>
#include "font.h"
#include "rect.h"

using namespace std;
using namespace glm;

ivec2 WindowSize=ivec2(800,600);

bool keys[256];

Rect rect(vec2(50,50),vec2(50,50));

void Display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, WindowSize.x, WindowSize.y, 0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    rect.draw();
    
    fontBegin();
    fontSetSize(FONT_DEFAULT_SIZE/4);
    fontSetColor(0, 0xff, 0xff);
    fontSetPosition(0, WindowSize.y-fontGetSize()*2);
    fontDraw("min:%f,max:%f",fontGetWightMin(),fontGetWightMax());
    fontEnd();
    
    glutSwapBuffers();
}

void Idle(){
    float f=5;
    if(keys['w'])rect.m_position.y-=f;
    if(keys['a'])rect.m_position.x-=f;
    if(keys['s'])rect.m_position.y+=f;
    if(keys['d'])rect.m_position.x+=f;
    glutPostRedisplay();
}

void Timer(int value){
    glutPostRedisplay();
    glutTimerFunc(1000/60, Timer, 0);
}

void Reshape(int Width,int Height){
    //cout<<"Width:"<<Width<<"  Height:"<<Height<<endl;
    glViewport(0 , 0, Width, Height);
    WindowSize=ivec2(Width,Height);
}

void Keyboad(unsigned char key,int a,int b){
    if(key==0x1b)exit(0);
    keys[key]=true;
    //printf("KeyDown:%c(%#x)\n",key,key);
}

void Keyboadup(unsigned char key,int a,int b){
    //printf("KeyUp:%c(%#x)\n",key,key);
    keys[key]=false;
}

int main(int argc,char *argv[]){
    glutInit(&argc,argv);
    glutInitDisplayMode(GL_DOUBLE);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(WindowSize.x,WindowSize.y);
    glutCreateWindow("OpenGL");
    glutDisplayFunc(Display);
    glutIdleFunc(Idle);
    glutReshapeFunc(Reshape);
    glutKeyboardFunc(Keyboad);
    glutKeyboardUpFunc(Keyboadup);
    glutIgnoreKeyRepeat(GL_TRUE);
    glutTimerFunc(0, Timer, 0);
    glutMainLoop();
}
