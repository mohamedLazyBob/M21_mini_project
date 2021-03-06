/******************************************************************************/
/*                              Mohamed zaboub                                */
/******************************************************************************/

#include "mini_project.h"

/*
** ****************************************************************************
**  main menu/function for contralocation
*/

void	ft_rental_management(void)
{
	int choice;
	char buff[7][50] = {"Location   d'une   voiture", 
		"Visualiser contrat....................1", 
		"louer voiture.........................2", 
		"Retourner voiture.....................3", 
		"Modifier contrat......................4", 
		"supprimer contrat.....................5", 
		"retour................................6"};

	while (1)
	{
		system("clear");
		choice = print_this_menu(buff, 7);
		if (choice == 1)	ft_visualizer_les_contrat();
		else if (choice == 2)	louer_une_voiture();
		else if (choice == 3)	retourner_une_voiture();
		else if (choice == 4)	modifier_une_contrat();
		else if (choice == 5)	sup_une_contrat();
		else if (choice == 6)	break ;
		printf("saisir un chiffre pour revenir au menu precedent : ");
		scanf("%d", &choice);
	}
}

/*
** **************************************************************************
** calls the propre functions to read and print one clien, 
** tell that prints all the contras.
*/

void	ft_visualizer_les_contrat(void)
{
	FILE	*file;
	contrat	cntr;

	if (!(file = fopen(CONTRA_FILE, "r")))
	{
		file = fopen(CONTRA_FILE, "w");
		fclose(file);
		file = fopen(CONTRA_FILE, "r");
	}
	system("clear");
	while (read_one_contrat(file, &cntr) != EOF)
		print_one_contrat(cntr);
	fclose(file);
}

/*
** ****************************************************************************
** get the new infos from the user, validate them, then adding them to the file
*/

void	louer_une_voiture(void)
{
	contrat	cntr;

	get_contrat_input(&cntr);
	if (verify_this_contrat(cntr) == -1)
		return ;
	add_this_contrat(cntr, CONTRA_FILE);
	modifier_car_enLocation(cntr.idVoiture, "Oui");
}

void	get_contrat_input(contrat *cntr)
{
	printf("S'il vous plait saisir les informatios sur le contrat : \n");
	printf("contrat number : "); 	scanf("%f", &(cntr->numContrat));
	printf("voiture id     : ");	scanf("%d",  &(cntr->idVoiture));
	printf("client id      : ");	scanf("%d",  &(cntr->idClient));
	printf("cout           : ");	scanf("%d",  &(cntr->cout));
	printf("le temp dans cette format : heure jour mois année \n");
	printf("debut          : ");	scanf("%d %d %d %d",   \
		&cntr->debut.hh, &cntr->debut.jour, \
		&cntr->debut.mois, &cntr->debut.year);
	printf("fin            : ");	scanf("%d %d %d %d",   \
		&cntr->fin.hh, &cntr->fin.jour, \
		&cntr->fin.mois, &cntr->fin.year);
}

/*
** ****************************************************************************
** verify the new contrat information.
** if there is a client/car with that data
*/

int	verify_this_contrat(contrat cntr)
{
	FILE	*ptr = NULL;
	voiture	car_var = {};
	client	client_var = {};
	int 	end = 0;
	
	if (!(ptr = fopen(CARS_FILE, "r")))
	{
		printf("ERROR: while opening voitures file.\n");
		return (-1);
	}
	car_var.idVoiture = -1;
	while (1)
	{
		// searching for the car information in file.
		end = read_one_car_info(ptr, &car_var);
		if (end == EOF || cntr.idVoiture == car_var.idVoiture)
			break;
	}
	if (cntr.idVoiture != car_var.idVoiture)
	{
		//there no car with that id
		printf("ERROR : there is no car with this Id.\n");
		return (-1);
	}
	else if ((cntr.idVoiture == car_var.idVoiture) && \
			(strcmp(car_var.EnLocation, "Non") != 0))
	{
		//check if car is already rented
		printf("ERROR : the car is already rented.\n");
		return (-1);
	}
	fclose(ptr);

	//check if the client id is valid
	if (!(ptr = fopen(CLIENT_FILE, "r")))
	{
		printf("ERROR while opening Clients file.\n");
		return (-1);
	}
	client_var.idClient = -1;
	while (1)
	{
		// searching for the client total info;
		end = read_one_client(&client_var, ptr);
		if (end == EOF || client_var.idClient == cntr.idClient)
			break ;
	}
	if (client_var.idClient != cntr.idClient)
	{
		// couldn't find the client in our data;
		printf("ERROR : No such client id.\n");
		return (-1);
	}
// check the contrat id here.
	return (1);
}

