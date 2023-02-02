#include <string.h>
#include <stdlib.h> 
#include <stdio.h> 

#include "lecture_caracteres.h"
#include "analyse_lexicale.h"


void analyser(char *fichier)
{
    demarrer(fichier);

    while (! fin_de_sequence()) 
    { 
        afficher (lexeme_courant());
	    printf("\n");
	    avancer();
    } ;
   arreter() ; // termine l'analyse lexicale
}