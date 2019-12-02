#include <stdio.h>
#include <stdlib.h>

static int sMemory[1024];
static char sNumBuf[11];

size_t fsize(FILE *f)
{
	size_t sz;
	
	fseek(f, 0, SEEK_END);
	sz = ftell(f);
	rewind(f);
	
	return sz;
}

void readOpcodeStringIntoMemory(const char *str)
{
	int *mem = sMemory;
	
	for (;;)
	{
		char *buf = sNumBuf;
		
		for (;;)
		{
			*buf++ = *str++;
			
			if (!*str) return;
			
			if (*str == ',')
			{
				*buf = 0;
				*mem++ = strtol(sNumBuf, NULL, 10);
				str++;	
				break;
			}
		}
	}
}

void emulate()
{
	int *mem = sMemory;
	
	for (;;)
	{		
		switch (*mem)
		{
			case 1: // opcode 1 adds
				sMemory[mem[3]] = sMemory[mem[1]] + sMemory[mem[2]];
				mem += 4;
				break;
			case 2: // opcode 2 multiplies
				sMemory[mem[3]] = sMemory[mem[1]] * sMemory[mem[2]];
				mem += 4;
				break;
			case 99: // halt
				return;
			default:
				printf("FATAL ERROR: Opcode %d encountered\n", *mem);
				return;
		}
	}
}

int main()
{
	char *strBuf;
	FILE *file;
	size_t sz;
	
	if ((file = fopen("input.txt", "r")) == 0)
	{
		perror("Error opening input.txt");
		return 1;
	}
	
	sz = fsize(file);	
	strBuf = calloc(sz + 1, 1);
	fread(strBuf, 1, sz, file);
	fclose(file);
	
	readOpcodeStringIntoMemory(strBuf);
	
	sMemory[1] = 12;
	sMemory[2] = 2;
	
	emulate();
	
	printf("Part 1 - Memory position 0: %d\n", *sMemory);
	
	for (int i = 0; i < 100; i++)
	for (int j = 0; j < 100; j++)
	{
		readOpcodeStringIntoMemory(strBuf);
		
		sMemory[1] = i;
		sMemory[2] = j;
		
		emulate();
		
		if (*sMemory == 19690720)
		{
			printf("Part 2 - Memory position 0: %d, noun: %d, verb: %d, answer: %d\n",
				sMemory[0], sMemory[1], sMemory[2], 100 * i + j);
			
			break;
		}
	}
	
	free(strBuf);
	
	return 0;
}