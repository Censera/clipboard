# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <err.h>
# include "include/libclipboard.h"

int	free_to_copy( const char *src )
{
	if ( 0 == fork() )
	{	
		clipboard_c *cb = clipboard_new(NULL);
		if ( NULL == cb )
		{
			errx(1, "Failed to open clipboard!");
		}
		clipboard_set_text_ex( cb, src, -1, LCB_CLIPBOARD );

		usleep(100000);

		clipboard_free(cb);
		exit(0);
	}
	return (0);
}

int	main( int argc, char** argv )
{
	const char *src;

	if ( 1 < argc && argv[1] != NULL )
	{
		src = argv[1];
	}
	else
	{
		char buf[32000];
		size_t read = fread(buf, 1, sizeof buf - 1, stdin);

		if (0 == read)
		{
			errx(1, "No source to copy from");
		}

		buf[read];
		src = buf;
	}

	int ret = free_to_copy(src);
	return ret;
}
