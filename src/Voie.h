/*************************************************************************
                           Voie  -  description
                             -------------------
    début                : Voie
    copyright            : (C) Voie par Voie
    e-mail               : Voie
*************************************************************************/

//---------- Interface de la tâche <Voie> (fichier Voie.h) -------
#if ! defined ( Voie_H )
#define Voie_H

//------------------------------------------------------------------------
// Rôle de la tâche <Voie>
//
//
//------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////  INCLUDE
//--------------------------------------------------- Interfaces utilisées
#include <unistd.h>
#include "/share/public/tp/tp-multitache/Outils.h"
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
void CreerEtActiverVoie ( TypeVoie uneVoie, int unIdMemCouleurFeux, int unIdBal );
// Mode d'emploi : Initialise le handler pour gerer le SIGUSR2
//
// Contrat :
//

#endif // Voie_H

