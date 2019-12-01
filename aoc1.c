#include <stdio.h>
#include <stdint.h>

static char sStr[sizeof(int64_t) + 1];
static FILE *sFile;

int64_t completePart1()
{
	int64_t totalMass = 0;
	
	rewind(sFile);
	
	while (fgets(sStr, sizeof(sStr), sFile))
		totalMass += (strtoll(sStr, NULL, 10) / 3) - 2;
	
	return totalMass;
}

int64_t completePart2()
{
	int64_t mass, totalMass = 0;
	
	rewind(sFile);
	
	while (fgets(sStr, sizeof(sStr), sFile))
	{
		totalMass += mass = (strtoll(sStr, NULL, 10) / 3) - 2;
		
		for (;;)
		{
			mass = (mass / 3) - 2;
			if (mass < 0) break; // No more fuel required.
			totalMass += mass;
		}
	}
	
	return totalMass;
}

int main(int argc, char **argv)
{
	if ((sFile = fopen("input.txt", "r")) == 0)
	{
		perror("Error opening input.txt");
		return 1;
	}
	
	printf("Fuel required for part 1: %I64d\n", completePart1());
	printf("Fuel required for part 2: %I64d\n", completePart2());
	
	fclose(sFile);
	
	return 0;
}