#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include "ConvexPolygon.hh"
#include "Point.hh"
#include <cmath>
#include <cassert>
using namespace std;

/** Constructor buit*/
ConvexPolygon::ConvexPolygon(){
    vector<Point> buit;
    Poligon = buit;
}

/** Constructor */
ConvexPolygon::ConvexPolygon(const vector<Point>& Vertexs){
  Poligon = Vertexs;
}


// retorna cert si p3 és a l'esquerra del segment (p1,p2)
bool leftof(const Point& p1,const Point& p2,const Point& p3) {
return ((p2.get_x() - p1.get_x()) * (p3.get_y() - p1.get_y())) > ((p2.get_y() - p1.get_y()) * (p3.get_x() - p1.get_x()));
}

/** Donat un vector de punts, retorna un poligon convex que inclou tots els
    demés punts a l'interior. Dut a terme mitjançant el Gift Wrapping algorithm.
    + info: https://en.wikipedia.org/wiki/Gift_wrapping_algorithm */
ConvexPolygon ConvexPolygon::convexHull(const vector<Point>& Punts) const{
    int n = Punts.size();
    vector<Point> hull;
    // Agafa el punt més a l'esquerra
    int left = 0;
    for (int i = 1; i < n; i++){
        if (Punts[i].get_x() < Punts[left].get_x()) left = i;
    }
    int p = left;
    do {
        hull.push_back(Punts[p]);
        int q = (p + 1)%n; // Agafem un punt diferent que p
        for (int i = 0; i < n; i++){
            if (leftof(Punts[p], Punts[q], Punts[i])) q = i;
        }
        p = q; // Punt més a l'esquerra pel convex hull
    } while (p != left); // Mentre el poligon no estigui tancat
    ConvexPolygon Convex_Hull = hull;
    return Convex_Hull;
}


//*****************************************************************************
/** Retorna si el punt p és dins el poligon convex Pol. Aquest és una traducció
    de Python a C++  del següent algorisme:
    https://algorithmtutor.com/Computational-Geometry/Check-if-a-point-is-inside-a-polygon/
    A més, en aquest link es pot trobar la prova de correctessa matemàtica de
    l'algorisme
    Prec: El poligon ha de ser convex */
bool point_inside(const Point& p, ConvexPolygon& Pol){
    vector<double> A;
    vector<double> B;
    vector<double> C;
    int sizePol = Pol.num_edges();
    for(int i = 0; i < sizePol; ++i){
        Point p1 = Pol[i];
        Point p2 = Pol[(i+1)% sizePol];

        //Calculem a, b i c
        double a = -(p2.get_y() - p1.get_y());
        double b = p2.get_x() - p1.get_x();
        double c = -(a * p1.get_x() + b * p1.get_y());

        A.push_back(a);
        B.push_back(b);
        C.push_back(c);
    }
    vector<double> D;
    int sizeA = A.size();
    for(int i = 0; i < sizeA; ++i){
        double d = A[i] * p.get_x() + B[i] * p.get_y() + C[i];
        D.push_back(d);
    }
    bool t1 = true;
    for(double d : D){
        if(d < 0) t1 = false;
    }
    bool t2 = true;
    for(double d : D){
        if(d > 0) t2 = false;
    }
    // si tots son mes grans que 0 o tots son mes petits que 0, és a dins
    return t1 or t2;
}



 /** Com els dos poligons són convexos, és suficient amb comprovar que
     tots els vértexs de l'objecte són dins del polígon paràmetre.*/
bool ConvexPolygon::inside(ConvexPolygon& Pol) const{
    int size = Poligon.size();
    for(int i = 0; i < size; ++i){
        // si algun dels  punts no és a l'interior, retorna fals
        if(not (point_inside(Poligon[i],Pol))) return false;
    }
    return true;
}


//***************************************************************
/** Retorna el punt de la intersecció entre els segment /PQ i /Pol_1,Pol_2 en el
    cas que existeixi, i en cas que no, canvia el booleà found a fals.
    La lògica per trobar la intersecció està extreta de:
            http://www.wyrmtale.com/blog/2013/115/2d-line-intersection-in-c*/
