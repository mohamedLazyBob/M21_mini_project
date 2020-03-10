#include "mini_project.h"

void	ft_rental_management(void)
{
	int choice;

	while (1)
	{
		choice = print_rental_menu();
		if (choice == 1)		ft_visualizer_les_contrat();
		else if (choice == 2)	louer_une_voiture();
		else if (choice == 3)	retourner_une_voiture();
		else if (choice == 4)	modifier_une_contrat();
		else if (choice == 5)	sup_une_contrat();
		else if (choice == 6)	break ;
	}
}

int		print_rental_menu()
{
	int	choice;

	choice = 0;
	do
	{
//		system("clear");
		printf("\t\t -------------------------------\t\t\t\n");
		printf("\t\t|\tLocation d'une voiture\t\t|\n");
		printf("\t\t -------------------------------\t\t\t\n\n");
		printf("\t -------------------------------------------------------\t\t\t\n");
		printf("\t|\tVisualiser contrat..............................1\t\t|\n");
		printf("\t|\tlouer voiture...................................2\t\t|\n");
		printf("\t|\tRetourner voiture...............................3\t\t|\n");
		printf("\t|\tModifier contrat................................4\t\t|\n");
		printf("\t|\tsupprimer contrat...............................5\t\t|\n");
		printf("\t|\tretour..........................................6\t\t|\n");
		printf("\t -------------------------------------------------------\t\t\t\n");
		printf("\t\t votre choix  :  ");
		scanf("%d", &choice);
	} while (choice < 1 || choice > 6);
	return (choice);
}

//	float	numContrat;
//	int		idVoiture;
//	int		idClient;
//	int		cout;
//	date	debut;
//	date	fin;

/*
** **************************************************************************
*/

void	ft_visualizer_les_contrat()
{
	contrat	cntr;
	FILE	*file = fopen("ContratsLocations", "r");

	if (file == NULL)
	{
		printf("ERROR, couldn't open contract file\n");
		return ;
	}
	while (read_one_contrat(file, &cntr) != EOF)
	{
		printf("\nContrat num : %f.\n", cntr.numContrat);
		printf("idVoiture : %d\n", cntr.idClient);
		printf("cout : %d\n", cntr.cout);
		printf("debut : %.2d:00, %.2d/%.2d/%.4d\n", \
				cntr.debut.hh, cntr.debut.jour, cntr.debut.mois, cntr.debut.year);
		printf("fin : %d:00 %.2d/%.2d/%.4d\n", \
				cntr.fin.hh, cntr.fin.jour, cntr.fin.mois, cntr.fin.year);
		printf("____________________\n");
	}
	fclose(file);
}

int		read_one_contrat(FILE *file, contrat *cntr)
{
	int		ret;
	char	line[10];

	fscanf(file, "%s",    line);
	fscanf(file, "%f\n",  &(cntr->numContrat));
	fscanf(file, "%d\n",  &(cntr->idVoiture));
	fscanf(file, "%d\n",  &(cntr->idClient));
	fscanf(file, "%d\n",  &(cntr->cout));
	fscanf(file, "%d %d %d %d\n",   \
				&cntr->debut.hh, &cntr->debut.jour, &cntr->debut.mois, &cntr->debut.year);
	fscanf(file, "%d %d %d %d\n",   \
				&cntr->fin.hh, &cntr->fin.jour, &cntr->fin.mois, &cntr->fin.year);
	ret = fscanf(file, "%s", line);
	return (ret);
}



/*
** **************************************************************************
*/

void	louer_une_voiture()
{
	contrat	cntr;

	get_contrat_input(&cntr);
	//verify_this_contrat(cntr);
	add_this_contrat(cntr, "ContratsLocations");
}

void	get_contrat_input(contrat *cntr)
{
	printf("please write the information of this contrat:\n");
	printf("contrat number : "); 	scanf("%f", &(cntr->numContrat));
	printf("\nvoiture id : ");	 	scanf("%d",  &(cntr->idVoiture));
	printf("\nclient id");		 	scanf("%d",  &(cntr->idClient));
	printf("\ncout : ");			 scanf("%d",  &(cntr->cout));

	printf("\ndebut : ");
	scanf("%d %d %d %d",   \
		&cntr->debut.hh, &cntr->debut.jour, &cntr->debut.mois, &cntr->debut.year);
	printf("\nfin : ");
	scanf("%d %d %d %d",   \
		&cntr->fin.hh, &cntr->fin.jour, &cntr->fin.mois, &cntr->fin.year);
}

