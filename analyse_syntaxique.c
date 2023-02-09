#include <string.h>
#include <stdlib.h> 
#include <stdio.h> 

#include "lecture_caracteres.h"
#include "analyse_lexicale.h"

Lexeme lexeme_en_cours ;
Nature_Caractere nature_caractere (char c);
void ajouter_caractere (char *s, char c);
int est_separateur(char c );
int est_chiffre(char c );
int est_symbole(char c );

void analyser(char *fichier)
{
    typedef enum {E_INIT, E_ENTIER, E_FIN} Etat_Automate;
    Etat_Automate etat=E_INIT;
    demarrer_car(fichier);

    while (est_separateur(caractere_courant())) 
    {
        avancer_car() ;
    } ;

    lexeme_en_cours.chaine[0] = '\0' ;

    while (etat != E_FIN) 
    {    
        switch (etat) 
        {
            case E_INIT: // etat initial
                switch(nature_caractere(caractere_courant())) 
                {
                    case C_FIN_SEQUENCE: 
                        lexeme_en_cours.nature = FIN_SEQUENCE;
                        etat = E_FIN;
                        break ;

                    case CHIFFRE: 
                        lexeme_en_cours.nature = ENTIER;
                        lexeme_en_cours.ligne = numero_ligne();
                        lexeme_en_cours.colonne = numero_colonne();
                        ajouter_caractere (lexeme_en_cours.chaine, caractere_courant());
                        lexeme_en_cours.valeur = caractere_courant() - '0';
                        etat = E_ENTIER;
                        avancer_car();
                        break;

                    case SYMBOLE: 
                        lexeme_en_cours.ligne = numero_ligne();
                        lexeme_en_cours.colonne = numero_colonne();
                        ajouter_caractere (lexeme_en_cours.chaine, caractere_courant());
                        switch (caractere_courant()) 
                        {
                            case '+':
                                lexeme_en_cours.nature = PLUS;
                                etat = E_FIN;
                                break;
                            case '-':
                                lexeme_en_cours.nature = MOINS;
                                etat = E_FIN;
                                break;
                            case '*':
                                lexeme_en_cours.nature = MUL;
                                etat = E_FIN;
                                break;
                            case '/':
                                lexeme_en_cours.nature = DIV;
                                etat = E_FIN;
                                break;
                            case '(':
                                lexeme_en_cours.nature = PARO;
                                etat = E_FIN;
                                break;
                            case ')':
                                lexeme_en_cours.nature = PARF;
                                etat = E_FIN;
                                break;
                            default:
                                printf("Erreur_Syntaxe_signe") ;
                                exit(0) ;
                        };
                        avancer_car() ;
                        break ;

                    default:
                        printf("Erreur_Lexicale_def\n") ;
                        exit(0) ;
                };
		        break ;

            case E_ENTIER:  // reconnaissance d'un entier
                switch(nature_caractere(caractere_courant())) 
                {
                    case CHIFFRE:
                        ajouter_caractere (lexeme_en_cours.chaine, caractere_courant());
                        lexeme_en_cours.valeur = lexeme_en_cours.valeur * 10 + caractere_courant() - '0';
                        etat = E_ENTIER;
                        avancer_car ();
                        break ;

                    default:
                        etat = E_FIN;
                } ;

            case E_FIN:  // etat final
                break ;
	    
	    } ; // fin du switch(etat)
	} ; // fin du while (etat != fin)







    //while (! fin_de_sequence()) 
    // 
        
	    //printf("%s\n",lexeme_en_cours.chaine);
    //    printf("%s\n",lexeme_en_cours.chaine);
	//    avancer();
    //} ;
   //arreter() ; // termine l'analyse lexicale
}