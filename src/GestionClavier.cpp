/*************************************************************************
                           GestionClavier  -  description
                             -------------------
    début                : GestionClavier
    copyright            : (C) GestionClavier par GestionClavier
    e-mail               : GestionClavier
*************************************************************************/

//---------- Réalisation de la tâche <GestionClavier> (fichier GestionClavier.cpp) ---

/////////////////////////////////////////////////////////////////  INCLUDE
//-------------------------------------------------------- Include système
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <sys/msg.h>
//------------------------------------------------------ Include personnel
#include "GestionClavier.h"
#include "/share/public/tp/tp-multitache/Menu.h"
#include "/share/public/tp/tp-multitache/Outils.h"
#include "/share/public/tp/tp-multitache/Voiture.h"	
///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//---------------------------------------------------- Variables statiques
static pid_t generateurId;
static int balId;
static bool Off;
static unsigned int numVoiture = 0;
//------------------------------------------------------ Fonctions privées
//static type nom ( liste de paramètres )
// Mode d'emploi :
//
// Contrat :
//
// Algorithme :
//
//{
//} //----- fin de nom

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
void CreerEtActiverGestionClavier ( pid_t geneId , int uneBalId )
// Algorithme : Appel Menu
//
{
	generateurId = geneId;
	balId = uneBalId;
	Off = false;
	Menu();
}

void Commande ( char code )
// Algorithme :
//
{
	if ( code=='Q' )
	{
		/* On quitte l application */
		exit(0);
		
	}
	else
	{
		if ( Off )
		{
			/* Il faut desactiver le generateur */
			kill ( generateurId , SIGSTOP );
			Effacer ( ETAT_GENERATEUR );
			Afficher ( ETAT_GENERATEUR , "OFF" , GRAS );
			Off = false;
			
		}
		else
		{
			/* Il faut activer le generateur */
			kill ( generateurId , SIGCONT );
			Effacer ( ETAT_GENERATEUR );
			Afficher ( ETAT_GENERATEUR , "ON" , GRAS );
			Off = true;
		}
	}
} //----- fin de Commande

void Commande ( TypeVoie uneEntree, TypeVoie uneSortie )
// Algorithme :
//
{
	struct Voiture voiture;
	voiture.entree = uneEntree;
	voiture.sortie = uneSortie;
	if ( numVoiture == numeroMaxManuel )
	{
		/* On a atteint le numero max */
		numVoiture = numeroMinManuel;
	}
	else
	{
		numVoiture++;
	}
	voiture.numero = numVoiture;

	//Creation et envoie du message
	struct MsgVoiture *ptrMsg, msgVoiture;
	ptrMsg=&msgVoiture;
	ptrMsg->type=(long)uneEntree;
	ptrMsg->uneVoiture=voiture;
	

	if ( (msgsnd( balId, ptrMsg, TAILLE_MSG_VOITURE, 0 )) == 0 )
	{
		Effacer (NUMERO);
		Afficher(NUMERO, voiture.numero, GRAS);
		Effacer (ENTREE);
		Afficher(ENTREE, voiture.entree, GRAS);
		Effacer (SORTIE);
		Afficher(SORTIE, voiture.sortie, GRAS);
		OperationVoie (PLUS, uneEntree);
	}
	//Effacer (MESSAGE);
	//Afficher(MESSAGE, "msg créé !", GRAS);
} //----- fin de Commande

void Commande ( TypeVoie uneVoie, unsigned int duree )
// Algorithme :
//
{

} //----- fin de Commande