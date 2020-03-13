#include<windows.h>
#include<stdio.h>
#include<time.h>
#include<conio.h>
#include"structure.h"
#include"prototype.h"




//************************************************************
//**    Procedure : Sauvegarder un type de voiture          **
//**    Parametre : la liste de type et une chaine caractere**          
//**    Traitement: c'est une procedure qui sauvegarde un   **
//**                type de voiture dans un fichier         **  
//**    Utilise   : les fonctions de manipulation des       **
//**                fichiers(fopen,fwrite,fclose)           **                               
//************************************************************


void sauvgarde(liste l,char nom[25])
{	
	FILE* stock;
	liste sauv;


	stock=fopen(nom,"w");

	sauv=(cellule *)malloc(sizeof cellule);
	sauv=l;

	while(sauv!=NULL)
	{
		fwrite(&sauv->voit,sizeof(voiture),1,stock);
		sauv=sauv->suivant;
	}
		
	fclose(stock);

	
	msgSauvCharg("Sauvgarde des type");
}
	






//************************************************************
//**    Fonction  : chargement d'un Type de voiture         **
//**    Parametre : une chaine de caractere                 **
//**    Traitement: c'est une procedure qui charge un type  ** 
//**                de voiture à partir du fichier si ce    ** 
//**                dernier n'est pas vide                  **
//**    Retourne  : la liste de type                        **
//**    Utilise   : les fonctions de manipulation des       **
//**                fichiers(fopen,fwrite,fclose )          **                               ** 
//************************************************************


liste chargementType(char *nom)
{
	FILE* stock;
	liste charge,retour;
	cellule *p;
	voiture voit;

	p=(cellule *)malloc(sizeof cellule);
	
	retour=(cellule *)malloc(sizeof cellule);
	retour=NULL;
	stock=fopen(nom,"r");
	
	if(stock!=NULL)
	{		
		while(fread(&voit,sizeof(voiture),1,stock))//&voit designe l'@ de la structure voiture
		{
			charge=(cellule *)malloc(sizeof cellule);
			charge->voit=voit;
			charge->suivant=NULL;
			
			if (retour==NULL)
				retour=charge;
			else
			{
				p=retour;
				while(p->suivant!=NULL)
					p=p->suivant;
				p->suivant=charge;
			}
		}
	//	fclose(stock);
	}

	msgSauvCharg("Chargement des types");
	return retour;
}







//************************************************************
//**    Procedure : Sauvegarder un matricule                **
//**    Parametre : la liste de matricule et une chaine de  **
//**                caractere                               **          
//**    Traitement: c'est une procedure qui sauvegarde un   **
//**                matricule de voiture dans un fichier         **  
//**    Utilise   : les fonctions de manipulation des       **
//**                fichiers(fopen,fwrite,fclose)           **                               
//************************************************************

void SauvgardeMatricule(listeMatricul l,char *nom)
{
	FILE *fp;

	fp=fopen(nom,"w");
	
	while(l!=NULL)
	{
		fwrite(&l->mat,sizeof(matriculVoiture),1,fp);
		l=l->suivant;
	}

//	free(l);

	fclose(fp);

	msgSauvCharg("Sauvgarde des matriculs");
}





//************************************************************
//**    Fonction  : chargement d'un matricule de voiture    **
//**    Parametre : une chaine de caractere                 **
//**    Traitement: c'est une procedure qui charge un       ** 
//**                matricule à partir du fichier si ce     ** 
//**                dernier n'est pas vide                  **
//**    Retourne  : la liste de matricule                   **
//**    Utilise   : les fonctions de manipulation des       **
//**                fichiers(fopen,fread,fclose )          **                               ** 
//************************************************************

listeMatricul ChargementMatricul(char *nom)
{
	FILE *stock;
	matriculVoiture mat;
	listeMatricul l,parc,retour;

	stock=fopen(nom,"r");
	
	retour=(listeMatricul )malloc(sizeof listeMatricul);
	parc=(listeMatricul )malloc(sizeof listeMatricul);
	retour=NULL;
	
	if(stock!=NULL)
	{
		while(fread(&mat,sizeof(matriculVoiture),1,stock))
		{	
			l=(listeMatricul )malloc(sizeof listeMatricul);
			l->mat=mat;
			l->suivant=NULL;
			
			if(retour==NULL)
				retour=l;
			else
			{
				parc=retour;
				while(parc->suivant!=NULL)
					parc=parc->suivant;
				parc->suivant=l;
			}
		}
	//	fclose(stock);
	}
		
	msgSauvCharg("Chargement des matriculs");	
	
	return retour;
}







