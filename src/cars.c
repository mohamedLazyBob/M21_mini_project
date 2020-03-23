#include "mini_project.h"

/*
** ****************************************************************************
*/

void	ft_cars_management(void)
{
	int	choice;
	char	str[100];

	char buff[6][50] = {"    Gestion des voiture   ", 
		"List des voitures.....................1", 
		"Ajouter voiture.......................2", 
		"Modifier voiture......................3", 
		"supprimer voiture.....................4", 
		"retour................................5"};
	while (1)
	{
		system("clear");
		choice = print_this_menu(buff, 6);
		if (choice == 1)	ft_list_cars();
		else if (choice == 2)	ft_add_car();
		else if(choice == 3)	ft_modify_car_info();
		else if(choice == 4)	ft_delete_car();
		else if(choice == 5)	break ;
		printf("saisir un chiffre pour revenir au menu precedent : ");
		scanf("%s", str);// this just a trick to free the input buffer
	}
}

/*
** ****************************************************************************
*/

void	ft_list_cars(void)
{
	int	ret;
	voiture	car;
	FILE	*file;
	char	line[5];

	if (!(file = fopen("Voitures", "r")))
	{
		printf("ERROR couldn't open Voitures file\n");
		return ;
	}
	while ((ret = read_one_car_info(file, &car)) != EOF)
		print_one_car(car);
	fclose(file);
}

/*
** ****************************************************************************
*/

void	print_one_car(voiture car)
{
	printf(G_UL G_HORZ G_HORZ G_HORZ G_HORZ G_HORZ G_HORZ G_HORZ G_HORZ \
		G_HORZ G_HORZ G_HORZ G_HORZ G_HORZ G_HORZ G_HORZ G_UR ENDL);
	printf("%s                        idVoiture: %.3d                      %s\n", \
		G_VERT, car.idVoiture, G_VERT);

	printf(G_ML G_T_HORZ G_T_HORZ G_T_HORZ G_T_HORZ G_T_HORZ G_T_HORZ G_T_HORZ G_T_HORZ \
		G_T_HORZ G_T_HORZ G_T_HORZ G_T_HORZ G_T_HORZ G_T_HORZ G_T_HORZ G_MR ENDL);

	printf("%s nomVoiture: %-15.15s  %s marque    : %-15.15s %s\n", \
		G_VERT, car.nomVoiture, G_VERT, car.marque, G_VERT);
	printf("%s nbplaces: %-16.2d   %s couleur : %-7.7s           %s\n", \
		G_VERT, car.nbplaces, G_VERT, car.couleur, G_VERT);
	printf("%s prixJour: %-17.3d  %s EnLocation : %-4.3s           %s\n", \
		G_VERT, car.prixJour, G_VERT, car.EnLocation, G_VERT);

	printf(G_DL G_HORZ G_HORZ G_HORZ G_HORZ G_HORZ G_HORZ G_HORZ G_HORZ \
		G_HORZ G_HORZ G_HORZ G_HORZ G_HORZ G_HORZ G_HORZ G_DR ENDL);
}

/*
** ***************************************************************************
** this function reads from the data/file one car information at every call
*/

int		read_one_car_info(FILE *file, voiture *car)
{
	char	line[10];
	int	ret;

	fscanf(file, "%s\n", line);

	fscanf(file, "<nomVoiture> %s </nomVoiture>\n", car->nomVoiture);
	fscanf(file, "<idVoiture> %d </idVoiture>\n",  &(car->idVoiture));
	fscanf(file, "<nbplaces> %d </nbplaces>\n",   &(car->nbplaces));
	fscanf(file, "<prixJour> %d </prixJour>\n",   &(car->prixJour));
	fscanf(file, "<marque> %s </marque>\n",     car->marque);
	fscanf(file, "<couleur> %s </couleur>\n",    car->couleur);
	fscanf(file, "<enLocation> %s </enLocation>\n", car->EnLocation);

	ret = fscanf(file, "%s", line);
	return (ret);
}

/*
** ****************************************************************************
*/

void	get_car_input(voiture *car)
{
	printf("Saisir les informations de la nouvelle voiture:\n");
	printf("\tnomVoiture  : "); scanf("%15s", car->nomVoiture);
	printf("\tidVoiture   : "); scanf("%d", &(car->idVoiture));
	printf("\tmarque      : "); scanf("%15s", car->marque);
	printf("\tnbplaces    : "); scanf("%d", &(car->nbplaces));
	printf("\tcouleur     : "); scanf("%7s", car->couleur);
	printf("\tprixJour    : "); scanf("%d", &(car->prixJour));
	strcpy(car->EnLocation, "Non"); 
}

void	ft_add_car(void)
{
	voiture car;

	get_car_input(&car);
	ft_add_this_car(car, "Voitures");
}

/*
** ****************************************************************************
*/

