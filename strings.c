#include "header.h"

/**
 * _strlen - finds and returns length of string
 * @str: string to find length
 *
 * Return: length of string
 */
unsigned int _strlen(const char *str)
{
	int i = 0;

	while (str[i] != '\0')
		i++;

	return (i);
}

/**
 * _strdup - takes a string and copies to another a new memory location
 * @str: string to copy
 *
 * Return: pointer to copied string
 */
char *_strdup(char *str)
{
	unsigned int len, j;
	char *ptrstring;

	if (str == NULL)
		return (NULL);

	len = _strlen(str);

	ptrstring = safe_malloc((len + 1) * sizeof(char));

	for (j = 0; j < len; j++)
		ptrstring[j] = str[j];
	ptrstring[j] = '\0';

	return (ptrstring);
}

/**
 * _strncmp - checks if 2 strings are of equal value and length
 * @s1: first string
 * @s2: second string
 * @n: number of bytes to compare
 *
 * Return: difference of first characters that are of diff value or 0 on success
 */
int _strncmp(char *s1, char *s2, unsigned int n)
{
	unsigned int j;

	for (j = 0; s1[j] != '\0' && s2[j] != '\0' && j < n; j++)
		if (s1[j] != s2[j])
			return (s1[j] - s2[j]);

	return (0);
}

/**
 * _strcpy - copies a string from src to dest
 * @dest: new copy of string
 * @src: the source of the copy
 *
 * Return: pointer to copy
 */
char *_strcpy(char *dest, char *src)
{
	int c;

	for (c = 0; src[c] != '\0'; c++)
		dest[c] = src[c];

	dest[c] = '\0';

	return (dest);
}

/**
 * _strncpy - copies string from source to destination
 * @dest: destination string
 * @src: source string to be copied
 * @n: bytes to be copied from source string
 *
 * Return: destination string concatenated
 */
char *_strncpy(char *dest, char *src, int n)
{
	int j;

	for (j = 0; j < n && src[j] != '\0'; j++)
		dest[j] = src[j];

	while (j < n)
	{
		dest[j] = '\0';
		j++;
	}

	return (dest);
}