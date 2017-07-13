#include <stdio.h>

int main(int argc, char const *argv[])
{
	int jour, mois, annee;

	printf("Tapez la date du jour\n");
	scanf("%d/%d/%d", &jour, &mois, &annee);
	printf("%d%d%d\n", jour, mois, annee);
	return 0;
}