/*
** ****************************************************************************
**  gets the id of contrat thats going to be ended.
**  delete id, and change the car back to be on for location.
*/

void	retourner_une_voiture(void)
{
	FILE	*file;
	contrat	cntr;
	int 	id;

	if (!(file = fopen(CONTRA_FILE, "r")))
	{
		printf("ERROR : contratsLocations file Doesn't exist.\n");
		return ;
	}
	printf("Donner l'id du contrat : ");
	scanf("%d", &id);

	while (read_one_contrat(file, &cntr) != EOF)
	{
		if (cntr.numContrat == id)
		{
			fclose(file);
			modifier_car_enLocation(cntr.idVoiture, "Non");
			del_this_contrat(cntr.numContrat);
			return ;
		}
	}
	fclose(file);
}

/*
** ****************************************************************************
** just the same as all the other contras.
*/

void	modifier_une_contrat(void)
{
	float	contrat_id;
	FILE	*file;
	int	choix;
	contrat	cntr;

	write (1, "\033[0;31m>> Modifier une Contras.\033[0m\n", 40);
	if (!(file = fopen(CONTRA_FILE, "r")))
	{
		printf("ContrasLocation file doesn't exist.\n");
		return ;
	}
	get_contrat_modification(&contrat_id, &choix);
	while (EOF != read_one_contrat(file, &cntr))
	{
		if ((contrat_id == cntr.numContrat) && \
			(choix >= 1 && choix <= 5))
		{
			fclose(file);
			del_this_contrat(cntr.numContrat);
			printf("saisir la modification : ");
			if (choix == 1)
				scanf("%d", &(cntr.idVoiture));
			else if (choix == 2)
				scanf("%d", &(cntr.idClient));
			else if (choix == 3)
				scanf("%d", &(cntr.cout));
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
			add_this_contrat(cntr, CONTRA_FILE);
			return ;
		}
		else if (contrat_id == cntr.numContrat)
		{
			printf("Choix invalid.\n");
			return ;
		}
	}
	fclose(file);
}

void	get_contrat_modification(float *contrat_id, int *choix)
{
	printf("Donner l'id de le contrat tu veut modifer : ");
	scanf("%f", contrat_id);
	printf("Que voulez-vous modifier?\n");
	printf("\t1 -- IdVoiture.\n");
	printf("\t2 -- IdClient.\n");
	printf("\t3 -- Cout.\n");
	printf("\t4 -- Date de debut.\n");
	printf("\t5 -- Date de fin.\n");
	printf("votre choix :  ");
	scanf("%d", choix);
}

/*
** ****************************************************************************
** askes the user for the contrat id,
**  and if car in it isn't rented, we delete it.
*/

