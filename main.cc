#include <iostream>
#include <fstream>
#include <stdio.h>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <pngwriter.h>
#include <cmath>
#include <bits/stdc++.h>
#include "Point.hh"
#include "ConvexPolygon.hh"
using namespace std;


// ************************************************************************************

/** Crea un poligon amb l'identificador i els punts donats */
void pol_def(map<string, ConvexPolygon>& Poligons){
    vector<Point> vertexs;
    string input;
    getline(cin, input);
    stringstream ss(input);
    string name;
    ss >> name;
    double x,y;
    while(ss >> x >> y){
        Point p={x,y};
        vertexs.push_back(p);
    }
    // si el poligon ja existia, el borrem per afegir-ne el nou
    if(Poligons.find(name) != Poligons.end()) Poligons.erase(name);
    ConvexPolygon poligon = vertexs;
    Poligons.insert({name,poligon});
    cout << "ok" << endl;
}

/** Escriu les coordenades dels vertex del poligon amb l'identificador donat */
void pol_print(map<string, ConvexPolygon>& Poligons){
    string name;
    cin >> name;
    auto it = Poligons.find(name);
    if(it != Poligons.end()){ // si el poligon està definit
        ConvexPolygon poligon = Poligons[name];
        cout << name << " ";
        // Obtenim el punt amb menor x per començar a imprimir
        int position_min_x = 0;
        double min_x = poligon[0].get_x();
        int size = poligon.num_edges();
        for(int i = 0; i < size; ++i){
            if(poligon[i].get_x() < min_x) position_min_x = i;
            else if(poligon[i].get_x() == min_x){
                if(poligon[i].get_y() < poligon[position_min_x].get_y()) position_min_x = i;
            }
        }
        // Imprimim les coordenades del poligon començant pel vertex que hem obtingut
        for(int i = 0; i < size; ++i){
            int position = (i+position_min_x)%size;
            cout << poligon[position].get_x() << " "  << poligon[position].get_y() << " ";
        }
        cout << endl;
    }
    else cout << "error: undefined identifier" << endl;
}


/** Escriu l'area del poligon amb l'identificador donat */
void pol_get_area(map<string, ConvexPolygon>& Poligons){
    string name;
    cin >> name;
    auto it = Poligons.find(name);
    if(it != Poligons.end()){
        double area = Poligons[name].area();
        cout << area << endl;
    }
    else cout << "error: undefined identifier" << endl;
}

/** Escriu les coordenades del centroide del poligon amb l'identificador donat */
void pol_get_centroid(map<string, ConvexPolygon>& Poligons){
    string name;
    cin >> name;
    Point centroid = Poligons[name].centroid();
    cout << centroid.get_x() << " " << centroid.get_y() << endl;
}

/** Escriu el perímetre que té el poligon amb l'identificador donat */
void pol_get_perimeter(map<string, ConvexPolygon>& Poligons){
    string name;
    cin >> name;
    double perimeter = Poligons[name].perimeter();
    cout << perimeter << endl;
}

/** Escriu el número de vertexs que té el poligon amb l'identificador donat */
void pol_get_vertices(map<string, ConvexPolygon>& Poligons){
    string name;
    cin >> name;
    int nverts = Poligons[name].num_edges();
    cout << nverts << endl;
}


void pol_save(map<string, ConvexPolygon>& Poligons){
    string file_name;
    cin >> file_name;

    vector<string> pols_to_save;
    string input;
    getline(cin, input);
    stringstream ss(input);
    string pol_name;
    while(ss >> pol_name){
        if(Poligons.find(pol_name) == Poligons.end()){ // si el poligon no ha estat definit
            cout << "error: undefined identifier" << endl;
            return;
        }
        else pols_to_save.push_back(pol_name);
    }

    ifstream f(file_name.c_str());
    if(f.good()){ //si existeix, el borrem
        // la funcio remove() rep com a parametre un const char,
        // per tant convertim l'string a aquest tipus
        int n = file_name.length();
        char char_file_name[n + 1];
        strcpy(char_file_name, file_name.c_str());
        remove(char_file_name);
    }
    // ara que sabem segur que no existeix el fitxer amb el mateix nom, el creem
    ofstream outfile;
    outfile.open(file_name, ios_base::app);
    outfile << fixed;
    outfile.precision(3); //guardem els vertexs amb 3 xifres decimals
    for (string name : pols_to_save) {
        ConvexPolygon Pol = Poligons[name];
        int size = Pol.num_edges();
        outfile << name << " ";
        for(int i = 0; i < size; ++i){
            outfile <<  Pol[i].get_x() << " " << Pol[i].get_y() << " ";
        }
        outfile << endl;
    }
    cout << "ok" << endl;
}


