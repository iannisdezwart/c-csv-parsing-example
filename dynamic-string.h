#ifndef DYNAMIC_STRING_HEADER
#define DYNAMIC_STRING_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

struct String
{
	char *str;
	size_t len;
	size_t cap;
};

void String_make(struct String *self, size_t init_cap)
{
	self->str = (char *) malloc(init_cap);
	self->len = 0;
	self->cap = init_cap;
}

void String_append(struct String *self, char c)
{
	if (self->len == self->cap)
	{
		char *new_str = (char *) malloc(self->cap * 2);

		for (size_t i = 0; i < self->len; i++)
		{
			new_str[i] = self->str[i];
		}

		free(self->str);
		self->str = new_str;
	}

	self->str[self->len++] = c;
}

void String_print(struct String *self)
{
	for (size_t i = 0; i < self->len; i++)
	{
		putc(self->str[i], stdout);
	}

	putc('\n', stdout);
}

void String_clear(struct String *self)
{
	self->len = 0;
}

void String_destroy(struct String *self)
{
	free(self->str);
}

#endif