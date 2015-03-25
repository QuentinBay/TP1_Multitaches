/*************************************************************************
                           GestionClavier  -  description
                             -------------------
    début                : GestionClavier
    copyright            : (C) GestionClavier par GestionClavier
    e-mail               : GestionClavier
*************************************************************************/

//--- Interface de la tâche <GestionClavier> (fichier GestionClavier.h) --
#if ! defined ( GestionClavier_H )
#define GestionClavier_H

//------------------------------------------------------------------------
// Rôle de la tâche <GestionClavier>
//
//
//------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////  INCLUDE
//--------------------------------------------------- Interfaces utilisées
#include "/share/public/tp/tp-multitache/Menu.h"
#include "Voie.h"
#include <unistd.h>
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
pid_t CreerEtActiverGestionClavier (void);
// Mode d'emploi :
//
// Contrat :
//

void Commande ( char code );
// Mode d'emploi :
//
// Contrat :
//

void Commande ( Voie entree, Voie sortie );
// Mode d'emploi : Gestion de l arrivee manuelle
//
// Contrat :
//

void Commande ( Voie uneVoie, unsigned int duree );
// Mode d'emploi : cas de changement de duree d un feu vert
//
// Contrat :
//

#endif // GestionClavier_H