/** Llegeix tots els poligons d'un fitxer  i els guarda en el diccionari de poligons*/
void pol_load(map<string, ConvexPolygon>& Poligons){
    string file_name;
    cin >> file_name;
    string line;
	ifstream infile;
	infile.open (file_name);
    if(infile.good()){
        while(!infile.eof()) // Per rebre totes les lines.
        {
	        getline(infile,line); // Guarda la linia a "line"
	        istringstream iss(line);
            string name;
            vector<Point> Poligon;
            iss >> name; // llegim l'identificador del poligon
            double x,y;
            while(iss >> x >> y) Poligon.push_back(Point{x,y}); // llegim els vertexs
            // si el poligon no hi era, l'afegim
            if(Poligons.find(name) == Poligons.end()) Poligons.insert({name,Poligon});
            // i si el poligon ja hi era, el canviem pel nou
            else Poligons[name] = Poligon;
        }
	infile.close();
    // Un cop carrega els continguts, borra el fitxer
    int n = file_name.length();
    char char_file_name[n + 1];
    strcpy(char_file_name, file_name.c_str());
    remove(char_file_name);
    cout << "ok" << endl;
    }
    else cout << "file does not exist" << endl;
}

void pol_list(map<string, ConvexPolygon>& Poligons){
    for (auto name : Poligons) {
        cout << name.first << " ";
    }
    cout << endl;
}

/** Si es donen dos identificadprs, escriu al primer, la unió convexa dels dos, i si se'n
    donen tres, escriu al primer la unió convexa dels dos següents */
void pol_union(map<string, ConvexPolygon>& Poligons){
    string input;
    getline(cin, input);
    stringstream ss(input);
    string name1,name2,name3;
    // utilitzem aquesta comanda per dividir la linia d'entrada en strings
    ss >> name1 >> name2 >> name3;
    if(name3 == ""){ //si nomes tenim 2 paràmetres
        if(Poligons.find(name1) == Poligons.end() or Poligons.find(name2) == Poligons.end()){
            cout << "error: undefined identifier" << endl;
        }else{
            Poligons[name1] = Poligons[name1].intersection(Poligons[name2]);
            cout << "ok" << endl;
        }
    }else{ //si en tenim tres paràmetres
        if(Poligons.find(name2) == Poligons.end() or Poligons.find(name3) == Poligons.end()){
            cout << "error: undefined identifier" << endl;
        }
        else if(Poligons.find(name1) == Poligons.end()){
            Poligons.insert({name1, Poligons[name2].convexUnion(Poligons[name3])});
            cout << "ok" << endl;
        }
        else{
            Poligons[name1] = Poligons[name2].convexUnion(Poligons[name3]);
            cout << "ok" << endl;
        }
    }
}


/** Donats l'identificador de dos poligons, escriu "si" si el primer és dins el segon
    i escriu "no" si no hi és */
void pol_inside(map<string, ConvexPolygon>& Poligons){
    string name1,name2;
    cin >> name1 >> name2;
    bool inside = Poligons[name1].inside(Poligons[name2]);
    if(inside) cout << "yes" << endl;
    else cout << "no" << endl;
}

/** Associa un poligon amb un color */
void pol_setcol(map<string, ConvexPolygon>& Poligons, map<string, vector<double>>& Colors){
    string name;
    double c1,c2,c3;
    cin >> name >> c1 >> c2 >> c3;
    if(Poligons.find(name) == Poligons.end()){ //si no trobem el nom del poligon escrivim error
        cout << "error: undefined identifier" << endl;
    }else{
        if(Colors.find(name) == Colors.end()){ //si encara no hem associat cap color l'afegim al diccionari
            vector <double> new_color = {c1,c2,c3};
            Colors.insert({name,new_color});
        }else{ // si ja estava afegit al diccionari, el modifiquem
            Colors[name][0] = c1;
            Colors[name][1] = c2;
            Colors[name][2] = c3;
        }
    }
    cout << "ok" << endl;
}

