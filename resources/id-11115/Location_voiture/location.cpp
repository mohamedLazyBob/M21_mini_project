#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#include"structure.h"
#include"prototype.h"

//#define  int supcond 20
//#define  int bebe 15
//#define  int livraison 20



//************************************************************
//**    Fonction  : Condition de location            		**
//**    Parametre : La structure client                 	**
//**    Traitement: elle compare l'age du client à 25 et    **
//**                verifie si la difference entre date de  **
//**                permis et la dte actuelle  est superieur**
//**                à 2 ans     							**
//**    Retourne  :	0 si la condition de loction est verifié**
//**	            et 1 sinon                              **
//**    Utilise   : convertDate								**
//************************************************************
int ConditionLocation(client cl)
{
	int tmp;
	int aa,mm,jj;

	if(cl.age>=25)
	{
		tmp=cl.date_permi;

		jj=tmp/1000000;
		mm=((tmp%1000000)/10000);
		aa=((tmp%1000000)%10000);

		if((convertDate().aa+2000)-aa>=2)
			return 0;
	}

	return 1;

}





//********************************************************
//**	Fonction  : Saisie d'un contrat  				**
//**	Parametre : liste de client,liste de matricule  **
//**	Traitement: Saisie des champs du contrat        **
//**	Retourne  : la cellule contrat sinon retourne NULL **
//********************************************************


ListeContrat saisieContrat(cellule_client *person,listeMatricul l)
{
	CelluleContrat *cel;
	Matricul *mat;
	int verif=0;
	char typ[5];
	
	if(ConditionLocation(person->person)!=0)
		return NULL;

	EnTete();

	mat=(Matricul *)malloc(sizeof Matricul);
	cel=(CelluleContrat *)malloc(sizeof CelluleContrat);

	strcpy(cel->cont.nom,person->person.nom);
	strcpy(cel->cont.pnom,person->person.prenom);

	cel->cont.num=generationCode();

	printf("\n\tNumero contrat : %.0f",cel->cont.num);

	do
	{
		if(verif==3)
			goto END_SAISIE;
		
		printf("\n\n\tType Voiture louee     :  ");
		scanf("%s",&typ);
		mat=RechercheVoitureLibre(l,typ);
		if(mat==NULL)
		{
			printf("\n\t\tPas de voiture disponible");
			verif++;
		}
				
	}while(mat==NULL);

	printf("\n\tVoiture disponible : %i TUN %i",mat->mat.matricule/10000,mat->mat.matricule%10000);
	cel->cont.voit_loue=mat->mat.matricule;
	do
	{
		printf("\n\tType de location (km/jr) :  ");
		scanf("%s",&cel->cont.type);
	} while((strcmp(cel->cont.type,"km")!=0)&&(strcmp(cel->cont.type,"jr")!=0));

	if(strcmp(cel->cont.type,"km")==0)
	{
		cel->cont.debu=mat->mat.kilometrage;
		printf("\n\t\tKilometrage actuel du vehicule  :  %d",cel->cont.debu);
		cel->cont.fin=0;
	}
	else
	{
		printf("\n\tDate du debut    :  ");
		scanf("%d",&cel->cont.debu);

		printf("\n\tDate retour      :  ");
		scanf("%d",&cel->cont.fin);
	}

	printf("\n\tAgence de location   :  ");
	scanf("%s",&cel->cont.agencDepar);

	printf("\n\t\tLes options......");

	do
	{
		printf("\n\t2eme conducteur (o/n) :");
		scanf("%s",&cel->cont.supcond);
	} while((cel->cont.supcond!='o')&&(cel->cont.supcond!='n'));

	do
	{
		printf("\n\tLivraison  (o/n) :  ");
		scanf("%s",&cel->cont.liv);
	}while((cel->cont.liv!='o')&&(cel->cont.liv!='n'));

	do
	{
		printf("\n\tSiege bebe (o/n) :  ");
		scanf("%s",&cel->cont.bebe);
	} while((cel->cont.bebe!='o')&&(cel->cont.bebe!='n'));

	
	do
	{
		printf("\n\n\t\tValider location oui(o) / non(n)");
		verif=getch();
	}while((verif!=111)&&(verif!=110));
	if(verif==110)
		return NULL;

	strcpy(cel->cont.agencRetour,"TMP");

	cel->cont.cout=0;

	person->person.ctr=cel->cont.num;

	mat->mat.stats='l';		//----->>>>>**********POUR DECLARER LA VOITURE LOUEE********

	return cel;

	END_SAISIE :			//----->>>>>**********ETIQUETTE D'ANNULATION***************
	MessageUrgence("Contrat Annule");
	return NULL;

}




