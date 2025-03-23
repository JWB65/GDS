#include "../Gds/gds.h"
#include "../List/list.h"

#include <stdio.h>
#include <stdlib.h>

int main()
{
	// Create the GDSII database from a file with "gds_new"

	wchar_t name[] = L"c:\\LOCAL\\TEST\\Test.gds";
	int error = ERR_SUCCESS;
	gds_db* db = gds_new(name, &error);

	// If errors occured gds_new() will return NULL with error code in @error
	if (db == NULL)
	{
		printf("Error %d found while creating GDSII database\n", error);
		return 0;
	}

	// Extract polygons from a cell in the GDSII data base

	char* cell_name = "0_PM02_Mask";
	gds_bbox target = {.xmin = -23441, .ymin = 17292, .xmax = -23441 + 48, .ymax = 17292 + 48};
	List* pset = list_new(); 
	int64_t nskipped = 0;

	gds_extract(db, cell_name, target, 1.5, pset, &nskipped);

	//gds_print_polyset(pset);

	gds_write(L"c:\\LOCAL\\TEST\\test_out.gds", pset, db->dbunit_in_uu, db->dbunit_in_meter);

	gds_delete(db);
	db = NULL;
}