/** Crea un poligon convex que es el resultat de fer la Bounding Box dels poligons donats */
void pol_bbox(map<string, ConvexPolygon>& Poligons){
    string name;
    cin >> name; // llegim el nom del polgion en el que guardarem la bounding box
    string input;
    getline(cin, input);
    stringstream ss(input);
    vector<string> poligons_ID;
    // utilitzem aquesta comanda per dividir la linia d'entrada en strings
    string ID;
    while(ss >> ID){
        if(Poligons.find(ID) == Poligons.end()){
            cout << "error: undefined identifier" << endl;
            return;
        }
        else poligons_ID.push_back(ID);
    }
    int n_pols = poligons_ID.size();
    vector <ConvexPolygon> poligons_bbox;
    // creem el vector amb els poligons convexos dels quals volem fer la bounding box
    for(int i = 0 ; i < n_pols; ++i) poligons_bbox.push_back(Poligons[poligons_ID[i]]);
    ConvexPolygon buit;
    Poligons.insert({name,buit.boundingBox(poligons_bbox)});
    cout << "ok" << endl;
}

void pol_intersection(map<string, ConvexPolygon>& Poligons){
    string input;
    getline(cin, input);
    stringstream ss(input);
    string name1,name2,name3;
    // utilitzem aquesta comanda per dividir la linia d'entrada en strings
    ss >> name1 >> name2 >> name3;
    if(name3 == ""){
        if(Poligons.find(name1) == Poligons.end() or Poligons.find(name2) == Poligons.end()){
            cout << "error: undefined identifier" << endl;
        }else{
            Poligons[name1] = Poligons[name1].intersection(Poligons[name2]);
            cout << "ok" << endl;
        }
    }else{
        if(Poligons.find(name2) == Poligons.end() or Poligons.find(name3) == Poligons.end()){
            cout << "error: undefined identifier" << endl;
        }
        else if(Poligons.find(name1) == Poligons.end()){
            Poligons.insert({name1, Poligons[name2].intersection(Poligons[name3])});
            cout << "ok" << endl;
        }
        else{
            Poligons[name1] = Poligons[name2].intersection(Poligons[name3]);
            cout << "ok" << endl;
        }
    }
}


// dibuixa els poligons amb els identificadors donats en un fitxer png
void pol_draw(map<string, ConvexPolygon>& Poligons, map<string, vector<double>>& Colors){
    string file_name;
    cin >> file_name;
    // convertim la string a un array de caràcter perquè ho demana la Funció
    int n = file_name.length();
    char filename[n + 1];
    strcpy(filename, file_name.c_str());
    pngwriter image(500, 500, 1.0, filename);
    // Agafem la linia amb els identificadors
    string input;
    getline(cin, input);
    stringstream ss(input);
    string ID;
    while(ss >> ID){ //dibuixem els poligons un per un
        // extreiem els colors que donarem al poligon del diccionari de colors
        if(Colors.find(ID) == Colors.end()){
            cout << "no colors specified, use command setcol" << endl;
            return;
        }else{
            double red = Colors[ID][0];
            double green = Colors[ID][1];
            double blue = Colors[ID][2];
            // pasem el poligon convex a format array de integers per dibuixar el poligon
            int size = Poligons[ID].num_edges();
            int points[(size*2) + 2];
            for(int i = 0, j = 0; i < size; ++i){
                points[j] = int(Poligons[ID][i].get_x());
                ++j;
                points[j] = int(Poligons[ID][i].get_y());
                ++j;
            }
            points[size*2] = int(Poligons[ID][0].get_x());
            points[size*2 + 1] = int(Poligons[ID][0].get_y());
            image.polygon(points, size + 1, red, green, blue);
        }
    }
    image.close(); // tanquem la imatge
    cout << "ok" << endl;
}

int main(){
    cout << fixed;
    cout.precision(3);
    map<string, ConvexPolygon> Poligons;
    map<string, vector<double>> Colors;
    string action;
    while (cin >> action) {
        if (action == "polygon")                  pol_def(Poligons);
        else if (action == "print")               pol_print(Poligons);
        else if (action == "area")                pol_get_area(Poligons);
        else if (action == "perimeter")           pol_get_perimeter(Poligons);
        else if (action == "vertices")            pol_get_vertices(Poligons);
        else if (action == "centroid")            pol_get_centroid(Poligons);
        else if (action == "save")                pol_save(Poligons);
        else if (action == "load")                pol_load(Poligons);
        else if (action == "list")                pol_list(Poligons);
        else if (action == "union")               pol_union(Poligons);
        else if (action == "inside")              pol_inside(Poligons);
        else if (action == "setcol")              pol_setcol(Poligons, Colors);
        else if (action == "draw")                pol_draw(Poligons, Colors);
        else if (action == "bbox")                pol_bbox(Poligons);
        else if (action == "intersection")        pol_intersection(Poligons);
        else cout << "error: unrecognized command" << endl;
    }
}
