#include "config.h"
#include "error.h"
#include "io.h"
#include "organize.h"

int main(int args, char **argv)
{
	setbuf(stdout, NULL);
	int status = OK;

	if (args != 2 && args != 4 && args != 5)
		status = ERR_CMD;
	if (status == OK)
	{
		switch (args)
		{
			case 2:
				if (!strcmp(argv[1], "h"))
					organize_info();
				else
					status = ERR_CMD;
				break;
			case 4:
				if (!strcmp(argv[1], "o"))
					status = organize_invertible(argv[2], argv[3]);
				else
					status = ERR_CMD;
				break;
			case 5:
				if (!strcmp(argv[1], "a"))
					status = organize_sum(argv[2], argv[3], argv[4]);
				else if (!strcmp(argv[1], "m"))
					status = organize_mult(argv[2], argv[3], argv[4]);
				else
					status = ERR_CMD;
				break;
		}
	}

	switch (status)
	{
		case OK:
			//printf("\nProgram has successfully completed.");
			break;
		case ERR_FILE:
			printf("\nProblems with files.");
			break;
		case ERR_MEMORY:
			printf("\nProblems with memory.");
			break;
		case ERR_CMD:
			printf("\nWrong CMD. Please, write: app.exe h.");
			break;
		case ERR_MATRIX_SIZE:
			printf("\nWrong size of matrix.");
			break;
		case ERR_DATA:
			printf("\nWrong data in file.");
			break;
		case ERR_DETER:
			printf("\nMatrix has zero determinant.");
			break;
	}

	return status;
}
