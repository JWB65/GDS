#include "Cell.h"

#include "BBox.h"

#include <limits.h>
#include <stdlib.h>

gds_cell::gds_cell()
{
	name[0] = 0;

	bbox_init(&bbox);

	srefs = new std::vector<gds_sref*>;
	arefs = new std::vector<gds_aref*>;
	boundaries = new std::vector<gds_boundary*>;
	paths = new std::vector<gds_path*>;

	initialized = false;
}

gds_cell::~gds_cell()
{
	for (gds_sref* sref : *srefs)
	{
		free(sref);
	}
	delete srefs;

	for (gds_aref* aref : *arefs)
	{
		free(aref);
	}
	delete arefs;

	for (gds_boundary* elem : *boundaries)
	{
		free(elem->pairs);
		free(elem);
	}
	delete boundaries;

	for (gds_path* elem : *paths)
	{
		//gds_path* elem = (gds_path*) cell->paths[j];
		free(elem->pairs);
		free(elem->epairs);
		free(elem);
	}
	delete paths;
}

/*
gds_cell*
cell_new()
{
	gds_cell* cell = (gds_cell*)calloc(1, sizeof(gds_cell));

	bbox_init(&cell->bbox);

	cell->srefs = new std::vector<gds_sref*>;
	cell->arefs = new std::vector<gds_aref*>;
	cell->boundaries = new std::vector<gds_boundary*>;
	cell->paths = new std::vector<gds_path*>;

	return cell;
}

void
cell_delete(gds_cell* cell)
{
	for (gds_sref* sref : *cell->srefs)
	{
		free(sref);
	}
	delete cell->srefs;

	for (gds_aref* aref : *cell->arefs)
	{
		free(aref);
	}
	delete cell->arefs;

	for (gds_boundary* elem : *cell->boundaries)
	{
		free(elem->pairs);
		free(elem);
	}
	delete cell->boundaries;

	for (gds_path* elem : *cell->paths)
	{
		//gds_path* elem = (gds_path*) cell->paths[j];
		free(elem->pairs);
		free(elem->epairs);
		free(elem);
	}
	delete cell->paths;

	free(cell);
}
*/