void	sup_une_contrat(void)
{
	contrat		contrat;
	FILE		*file;
	FILE		*cars;
	voiture		car;
	int		id;

	cars = fopen(CARS_FILE, "r");
	file = fopen(CONTRA_FILE, "r");
	if (!cars || !file)
	{
		if (file)
			fclose(file);
		if (cars)
			fclose(cars);
		printf("ERROR : file Doesn't exist.\n");
		return ;
	}
	printf("Donnez le nome du contrat que vous souhaitez supprimer : ");
	scanf("%d", &id);
	while (1)
	{
		// validating the given conract id
		if (EOF == read_one_contrat(file, &contrat))
		{
			// we've reached the end of file without finding the id
			printf("this Contrat Doesn't exist.\n");
			fclose(cars);
			fclose(file);
			return ;
		}
		if (contrat.numContrat == id)
			break;
	}
	// checking if the car in not located
	while (1)
	{
		read_one_car_info(cars, &car);
		if (car.idVoiture == contrat.idVoiture)
		{
			if (strcmp(car.EnLocation, "Non") == 0)
			{
				fclose(cars);
				fclose(file);
				del_this_contrat(contrat.numContrat);
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
** ****************************************************************************
** ****************************************************************************
**		main functions: their names are expressive.
*/

void	add_this_contrat(contrat cntr, char *filename)
{
	FILE	*file;

	if (!(file = fopen (filename, "a+")))
	{
		file = fopen(filename, "w");
		fclose(file);
		file = fopen(filename, "a+");
	}
	fprintf(file, "<contart>\n");

	fprintf(file, "\t<numcontrat> %f </numcontrat>\n", cntr.numContrat);
	fprintf(file, "\t<idVoiture> %d </idVoiture>\n", cntr.idVoiture);
	fprintf(file, "\t<idClient> %d </idClient>\n", cntr.idClient);
	fprintf(file, "\t<cout> %d </cout>\n", cntr.cout);

	fprintf(file, "\t<date_debut>\n");
	fprintf(file, "\t\t<hh> %d </hh>\n", 	 cntr.debut.hh);
	fprintf(file, "\t\t<jour> %d </jour>\n", cntr.debut.jour);
	fprintf(file, "\t\t<mois> %d </mois>\n", cntr.debut.mois);
	fprintf(file, "\t\t<year> %d </year>\n", cntr.debut.year);
	fprintf(file, "\t</date_debut>\n");

	fprintf(file, "\t<date_fin>\n");
	fprintf(file, "\t\t<hh> %d </hh>\n",     cntr.fin.hh);
	fprintf(file, "\t\t<jour> %d </jour>\n", cntr.fin.jour);
	fprintf(file, "\t\t<mois> %d </mois>\n", cntr.fin.mois);
	fprintf(file, "\t\t<year> %d </year>\n", cntr.fin.year);
	fprintf(file, "\t</date_fin>\n");

	fprintf(file, "</contrat>\n");
	fclose(file);
}

/*
** ---------------------------------------------------------------------------- 
** reads one contrat from the file, that is already open.
*/

int	read_one_contrat(FILE *file, contrat *cntr)
{
	int	ret;
	char	line[20];

	fscanf(file, "%s\n",    line);

	fscanf(file, "<numcontrat> %f </numcontrat>\n", &(cntr->numContrat));
	fscanf(file, "<idVoiture> %d </idVoiture>\n",   &(cntr->idVoiture));
	fscanf(file, "<idClient> %d </idClient>\n", 	&(cntr->idClient));
	fscanf(file, "<cout> %d </cout>\n", 		&(cntr->cout));

	fscanf(file, "%s\n", line);
	fscanf(file, "<hh> %d </hh>\n",		&(cntr->debut.hh));
	fscanf(file, "<jour> %d </jour>\n",	&(cntr->debut.jour));
	fscanf(file, "<mois> %d </mois>\n",	&(cntr->debut.mois));
	fscanf(file, "<year> %d </year>\n",	&(cntr->debut.year));
	fscanf(file, "%s\n", line);

	fscanf(file, "%s\n", line);
	fscanf(file, "<hh> %d </hh>\n",		&(cntr->fin.hh));
	fscanf(file, "<jour> %d </jour>\n",	&(cntr->fin.jour));
	fscanf(file, "<mois> %d </mois>\n",	&(cntr->fin.mois));
	fscanf(file, "<year> %d </year>\n",	&(cntr->fin.year));
	fscanf(file, "%s\n", line);

	ret = fscanf(file, "%s\n", line);
	return (ret);
}

/*
** ---------------------------------------------------------------------------- 
** prints the the one contrat that had been sent to it.
*/

void	print_one_contrat(contrat contrat)
{
	printf(G_UL G_HORZ G_HORZ G_HORZ G_HORZ G_HORZ G_HORZ G_HORZ \
		G_HORZ G_HORZ  G_HORZ G_HORZ G_HORZ  G_HORZ G_HORZ G_HORZ \
		G_UR ENDL);
	printf("%-30s Numéro de contrat : %4.4f %30s\n", \
		G_VERT, contrat.numContrat, G_VERT);
	printf(G_ML G_T_HORZ G_T_HORZ G_T_HORZ G_T_HORZ G_T_HORZ \
		G_T_HORZ G_T_HORZ G_T_HORZ G_T_HORZ  G_T_HORZ G_T_HORZ \
		G_T_HORZ  G_T_HORZ G_T_HORZ G_T_HORZ G_MR ENDL);

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

/*
** ---------------------------------------------------------------------------- 
**  Delets the contrat that it receives as argument.
*/

void	del_this_contrat(int idContrat)
{
	contrat	temp_cntr;
	FILE	*ptr1;
	FILE	*ptr2;

	if (!(ptr1 = fopen(CONTRA_FILE, "r")))
	{
		printf("ERROR: ContrasLocations file Doesn't exist.\n");
		return ;
	}
	ptr2 = fopen("cntr_replica.txt", "w");
	fclose(ptr2);
	while (1)
	{
		if (read_one_contrat(ptr1, &temp_cntr) == EOF)
			break ;
		if (temp_cntr.numContrat != idContrat)
			add_this_contrat(temp_cntr, "cntr_replica.txt");
	}
	fclose(ptr1);
	remove(CONTRA_FILE);
	rename("cntr_replica.txt", CONTRA_FILE);
}

/*
** ****************************************************************************
*/
