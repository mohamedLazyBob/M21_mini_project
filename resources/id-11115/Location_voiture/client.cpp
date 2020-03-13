#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"structure.h"
#include"prototype.h"



//************************************************************
//**	Fonction  : RetourTete								**
//**	Parametre : liste de client							**
//**	Traitement: Elle retourne le pointeur de la liste	**
//**				à la tete depuis sa position			**
//**	Retourne  : La liste de client						**
//************************************************************

cellule_client* RetourTete(cellule_client *t)
{
	if(t!=NULL)	///***Si la liste n'est pas vide

		while(t->precedent!=NULL) //***Tant que la tete n'est pas ateinte***
			t=t->precedent;

	return t;
}



//********************************************************
//**	Fonction  : Saisie d'un client					**
//**	Parametre : pas de parametre					**
//**	Traitement: Saisie des champs d'un client		**
//**	Retourne  : Cellule client apres initialitation **
//********************************************************

liste_client SaisieClient()
{
	client *clt;	//***pointeut sur structure client a saisir***
    liste_client retour;	//***Cellule client a retourner***

	EnTete();
	
	retour=(cellule_client *)malloc(sizeof cellule_client);
	clt=(client *)malloc(sizeof client);

//****SAISIE DU CLIENT*****
	
	printf("\nSaisie personne........");
	
	printf("\n\t\tNom           : ");
	scanf("%s",&clt->nom);
	
	printf("\n\t\tPrenom        : ");
	scanf("%s",&clt->prenom);
	
	printf("\n\t\tAge           : ");
	scanf("%d",&clt->age);
	
	printf("\n\tAdresse...");
	
	printf("\n\t\tNumero        : ");
	scanf("%d",&clt->num);
	
	printf("\n\t\tRue           : ");
	scanf("%s",&clt->rue);
	
	printf("\n\t\tVille         : ");
	scanf("%s",&clt->ville);
	
	printf("\n\t\tCode postal   : ");
	scanf("%d",&clt->cpostal);

	printf("\n\t\tN° telephone  : ");
	scanf("%d",&clt->telephone);
	
	printf("\n\t\tNum. CIN      : ");
	scanf("%d",&clt->cin);
	
	printf("\n\t\tDate permis (jjmmaaaa)  : ");
	scanf("%d",&clt->date_permi);
	
	printf("\n\t\tTravail       : ");
	scanf("%s",&clt->travail);

	clt->ctr=0;		//*****LE NUMERO DU CONTRAT EST MIS A 0 JUSQU'A SAISIE DU CONTRAT RELATIF

	///****INITIALISATION DE LA CELLULE CLIENT****
	retour->person=*clt;
	retour->suivant=NULL;
	retour->precedent=NULL;

	return retour;
}





//********************************************************
//**	Fonction  : Rechercher un client				**
//**	Parametre : Liste de client "pour y rechercher  **
//**				nom et prenom du client rechercher	**
//**	Traitement: Comparer le nom et prenom avec ceux **
//**				des clinet existant					**
//**	Retourne  : NULL si le client n'est pas trouver **
//**				La cellule du client si existant	**
//**    Utilise   : La fonction RetourTete qui prend    **
//**                comme parametre la liste de client  **
//********************************************************       

liste_client RechercheClient(liste_client l,char *nom,char *pnom)
{

	l=RetourTete(l);

	
	while(l!=NULL)//***si la liste n'est pas vide
		{
			if(strcmp(l->person.nom,nom)==0)
				if(strcmp(l->person.prenom,pnom)==0)
					return l;
			
			l=l->suivant;
		}

 	return NULL;

}




//********************************************************
//**    Fonction  : Modifier un client                  **
//**    Parametre : Liste de client                     **
//**    Traitement: Modifie un client s'il existe       **      
//**    Retourne  : Liste de client                     **
//**    Utilise   : RetourTete,RechercheClient          **
//**                et SaisieClient                     **
//********************************************************

