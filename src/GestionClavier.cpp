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
//------------------------------------------------------ Include personnel
#include "GestionClavier.h"
#include "/share/public/tp/tp-multitache/Menu.h"
#include "/share/public/tp/tp-multitache/Outils.h"
///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//---------------------------------------------------- Variables statiques

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
void Commande ( char code )
// Algorithme :
//
{
	if (code=='q' || code=='Q')
	{
		/* On quitte l application */
		exit(0);
		
	}
	else if (code=='g' || code=='G')
	{
		/* On active/desactive le generateur */
	}
	else if (code=='m' || code=='M')
	{
		/* Arrivee manuelle d une voiture sur le carrefour */
	}
	else if (code=='d' || code=='D')
	{
		/* Modifie la duree du feu vert */
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