Point GetIntersectionPoint(Point& P, Point& Q, Point& Pol_1, Point& Pol_2, bool& found){
    double A1 = Q.get_y() - P.get_y();
   double B1 = P.get_x() - Q.get_x();
   double C1 = A1 * P.get_x() + B1 * P.get_y();

   double A2 = Pol_2.get_y() - Pol_1.get_y();
   double B2 = Pol_1.get_x() - Pol_2.get_x();
   double C2 = A2 * Pol_1.get_x() + B2 * Pol_1.get_y();


   double det = A1 * B2 - A2 * B1;
   if (det < 0.000000000001)
   {
       // son linies paral·leles
       found = false;
       return Point(0,0);
   }
   else // no son paralleles
   {
       double x = (B2 * C1 - B1 * C2) / det;
       double y = (A1 * C2 - A2 * C1) / det;
       bool online1 = (((min(P.get_x(), Q.get_x()) < x)  or (min(P.get_x(), Q.get_x()) == x))
           and ((max(P.get_x(), Q.get_x()) > x) or (max(P.get_x(), Q.get_x()) ==  x))
           and ((min(P.get_y(), Q.get_y()) < y) or (min(P.get_y(), Q.get_y()) == y))
           and ((max(P.get_y(), Q.get_y()) > y) or (max(P.get_y(), Q.get_y()) == y))
           );
       bool online2 = (((min(Pol_1.get_x(), Pol_2.get_x()) < x)  or (min(Pol_1.get_x(), Pol_2.get_x()) == x))
           and ((max(Pol_1.get_x(), Pol_2.get_x()) > x) or (max(Pol_1.get_x(), Pol_2.get_x()) ==  x))
           and ((min(Pol_1.get_y(), Pol_2.get_y()) < y) or (min(Pol_1.get_y(), Pol_2.get_y()) == y))
           and ((max(Pol_1.get_y(), Pol_2.get_y()) > y) or (max(Pol_1.get_y(), Pol_2.get_y()) == y))
           );

       if (online1 and online2)
           return Point(x,y);
   }
   // la interseccio és fora del segment, llavors marquem com que no l'hem trobat
   // i obligatoriament retornem un punt qualsevol, el qual serà ignorat.
   found = false;
   return Point(0,0);

}


/** Rep dos punts P i Q i troba els punts d'intersecció entre el segment que formen
    i el poligon Pol */
vector<Point> GetIntersectionPoints(Point& P , Point& Q, ConvexPolygon& Pol){
    vector<Point> intersectionPoints;
    int size = Pol.num_edges();
    for (int i = 0; i < size; ++i){
        int next = (i + 1 == size) ? 0 : i + 1;
        bool found = true;
        Point ip = GetIntersectionPoint(P, Q, Pol[i], Pol[next], found);
        // si l'hem trobat, l'afegim, sinò no fem res
        if(found) intersectionPoints.push_back(ip);
    }
    return intersectionPoints;
}

/** Si el punt p no era un dels vertexs, l'afegeix */
void add_points(vector<Point>& Vertexs, vector<Point>& inter_points){
    for(Point& p : inter_points){
        bool found = false;
        int size = Vertexs.size();
        for(int i = 0; i < size and found == false; ++i){
            if(p.get_x() == Vertexs[i].get_x() and p.get_y() == Vertexs[i].get_y()){
                found = true;
            }
        }
        if(!found) Vertexs.push_back(p);
    }
}

/** Retorna el poligon convex que representa la interseccio entre els dos poligons
    El que fa l'algorisme és construir un poligon convex mitjançant els vertex
    del poligon 1 que són dins el poligon 2, viceversa, i també hi afegeix els
    punts de tall entre els dos poligons. Posteriorment ordena aquests vertex
    en sentit contrari a les agulles del rellotge
    Adaptació a C++ de l'algorisme:
        https://www.swtestacademy.com/intersection-convex-polygons-algorithm/*/
ConvexPolygon ConvexPolygon::intersection(ConvexPolygon& Pol){
    vector<Point> ClippedCorners;
    // Afegim els vertex del poligon objecte que son dins el poligon paràmetre.
    ConvexPolygon Poli = Poligon;
    int size1 = Poli.num_edges();
    for(int i = 0; i < size1; ++i){
        if(point_inside(Poli[i],Pol)){
            vector<Point> ins_Point = {Poligon[i]};
            add_points(ClippedCorners,ins_Point);
        }
    }
    // Ara a la inversa
    int size2 = Pol.num_edges();
    for(int i = 0; i < size2; ++i){
        if(point_inside(Pol[i],Poli)) {
            vector<Point> ins_Point = {Poligon[i]};
            add_points(ClippedCorners,ins_Point);
        }
    }
    // Afegim el punts de tall entre els dos poligons
    for (int i = 0, next = 1; i < size1; i++, next = (i + 1 == size1) ? 0 : i + 1)
    {
        vector<Point> intersections = GetIntersectionPoints(Poligon[i], Poligon[next], Pol);
        add_points(ClippedCorners, intersections);
    }
    //return ConvexPolygon Intersection = order_couterclockwise(ClippedCorners);
    return convexHull(ClippedCorners);
}


//****************************************************************************
/** Retorna el rectangle que conté tots els poligons convexos donats.*/
ConvexPolygon ConvexPolygon::boundingBox(vector<ConvexPolygon>& Poligons) const{
    int n_polygons = Poligons.size();
    //si no hi ha poligons, retornem un vector buit
    if(n_polygons == 0) return (vector<Point> (0));
    // inicialitzem amb un valor qualsevol
    double max_x = Poligons[0][0].get_x();
    double min_x = Poligons[0][0].get_x();
    double max_y = Poligons[0][0].get_y();
    double min_y = Poligons[0][0].get_y();
    for(int i=0; i < n_polygons; ++i){
        int pol_size = Poligons[i].num_edges();
        // buquem els maxims i minims totals
        for(int j=0; j < pol_size; ++j){
            double x = Poligons[i][j].get_x();
            double y = Poligons[i][j].get_y();
            if(x > max_x) max_x = x;
            if(x < min_x) min_x = x;
            if(y > max_y) max_y = y;
            if(y < min_y) min_y = y;
        }
    }
    vector<Point> Bounding_Box = {Point(min_x,min_y), Point(max_x,min_y),
        Point(max_x,max_y), Point(min_x,max_y)};
    return Bounding_Box;
}


