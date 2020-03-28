/******************************************************************************/
/*                              Mohamed zaboub                                */
/******************************************************************************/

#include "mini_project.h"

/*
** ****************************************************************************
**  the main function to take care of the cars.
*/

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

/*
** ****************************************************************************
** reads all clients from the file, and printing them to the user, 
** in a user friendlu matter.
*/

void	list_all_clients(void)
{
	FILE	*fileptr;
	int	ret;
	client	cl;

	if (!(fileptr = fopen(CLIENT_FILE, "r")))
	{
		printf("ERROR: Clients file doesn't exist.\n");
		return ;
	}
	system("clear");
	while (read_one_client(&cl, fileptr) != EOF)
		print_one_client(cl);
	fclose(fileptr);
}

/*
** ****************************************************************************
** those two funcs are for adding a new client
** the first one gets his information,"reading multiple words for all string"
** the 2nd funcs sums every thing and checking if the client id is duplicated
*/

void	add_client(void)
{
	client	cl;

	write (1, "\033[0;31m>> Ajouter un client.\033[0m\n", 40);
	get_client_info(&cl);
	if (true == ft_check_client(cl.idClient))
		printf("Client is duplicated, try another Id.\n");
	else
		add_this_client(cl, CLIENT_FILE);
}

static void	get_client_info(client *cl)
{
	char temp[10];
	printf("Saisir les informations du nouveau client : \n");
	printf("IdClient   : ");
	ft_read_buffer(temp, 10);
	cl->idClient = atoi(temp);
	printf("Nom        : ");
	ft_read_buffer(cl->nom, 20);
	printf("Prenom     : ");
	ft_read_buffer(cl->prenom, 20);
	printf("Cin        : ");
	ft_read_buffer(temp, 10);
	cl->cin = atoi(temp);
	printf("Adresse    : ");
	ft_read_buffer(cl->adresse, 15);
	printf("Telephone  : ");
	ft_read_buffer(temp, 10);
	cl->telephone = atoi(temp);
}

/*
** ****************************************************************************
**  this function check if the client is duplicated, using it's given id
**  if there is already a client with that spesific id return true 
**  else false
*/

bool	ft_check_client(int id)
{
	client	temp_client;
	FILE	*ptr1;
	int	tmp;

	if (!(ptr1 = fopen(CLIENT_FILE, "r")))
	{
		printf("ERROR: clients file doesn't exist.\n");
		return (false);
	}
	memset((void*)&temp_client, 0, sizeof(client));
	while (1)
	{
		tmp = read_one_client(&temp_client, ptr1);
		if (tmp == EOF)
			break;
		if (temp_client.idClient == id)
		{
			fclose(ptr1);
			return (true);
		}
	}
	fclose(ptr1);
	return (false);
}

/*
** ****************************************************************************
**  - prints the menu for modification.
**  - searches for the client.
**  - modify what the user wants.
**  - modiy the original file.
*/

void	modify_client(void)
{
	FILE	*file;
	int	choix;
	char	buff[10];
	int	ret;
	int	id;
	client	cl;

	write (1, "\033[0;31m>> Modifier un client.\033[0m\n", 40);
	if (!(file = fopen(CLIENT_FILE, "r")))
	{
		printf("ERROR: Clients file doesn't exist.\n");
		return ;
	}
	printf("Donner l'id du client : ");
	scanf("%d", &id);
	printf("Que voulez-vous modifier?\n");
	printf("\t1 -- Nom.\n");
	printf("\t2 -- Prenom.\n");
	printf("\t3 -- Cin.\n");
	printf("\t4 -- Adresse.\n");
	printf("\t5 -- Telephone.\n");
	printf("Votre choix :  ");
	scanf("%d", &choix);

	while (EOF != read_one_client(&cl, file))
		if (cl.idClient == id)
		{
			fclose(file);
			if (choix >= 1 && choix <= 5)
			{
				del_this_client(cl.idClient);
				printf("Saisir la modification : ");
				if (choix == 1)
					ft_read_buffer(cl.nom, 20);
				else if (choix == 2)
					ft_read_buffer(cl.prenom, 20);
				else if (choix == 3)
				{
					ft_read_buffer(buff, 10);
					cl.cin = atoi(buff);
				}
				else if (choix == 4)
					ft_read_buffer(cl.adresse, 15);
				else if (choix == 5)
				{
					ft_read_buffer(buff, 10);
					cl.telephone = atoi(buff);
				}
				add_this_client(cl, CLIENT_FILE);
			}
			else
				printf("choix invalid.\n");
			return ;
		}
	fclose(file);
}