//************************************************************
//**    Procedure : Sauvegarder un client                   **
//**    Parametre : la liste de client et une chaine de     **
//**                caractere                               **          
//**    Traitement: c'est une procedure qui sauvegarde un   **
//**                client dans un fichier                  **  
//**    Utilise   : les fonctions de manipulation des       **
//**                fichiers(fopen,fwrite,fclose)           **                               
//************************************************************

void sauvgardeClient(liste_client l,char *nom)
{
	FILE *fp;

	l=RetourTete(l);

	fp=fopen(nom,"w");

	while(l!=NULL)
	{
		fwrite(&l->person,sizeof(client),1,fp);
		l=l->suivant;
	}
	
	fclose(fp);

//	free(l);

	msgSauvCharg("Sauvgarde des clients");
}






//************************************************************
//**    Fonction  : chargement d'un client                  **
//**    Parametre : une chaine de caractere                 **
//**    Traitement: c'est une procedure qui charge un       ** 
//**                client à partir du fichier si ce        ** 
//**                dernier n'est pas vide                  **
//**    Retourne  : la liste de matricule                   **
//**    Utilise   : les fonctions de manipulation des       **
//**                fichiers(fopen,fread,fclose )           **                               ** 
//************************************************************

liste_client chargementClient(char *nom)
{
	FILE *fp;
	client person;
	liste_client parc,retour;

	fp=fopen(nom,"r");
	
	retour=(liste_client)malloc(sizeof liste_client);
	parc=(liste_client)malloc(sizeof liste_client);
	retour=NULL;


	if(fp!=NULL)
	{
		while(fread(&person,sizeof(client),1,fp))
		{
			retour=InsererEnFinClient(retour,person);
		}

	//	fclose(fp);
	}
		
	msgSauvCharg("Chargement des clients...");

	return retour;
}





//************************************************************
//**    Procedure : Sauvegarder un contrat                  **
//**    Parametre : la liste de contrat et une chaine de    **
//**                caractere                               **          
//**    Traitement: c'est une procedure qui sauvegarde un   **
//**                contrat dans un fichier                 **  
//**    Utilise   : les fonctions de manipulation des       **
//**                fichiers(fopen,fwrite,fclose)           **                               
//************************************************************

void SauvgardeContrat(ListeContrat l,char *nom)
{
	FILE *fp;

	fp=fopen(nom,"w");

	while(l!=NULL)
	{
		fwrite(&l->cont,sizeof(contrat),1,fp);
		l=l->suivant;
	}
	

	fclose(fp);


	msgSauvCharg("Sauvgarde des contrats");

}





//************************************************************
//**    Fonction  : chargement d'un contrat                 **
//**    Parametre : une chaine de caractere                 **
//**    Traitement: c'est une procedure qui charge un       ** 
//**                contrat à partir du fichier si ce       ** 
//**                dernier n'est pas vide                  **
//**    Retourne  : la liste de matricule                   **
//**    Utilise   : les fonctions de manipulation des       **
//**                fichiers(fopen,fread,fclose )           **                               ** 
//************************************************************

ListeContrat chargementContrat(char *nom)
{
	FILE* fp;
	contrat cont;
	ListeContrat l,parc,retour;

	fp=fopen(nom,"r");
	
	retour=(ListeContrat)malloc(sizeof ListeContrat);
	parc=(ListeContrat)malloc(sizeof ListeContrat);
	retour=NULL;


	if(fp!=NULL)
	{
		while(fread(&cont,sizeof(contrat),1,fp))
		{
			l=(ListeContrat)malloc(sizeof ListeContrat);
			l->cont=cont;
			l->suivant=NULL;
			if(retour==NULL)
				retour=l;
			else
			{
				parc=retour;
				while(parc->suivant!=NULL)
					parc=parc->suivant;
				parc->suivant=l;
			}
		}
	//	fclose(fp);
	}
		
	msgSauvCharg("Chargement des contrats");	
	
	return retour;
}



//************************************************************
//**    Procedure : Sauvegarde generale                     **
//**    Parametre : un entier,les liste de type,de contrat, **
//**                de matricule,de client                  **
//**    Traitement: c'est une procedure qui permet le       ** 
//**                sauvegarde des changements effectuer sur**                          
//**                les voiture,les contrats et les clients **  
//**    Utilise   : les 3 procedures de sauvegardes         **
//**                précédentes                             **
//************************************************************

