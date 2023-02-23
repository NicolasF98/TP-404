#include <string.h>
#include <stdlib.h> 
#include <stdio.h> 

#include "lecture_caracteres.h"
#include "analyse_lexicale.h"

Lexeme lexeme_en_cours;	/* le lexeme courant */

void ajouter_caractere (char *s, char c);
Nature_Caractere nature_caractere (char c);
int est_separateur(char c ) ;
int est_chiffre(char c );
int est_symbole(char c ) ;


void reconnaitre_syntaxe() 
{
      typedef enum {E_INIT, E_ENTIER, E_SIGNE, E_FIN} Etat_Automate;
      Etat_Automate etat=E_INIT;

      // on commence par lire et ignorer les separateurs
      while (est_separateur(caractere_courant())) 
      {
        	avancer_car() ;
      } ;

      lexeme_en_cours.chaine[0] = '\0' ;

      // on utilise ensuite un automate pour reconnaitre et construire le prochain lexeme

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
                  printf("Erreur_syntax (operation vide)\n") ;                     
                  exit(0);

               case CHIFFRE: 
                  lexeme_en_cours.nature = ENTIER;
                  lexeme_en_cours.ligne = numero_ligne();
                  lexeme_en_cours.colonne = numero_colonne();
                  ajouter_caractere (lexeme_en_cours.chaine, caractere_courant()) ;
                  lexeme_en_cours.valeur = caractere_courant() - '0';
                  etat = E_ENTIER;
                  avancer_car() ;
                  break ;

               default:
			   		etat = E_FIN;
                	printf("Erreur_syntax (ne commence pas par entier)\n") ;
					exit(0);
                
            } ;
		    break ;

			case E_ENTIER:  // reconnaissance d'un entier
				switch(nature_caractere(caractere_courant())) 
				{
					case SYMBOLE:
						lexeme_en_cours.ligne = numero_ligne();
						lexeme_en_cours.colonne = numero_colonne();
						ajouter_caractere (lexeme_en_cours.chaine, caractere_courant()) ;
						switch (caractere_courant()) 
						{
							case '+':
								lexeme_en_cours.nature = PLUS;
								etat = E_SIGNE;
								break;
							case '-':
								lexeme_en_cours.nature = MOINS;
								etat = E_SIGNE;
								break;
							case '*':
								lexeme_en_cours.nature = MUL;
								etat = E_SIGNE;
								break;
							default:
								etat = E_FIN;
								printf("Erreur_syntax (pas de signe apres entier)\n") ;
								exit(0);

						} ;
						avancer_car();
						break;

					default:
						printf("Erreur_syntax (pas de signe apres entier)\n") ;
						exit(0);
				};	

			case E_SIGNE:  // reconnaissance d'un signe
				switch(nature_caractere(caractere_courant())) 
				{
					case CHIFFRE:
						ajouter_caractere (lexeme_en_cours.chaine, caractere_courant()) ;
                     	lexeme_en_cours.valeur = lexeme_en_cours.valeur * 10 + caractere_courant() - '0';
                  		etat = E_FIN;
                  		avancer_car ();
						break ;

					default:
						etat = E_FIN;
						printf("Erreur_syntax (pas de signe apres entier)Z\n") ;
						break;
               	} ;	

			case E_FIN:  // etat final
		        	break ;
	    
	    } ; // fin du switch(etat)
	} ; // fin du while (etat != fin)
}


void analyser(char *fichier)
{   
    demarrer_car(fichier);
	reconnaitre_syntaxe();
}