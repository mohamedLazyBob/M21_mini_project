#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>
#include"structure.h"
#include"prototype.h"





//*****************************************************************
//****                ********************                     ****
//******            **                    **                  *****
//*********        ***PROGRAMME PRINCIPALE***            **********
//******            **                    **                  ***** 
//****                ********************                     ****  
//*****************************************************************


void main()
{
	liste stock_voiture,typ;
	liste_client les_clients;
	ListeContrat uncontrat,lescontrat;
	cellule *voit;
	cellule_client *unclient;
	int choix_principal=0,choix_second=0,choix,tmp;
	listeMatricul stock_matricul,matr;
	char nom[20],pnom[20];
	

	//**************************************************************
	//****      INITIALISATION DE LA LISTE DES CLIENTS     *********
	//****      UNE LISTE DOUBLEMENT CHAINEE               *********
	//**************************************************************
	les_clients=(cellule_client *)malloc(sizeof cellule_client);
	les_clients=NULL;
	

	
    //**************************************************************
	//***       INITIALISATION DE LA LISTE DES TYPES DE VOITURE  ***
	//**************************************************************
	
	
	stock_voiture=(cellule *)malloc(sizeof cellule);
	typ=(cellule *)malloc(sizeof cellule);
	stock_voiture=NULL;


	
    //**************************************************************
	//***        INITIALISATION DE LA LISTE DES MATRICULE        ***
	//**************************************************************
	
	stock_matricul=(Matricul *)malloc(sizeof Matricul);
	stock_matricul=NULL;
	
	
    //*************************************************************
	//***       INITIALISATION DE LA LISTE DE CONTRATS          ***
	//*************************************************************

	lescontrat=(CelluleContrat *)malloc(sizeof CelluleContrat);
	lescontrat=NULL;


	//**************************************************************
	//***        CHARGEMENT DES DONNEES                          ***
	//**************************************************************


	stock_voiture=chargementType("type.txt");
	stock_matricul=ChargementMatricul("matricul.txt");
	les_clients=chargementClient("client.txt");
	lescontrat=chargementContrat("contrat.txt");

	


	//***************************************************************
	//***			TRAITEMENT DES MENUS						  ***
	//***************************************************************
while((choix_second!=27)&&(choix_principal!=9))
{
	choix_principal=MenuPrincipal();
	
	switch(choix_principal)
	{	

	case 1:	
		while(choix_second!=27)
		{
			choix_second=MenuLocation();
			if(choix_second==49)
			{
				printf("\n\t\tUn contrat(1)\tLes contrats(2)");
				choix=getch();
				if(choix==49)
				{
					uncontrat=RechercheContrat(lescontrat);
					if(uncontrat==NULL)
						MessageUrgence("Contrat non-trouvee");
					else
						AfficheContrat(uncontrat->cont);
				}
				if(choix==50)
				{
					uncontrat=lescontrat;
					while(uncontrat!=NULL)
					{
						AfficheContrat(uncontrat->cont);
						uncontrat=uncontrat->suivant;
					}
				}
			}
		
			if(choix_second==50)
			{

				printf("\n\n\t\tSelectionner un client oui(o)/non(n) : ");
				do
				{	choix=getch();
				}while((choix!=111)&&(choix!=110));
				if(choix==111)
				{
					EnTete();

					printf("\n\n\tClient a selectionne...");
					printf("\n\n\t\tNom       : ");
					scanf("%s",&nom);
					printf("\n\n\t\tPrenom    : ");
					scanf("%s",&pnom);
					unclient=RechercheClient(les_clients,nom,pnom);
					if(unclient==NULL)
					{
						MessageUrgence("Client non-trouve");
						unclient=SaisieClient();
						uncontrat=saisieContrat(unclient,stock_matricul);
					}
					else
						uncontrat=saisieContrat(unclient,stock_matricul);
				}
				else
				{
					unclient=SaisieClient();
					uncontrat=saisieContrat(unclient,stock_matricul);
				}

				if(uncontrat==NULL)
				{
					MessageUrgence("Condition non-verifiee\n\t\t\t\tLocation impossible");
					MessageUrgence("Client non-sauvgarde");
				}
				else
				{
					if(choix==110)		//***SI J'AI PAS SELECTIONNE UN CLIENT***
						les_clients=InsererEnFinClient(les_clients,unclient->person);
					
					//******INSERTION D'UN CONTRAT*************
					uncontrat->suivant=lescontrat;
					lescontrat=uncontrat;
					MessageUrgence("Location effectuee");
				}
			}

			if(choix_second==51)
				RetourContrat(lescontrat,stock_matricul,stock_voiture);

			if(choix_second==52)
				lescontrat=ModifierContrat(lescontrat,stock_matricul);


			if(choix_second==53)
			{
				uncontrat=RechercheContrat(lescontrat);
				if(uncontrat==NULL)
					MessageUrgence("Contrat non-trouvee");
				else
				{
					lescontrat=SupprimerContrat(lescontrat,uncontrat);
					MessageUrgence("Contrat supprimer");
				}
			}

			if(choix_second==57)
				choix_second=27;
		}
			typ=stock_voiture;
			matr=stock_matricul;
			uncontrat=lescontrat;
			unclient=les_clients;
			SauvgardeGeneral(1,typ,unclient,uncontrat,matr);
			choix_second=0;
	//	goto RETOUR;
	
		
		break;
        //**************************************************
		//***   L'ACCEE AU MENU DE GESTION DE VOITURE    ***
        //**************************************************
	case 2 :
		while(choix_second!=27)
		{
			choix_second=MenuGestionVoiture();

			if(choix_second==49)	
			{
				//**********************************************
				//***   Affichage des voitures et des types  ***
				//**********************************************
				printf("\n\n\t\tType (1)\t\tVoiture (2)");
				choix=getch();

				if(choix==49)		//****Un type****
				{
					printf("\n\n\t\tUn type (1)\t\tTous les types (2)");
					if(getch()==49)
					{
						EnTete();
						printf("\n\n\t\tType recherche...");
						printf("\n\n\t\tIdentifiant    :  ");
						scanf("%s",&nom);
						typ=RechercheTypeVoiture(stock_voiture,nom);
						if(typ==NULL)
							MessageUrgence("Type non-trouve");
						else
							AfficheType(typ->voit);
					}

					if(getch()==50)
					{
						typ=stock_voiture;
						while(typ!=NULL)
						{
							AfficheType(typ->voit);
							typ=typ->suivant;
						}
					}
				}
		
				if(choix==50)		//****AFFICHE UN MATRICUL******
				{
					printf("\n\n\t\tUne voiture (1)\t\tTous les voitures (2)");

					if(getch()==49)
					{
						EnTete();
						printf("\n\n\t\tVoiture recherchee...");
						printf("\n\n\t\tMatricul    :  ");
						scanf("%d",&tmp);

						matr=rechecherMatricul(stock_matricul,tmp);
						if(matr==NULL)
							MessageUrgence("Voiture non-trouvee");
						else
							AfficheVoiture(matr->mat);
					}

					if(getch()==50)
					{
						matr=stock_matricul;
						while(matr!=NULL)
						{
							AfficheVoiture(matr->mat);
							matr=matr->suivant;
						}
					}
				}
			}


			if(choix_second==50)
			{
				//***************************************************************
				//**      SAISIE D'UN NOUVEAU TYPE OU MATRICUL DE VOITURE      **
				//**      LA VALEUR 1 INDIQUE LA SAISIE D'UN TYPE              **
				//**      LA VALEUR 2 INDIQUE LA SAISIE D'UN MATRICULE         **
				//**      "ECHAPE" INDIQUE LA SORTIE DE CETTE RUBRIQUE         **
				//***************************************************************
				do
				{
					printf("\n\n\t\tType (1)\t\tVoiture (2)\n\t\t");
					//scanf("%d",&choix);
					choix=getch();
				}while((choix==49)&&(choix==50)&&(choix==27));
					
				
				if(choix==49)		//**SAISIE D'UN NOUVEAU TYPE
				{
					voit=SaisieTypeVoiture(stock_voiture);
					stock_voiture=inserer_en_fin(stock_voiture,voit);
				}
				
	 			if(choix==50)		//**SAISIE D'UN NOUVEAU MATRICUL
				{
					matr=saisieMatricul(stock_matricul,stock_voiture);
					if(matr!=NULL)
						stock_matricul=insererVoiture(stock_matricul,matr);
				}					

			}
			if(choix_second==51)
				stock_voiture=ModifierTypeVoiture(stock_voiture);
			
			if(choix_second==52)
			{
				do
				{
					printf("\n\n\t     Type (1)\t\tVoiture (2)\n\t\tchoix  :  ");
					scanf("%d",&choix);
				}while((choix==1)&&(choix==2)&&(choix==0));
				
				if(choix==1)
					stock_voiture=SupprimerVoiture(stock_voiture);
				else
					if(choix==2)
						stock_matricul=supprimerMatricul(stock_matricul);
			}

			if(choix_second==57)
				choix_second=27;
		}

		typ=stock_voiture;
		matr=stock_matricul;
		uncontrat=lescontrat;
		unclient=les_clients;
		SauvgardeGeneral(2,typ,unclient,uncontrat,matr);
		choix_second=0;
	//	goto RETOUR;		//*********EQUIVALENT A JMP EN ASSEMBLEUR*********
		break;
		
	case 3 :
		while(choix_second!=27)
		{
			unclient=(cellule_client *)malloc(sizeof cellule_client);
			choix_second=MenuGestionClient();
			if(choix_second==49)
			{
				printf("\n\n\tUn client(1)\tLes clients(2)");
				choix=getch();
				if(choix==49)
				{
					EnTete();
					printf("\n\n\tClient recherche...");
					printf("\n\t\tNom          : ");
					scanf("%s",&nom);
					printf("\n\t\tPrenom       : ");
					scanf("%s",&pnom);
					unclient=RechercheClient(les_clients,nom,pnom);
					if(unclient==NULL)
						MessageUrgence("Client non-trouve");
					else
						AfficheClient(unclient->person);
				}
				if(choix==50)
				{
					unclient=les_clients;
					while(unclient!=NULL)
					{
						AfficheClient(unclient->person);
						unclient=unclient->suivant;
					}
				}
			}				
			if(choix_second==50)
				les_clients=modifierClient(les_clients);
			
			if(choix_second==51)
				les_clients=supprimerClient(les_clients);

			if(choix_second==57)
				choix_second=27;
		}
		typ=stock_voiture;
		matr=stock_matricul;
		uncontrat=lescontrat;
		unclient=les_clients;
		SauvgardeGeneral(3,typ,unclient,uncontrat,matr);
		choix_second=0;
	
		break;

	case 4:
		typ=stock_voiture;
		matr=stock_matricul;
		uncontrat=lescontrat;
		unclient=les_clients;
		Statistique(typ,unclient,matr,uncontrat);
		break;

	case 8:
		A_Propos();

		break;

	case 9 :
		break;
	

	}
}


//******************************************************************	
//***                     SAUVEGARDE DES DONNEES                 ***
//******************************************************************



	typ=stock_voiture;
	matr=stock_matricul;
	uncontrat=lescontrat;
	unclient=les_clients;
	SauvgardeGeneral(9,typ,unclient,uncontrat,matr);
    //**************************************************************
	//***           LIBERATION DE L'ESPACE MEMOIRE               ***
	//**************************************************************
/*
	free(stock_voiture);
	free(stock_matricul);
	free(lescontrat);
	free(les_clients);
*/
}
