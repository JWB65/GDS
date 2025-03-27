#include "gds.h"

#include <inttypes.h>
#include <stdio.h>

void gds_print_polyset(List* pset)
{
	printf("\nPrinting polygon set:\n");

	if (pset->length == 0)
		printf("--> List is empty\n");

	for (int i = 0; i < pset->length; i++)
	{
		gds_polygon* poly = list_at(pset, i);
		
		printf("\nLayer %d polygon with %d vertices:\n", poly->layer, poly->npairs - 1);
		for (int j = 0; j < poly->npairs; j++)
		{
			gds_pair pair = poly->pairs[j];
			printf("\t(%"PRId64", %"PRId64")\n", pair.x, pair.y);
		}
	}
}