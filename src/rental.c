#include "mini_project.h"

void	ft_rental_management(void)
{
	int choice;
	char buff[8][50] = {"Location   d'une   voiture", 
		"Visualiser contrat....................1", 
		"louer voiture.........................2", 
		"Retourner voiture.....................3", 
		"Modifier contrat......................4", 
		"supprimer contrat.....................5", 
		"retour................................6"};

	while (1)
	{
		choice = print_this_menu(buff, 7);
		if (choice == 0)
			system("clear");
		else if (choice == 1)	ft_visualizer_les_contrat();
		else if (choice == 2)	louer_une_voiture();
		else if (choice == 3)	retourner_une_voiture();
		else if (choice == 4)	modifier_une_contrat();
		else if (choice == 5)	sup_une_contrat();
		else if (choice == 6)	break ;
	}
}

/*
** **************************************************************************
*/

void	ft_visualizer_les_contrat()
{
	contrat	cntr;
	FILE	*file = fopen("ContratsLocations", "r");

	if (file == NULL)
	{
		file = fopen("ContratsLocations", "w");
		fclose(file);
		file = fopen("ContratsLocations", "r");
	}
	while (read_one_contrat(file, &cntr) != EOF)
		print_one_contrat(cntr);
	fclose(file);
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
	modifier_car_enLocation(cntr.idVoiture, "Yes");
}

