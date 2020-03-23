#include "mini_project.h"


void	ft_clients_management(void)
{
	int choice;
	char str[100];
	char buff[][50] = {
		"    Gestion des Clients   ", 
		"List des clients......................1", 
		"Ajouter client........................2", 
		"Modifier client.......................3", 
		"Supprimer client......................4", 
		"retour................................5"};

	while (1)
	{
		system("clear");
		choice = print_this_menu(buff, 6);
		if (choice == 1)	list_all_clients();
		else if (choice == 2)	add_client();
		else if (choice == 3)	modify_client();
		else if (choice == 4)	del_client();
		else if (choice == 5)	break ;
		printf("saisir un chiffre pour revenir au menu precedent : ");
		scanf("%s", str);
	}
}


void	list_all_clients(void)
{
	FILE	*fileptr;
	int	ret;
	client	cl;

	if (!(fileptr = fopen("Clients", "r")))
	{
		printf("ERROR: Clients file doesn't exist.\n");
		return ;
	}
	while (read_one_client(&cl, fileptr) != EOF)
		print_one_client(cl);
	fclose(fileptr);
}

/*
**	**************************************************************************
*/

void	get_client_info(client *cl)
{
	printf("Saisir les informations du nouveau client : \n");
	printf("IdClient   : ");	scanf("%d", &cl->idClient);
	printf("Nom        : ");	scanf("%19s", cl->nom);
	printf("Prenom     : ");	scanf("%19s", cl->prenom);
	printf("Cin        : ");	scanf("%d", &cl->cin);
	printf("Adresse    : ");	scanf("%14s", cl->adresse);
	printf("Telephone  : ");	scanf("%d", &cl->telephone);
}

void	add_client(void)
{
	client	cl;

	get_client_info(&cl);
	add_this_client(cl, "Clients");
}

/*
** ***************************************************************************
*/

void	modify_client(void)
{
	FILE	*file;
	int	choix;
	int	ret;
	int	id;
	client	cl;

	if (!(file = fopen("Clients", "r")))
	{
		printf("ERROR: Clients file doesn't exist.\n");
		return ;
	}
	printf("Donner l'id du client : ");
	scanf("%d", &id);
	printf("\tQue voulez-vous modifier?\n");
	printf("\tNom................1\n");
	printf("\tPrenom.............2\n");
	printf("\tCin................3\n");
	printf("\tAdresse............4\n");
	printf("\tTelephone..........5\n");
	printf("\t\tvotre choix :  ");	scanf("%d", &choix);

	while (1)
	{
		ret = read_one_client(&cl, file);
		if (ret == EOF)
		{
			fclose(file);
			return;
		}
		if (cl.idClient == id)
		{
			fclose(file);
			if (choix >= 1 && choix <= 5)
			{
				del_this_client(cl.idClient);
				
				printf("saisir la modification : ");
				if (choix == 1)		scanf("%19s\n", cl.nom);
				else if (choix == 2)	scanf("%19s", cl.prenom);
				else if (choix == 3)	scanf("%d", &cl.cin);
				else if (choix == 4)	scanf("%14s", cl.adresse);
				else if (choix == 5)	scanf("%d", &cl.telephone);
				add_this_client(cl, "Clients");
			}
			else
				printf("choix invalid.\n");
			return ;
		}
	}
	fclose(file);
}

/*
** ***************************************************************************
*/

void	del_client(void)
{
	int	id;

	printf("Saisir l'id du contrat que vous souhaitez supprimer : ");
	scanf("%d", &id);
	del_this_client(id);
}

/*
** ***************************************************************************
*/

void	add_this_client(client cl, char *filename)
{
	FILE	*file;

	if (!(file = fopen(filename, "a+")))
	{
		file = fopen(filename, "w");
		fclose(file);
		file = fopen(filename, "a+");
	}
	fprintf(file, "<client>\n");	
	fprintf(file, "<idClient> %d </idClient>\n", cl.idClient);	
	fprintf(file, "<nom> %20.20s </nom>\n", cl.nom);	
	fprintf(file, "<prenom> %20.20s </prenom>\n", cl.prenom);	
	fprintf(file, "<cin> %d </cin>\n", cl.cin);	
	fprintf(file, "<adresse> %15.15s </adresse>\n", cl.adresse);	
	fprintf(file, "<telephone> %d </telephone>\n", cl.telephone);	
	fprintf(file, "</client>\n");
	fclose(file);
}

/*
** ***************************************************************************
*/

int	read_one_client(client *cl, FILE *file)
{
	char	line[10];
	int	ret;

	fscanf(file, "%s\n", line);
	fscanf(file, "<idClient> %d </idClient>\n", &(cl->idClient));	
	fscanf(file, "<nom> %20s </nom>\n", cl->nom);	
	fscanf(file, "<prenom> %20s </prenom>\n", cl->prenom);	
	fscanf(file, "<cin> %d </cin>\n", &(cl->cin));
	fscanf(file, "<adresse> %15s </adresse>\n", cl->adresse);	
	fscanf(file, "<telephone> %d </telephone>\n", &(cl->telephone));	
	ret = fscanf(file, "%s\n", line);
	return (ret);
}

/*
** ***************************************************************************
*/

void	del_this_client(int id)
{
	client	temp_client;
	FILE	*ptr1;
	FILE	*ptr2;
	int	tmp;

	if (!(ptr1 = fopen("Clients", "r")))
	{
		printf("ERROR: clients file doesn't exist.\n");
		return ;
	}
	ptr2 = fopen("clients_replica.txt", "w");
	fclose(ptr2);
	while (1)
	{
		tmp = read_one_client(&temp_client, ptr1);
		if (tmp == EOF)
			break;
		if (temp_client.idClient != id)
			add_this_client(temp_client, "clients_replica.txt");
	}
	fclose(ptr1);
	remove("Clients");
	rename("clients_replica.txt", "Clients");
}

/*
** ***************************************************************************
*/

void	print_one_client(client cl)
{
	printf(G_UL G_HORZ G_HORZ G_HORZ G_HORZ G_HORZ G_HORZ G_HORZ G_HORZ \
		G_HORZ G_HORZ G_HORZ \
		G_HORZ G_HORZ G_HORZ G_HORZ G_HORZ G_HORZ G_HORZ G_UR ENDL);
	printf("%-43s idClient  : %-13d %30s\n", G_VERT, cl.idClient, G_VERT);
	printf(G_ML G_T_HORZ G_T_HORZ G_T_HORZ G_T_HORZ G_T_HORZ G_T_HORZ \
		G_T_HORZ G_T_HORZ G_T_HORZ G_T_HORZ G_T_HORZ G_T_HORZ G_T_HORZ \
		G_T_HORZ G_T_HORZ G_T_HORZ G_T_HORZ G_T_HORZ G_MR ENDL);
	printf("%s nom       : %-20.20s %s cin       : %20d    %s\n", \
			G_VERT, cl.nom, G_VERT, cl.cin, G_VERT);
	printf("%s prenom    : %-20.20s %s telephone : %20.12d    %3s\n", \
			G_VERT, cl.prenom, G_VERT, cl.telephone, G_VERT);
	printf("%s adresse   : %-20.15s %s %50s\n", \
			G_VERT, cl.adresse, G_VERT, G_VERT);
	printf(G_DL G_HORZ G_HORZ G_HORZ G_HORZ G_HORZ G_HORZ G_HORZ \
		G_HORZ G_HORZ G_HORZ G_HORZ G_HORZ G_HORZ G_HORZ G_HORZ \
		G_HORZ G_HORZ G_HORZ G_DR ENDL);
}

/*
** ***************************************************************************
*/
