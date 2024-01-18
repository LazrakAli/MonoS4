

Association* creerAssociation(char *nom){
    Association *Assoc=(Association *)malloc(sizeof(Association));
    Assoc->nomAssoc=strdup(nom);
    Assoc->lesMembres=NULL;
    return Assoc;
}

void ajouterPersonne(Association *Assoc, char *nom) {
    Element *elm = (Element *)malloc(sizeof(Element));
    elm->nom = strdup(nom);
    elm->suivant = Assoc->lesMembres;
    Assoc->lesMembres = elm;
}


void supprimerPersonne(Association *Assoc, char *nom) {
    if (Assoc->lesMembres == NULL) {
        return; // La liste des membres est vide, rien à supprimer
    }

    if (!strcmp(Assoc->lesMembres->nom, nom)) {
        Element *aSupprimer = Assoc->lesMembres;
        Assoc->lesMembres = Assoc->lesMembres->suivant;
        free(aSupprimer->nom);
        free(aSupprimer);
        return;
    }

    Element *el = Assoc->lesMembres;
    while (el->suivant != NULL) {
        if (!strcmp(el->suivant->nom, nom)) {
            Element *aSupprimer = el->suivant;
            el->suivant = el->suivant->suivant;
            free(aSupprimer->nom);
            free(aSupprimer);
            return;
        }
        el = el->suivant;
    }
}


MaisonDesAssociations* creerMaisonAssoc() {
    MaisonDesAssociations *massoc = (MaisonDesAssociations *)malloc(sizeof(MaisonDesAssociations));
    massoc->mesAssociations = NULL;
    massoc->suivant = NULL;
    return massoc;
}

void ajouterAssociation(MaisonDesAssociations *massoc,Association *assoc){
    if (!massoc || !assoc){
        printf("Erreur dans les parametre passée!");
        return;
    }
    assoc->lesMembres=massoc->mesAssociations;
    massoc->mesAssociations=assoc;
}

void supprimerAssociation(MaisonDesAssociations *massoc, Association *assoc) {
    if (!massoc || !assoc) {
        printf("Erreur dans les parametres passes !");
        return;
    }

    if (massoc->mesAssociations == assoc) {
        massoc->mesAssociations = assoc->suivant;
        free(assoc);
        return;
    }

    Association *prevAssoc = massoc->mesAssociations;
    while (prevAssoc->suivant) {
        if (prevAssoc->suivant == assoc) {
            prevAssoc->suivant = assoc->suivant;
            free(assoc);
            return;
        }
        prevAssoc = prevAssoc->suivant;
    }
}
