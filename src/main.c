#	include	<unistd.h>
#	include	<stdio.h>
#	include	<string.h>
#	include	<stdlib.h>
#	include	<stdbool.h>
#	include	<err.h>

#	include	"../inc/libclipboard.h"

int	available_to_copy(const char *src)
{
	pid_t	pid = fork();

	if (pid < 0)
	{
		errx(1, "fork fails");
	}
	else if (pid == 0)
	{
		fclose(stderr);

		clipboard_c *cb = clipboard_new(NULL);
		if (NULL == cb)
		{
			errx(1, "Failed to open clipboard!");
		}

		clipboard_set_text_ex(cb, src, -1, LCB_CLIPBOARD);

		sleep(10);

		clipboard_free(cb);
		exit(0);
	}

	return (0);
}

int	main(int argc, char** argv)
{
	const char	*src;

	if (argc >= 2 && argv[1] != NULL)
	{
		src = argv[1];
	}
	else
	{
		if (isatty(STDIN_FILENO))
			errx(1, "No input");

		size_t	cap = 4096;
		size_t	bytes_read = 0;
		char	*buf = malloc(cap);

		if (buf == NULL)
			errx(1, "Out of memory");

		while (1)
		{
			size_t	space_left = cap - bytes_read - 1;
			size_t	input = fread(buf + bytes_read, 1, space_left, stdin);

			if (input == 0)
			{
				if (ferror(stdin))
					errx(1, "Couldn't read");
				break;
			}

			bytes_read += input;

			if (bytes_read >= cap - 1)
			{
				cap *= 2;
				char	*new_buf = realloc(buf, cap);

				if (new_buf == NULL)
				{
					free(buf);
					errx(1, "Out of memory while resizing");
				}

				buf = new_buf;
			}
		}

		buf[bytes_read] = '\0';
		src = buf;
	}

	size_t	words = 0;
	size_t	lines = 0;
	bool	is_space = true;
	const char	*p = src;

	while (*p != 0)
	{
		if (*p == '\n')
		{
			lines++;
		}

		if (*p == ' ' || *p == '\t' || *p == '\n' || *p == '\r')
		{
			is_space = true;
		}
		else if (is_space)
		{
			is_space = false;
			words++;
		}
		p++;
	}

	if (p > src && *(p - 1) != '\n')
	{
		lines++;
	}

	printf("Processed:\t[\033[0;35m%zu\033[0m] Words\n\t\t[\033[0;35m%zu\033[0m] Lines\n", words, lines);

	return available_to_copy(src);
}