/*
** ****************************************************************************
** deletes a client from the file.
*/

void	del_client(void)
{
	int	id;
	int	bol;

	write (1, "\033[0;31m>> supprimer un client.\033[0m\n", 40);
	printf("Saisir l'id du contrat que vous souhaitez supprimer : ");
	scanf("%d", &id);
	bol = del_this_client(id);
	if (bol == 1)
		printf("Client deleted succesfully!\n");
	else
		printf("Client Id isn't valid!\n");
}

/*
** ****************************************************************************
**		here the functions used to edit one client info starts.
** ****************************************************************************
** adds ONE Client to the file, (using xml tagges)
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
	fprintf(file, "\t<idClient> %d </idClient>\n", cl.idClient);	
	fprintf(file, "\t<nom> %s </nom>\n", cl.nom);	
	fprintf(file, "\t<prenom> %s </prenom>\n", cl.prenom);	
	fprintf(file, "\t<cin> %d </cin>\n", cl.cin);	
	fprintf(file, "\t<adresse> %s </adresse>\n", cl.adresse);	
	fprintf(file, "\t<telephone> %d </telephone>\n", cl.telephone);	
	fprintf(file, "</client>\n");
	fclose(file);
}

/*
** ----------------------------------------------------------------------------
** reads one client from the file, 
** just one client at every call to the function.
** the scanf delemeter is '<' 
** 	so that it can read the whole string (including the white spaces).
*/

int	read_one_client(client *cl, FILE *file)
{
	char	line[10];
	int	ret;

	fscanf(file, "%s\n", line);
	fscanf(file, "<idClient> %d </idClient>\n", &(cl->idClient));

	fscanf(file, "<nom> %[^<]s", cl->nom);
	fscanf(file, "</nom>\n");
	cl->nom[strlen(cl->nom) - 1] = 0;

	fscanf(file, "<prenom> %[^<]s", cl->prenom);
	fscanf(file, "</prenom>\n");
	cl->prenom[strlen(cl->prenom) - 1] = 0;

	fscanf(file, "<cin> %d </cin>\n", &(cl->cin));

	fscanf(file, "<adresse> %[^<]s", cl->adresse);
	fscanf(file, "</adresse>\n");
	cl->adresse[14] = 0;

	fscanf(file, "<telephone> %d </telephone>\n", &(cl->telephone));
	ret = fscanf(file, "%s\n", line);
	return (ret);
}

/*
** ----------------------------------------------------------------------------
** this deletes one client at a time.
** returning 1 if that went right, else -1 (id doesn't exist).
*/

int	del_this_client(int id)
{
	client	temp_client;
	FILE	*ptr1;
	FILE	*ptr2;
	int	tmp;
	int	found = -1;

	if (!(ptr1 = fopen(CLIENT_FILE, "r")))
	{
		printf("ERROR: clients file doesn't exist.\n");
		return (found);
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
		if (temp_client.idClient == id)
			found = 1;
	}
	fclose(ptr1);
	remove(CLIENT_FILE);
	rename("clients_replica.txt", CLIENT_FILE);
	return (found);
}

/*
** ----------------------------------------------------------------------------
** this prints one client at each time we call it with it's information
** with some unicode characters, so that the table is representative.
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
** ****************************************************************************
** 				THE END
*/