/** Retorna el poligon convex més petit que conté els dos poligons. Ës el resultat
    de fer el convex hull de tots els punts dels dos poligons*/
ConvexPolygon ConvexPolygon::convexUnion(ConvexPolygon& Pol) const{
    vector<Point> convex_union (0);
    int size1 = Poligon.size();
    for(int i = 0; i < size1; ++i) convex_union.push_back(Poligon[i]);
    int size2 = Pol.num_edges();
    for(int i = 0; i < size2; ++i) convex_union.push_back(Pol[i]);
    return convexHull(convex_union);
}


/** Utilitzem un vertex com a pivot per fer un tipus de cerca binària,en la
    qual anem partint el poligon convex en dos i ens quedem la meitat en la
    qual queda el punt p respecte la recta que formen el pivot i el punt
    que hem escollit per fer la partició
    Prec: size(Pol) >= 3
     */



int ConvexPolygon::num_edges() const{
    return Poligon.size();
}

/** Retorna la distància euclidiana entre dos punts A i B */
double euclidian_distance(const Point& A, const Point& B){
      return sqrt(pow(A.get_x() - B.get_x(),2) + pow(A.get_y() - B.get_y(),2));
}

/** Per calcular el perímetre d'un poligon sumem les distàncies euclidianes entre els
    punts consecutius*/
double ConvexPolygon::perimeter() const{
    int size = Poligon.size();
    if(size <= 1) return 0; // 1 o 0 punts
    if(size == 2) return euclidian_distance(Poligon[0],Poligon[1]); // 1 segment
    double per = 0;
    for (int i = 0; i < size - 1; ++i){
       per += euclidian_distance(Poligon[i], Poligon[i+1]);
    }
    // Afegir la aresta entre l'últim i el primer punt
    per += euclidian_distance(Poligon[size-1], Poligon[0]);
    return per;
}

/*Point edge_midpoint(const Point& P, const Point& Q) {
    double puntmigX = (P.get_x() - Q.get_x()) / 2;
    double puntmigY = (P.get_y() - Q.get_y()) / 2;
    return Point{puntmigX, puntmigY};
}*/

/** Diem que un poligon és regular si tots els seus costats son iguals,
    per tant, es suficient amb mirar que tots tinguin la mateixa llargada
    Prec: #vertex >= 0 */
bool ConvexPolygon::is_regular() const{
    int size = Poligon.size();
    if(size < 3) return true;
    // Prenem la mida de la primera aresta amb la fórmula de la distància euclidiana
    double aresta1 = euclidian_distance(Poligon[size-1], Poligon[0]);
    for(int i = 0; i < size-1 ;++i){
        // Si una de les arestes té mida diferent a la primera, el poligon és irregular
        double arestax = euclidian_distance(Poligon[i], Poligon[i+1]);
        if(aresta1 - arestax > 0.000000000001) return false;
    }
    return true;
}

/** Retorna el producte vectorial del vectors formats pels dos vertexs
    adjacents Poligon[i], Poligon[i+1] */
double cross_Det(int i, int j, vector<Point>& Poligon){
    return Poligon[i].get_x() * Poligon[j].get_y() - Poligon[i].get_y() * Poligon[j].get_x();
}

/** L'area d'un polígon convex es calcula fent el producte de matrius 2*2
    entre tots els parells de punts x(i), x(i+1), inclós x(n),x(0)
    + info : http://mathworld.wolfram.com/PolygonArea.html
    Obs: No marco la funció com a constant perquè a l'intentar accedir als
    punts de "Poligon" donaria error */
double ConvexPolygon::area() {
        int size = Poligon.size();
        if (size < 3) return 0;
        double area = 0;
        for(int i = 0; i < size; ++i) area += cross_Det(i, (i+1)%size, Poligon);
        // posem el modul per poder fer el producte entre l'ultim i el primer punt
        return abs(area/2);
}

/** Centroide d'un poligon convex format per un conjunt de punts de
    mida k = (P1(x,y) + .. Pk(x,y)) / k
    +info : https://en.wikipedia.org/wiki/Centroid#Of_a_finite_set_of_points
    Prec : k>= 0  */
Point ConvexPolygon::centroid() const{
  int k = num_edges();
  double x_total = 0;
  double y_total = 0;
  for(int i = 0; i < k; ++i){
    x_total += Poligon[i].get_x(); // sumem les components x
    y_total += Poligon[i].get_y(); // sumem les components y
  }
  return Point(x_total/k , y_total/k);
}

/** Retorna una referència al punt de l'index especificat */
Point& ConvexPolygon::operator[](const int& i){
    int size = Poligon.size();
    assert(i >= 0);
    assert(i < size);
    return Poligon[i];
}