//************************************************************
//**    Fonction  : Recherche d'un contrat          		**
//**    Parametre : liste de contrat                     	**
//**    Traitement: elle cherche un contrat celon le        **
//**                matricule,le nom et le prénom du client **
//**                    							        **
//**    Retourne  :	la cellule contrat si elle est trouvée  **
//**                et NULL sinon                           ** 
//**	                                                    **
//**    Utilise   : strcmp pour comparer les champs         **
//************************************************************

ListeContrat RechercheContrat(ListeContrat l)
{
	ListeContrat parc;
	int mat;
	char nom[20],pnom[20];

	parc=(ListeContrat)malloc(sizeof ListeContrat);
	
	printf("\n\tMatricul voiture louee   :  ");
	scanf("%d",&mat);
	printf("\n\tNom      :  ");
	scanf("%s",&nom);
	printf("\n\tPrenom   :  ");
	scanf("%s",&pnom);

	parc=l;
	while(parc!=NULL)
	{
		if(parc->cont.voit_loue==mat)
			if(strcmp(parc->cont.nom,nom)==0)
				if(strcmp(parc->cont.pnom,pnom)==0)
					return parc;
		
		parc=parc->suivant;

	}

	return NULL;

}








//************************************************************
//**    Procedure : Retour d'une voiture            		**
//**    Parametre : liste de contrat, liste de matricule,   **
//**                et liste de client                     	**
//**    Traitement: permet de completer les champs d'un     **
//**                contrat lors du retour de la véhicule   **
//**                louée(calcul du prix total de location) **
//**                     							        **
//**    Utilise   : les fonctions de recherche:             **
//**                RechercheContrat,RechercheTypeVoiture   **
//**                RechercheMatricule                      **                  **
//************************************************************


void RetourContrat(ListeContrat lcr,listeMatricul lm,liste l)
{
	ListeContrat crt;
	listeMatricul mat;
	liste typ;

	int supcond=20;
	int bebe =15;
	int livraison =20;

	crt=(ListeContrat)malloc(sizeof ListeContrat);
	mat=(listeMatricul)malloc(sizeof listeMatricul);
	typ=(liste)malloc(sizeof liste);

	EnTete();

	crt=RechercheContrat(lcr);

	if(crt==NULL)
		MessageUrgence("Contrat non-trouve");
	else
	{
		crt->cont.cout=0;
		mat=rechecherMatricul(lm,crt->cont.voit_loue);
		typ=RechercheTypeVoiture(l,mat->mat.type);

		printf("\n\tContrat numero   :  %.0f",crt->cont.num);

		printf("\n\tAgence de retour   :  ");
		scanf("%s",&crt->cont.agencRetour);
		
		if(strcmp(crt->cont.type,"km")==0)
		{
			printf("\n\tKilometrage retour  :  ");
			scanf("%d",&crt->cont.fin);
			 mat->mat.kilometrage=crt->cont.fin;
		}
		else
		{
			printf("\n\tDuree (jour)  :  ");
			scanf("%d",&crt->cont.fin);
			printf("\n\tKilometrage retour  :  ");
			scanf("%d",&mat->mat.kilometrage);
		}

		if(crt->cont.bebe=='o')
			crt->cont.cout+=bebe;
		if(crt->cont.liv=='o')
			crt->cont.cout+=livraison;
		if(crt->cont.supcond=='o')
			crt->cont.cout+=supcond;

		if(strcmp(crt->cont.type,"km")==0)
			crt->cont.cout+=(crt->cont.fin-crt->cont.debu)*typ->voit.prixKilo;
		else
			crt->cont.cout+=crt->cont.fin*typ->voit.prixJour;
		
		printf("\n\tCout   :  %d\n\n",crt->cont.cout);

		strcpy(&mat->mat.stats,"n");

	}


	system("pause");
}





