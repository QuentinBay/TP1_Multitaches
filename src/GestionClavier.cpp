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

//------------------------------------------------------ Include personnel
#include "GestionClavier.h"
#include "/share/public/tp/tp-multitache/Menu.h"
#include "/share/public/tp/tp-multitache/Outils.h"
///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//---------------------------------------------------- Variables statiques
static pid_t generateurId;
static bool Off;
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
void CreerEtActiverGestionClavier ( pid_t geneId )
// Algorithme : Appel Menu
//
{
	generateurId = geneId;
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

void Commande ( TypeVoie entree, TypeVoie sortie )
// Algorithme :
//
{

} //----- fin de Commande

void Commande ( TypeVoie uneVoie, unsigned int duree )
// Algorithme :
//
{

} //----- fin de Commande