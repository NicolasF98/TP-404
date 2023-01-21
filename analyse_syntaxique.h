#include <stdlib.h> 
#include <stdio.h> 
#include <string.h>

#include "analyse_lexicale.h"

void analyser (char *fichier) ;
// e.i : indifferent
// e.f : une Expression Arithmetique a ete lue dans fichier
// si elle ne contient pas d’erreur de syntaxe un message est affiche
// sinon le pgm termine sur un message d’erreur