//************************************************************
//**    Procedure : Afichage d'un contrat                   **
//**    Parametre : la structure contrat                    **
//**    Traitement: c'est une procedure qui affiche         **  
//**                un contrat                              ** 
//************************************************************

void AfficheContrat(contrat crt)
{
	EnTete();

	printf("\n\tN\xf8 du contrat  :  %.0f",crt.num);
	
	printf("\n\n\tAgence de location :  %s",crt.agencDepar);
	printf("\t\tAgence de retour   :  %s",crt.agencRetour);

	printf("\n\n\tNom locataire      :  %s",crt.nom);
	printf("\t\tType de location   :  %s",crt.type);
	
	printf("\n\n\tPrenom             :  %s",crt.pnom);
	printf("\t\tVoiture loue       :  %dTUN%d",crt.voit_loue/10000,crt.voit_loue%10000);

	printf("\n\n\tDebut              :  %d",crt.debu);
	printf("\t\tFin                :  %d",crt.fin);

	printf("\n\n\tLes options...");
	printf("\n\n\tLivraison  : %c\t\tSup.conducteur  : %c\t\tSiege beb\x82  : %c",crt.liv,crt.supcond,crt.bebe);

	printf("\n\n\tCout location    :   %d TTC",crt.cout);

	printf("\n\n");

	system("pause");

}




//************************************************************
//**    Fonction  : Supprimer un Contrat					**
//**    Parametre : Liste de contrat et cellule de contrat	**
//**    Traitement: elle supprime un contrat            	**
//**    Retourne  :	La liste contrat apres suppression      **
//**                si effectuer                            **
//**	Utilise   : rien               						**
//************************************************************


ListeContrat SupprimerContrat(ListeContrat l,CelluleContrat *supp)
{
	ListeContrat parc;			//LISTE DE PARCOUR
	

	
	if(supp==l)					//SUPPRIMER EN TETE
	{
		l=l->suivant;
	//	free(supp);
	}
		
	parc=(CelluleContrat *)malloc(sizeof CelluleContrat);	//ALLOCATION

	parc=l;
	while((parc!=NULL)&&(parc->suivant!=supp))
		parc=parc->suivant;

	if(parc->suivant==supp)
	{
		parc->suivant=supp->suivant;
	//	free(supp);
	}

	return l;

}




