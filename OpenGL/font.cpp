#include "font.h"
#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>
#include <glm/glm.hpp>
#include <stdio.h>
#include <stdarg.h>

using namespace glm;

static vec2 position;
static float size=FONT_DEFAULT_SIZE;
static unsigned char color[3];  //R,G,B
static float weight=1;

void fontBegin(){
    glPushMatrix();
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLint vewport[4];
    glGetIntegerv( GL_VIEWPORT, vewport);
    gluOrtho2D(0, vewport[2], vewport[3], 0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    
}

void fontEnd(){
    glPopMatrix();
    glPopAttrib();
}

void fontSetPosition(float _x,float _y){
    position=vec2(_x,_y);
    
}

void fontSetSize(float _size){
    size=_size;
}

float fontGetSize(){
    return size;
}

float fontGetWightMin(){
    GLfloat Wight[2];
    glGetFloatv(
        GL_LINE_WIDTH_RANGE,
        Wight
    );
    return Wight[0];
}

float fontGetWightMax(){
        GLfloat Wight[2];
    glGetFloatv(
        GL_LINE_WIDTH_RANGE,
        Wight
    );
    return Wight[1];
}

void fontSetWeight(float _weight){
    weight=_weight;
}

void fontSetColor(unsigned char _red,unsigned char _green,unsigned char _blue){
    color[0]=_red;
    color[1]=_green;
    color[2]=_blue;
}

void fontDraw(const char* _format,...){
    va_list argList;
    va_start(argList,_format);
    char str[256];
    vsprintf(str, _format, argList);
    va_end(argList);
    glColor3ub(color[0], color[1], color[2]);
    glPushMatrix();
    glTranslatef(position.x, position.y+size+1, 0);
    float s=size/FONT_DEFAULT_SIZE;
    glScaled(s, -s, s);
    
    for(char *p=str;*p!='\0';p++){
        glutStrokeCharacter(GLUT_STROKE_ROMAN, *p);
    }
    printf("%s\n",str);
}
