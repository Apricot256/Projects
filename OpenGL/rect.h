#ifndef rect_hpp
#define rect_hpp

#include <glm/glm.hpp>

using namespace glm;

struct Rect{
    vec2 m_position;
    vec2 m_size;
    void draw();
    Rect(vec2 const& _Position,vec2 const& _size);
    bool intersect(vec2 const& _point);
    bool intersect(Rect const& _Rect);
};

#endif /* rect_hpp */