//********************************************************
//**    Fonction  : Modifier un contrat                 **
//**    Parametre : Liste contrat et liste de matricule **
//**    Traitement: Modifie un contrat s'il existe      **      
//**    Retourne  : Liste de contrat                    **
//**    Utilise   : rechecherMatricul                   **
//**                RechercheContrat                    **
//********************************************************
ListeContrat ModifierContrat(ListeContrat l,listeMatricul m)
{
	ListeContrat rech;
	listeMatricul mat;
	contrat crt;
	int verif=0;


	if(l==NULL)
	{
		MessageUrgence("Pas de contrat disponible");	//***LISTE DE CONTRAT VIDE****
		return l;
	}

	rech=(ListeContrat)malloc(sizeof ListeContrat);
	
	rech=RechercheContrat(l);

	if(rech==NULL)
	{
		MessageUrgence("Contrat non-trouve");
		return l;
	}

	mat=(listeMatricul)malloc(sizeof listeMatricul);

	mat=rechecherMatricul(m,rech->cont.voit_loue);		
	strcpy(&mat->mat.stats,"n");					//***ANNULEE LA LOCATION DU VEHICULE*********



//**************RE-SAISIE DU CONTRAT*****************

	strcpy(crt.nom,rech->cont.nom);
	strcpy(crt.pnom,rech->cont.pnom);
	crt.num=rech->cont.num;
	do
	{
		if(verif==2)
			goto END_SAISIE;
		
		printf("\n\n\tVoiture louee     :  ");
		scanf("%d",&crt.voit_loue);
		mat=rechecherMatricul(m,crt.voit_loue);
		if((mat->mat.stats=='l')&&(mat!=NULL))
		{
			printf("\n\t\t\tVoiture louee");
			verif++;
		}
		
	}while((mat!=NULL)&&(mat->mat.stats!='n'));

	do
	{
		printf("\n\tType de location  :  ");
		scanf("%s",&crt.type);
	} while((strcmp(crt.type,"km")!=0)&&(strcmp(crt.type,"jr")!=0));

	if(strcmp(crt.type,"km")==0)
	{
		crt.debu=mat->mat.kilometrage;
		printf("\n\t\tKilometrage actuel du vehicule  :  %d",crt.debu);
	}
	else
	{
		printf("\n\tDate du debut    :  ");
		scanf("%d",&crt.debu);

		printf("\n\tDate retour      :  ");
		scanf("%d",&crt.fin);
	}

	printf("\n\tAgence de location   :  ");
	scanf("%s",&crt.agencDepar);

	printf("\n\t\tLes options......");

	do
	{
		printf("\n\t2eme conducteur :  ");
		scanf("%s",&crt.supcond);
	} while((crt.supcond!='o')&&(crt.supcond!='n'));

	do
	{
		printf("\n\tSiege bebe      :  ");
		scanf("%s",&crt.bebe);
	} while((crt.bebe!='o')&&(crt.bebe!='n'));

	do
	{
		printf("\n\tLivraison       :  ");
		scanf("%s",&crt.liv);
	}while((crt.liv!='o')&&(crt.liv!='n'));

	do
	{
		printf("\n\n\t\tValider location oui(o) / non(n)");
		verif=getch();
	}while((verif!=111)&&(verif!=110));
	if(verif==110)
		return l;			//------->>>>>>>*******ANNULEE LA MODIFICATION***********

	strcpy(crt.agencRetour,rech->cont.agencRetour);

	crt.cout=0;

	mat->mat.stats='l';
	rech->cont=crt;

	MessageUrgence("Contrat modifie");
	return l;

END_SAISIE:
	MessageUrgence("Modification annule");
	return l;

}
		







//**************************GENERATION DU CODE DU CONTRAT**********************

//********************************************************
//**    Fonction  : Generation du code du contrat       **
//**    Parametre : Pas de paramètre                    **
//**    Traitement: géneration du code du contrat       **      
//**    Retourne  : un réel                             **
//**    Utilise   : _strdate                            **
//********************************************************
float generationCode()
{
	char *dat_buff;
	int jj,mm,aa,tmp2,tmp;
	float code;

	dat_buff=(char *)malloc(sizeof (char));
	_strdate(dat_buff);

	strncpy(dat_buff+2,"0",1);
	strncpy(dat_buff+5,"0",1);
	tmp=atoi(dat_buff);///************

	mm=tmp/1000000;
	jj=((tmp%1000000)/1000);
	aa=((tmp%1000000)%1000);
	tmp=jj*10000+mm*100+aa;

	_strtime(dat_buff);
	strncpy(dat_buff+2,"0",1);
	strncpy(dat_buff+5,"0",1);
	tmp2=atoi(dat_buff);
	
	jj=tmp2/1000000;
	mm=((tmp2%1000000)/1000);
	aa=((tmp2%1000000)%1000);
	tmp2=(jj*10000+mm*100+aa)/100;

	code=(float)tmp*10000+tmp2;
	
	return code;
}
