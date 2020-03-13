#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"structure.h"
#include"prototype.h"





//********************************************************
//**	Fonction  : ListeMatriculeVide					**
//**	Parametre : liste de matricule   				**
//**	Traitement: Verifier si la liste de matricule   **
//**                est vide ou pas                     **
//**	Retourne  : 0 si la liste et vide et1 sinon     **
//********************************************************

int ListeMatriculVide(listeMatricul l)
{
	if(l==NULL)
		return 0;
	else
		return 1;
}




//********************************************************
//**	Fonction  : Inserer voiture                 	**
//**	Parametre : liste de matricule  et une cellule  **
//**                 matricule 				            **
//**	Traitement: Inserer un matricule dans la        ** 
//**                liste de matricule au debut         **
//**	Retourne  : Liste de matricule                  **
//**    Utilise   : ListeMatriculVide                   **
//********************************************************
listeMatricul insererVoiture(listeMatricul l,Matricul *m)
{
	if(ListeMatriculVide(l)==0)
		return m;
	else
		m->suivant=l;
	
	return m;
}




//********************************************************
//**	Fonction  : Rechercher une voiture          	**
//**	Parametre : liste de matricule  et un entier    **
//**	Traitement: Rechercher un matricule dans la     ** 
//**                liste de matricule                  **
//**	Retourne  : La cellule matricule si ce dernier  **
//**                 est trouvé et NULL sinon           **
//**                                                    **
//********************************************************
listeMatricul rechecherMatricul(listeMatricul l,int m)
{
	Matricul *parc;

	if(l!=NULL)
	{
		parc=l;
		while(parc!=NULL)
		{
			if(parc->mat.matricule==m)
				return parc;
			parc=parc->suivant;
		}
	}
	
	return NULL;
}

//********************************************************
//**	Fonction  : Rechercher une voiture          	**
//**	Parametre : liste de matricule  et une chaine   ** 
//**                de caractere                        **
//**	Traitement: Rechercher un matricule dans la     ** 
//**                liste de matricule                  **
//**	Retourne  : La cellule matricule si ce dernier  **
//**                 est trouvé et NULL sinon           **
//**                                                    **
//********************************************************

listeMatricul RechercheVoitureLibre(listeMatricul lm, char *typ)
{
	
	if(lm==NULL)
		return NULL;
	if((strcmp(&lm->mat.stats,"n")==0) && (strcmp(lm->mat.type,typ)==0))
		return lm;
	else return RechercheVoitureLibre(lm->suivant,typ);
}












//********************************************************
//**	Fonction  : Supprimer un matricule   			**
//**	Parametre : liste de matricule   				**
//**	Traitement: supprime un matricule si la liste   **
//**                n'est pas vide                      **
//**	Retourne  : liste de matricule                  **
//**    Utilise   : rechecherMatricul()                 **
//********************************************************
listeMatricul supprimerMatricul(listeMatricul l)
{
	Matricul *parc,*m;
	int mat;

	if(l==NULL)
	{
		MessageUrgence("Pas de voiture a supprimer");
		return l;
	}
	
	do
	{
		printf("\n\tMatricule :  ");
		scanf("%d",&mat);
	}while((mat<=9999999)&&(mat>=10000)&&(mat==0));
	if(mat!=0)
	{
		m=rechecherMatricul(l,mat);
	
		if(m!=NULL)
		{
			if(l==m)
			{
				l=l->suivant;
//				free(m);
				MessageUrgence("Voiture supprimer");
				return l;
			}
			parc=l;
			while((parc->suivant!=m)&&(parc!=NULL))
				parc=parc->suivant;

			if(parc->suivant==m)
			{
				parc->suivant=m->suivant;
//				free(m);
				MessageUrgence("Voiture supprimer");
		
			}
			else
				MessageUrgence("Voiture non trouvee");
		}
	}
	return l;


}






		

		







//********************************************************
//**	Fonction  : ListeVide       					**
//**	Parametre : liste               				**
//**	Traitement: Verifier si la liste est vide ou pas**                     
//**	Retourne  : 0 si la liste et vide et 1 sinon    **
//********************************************************

int ListeVide(liste l)
{
	if(l==NULL)
		return 0;
	else
		return 1;

}





//********************************************************
//**	Fonction  : Inserer voiture en fin          	**
//**	Parametre : liste de matricule  et une cellule  **
//**                 matricule 				            **
//**	Traitement: Inserer un matricule à la fin de la ** 
//**                liste de matricule                  **
//**	Retourne  : Liste de matricule                  **
//**    Utilise   : ListeVide                           **
//********************************************************

liste inserer_en_fin(liste l,cellule *elt)
{
	cellule *p;

	p=(cellule *)malloc(sizeof cellule);

	if (ListeVide(l)==0)
		return elt;
	
	p=l;
	while(p->suivant!=NULL)
	{
		p=p->suivant;
	}
	p->suivant=elt;
	return l;
}
/*liste inserer_en_fin(liste l,cellule *elt)
{
	if(l==NULL)
		return elt;
	else return inserer_en_fin(l->suivant,elt);
}*/






//*******************************************************
//**    Fonction  : SupprimerPosition				   **												
//** 	Parametre :	Elle prend la liste et la position **
//**                de l'element			           **
//**		Traitement: Supprimer un element à partir  **
//**                de sa position					   **									
//**    Retourne  : la liste apres ou sans suppression **																		
//*******************************************************



liste SupprimerPosition(liste l,cellule *supp)
{
	cellule *tmp;
	tmp=l;
	while((tmp->suivant!=supp)&&(tmp!=NULL))
		tmp=tmp->suivant;
			
	if(tmp->suivant==supp)
	{
		tmp->suivant=supp->suivant;
		free(supp);
	}

	return l;
}






