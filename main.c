#include "csv.h"

int main()
{
	FILE *file = fopen("notes.csv", "r");
	skip_csv_header(file);

	struct Note note;

	while (read_next_note(file, &note) != -1)
	{
		Note_print(&note);
		Note_destroy(&note);
	}

	fclose(file);
}