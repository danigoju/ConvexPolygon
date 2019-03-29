# ConvexPolygon Calculator
ConvexPolygon Calculator is an application to operate with convex polygons.

### Summary
ConvexPolygon Calculator is an interactive application whose objective is to
give the user a tool to operate with polygons in an easy and visual way, since
this application includes a polygon plotter. The code of the calculator is open,
so you can add new utilities to the application in order to make it more useful
for you objectives.


### Installation
In order to install the ConvexPolygon Calculator, you have to do the following,
depending on which Operative System you are using:

* For **Linux** and **iOS**:

··· Install the PngWriter library, in order to be able to draw your polygons.
More info about de download in it's github repository: <https://github.com/pngwriter/pngwriter>

···Download the folder with all it's containing files and execute the command make
in your command line executer.

* For **Windows** :
···It is not supported, although it might work making some small modifications.

### The Convex Polygon
A convex polygon is a simple polygon in which all its interior angles are strictly less
than 180°, as you can see in the following example.

![alt text](https://docs.derivative.ca/images/4/44/ConvexPolys.jpg)

A polygon has n vertices and n edges and is said to be regular when all edges have the same length.

In our application, the convex polygons are implemented through the **ConvexPolygon class.**, which
defines a convex polygon as a vector of points, and these are represented by the Cartesian Coordinates (x,y).

Now, we are going to define some utilities that can be done with Convex Polygons, including
operations between them, and usefull information we can ask about.

#### Convex Polygon operations
* **Convex Hull:** Given a set of points, we can calculate the smallest convex polygon that contains the set.

![alt text](https://miro.medium.com/max/1354/1*F4IUmOJbbLMJiTgHxpoc7Q.png)

* **Convex Union:** Given two convex polygons, the convex union is the smallest convex polygon that contains both polygons. Equivalently, it is the convex hull of both polygons.

![alt text](https://daveagp.files.wordpress.com/2009/09/union.png)

* **Intersection:** The intersection of two convex polygons is a convex polygon.

![alt text](http://esri.github.io/geometry-api-java/doc/Images/Relate/Relate1.jpg)

* **Bounding Box:** Given a set of convex polygons, find the smallest bounding box that encloses all polygons.

![alt text](https://camo.githubusercontent.com/de0f481e05a986f9f3864e81989186bec38c68b3/68747470733a2f2f75706c6f61642e77696b696d656469612e6f72672f77696b6970656469612f636f6d6d6f6e732f7468756d622f352f35622f4d696e696d756d5f626f756e64696e675f72656374616e676c652e7376672f32303070782d4d696e696d756d5f626f756e64696e675f72656374616e676c652e7376672e706e67)

* **Inside:** We can check whether a convex polygon is inside another convex polygon.

![alt text](http://cgm.cs.mcgill.ca/~athens/cs507/Projects/2003/DanielSud/poly2.gif)


### Convex Polygon information
* Number of **vertices** and **edges**
* Length of the **perimeter**
* **Area**
* Coordinates of the **centroid**

### Particular cases
For convenience, we will consider some particular cases of polygons (not always recognized as polygons by mathematicians):
* **Empty polygon:**  a polygon with zero vertices.
* **Monogon:**  a polygon with one vertex (a point).
* **Digon:**  a polygon with two vertices (a segment).

## The ConvexPolygon Calculator
The calculator consists on a command line reader which will play the following commands,
some of which results have been explained in the previous sections. Each command produces
a line of output.

### A usage example



#### Points
Points in the commands are given by two pairs of real numbers, in standard notation, to denote the X and Y coordinates. For instance, `0 0` or `3.14 -5.5`. When printed, all real numbers must be formatted with three digits after the decimal dot.

### Polygon Identifiers
All commands include polygon identifiers. These are made by words, such as `p`, `p1`, `p2`, or `pol_gr`.

### Comments
Lines starting with a hash sign (`#`) are comments. Their output is just a hash sign.

### Colors
Colors in the commands are given by three real numbers in [0,1], in standard notation, to denote the RGB color. For instance, 0 0 0 denotes black, `1 0 0` denotes red, and `1 0.64 0` denotes orange.

### File names
Filenames in the commands are made up of words, such as `f`, `pol.txt` or `some_file_name.pol`.

### Commands:
#### `polygon`
The `polygon` command associates an identifier with a convex polygon made by a set of zero or more points. If the polygon identifier is new, it will create it. If it already existed, it will overwrite the previous polygon. New polygons are black.

#### `print`
`print` command prints the name and the vertices of a vertices of a given polygon. The output must only contain the vertices in the convex hull of the polygon, in clockwise order, starting from the vertex will lower X (and the vertex with lower Y in case of ties). They must be printed in a single line, with one space separating each value.

#### `area`
The `area` command prints the area of the given polygon.

#### `perimeter`
The `perimeter` command prints the perimeter of the given polygon.

#### `vertices`
The `vertices` command prints the number of vertices of the convex hull of the given polygon.

#### `centroid`
The `centroid` command prints the centroid of the given polygon.

#### `list`
The `list` command lists all polygon identifiers, lexycographically sorted.

#### `save`
The `save` command saves the given polygons in a file, overwriting it if it already existed. The contents of the file must be the same as in the `print` command, with a polygon per line.

#### `load`
The `load` command loads the polygons stored in a file, in the same way as `polygon`, but retrieving the vertices and identifiers from the file.

#### `setcol`
The `setcol` command associates a color to the given polygon.

#### `draw`
The `draw` command draws a list of polygons in a PNG file, each one with its associated color. The image should be of 500x500 pixels, with white background and the coordinates of the vertices should be scaled to fit in the 498x498 central part of the image, while preserving the original aspect ratio.

#### `intersection`
This command may receive two or three parameters:

* When receiving two parameters p1and `p2`, `p1` should be updated to the intersection of the original `p1` and `p2`.

* When receiving three parameters `p1`, `p2` and `p3`, `p1` should be updated to the intersection of `p2` and `p3`.

Take into account that identifiers may be repeated.

#### `union`
Just as the `intersection` command, but with the convex union of polygons.

#### `inside`
Given two polygons, the `inside` command prints `yes` or `no` to tell whether the first is inside the second or not.

#### `bbox`
The `bbox` command creates a new polygon with the four vertices corresponding to the bounding box of the given polygons.

### Commands without answer
As seen in the examples, some commands do not really produce an answer. In this case `ok` must be printed, unless there was some error.