void	ft_add_this_car(voiture car, char *filename)
{
	FILE *ptr;

	if (!(ptr = fopen(filename, "a+")))
	{
		ptr = fopen(filename, "w");
		fclose(ptr);
		ptr = fopen(filename, "a+");
	}
	fprintf(ptr, "<car>\n");
	fprintf(ptr, "<nomVoiture> %.15s </nomVoiture>\n", car.nomVoiture);
	fprintf(ptr, "<idVoiture> %d </idVoiture>\n",  car.idVoiture);
	fprintf(ptr, "<nbplaces> %d </nbplaces>\n",   car.nbplaces);
	fprintf(ptr, "<prixJour> %d </prixJour>\n",   car.prixJour);
	fprintf(ptr, "<marque> %.15s </marque>\n",     car.marque);
	fprintf(ptr, "<couleur> %.7s </couleur>\n",    car.couleur);
	fprintf(ptr, "<enLocation> %.4s </enLocation>\n", car.EnLocation);
	fprintf(ptr, "</car>\n");
	fclose(ptr);
}

/*
** ****************************************************************************
*/

void	ft_modify_car_info(void)
{
	char	input_str[20];
	int	input_nbr;
	int	choice;
	FILE	*file;
	int	num;
	voiture car;
	int	ret;
	int	id;

	if (!(file = fopen("Voitures", "r")))
	{
		printf("Voitures file Doesn't exist.\n");
		return ;
	}
	print_modify_menu(&id, &choice, &input_nbr, input_str);
	while ((ret = read_one_car_info(file, &car)) != EOF)
	{
		if (car.idVoiture == id)
		{
			fclose(file);
			delete_this_car(car);
			if(choice == 1)		car.nbplaces = input_nbr;
			else if (choice == 2)	car.prixJour = input_nbr;
			else if (choice == 3)	car.idVoiture = input_nbr;
			else if (choice == 4)	strncpy(car.marque, input_str, 15);
			else if (choice == 5) 	strncpy(car.couleur, input_str, 7);
			else if (choice == 6)	strncpy(car.nomVoiture, input_str, 15);
			else if (choice == 7)
			{
				if ((strcmp(input_str, "non") == 0) || \
					(strcmp(input_str, "NON") == 0) || \
					(strcmp(input_str, "NO") == 0) || \
					(strcmp(input_str, "no") == 0) || \
					(strcmp(input_str, "Non") == 0))
					strcpy(car.EnLocation, "Non");
				else
					strcpy(car.EnLocation, "Oui");
			}
			file = fopen("Voitures", "a+");
			ft_add_this_car(car, "Voitures");
			break;
		}
	}
	fclose(file);
}

/*
** ****************************************************************************
*/

int	print_modify_menu(int *id, int *choice, int *nbr, char *str)
{
	write (1, "\033[0;31m>> Modifier une voiture.\033[0m\n", 40);
	printf("L'id de la voiture que vous souhaitez modifier : ");
	scanf("%d", id);
	while (1)
	{
		printf("Choisir l'attribut que vous souhaitez modifier :\n");
		printf("\tNbplaces:.........1\n");
		printf("\tPrixJour:.........2\n");
		printf("\tIdVoiture:........3\n");
		printf("\tMarque:...........4\n");
		printf("\tCouleur:..........5\n");
		printf("\tNomVoiture:.......6\n");
		printf("\tEnLocation:.......7\n");
		scanf("%d", choice);
		if (*choice > 0 && *choice < 4)
		{
			printf("saisir la modification: ");
			scanf("%d", nbr);
			return (0);
		}
		else if (*choice > 3 && *choice < 8)
		{
			printf("saisir la modification: ");
			scanf("%20s", str);
			return (1);
		}
	}
}

/*
** ****************************************************************************
*/

void	ft_delete_car(void)
{
	FILE	*file;
	voiture car;
	int	ret;
	int	id;

	if (!(file = fopen("Voitures", "r")))
	{
		printf("ERROR: Voiture file Doesn't exist.\n");
		return ;
	}
	printf("Donner l'id de la voiture tu veut supprimer : ");
	scanf("%d", &id);
	while ((ret = read_one_car_info(file, &car)) != EOF)
	{
		if (car.idVoiture == id)
		{
			fclose(file);
			delete_this_car(car);
			return ;
		}
	}
	fclose(file);
	return ;
}


/*
** ****************************************************************************
*/

void	delete_this_car(voiture car)
{
	FILE	*fileptr1;
	FILE	*fileptr2;
	voiture	temp_car;
	int	end;

	if (!(fileptr1 = fopen("Voitures", "r")))
	{
		printf("ERROR: Voiture file Doesn't exist.\n");
		return ;
	}
	fileptr2 = fopen("replica.txt", "w");
	fclose(fileptr2);
	while (1)
	{
		end = read_one_car_info(fileptr1, &temp_car);
		if (end == EOF)
			break;
		if (temp_car.idVoiture != car.idVoiture)
			ft_add_this_car(temp_car, "replica.txt");
	}
	fclose(fileptr1);
	remove("Voitures");
	rename("replica.txt", "Voitures");
	return ;
}

/*
** ****************************************************************************
*/

void	modifier_car_enLocation(int id, char *str)
{
	FILE	*file;
	voiture	car;

	if (!(file = fopen("Voitures", "r")))
	{
		printf("ERROR: Voiture file Doesn't exist.\n");
		return ;
	}
	while (read_one_car_info(file, &car) != EOF)
	{
		if (car.idVoiture == id)
		{
			fclose(file);
			delete_this_car(car);
			strcpy(car.EnLocation, str);
			ft_add_this_car(car, "Voitures");
			return ;
		}
	}
	fclose(file);
}

/*
** ****************************************************************************
*/