void SauvgardeGeneral(int verif,liste stock_voiture,liste_client lesclients,ListeContrat lescontrat,listeMatricul stock_matricul)
{
	int tmp;

	if(verif==9)
	{	
		do
		{
			system("cls");
			printf("\n\n\n\n\n\n");
			printf("\n                    \xda\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xbf");
			printf("\n                    \xb3     Sauvgarder les changements ?     \xb3");
			printf("\n                    \xb3          oui(o)    non(n)            \xb3");
			printf("\n                    \xc0\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xd9");
			tmp=getch();
	
			if(tmp==111)
			{
				sauvgarde(stock_voiture,"type.txt");
				SauvgardeMatricule(stock_matricul,"matricul.txt");
				sauvgardeClient(lesclients,"client.txt");
				SauvgardeContrat(lescontrat,"contrat.txt");
			}
			if(tmp==110)
				MessageUrgence("Pas de sauvgarde");
		}while((tmp!=111)&&(tmp!=110));
	}

	if(verif==1)
	{
		do
		{
			system("cls");
			printf("\n\n\n\n\n\n");
			printf("\n                    \xda\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xbf");
			printf("\n                    \xb3     Sauvgarder les changements       \xb3");
			printf("\n                    \xb3     effectuer sur les contrat ?      \xb3");
			printf("\n                    \xb3          oui(o)    non(n)            \xb3");
			printf("\n                    \xc0\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xd9");
			tmp=getch();
	
			if(tmp==111)
			{
				SauvgardeContrat(lescontrat,"contrat.txt");
				sauvgardeClient(lesclients,"client.txt");
			}
			if(tmp==110)
				MessageUrgence("Pas de sauvgarde");
		}while((tmp!=111)&&(tmp!=110));
	}

	if(verif==2)
	{
		do
		{
			system("cls");
			printf("\n\n\n\n\n\n");
			printf("\n                    \xda\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xbf");
			printf("\n                    \xb3     Sauvgarder les changements       \xb3");
			printf("\n                    \xb3     effectuer sur les voitures ?     \xb3");
			printf("\n                    \xb3          oui(o)    non(n)            \xb3");
			printf("\n                    \xc0\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xd9");
			tmp=getch();
		
			if(tmp==111)
			{
				SauvgardeMatricule(stock_matricul,"matricul.txt");
				sauvgarde(stock_voiture,"type.txt");
			}
			if(tmp==110)
				MessageUrgence("Pas de sauvgarde");
		}while((tmp!=111)&&(tmp!=110));
	}

	if(verif==3)
	{
		do
		{
			system("cls");
			printf("\n\n\n\n\n\n");
			printf("\n                    \xda\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xbf");
			printf("\n                    \xb3     Sauvgarder les changements       \xb3");
			printf("\n                    \xb3     effectuer sur les clients ?      \xb3");
			printf("\n                    \xb3          oui(o)    non(n)            \xb3");
			printf("\n                    \xc0\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xd9");
			tmp=getch();
	
			if(tmp==111)
			{
				sauvgardeClient(lesclients,"client.txt");
			}
			if(tmp==110)
				MessageUrgence("Pas de sauvgarde");
		}while((tmp!=111)&&(tmp!=110));
	}

}








//************************************************************
//**    Procedure : Message d'urgence                       **
//**    Parametre : une chaine de caractere contenant le    **
//**                message à afficher                      **          
//**    Traitement: c'est une procedure qui affiche         ** 
//**                un message clignotant lors d'une action **
//**				particulière tel que erreur ou recherche**
//**    Utilise   : la fonction sleep                       **
//**                                                        **                               
//************************************************************


void MessageUrgence(char *msg)
{
	int i;

	
	for(i=0;i<2;i++)
	{
		
		system("cls");
		Sleep(500);
		printf("\n\n\n\n\n\n\n\n\n\t\t\t\t\a\a%s",msg);
		Sleep(500);
	}
}

//***********************************************************
//*******************MESSAGE DU SAUVE-CHARGE*****************
//***********************************************************

void  msgSauvCharg(char *msg)
{
	int j;

	system("cls");
	printf("\n\n\n\n\n\n\n\n\n\t\t\t\t%s",msg);
	for(j=0;j<=5;j++)
	{
		Sleep(120);
		printf(".");
	}

}









//********************************************************
//**    Fonction  : convertir une date                  **
//**    Parametre : pas de parametre                    **
//**    Traitement: conversion DATE-CHAINE A UNE        ** 
//**                DATE-ENTIER                         **      
//**    Retourne  : date                                **
//**    Utilise   :  strncpy, atoi                      **
//********************************************************                                                 **

date convertDate()
{
	char *dat_buff;
	int tmp;
	date d;

	dat_buff=(char *)malloc(sizeof (char));
	_strdate(dat_buff);	//**********DONNE LA DATE SOUS FORME D'UNE CHAINE****

//***************************************************************************
//*****REMPLACE UN CARACTERE PAR UN AUTRE CARACTERE SUIVANT UN POSITION******
//***************************************************************************	
	strncpy(dat_buff+2,"0",1);
	strncpy(dat_buff+5,"0",1);

	
//****************************************************************************
//****CONVERTIE UNE CHAINE DE CARACTERE EN UN ENTIER SI C'EST POSSIBLE********
//****************************************************************************	
	tmp=atoi(dat_buff);

	
	
	
	
	//****************************************************************************

	d.mm=tmp/1000000;

	d.jj=((tmp%1000000)/1000);

	d.aa=((tmp%1000000)%1000)+2000;

	return d;

}




