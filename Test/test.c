#include "../Gds/gds.h"
#include "../List/list.h"

#include <stdio.h>
#include <stdlib.h>

int main()
{
	//
	// Create the GDSII database from a file with "gds_new"
	//

	wchar_t name[] = L"c:\\LOCAL\\TEST\\Test.gds";
	int error = ERR_SUCCESS;
	gds_db* db = gds_new(name, &error);

	// If errors occured gds_new() will return NULL with error code in @error
	if (db == NULL)
	{
		printf("Error %d found while creating GDSII database\n", error);
		return 0;
	}

	//
	// Extract polygons from a cell in the GDSII data base
	//

	// The name of the cell to extract polygons from
	char* cell_name = "0_PM02_Mask";

	// The target rectangle. Only polygons that overlap with this rectange will be included.
	gds_bbox target = {.xmin = -23441, .ymin = 17292, .xmax = -23441 + 48, .ymax = 17292 + 48};

	// The polygons will be added to a dynamin pointer list
	List* pset = list_new();

	// The number of polygons skipped during extraction because their size < resolution
	int64_t nskipped = 0;

	// Do the polygon extraction
	gds_extract(db, cell_name, target, 1.5, pset, &nskipped);

	// Print all polygons to stdout
	//gds_print_polyset(pset);

	//
	// Write the polygons to a new GDS file
	//

	gds_write(L"c:\\LOCAL\\TEST\\test_out.gds", pset, db->dbunit_in_uu, db->dbunit_in_meter);

	//
	// Clean-up
	//

	// Delete the polygon list
	for (int i = 0; i < pset->length; i++)
	{
		gds_polygon* p = list_at(pset, i);

		free(p->pairs);
		free(p);
	}
	list_delete(pset);

	// Delete the database
	gds_delete(db);
	db = NULL;
}