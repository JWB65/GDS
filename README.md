# GDSII

A simple C++ library for reading and extracting polygons from a GDSII layout database used in the semiconductor, MEMS, and TFT industries.

# Features

* Reads-in a GDSII database which basically is a list of cells (also called structures) each with several elements like polygons and references to other cells.
* Extract polygons from a GDSII cell. The user of the library can use this polygon list for further programming work.
* Write the polygons to a newly created GDSII file.

# How to add the library to your project

No dependencies except the standard library. Just move the Gds folder with all its files to a folder named Gds in your project, and include
```
#include "../Gds/Gds.h"
```
in your source code.

# Instructions to use

* An example of its use is given in the `Test.cpp` in the Test folder with further information on the use of each function.

* Create a GDSII database with `gds_db* db = new gds_db(name, &result);` with 'name' the file name of the related GDS file.

* Read in the polygons of a given cell into a pointer list by `gds_extract(db, cell_name, target, resolution, pset, &nskipped);`. Only polygons that overlap with bounding
  box `target` are included. Also, in this example, the polygons need to be larger than the `resolution`. The number of polygons that are skipped because their size
  is below `resolution`are placed in `nskipped`.

* The polygons are stored polygon set pointed to by `pset` which can be initialized by `gds_polyset* pset = new gds_polyset;`. After use, the polygons stored in `pset` need
  to be cleared to prevent memory leaks. This is done with the function `gds_polyset_clear(pset)`. This is shown in the `Test.cpp` file.

* If desired, create a new GDSII file from the extracted polygons with `gds_write(L"c:\\foo.gds", pset, db->dbunit_in_uu, db->dbunit_in_meter);`.

# The polygon structure

The polygon class `gds_polygon` is just an array of pairs with an integer specifying the layer number in the GDSII database.

```
struct gds_pair {
	int64_t x, y;
};

struct gds_polygon {
public:
	gds_polygon(gds_pair* pairs, int npairs, gds_bbox box, uint16_t layer);
	~gds_polygon();

	gds_pair* pairs; // Coordinates of vertices in database units
	int npairs; // Number of coordinates (note GDSII polygons are closed polygons)

	uint16_t layer; // Layer in the GDSII database to which the polygon belongs

	gds_bbox bbox; // Bounding box of the polygon
};
```
The `layer` member of the structure identifies the GDS layer number the polygon belongs to.

Questions: janwillembos@yahoo.com
