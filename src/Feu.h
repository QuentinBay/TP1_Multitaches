/*************************************************************************
                           Feu  -  description
                             -------------------
    début                : Feu
    copyright            : (C) Feu par Feu
    e-mail               : Feu
*************************************************************************/

//---------- Interface de la tâche <Feu> (fichier Feu.h) -------
#if ! defined ( Feu_H )
#define Feu_H

//------------------------------------------------------------------------
// Rôle de la tâche <Feu>
//
//
//------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////  INCLUDE
//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
void CreerEtActiverFeu (int unIdDureeFeu, int unIdCouleurFeu, int unIdSemFeu);
// Mode d'emploi : Initialise le handler pour gerer le SIGUSR2
//
// Contrat :
//

#endif // Feu_H

