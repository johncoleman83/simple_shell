#include "header.h"

/**
 * _getline - custom getline currently reads 1 char at a time
 * @buffer: address of pointer to input commands buffer
 * @limit: maxsize of input character string, realloc if necessary
 *
 * Return: number of characters written
 */
ssize_t _getline(char **buffer, size_t *limit)
{
	unsigned int i, j;
	size_t charcount, iterations;

	charcount = 0;
	iterations = 1;
	j = 0;
	i = -1;

	while (i != 0)
	{
		i = read(STDIN_FILENO, (*buffer + j), 1);

		if ((*buffer + j++)[0] == '\n')
		{
			charcount++;
			break;
		}

		if (charcount++ % *limit == 0)
		{
			iterations++;
			*buffer = _realloc(*buffer, charcount, (*limit * iterations));
		}
	}

	if (i == 0)
	{
		free(*buffer);
		exit(EXT_SUCCESS);
	}

	return ((ssize_t)charcount);
}

/**
 * _filemode - finds file mode of standard input
 * @fd: STDIN_FILENO
 *
 * Return: 1 a device like a terminal, 0 a FIFO special file, or a pipe
 */
int _filemode(int fd)
{
	int result = -1;
	struct stat buf;

	fstat(fd, &buf);

	switch (buf.st_mode & S_IFMT)
	{
	case S_IFCHR:
		result = 1;
		break;
	case S_IFIFO:
		result = 0;
		break;
	default:
		break;
	}

	return (result);
}
