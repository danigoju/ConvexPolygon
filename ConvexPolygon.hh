#include <vector>

#ifndef ConvexPolygon_hh
#define ConvexPolygon_hh

#include "Point.hh"
using namespace std;

class ConvexPolygon {

    public:
        /** Constructor buit */
        ConvexPolygon();

        /** Constructor. */
        ConvexPolygon(const vector<Point>& Vertex);

        /** Retorna el polígon convex més petit que conté a l'interior tots el punts donats */
        ConvexPolygon convexHull(const vector<Point>& Punts) const;

        /** Retorna el polígon que resulta de la intersecció dels dos polígons */
        ConvexPolygon intersection(ConvexPolygon& Pol);

        /** Retorna el polígon convex més petit que conté a l'interior el conjunt de polígons  */
        ConvexPolygon boundingBox(vector<ConvexPolygon>& Poligons) const;

        /** Retorna el polígon convex més petit que conté els dos polígons */
        ConvexPolygon convexUnion(ConvexPolygon& Pol) const;

        /** Retorna si el polígon objecte és dins el polígon pasat com a paràmetre o no ho està */
        bool inside(ConvexPolygon& Pol) const;

        /** Retorna el número d'arestes del poligon convex */
        int num_edges() const;

        /** Retorna el preímetre del poligon convex */
        double perimeter() const;

        /** Retorna l'àrea del poligon convex */
        double area() ;

        /** Retorna si el poligon convex és regular o no */
        bool is_regular() const;

        /** Retorna el centroide del poligon convex */
        Point centroid() const;

        /** Retorna una referència al punt de l'index especificat */
        Point& operator[](const int& i);

    private:

    /** Vertexs del polígon convex. No estan ordenats de cap manera.  */
    vector<Point> Poligon;

};


#endif