void	add_this_contrat(contrat cntr, char *filename)
{
	FILE	*file = fopen (filename, "a+");

	fprintf(file, "<<\n");
	fprintf(file, "%f\n", cntr.numContrat);
	fprintf(file, "%d\n", cntr.idVoiture);
	fprintf(file, "%d\n", cntr.idClient);
	fprintf(file, "%d\n", cntr.cout);
	fprintf(file, "%d %d %d %d\n", \
			cntr.debut.hh, cntr.debut.jour, cntr.debut.mois, cntr.debut.year);
	fprintf(file, "%d %d %d %d\n", \
			cntr.fin.hh, cntr.fin.jour, cntr.fin.mois, cntr.fin.year);
	fprintf(file, "/>>");
	fclose(file);
}

/*
** **************************************************************************
*/

void	retourner_une_voiture()
{
	int 	id;
	contrat	cntr;
	FILE	*file =  fopen("ContratsLocations", "r");

	printf("Donner l'id du contrat : ");
	scanf("%d", &id);

	while (read_one_contrat(file, &cntr) != EOF)
	{
		if (cntr.numContrat == id)
		{
			sup_cette_contrat(cntr);
			break;
		}
	}
	modifier_car_enLocation(cntr.idVoiture, "Non");
	fclose(file);
}

/*
** **************************************************************************
*/

void	modifier_une_contrat()
{
	FILE	*file = fopen("ContratsLocations", "r");
	float	contrat_id;
	int		choix;
	int		tmp;
	contrat	cntr;

	if (file == NULL)
		printf("A BIIIG FAT PROBLEM\n");
	get_contrat_modification(&contrat_id, &choix);

	while (1)
	{
		printf("you have choosed : %f. choix : %d\n", contrat_id, choix);
		tmp = read_one_contrat(file, &cntr);
		printf("cntr == %f\n", cntr.numContrat);
		if (tmp != EOF && contrat_id == cntr.numContrat)
		{
			fclose(file);
			if (choix >= 1 && choix <= 5)
			{
				sup_cette_contrat(cntr);
				printf("saisir la modification : ");
				if (choix == 1)
					scanf("%d", &cntr.idVoiture);
				else if (choix == 2)
					scanf("%d", &cntr.idClient);
				else if (choix == 3)
					scanf("%d", &cntr.cout);
				else if (choix == 4)
				{
					printf("\ndebut in this format hh dd/mm/yy : ");
					scanf("%d %d %d %d",   \
						&cntr.debut.hh, &cntr.debut.jour, \
						&cntr.debut.mois, &cntr.debut.year);
				}
				else if (choix == 5)
				{
					printf("\nfin in this format hh dd/mm/yy :  ");
					scanf("%d %d %d %d",   \
						&cntr.fin.hh, &cntr.fin.jour, \
						&cntr.fin.mois, &cntr.fin.year);
				}
				add_this_contrat(cntr, "ContratsLocations");
			}
			else
				printf("choix invalid\n");
			return ;
		}
		if (tmp == EOF)
			break ;
	}
	fclose(file);
}

void	get_contrat_modification(float *contrat_id, int *choix)
{
	printf("Donner l'id de le contrat tu veut modifer : ");
	scanf("%f", contrat_id);
	printf("que voulez-vous modifier?\n");
	printf("idVoiture...............1\n");
	printf("idClient................2\n");
	printf("cout....................3\n");
	printf("debut...................4\n");
	printf("fin.....................5\n");
	printf("votre choix :  ");	scanf("%d", choix);
}

//	float	numContrat;
//	int		idVoiture;
//	int		idClient;
//	int		cout;
//	date	debut;
//	date	fin;

/*
** **************************************************************************
*/

void	sup_une_contrat()
{

	//sup_cette_contrat(cntr);
}

void	sup_cette_contrat(contrat cntr)
{
	FILE	*ptr1, *ptr2;
	contrat	temp_cntr;
	int tmp;

	ptr1 = fopen("ContratsLocations", "r");
	ptr2 = fopen("cntr_replica.txt", "w");
	fclose(ptr2);

	while (1)
	{
		tmp = read_one_contrat(ptr1, &temp_cntr);
		if (tmp != EOF && temp_cntr.numContrat != cntr.numContrat)
			add_this_contrat(temp_cntr, "cntr_replica.txt");
		if (tmp == EOF)
			break ;
	}
	fclose(ptr1);
	remove("ContratsLocations");
	rename("cntr_replica.txt", "ContratsLocations");
}

/*
** **************************************************************************
*/