//*********************************************************************
//************************    A PROPOS       **************************
//*********************************************************************
void A_Propos()
{
	

	EnTete();


	printf("\n\t\tECOLE SUPERIEUR DE TECHNOLOGIE ET D'INFORMTIQUE");
	
	printf("\n\n\n\t\tMini projet  : Gestion location de voiture");

	printf("\n\n\n\t\tRealiser par :\tREZGUI Mohamed");
	printf("\n\n\t\t              \tMLAOUHI Hamdi");

	printf("\n\n\n\t\tEncadrer par :\tMr. KADRI *****");
	printf("\n\n\t\t              \tMr. BENNARI *****");

	printf("\n\n\n\n\t\t\tAnnee universitaire   2005/2006");

	printf("\n\n");
	system("pause");
	

}






//**************************************************************
//******************   STATISTIQUE     *************************
//**************************************************************

//********************************************************
//**    Procedure  : Statistique                        **
//**    Parametre : les listes de:voiture, client,      **
//**                matricule et contrat                **
//**    Traitement: Calculer le nbre de: type disponible**
//**                client,contrats, voitures loués     **
//**                et non-louées ainsi que le cout     **
//**                totale des locations éffectuées     **
//**    Utilise   : RetourTete pour placer le pointeur  **
//**                1er cellule de la liste             **
//******************************************************** 

void Statistique(liste typ,liste_client clt,listeMatricul mat,ListeContrat crt)
{
	int NBtyp=0,NBmat=0,NBcrt=0,NBclt=0,total=0,NBvoit=0,NBvoitl=0,cout=0;
	
	liste l;
	liste_client client;
	ListeContrat contrat;
	listeMatricul matricul;


	system("cls");

	EnTete();

	l=(liste)malloc(sizeof liste);
//*********************************************************************
//*********		CALCULE DU NOMBRE DES TYPES DISPONIBLES		***********
//*********************************************************************
	l=typ;

	while(l!=NULL)
	{
		NBtyp++;
		l=l->suivant;
	}

//*********************************************************************
//********		CALCULE DU NOMBRE DES VOITURES LOUEES ET NON-LOUEES****
//*********************************************************************

	matricul=(listeMatricul)malloc(sizeof listeMatricul);
	matricul=mat;

	while(matricul!=NULL)
	{
		NBvoit++;
		if(strcmp(&matricul->mat.stats,"l")==0)
			NBvoitl++;
		matricul=matricul->suivant;
	}

//*********************************************************************
//*********		CALCULE DU NOMBRE DE CLIENT		***********************
//*********************************************************************

	client=(liste_client)malloc(sizeof liste_client);
	
	client=RetourTete(clt);
	while(client!=NULL)
	{
		NBclt++;
		client=client->suivant;
	}


//*********************************************************************
//*********		CALCULE DU NOMBRE DES CONTRATS	***********************
//*********************************************************************

	contrat=(ListeContrat)malloc(sizeof ListeContrat);

	contrat=crt;

	while(contrat!=NULL)
	{
		NBcrt++;
		cout+=contrat->cont.cout;
		contrat=contrat->suivant;
	}

//*********************************************************************
//************		DESSIN DU TABLEAU RECUPELATIF DES TOTALES  ********
//*********************************************************************

	printf("\n\n\n \xda");
	printf("\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc2");
	printf("\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc2");
	printf("\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc2");
	printf("\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc2");
	printf("\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc2");
	printf("\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4");
	printf("\xbf\n");

	printf(" \xb3         \xb3");
	printf("    TYPE   \xb3");
	printf("  VOITURE  \xb3");
	printf("  CONTRAT  \xb3");
	printf("   CLIENT  \xb3");
	printf("  COUT LOCATION  \xb3");

	printf("\n \xc3");
	printf("\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc5");
	printf("\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc5");
	printf("\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc5");
	printf("\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc5");
	printf("\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc5");
	printf("\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4");
	printf("\xb4\n");
	
	printf(" \xb3  TOTALE \xb3");
	printf("   %3.0d     \xb3",NBtyp);
	printf("   %3.0d     \xb3",NBvoit);
	printf("   %3.0d     \xb3",NBcrt);
	printf("   %3.0d     \xb3",NBclt);
	printf("    %7.0d      \xb3",cout);
	
	printf("\n \xc0");
	printf("\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc1");
	printf("\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc1");
	printf("\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc1");
	printf("\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc1");
	printf("\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc1");
	printf("\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4");
	printf("\xd9\n");
	

	
	printf("\n\n");
	system("pause");
}


