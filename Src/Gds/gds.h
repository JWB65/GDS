#pragma once

#include "gds_bbox.h"
#include "gds_errors.h"
#include "gds_pair.h"
#include "gds_transform.h"

#include "..\List\list.h"

#include <stdbool.h>
#include <stdint.h>

#define GDS_MAX_CELL_NAME 32

typedef struct gds_polygon
{
	gds_pair* pairs;
	int npairs;
	uint16_t layer;
	gds_bbox bbox;
} gds_polygon;

typedef struct gds_boundary
{
	uint16_t layer;
	gds_pair* pairs;
	int npairs;
	gds_bbox bbox;
} gds_boundary;

typedef struct gds_path
{
	uint16_t layer, pathtype;
	uint32_t width;

	gds_pair* pairs;
	int npairs;

	// When a gds file is read, path elements will be expanded into a normal boundary element
	gds_pair* epairs;
	int nepairs;

	gds_bbox bbox;
} gds_path;

// Forward declaration type gds_cell because of circular dependency
typedef struct gds_cell gds_cell;

typedef struct gds_sref
{
	uint16_t strans;
	double angle, mag;
	gds_pair origin;
	char sname[GDS_MAX_CELL_NAME + 1];
	gds_cell* cell;
} gds_sref;

typedef struct gds_aref
{
	double angle, mag;
	uint16_t strans;
	int ncols, nrows;
	gds_pair vectors[3];
	char sname[GDS_MAX_CELL_NAME + 1];
	gds_cell* cell;
} gds_aref;

typedef struct gds_cell
{
	char name[GDS_MAX_CELL_NAME + 1];
	List* boundaries, * paths, * srefs, * arefs;
	gds_bbox bbox; /* Is recursively calculated after loading the database */
	bool initialized; /* Is set true when member @bbox is initialized */
} gds_cell;

typedef struct gds_db
{
	uint16_t version;

	// The UNIT records
	double dbunit_in_uu, dbunit_in_meter;

	List* cell_list;
} gds_db;

/*
 *  Create a gds_db structure from a file. A pointer to int needs to be provided for a possible
 *	error code upond return.
 *
 *  @file: file name of the GDS file to be loaded
 *  @error: pointer to int which will be filled with 0 (success) or an error code
 *  @return: A pointer to the gds_db if succesful or NULL if loading failed
 */
gds_db* gds_new(const wchar_t* file, int* error);

/*
 *  @db: pointer to gds_db structure to delete
 */
void gds_delete(gds_db* db);

/*
 *  Find the pointer to cell with name @sname
 */
gds_cell* find_cell(gds_db* db, const char* name);

/*
 *  Extract polygons from a region (given by @target) of a cell in a GDSII database
 *
 *	@db: pointer to the gds_db structure previously loaded from a GDSII database file
 *	@cellname: name of the cell in @db to extract the polygons from
 *	@target: boundings box of the target area in um
 *	@resolution: polygon sized smaller than @res (in um) are ignored
 *	@pset: pointer to list of polygons
 *  @return: error code (in case of error)
 *
 */
gds_error gds_extract(gds_db* db, const char* cell_name, gds_bbox target, double resolution,
	List* pset, int64_t* nskipped);

/*
 *  Print to stdout all polygons elements of a polygon set
 */
void gds_print_polyset(List* pset);

/*
 *  Write all polygon elements of a polygon set to a GDS file
 *
 *  All polygons are saved as boundary elements in top cell "TOP"
 *
 *  @dbunit_size_uu: database size in user units
 *  @dbunit_size_in_m: database size in meter
 */
int gds_write(const wchar_t* dest, List* pset, double dbunit_size_uu, double dbunit_size_in_m);
