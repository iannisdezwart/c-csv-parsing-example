#ifndef CSV_HEADER
#define CSV_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "dynamic-string.h"

struct Note
{
	struct String title;
	struct String file_name;
	struct String date;
};

void Note_print(struct Note *self)
{
	printf("Note\n");

	printf("    title: ");
	String_print(&(self->title));

	printf("    file_name: ");
	String_print(&(self->file_name));

	printf("    date: ");
	String_print(&(self->date));
}

void Note_destroy(struct Note *self)
{
	String_destroy(&(self->title));
	String_destroy(&(self->file_name));
	String_destroy(&(self->date));
}

int8_t skip_csv_header(FILE *file)
{
	while (1)
	{
		int c = fgetc(file);
		if (c == EOF) return -1; // Unexpected EOF

		if (c == '\n') break;
	}

	return 0;
}

int8_t read_next_value(FILE *file, struct String *buf)
{
	uint8_t started = 0;

	// Read next value

	while (1)
	{
		int c = fgetc(file);
		if (c == EOF) return -1; // Unexpected EOF

		if (c == ',' || c == '\n') break;
		if (c == ' ' && !started) continue;

		started = 1;
		String_append(buf, c);
	}

	return 0;
}

int8_t read_next_note(FILE *file, struct Note *note)
{
	String_make(&(note->title), 16);
	if (read_next_value(file, &(note->title)) == -1) goto err_1;

	String_make(&(note->file_name), 16);
	if (read_next_value(file, &(note->file_name)) == -1) goto err_2;

	String_make(&(note->date), 16);
	if (read_next_value(file, &(note->date)) == -1) goto err_3;

	return 0;

	err_3:
	String_destroy(&(note->date));
	err_2:
	String_destroy(&(note->file_name));
	err_1:
	String_destroy(&(note->title));

	return -1;
}

#endif