#include "gds.h"

#include <limits.h>
#include <stdlib.h>

gds_cell*
cell_new()
{
	gds_cell* cell = calloc(1, sizeof(gds_cell));

	bbox_init(&cell->bbox);

	cell->srefs = list_new();
	cell->arefs = list_new();
	cell->boundaries = list_new();
	cell->paths = list_new();

	return cell;
}

void
cell_delete(gds_cell* cell)
{
	for (int j = 0; j < ((cell->srefs))->length; j++)
	{
		gds_sref* sref = list_at(cell->srefs, j);
		free(sref);
	}
	list_delete(cell->srefs);
	cell->srefs = NULL;

	for (int j = 0; j < ((cell->arefs))->length; j++)
	{
		gds_aref* aref = list_at(cell->arefs, j);
		free(aref);
	}
	list_delete(cell->arefs);
	cell->arefs = NULL;

	for (int j = 0; j < ((cell->boundaries))->length; j++)
	{
		gds_boundary* elem = list_at(cell->boundaries, j);
		free(elem->pairs);
		free(elem);
	}
	list_delete(cell->boundaries);
	cell->boundaries = NULL;

	for (int j = 0; j < ((cell->paths))->length; j++)
	{
		gds_path* elem = list_at(cell->paths, j);
		free(elem->pairs);
		free(elem->epairs);
		free(elem);
	}
	list_delete(cell->paths);
	cell->paths = NULL;

	free(cell);
}
