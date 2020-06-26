#include "rect.h"
#include <GLUT/GLUT.h>

Rect::Rect(vec2 const& _Position,vec2 const& _size):m_position(_Position),m_size(_size){
    
}

void Rect::draw(){
    glRectf(m_position.x,
            m_position.y,
            m_position.x+m_size.x,
            m_position.y+m_size.y);
}