void	get_contrat_input(contrat *cntr)
{
	printf("please write the information of this contrat : \n");
	printf("contrat number : "); 	scanf("%f", &(cntr->numContrat));
	printf("voiture id     : ");	scanf("%d",  &(cntr->idVoiture));
	printf("client id      : ");	scanf("%d",  &(cntr->idClient));
	printf("cout           : ");	scanf("%d",  &(cntr->cout));
	printf("le temp dans cette format : heure jour mois année \n");
	printf("debut          : ");	scanf("%d %d %d %d",   \
		&cntr->debut.hh, &cntr->debut.jour, &cntr->debut.mois, &cntr->debut.year);
	printf("fin            : ");	scanf("%d %d %d %d",   \
		&cntr->fin.hh, &cntr->fin.jour, &cntr->fin.mois, &cntr->fin.year);
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
			fclose(file);
			modifier_car_enLocation(cntr.idVoiture, "Non");
			del_one_contrat(cntr);
			return ;
		}
	}
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
	{
		printf("A BIIIG FAT PROBLEM\n");
		//exit(0);
	}
	get_contrat_modification(&contrat_id, &choix);
	printf("you have choosed\tid : %f. choix : %d\n", contrat_id, choix);

	while (1)
	{
		tmp = read_one_contrat(file, &cntr);
		if (tmp != EOF && contrat_id == cntr.numContrat)
		{
			fclose(file);
			if (choix >= 1 && choix <= 5)
			{
				del_one_contrat(cntr);
				printf("saisir la modification : ");
				if (choix == 1)			scanf("%d", &(cntr.idVoiture));
				else if (choix == 2)	scanf("%d", &(cntr.idClient));
				else if (choix == 3)	scanf("%d", &(cntr.cout));
				else if (choix == 4)
				{
					printf("\ndebut in this format hh dd/mm/yy : ");
					scanf("%d %d %d %d",   \
						&(cntr.debut.hh), &(cntr.debut.jour), \
						&(cntr.debut.mois), &(cntr.debut.year));
				}
				else if (choix == 5)
				{
					printf("\nfin in this format hh dd/mm/yy :  ");
					scanf("%d %d %d %d",   \
						&(cntr.fin.hh), &(cntr.fin.jour), \
						&(cntr.fin.mois), &(cntr.fin.year));
				}
				printf("going to add this contrat : \n");
				print_one_contrat(cntr);
				add_this_contrat(cntr, "ContratsLocations");
				return ;
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
	printf("\tque voulez-vous modifier?\n");
	printf("\tidVoiture...............1\n");
	printf("\tidClient................2\n");
	printf("\tcout....................3\n");
	printf("\tdebut...................4\n");
	printf("\tfin.....................5\n");
	printf("\t\tvotre choix :  ");	scanf("%d", choix);
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
	int		id;
	int		ret;
	voiture car;
	contrat	contrat;
	FILE	*cars = fopen("Voitures", "r");
	FILE	*file = fopen("ContratsLocations", "r");

	printf("donnez l'id du contrat que vous souhaitez supprimer : ");
	scanf("%d", &id);
	while (1)
	{
		ret = read_one_contrat(file, &contrat);	
		if (ret == EOF)
		{
			printf("this id doesn't exist.\n");
			return ;
		}
		if (contrat.idVoiture == id)
			break;
	}
	while (1)
	{
		read_one_car_info(cars, &car);
		if (car.idVoiture == contrat.idVoiture)
		{
			if (strcmp(car.EnLocation, "Non") == 0)
			{
				fclose(cars);
				fclose(file);
				del_one_contrat(contrat);
				return ;
			}
			else
			{
				printf("la voiture est louée.\n");
				break ;
			}
		}
	}
	fclose(cars);
	fclose(file);
}


/*
** **************************************************************************
**					main functions
*/

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
	fprintf(file, "/>>\n");
	fclose(file);
}

int		read_one_contrat(FILE *file, contrat *cntr)
{
	int		ret;
	char	line[10];
	//static int i;

	//printf("read i == %d;\n", i++);
	ret = fscanf(file, "%s\n",    line);
	if (ret == EOF)	return (ret);
	ret = fscanf(file, "%f\n",  &(cntr->numContrat));
	if (ret == EOF)	return (ret);
	ret = fscanf(file, "%d\n",  &(cntr->idVoiture));
	if (ret == EOF)	return (ret);
	ret = fscanf(file, "%d\n",  &(cntr->idClient));
	if (ret == EOF)	return (ret);
	ret = fscanf(file, "%d\n",  &(cntr->cout));
	if (ret == EOF)	return (ret);
	ret = fscanf(file, "%d %d %d %d\n",   \
				&cntr->debut.hh, &cntr->debut.jour, &cntr->debut.mois, &cntr->debut.year);
	if (ret == EOF)	return (ret);
	ret = fscanf(file, "%d %d %d %d\n",   \
				&cntr->fin.hh, &cntr->fin.jour, &cntr->fin.mois, &cntr->fin.year);
	if (ret == EOF)	return (ret);
	ret = fscanf(file, "%s\n", line);
	return (ret);
}

void	print_one_contrat(contrat contrat)
{
	printf(G_UL G_HORZ G_HORZ G_HORZ G_HORZ G_HORZ G_HORZ G_HORZ \
		G_HORZ G_HORZ  G_HORZ G_HORZ G_HORZ  G_HORZ G_HORZ G_HORZ G_UR ENDL);
	printf("%-30s Numéro de contrat : %4.4f %30s\n", \
		G_VERT, contrat.numContrat, G_VERT);
	printf(G_ML G_T_HORZ G_T_HORZ G_T_HORZ G_T_HORZ G_T_HORZ G_T_HORZ G_T_HORZ G_T_HORZ \
		G_T_HORZ  G_T_HORZ G_T_HORZ G_T_HORZ  G_T_HORZ G_T_HORZ G_T_HORZ G_MR ENDL);

	printf("%s Voiture ID : %-14.4d %s Debut    : %.2d:00, %.2d/%.2d/%.4d %s\n", \
		G_VERT, contrat.idVoiture, G_VERT, contrat.debut.hh, 
		contrat.debut.jour, contrat.debut.mois, contrat.debut.year, G_VERT);

	printf("%s Client ID  : %-14.4d %s Fin      : %.2d:00, %.2d/%.2d/%.4d %s\n", \
		G_VERT, contrat.idClient, G_VERT, contrat.fin.hh, \
		contrat.fin.jour, contrat.fin.mois, contrat.fin.year, G_VERT);
	printf("%s cout       : %.4d %24s %43s\n", \
		G_VERT, contrat.cout, G_VERT, G_VERT);
	printf(G_DL G_HORZ G_HORZ G_HORZ G_HORZ G_HORZ G_HORZ  G_HORZ G_HORZ \
		G_HORZ G_HORZ G_HORZ G_HORZ  G_HORZ G_HORZ G_HORZ G_DR ENDL);
}

void	del_one_contrat(contrat cntr)
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
		if (tmp == EOF)
			break ;
		if (tmp != EOF && temp_cntr.numContrat != cntr.numContrat)
			add_this_contrat(temp_cntr, "cntr_replica.txt");
	}
	fclose(ptr1);
	remove("ContratsLocations");
	rename("cntr_replica.txt", "ContratsLocations");
}


