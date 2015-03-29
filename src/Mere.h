/*************************************************************************
                           Mere  -  description
                             -------------------
    début                : Mere
    copyright            : (C) Mere par Mere
    e-mail               : Mere
*************************************************************************/

//---------- Interface de la tâche <Mere> (fichier Mere.h) -------
#if !defined ( Mere_H )
#define Mere_H

//------------------------------------------------------------------------
// Rôle de la tâche <Mere>
//
//
//------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////  INCLUDE
//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types
//Structure que l on va stocker dans la memoire partagee pour communiquer 
//la couleur du feu a la tache voie.
// - couleurNS est vrai si le feu de l axe nord sud est vert, faux sinon
// - couleurEO est vrai si le feu de l axe est ouest est vert, faux sinon
struct CouleurFeux
{
	bool couleurNS;
	bool couleurEO;
};

//Structure que l on va stocker dans la memoire partagee pour communiquer
//la duree des feux Nord-Sud et Est-Ouest
struct DureeFeux
{
	int dureeNS;
	int dureeEO;
};
//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
// type Nom ( liste de paramètres );
// Mode d'emploi :
//
// Contrat :
//

#endif // XXX_H