liste_client modifierClient(liste_client l)
{
	liste_client modif;
	cellule_client *save;
	char nom[20],pnom[20];
	
	l=RetourTete(l);

	if(l==NULL)
		MessageUrgence("Pas de client");
	else
	{
		printf("\n\t\tNom    ( \x22 exit \x22 pour annuler) :  ");
		scanf("%s",&nom);
		if(strcmp(nom,"exit")!=0)
		{
			printf("\n\t\tPrenom ( \x22 exit \x22 pour annuler) :  ");
			scanf("%s",&pnom);
		}
		
		if((strcmp(pnom,"exit")!=0)&&(strcmp(nom,"exit")!=0))
		{
			modif=RechercheClient(l,nom,pnom);

			if(modif==NULL)
				MessageUrgence("Client non trouve");
			else
			{
				save=modif;
				modif=SaisieClient();
				save->person=modif->person;
				MessageUrgence("Client modifie");
			}
		}
	}

	return l;
}



//************************************************************
//**    Fonction  : Supprimer un Client						**
//**    Parametre : Liste de client							**
//**    Traitement: elle supprime un client à partir de		**
//**                sa position								**
//**    Retourne  :	La liste apres suppression si effectuer **
//**	Utilise   : RetourTete								**
//**			    RechercheClient "pour trouver le client **
//************************************************************


liste_client supprimerClient(liste_client l)
{
	cellule_client *supp;
	char nom[20],pnom[20];


	
	if(l==NULL)//*** si la liste est vide
		MessageUrgence("Pas de client");
	else
	{
		printf("\n\t\tNom    :  ");
		scanf("%s",&nom);
		if(strcmp(nom,"exit")!=0)
		{
			printf("\n\t\tPrenom :  ");
			scanf("%s",&pnom);
		}
		
			l=RetourTete(l);
			supp=RechercheClient(l,nom,pnom);
			if(supp!=NULL)
			{
				if(supp==l)		//*******SUPPRIMER TETE**********
				{
					l=l->suivant;
					
					free(supp);
					MessageUrgence("Client supprime");
					return l;
				}

				else
					if(supp->suivant==NULL)
					{
						supp->precedent->suivant=NULL;
				//		free(supp);
						MessageUrgence("Client supprime");
						return l;
						
					}
					else
					{
						supp->precedent->suivant=supp->suivant;
						supp->suivant->precedent=supp->precedent;
						free(supp);
						MessageUrgence("Client supprime");
						return l;
					}
			}
			else
				MessageUrgence("Client non trouve");
	
	}
	
	return l;

}



//************************************************************
//**    Procedure : Afichage d'un client                    **
//**    Parametre : la structure client                     **
//**    Traitement: c'est une procedure qui affiche         **  
//**                un client                               ** 
//************************************************************

void AfficheClient(client cl)
{
	EnTete();

	printf("\n\tNom          : %s",cl.nom);
	printf("\t\tPrenom         : %s",cl.prenom);

	printf("\n\n\tAge          : %d",cl.age);
	printf("\t\tCIN          : %d",cl.cin);

	printf("\n\n\tDate permis  : %d/%d/%d",cl.date_permi/10000,(cl.date_permi%10000)/100,(cl.date_permi%10000)%100);
	printf("\t\tNum telephone: %d",cl.telephone);

	printf("\n\n\tTravail      : %s",cl.travail);
	
	printf("\n\n\tAdresse...");

	printf("\n\n\tNum          : %d",cl.num);
	printf("\t\tRue          : %s",cl.rue);

	printf("\n\n\tVille        : %s",cl.ville);
	printf("\t\tCode postal  : %d",cl.cpostal);

	printf("\n\n\n");

	system("pause");
}




//**********************************************************
//**    Fonction  : Inserer un client a la fin de liste   **
//**    Parametre : Liste de client et la structure client**
//**    Traitement: Insere un client à la fin de la liste **
//**    Retourne  : Liste de client                       **
//**    Utilise   : RetourTete                            **
//**                                                      **
//**********************************************************


liste_client InsererEnFinClient(liste_client l,client cl)
{
	cellule_client *inser;

	inser=(cellule_client *)malloc(sizeof(cellule_client));
	inser->person=cl;

	l=RetourTete(l);

	if(l==NULL)
	{
		inser->precedent=NULL;
		inser->suivant=NULL;
		l=inser;
	}
	else
	{
		while(l->suivant!=NULL)
			l=l->suivant;

		inser->precedent=l;
		l->suivant=inser;
		inser->suivant=NULL;
	}

	return RetourTete(l);
}
