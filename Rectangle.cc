#include "Rectangle.hh"

#include <cassert>
using namespace std;


/** Constructor. */
Rectangle::Rectangle (double w, double h, const Point& p)
:   p(p),
    w(w),
    h(h)
{
    assert(w >= 0);
    assert(h >= 0);
}


/** Gets the LL (lower-left) point of this rectangle. */
Point Rectangle::get_LL () const {
    return p;
}


/** Gets the UR (upper-right) point of this rectangle. */
Point Rectangle::get_UR () const {
    return Point(p.get_x() + w, p.get_y() + h);
}


/** Gets the area of this rectangle. */
double Rectangle::area () const {
    return w * h;
}


/** Gets the width of this rectangle. */
double Rectangle::width () const {
    return w;
}


/** Gets the height of this rectangle. */
double Rectangle::height () const {
    return h;
}


double Rectangle::area () const{
    return w*h;
}

    /** Scales this rectangle with a factor s >= 0. */
void Rectangle::scale (double s){
    w = w*s;
    h = h*s;
}

    /** Moves the LL of this rectangle to some point p. */
void Rectangle::move_to (const Point& p2){
    p = p2;
}

    /** Compares this rectangle to rectangle r. */
bool Rectangle::operator== (const Rectangle& r) const{
    return w == r.w and h==r.h and p == r.p;
}

    /** Compares this rectangle to rectangle r. */
bool Rectangle::operator!= (const Rectangle& r) const{
    return not operator==(r);
}

    /** Intersects this rectangle with another rectangle. */
Rectangle& Rectangle::operator*= (const Rectangle& r){

}

    /** Returns the intersection of this rectangle with another rectangle. */
Rectangle Rectangle::operator* (const Rectangle& r) const{

}

    /** Rotates this rectangle 90 degrees clockwise or counterclockwise around its LL point. */
void Rectangle::rotate (bool clockwise=true){
    if(clockwise){
        p.y = p.y + (-w);
        int ww = w;
        w = h;
        h = ww;
    }else{
        p.x = p.x + (-h);
        int ww = w;
        w = h;
        h = ww;
    }
}

    /** Horizontally flips this rectangle around its LL point.*/
void Rectangle::flip_hor (){
    p.x = p.x + (-w);
}

    /** Vertically flips this rectangle around its LL point.*/
void Rectangle::flip_ver (){
    p.y = p.y + (-h);
}

    /** Check whether point p is contained in this rectangle. */
bool Rectangle::contains (const Point& p1) const{
    return p1.x - p.x >= 0 and p1.x - p.x <= w and p1.y - p.y >= 0 and p1.y - p.y <= h;
}

    /** Check whether rectangle r is fully contained in this rectangle. */
bool Rectangle::contains (const Rectangle& r) const{
    return r.p.x >= p.x and r.p.y >= p.y and r.p.x + r.w <= p.x + w and r.p.y + r.h <= p.y + h;
}



// ***********************************************************
// Implement the rest of the Rectangle methods by yourself !!!
// ***********************************************************


