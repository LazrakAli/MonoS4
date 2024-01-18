# __MiniProjet 2__
Lazrak Ali 28605235
Selda Yildirim 3705100

## __Exercice 1__ 

### __Main_Default__ :

Pour un test par default des fonctions de recherche/affichage :
- Modifier ``main.o`` par ``mainBis.o`` dans le Makefile et Executer : 

```shell
./miniProjet2p1 ../GdeBiblio.txt 100
```
Cela testera la plupart des fonctions 

### __Main_Menu__ :

Executer :
```shell
./miniProjet2p1 
```
Vous pourrez ensuite tester les differentes fonction en parcourant le menu.

## __Exercice 2__ 

### __Main_Default__ 

Pour un test par default des fonctions de recherche/affichage :
Executer : 

```shell
./miniProjet2p2 ../GdeBiblio.txt 100
```
Cela testera la plupart des fonctions
Commenter dans le main les fonctions que l'on veut tester ou non


## __Exercice 3__ 

### __Question 1__ : 

#### __Recherche en fonction du numéro et titre__:

La recherche des livres par titre et numero est plus rapide par liste chainé avec biblioLC

- Pour la __liste chainée__ nous le temps de recherche en fonction du numéro et du titre semble linéaire car on insère en tête chaque nouveau livre. Ainsi pour une bibliothèque avec des numéros trié dans l'ordre croissant si on part du principe que l'on débute l'insertion par 0 alors plus on cherchera un livre dont le numéro est proche de 0 plus l'on mettra du temps à le trouver. Le constat est le même pour les titres, en revanche, si un titre se répètes le temps de rechercher sera identique.

- Pour une __table de hachage__ le temps de recherche en fonction du numéro et du titre fluctue aleatoirement ce qui s'explique par le fait que les clés de la table de hachage ne sont pas faites en fonction de ses deux arguments, on doit alors chercher dans chaque case du tableau de hachage. 
    - Temps de recherche en fonction du titre et du numéro dépend de la "chance", si la clé de l'auteur associé au numéro est au début du tableau, alors le temps sera plus court.


- Lorsque le livre est absent il s'agit du pire cas pour la recherche par numero et titre comme on doit parcourir toute la bibliotheque sans distinction entre la liste et la table de hachage. 

#### __Recherche en fonction de l'auteur__:

La recherche des livres par auteur est plus rapide par table de hachage car les cles sont calculé en fonction du nom de l'auteur (cle = somme des valeurs ascii sous la fonction de hachage)

- Pour la __liste chainée__ la vitesse de recherche reste lineaire donc sensiblement la meme avec la recherche par titre et auteur.

- Pour une __table de hachage__ la table de hachage nous economise du temps de recherche a l'aide des clés de hachage obtenu a l'aide du nom de l'auteur. En effet, on ignore tous les livres dont le nom d'auteur haché ne correspond pas a celui recherché


### __Question 2__ : 

Plus la table de hachage est grande plus le temps de calcul est long comme on doit parcourir plus de cases.

Le temps de recherche en fonction de la taille de la table de hachage correspond au fluctuation d'une fonction du type x².
Ainsi, si on choisit une taille trop petite alors le temps augmente, et si elle est trop grande alors le temps augmente aussi

### __Question 3__ : 

Les mains utilisés pour obtenir les données necessaire a la creation de courbe sont dans :
- ``./exo3/LC/*`` 
- ``./exo3/H/*`` 

Les courbes obtenu avec gnuplot sont dans le repertoire : ``./exo3/data/*``

### __Question 4__ : 

- Pour la ``liste chainée``, comme nous devons parcourir toute la liste pour vérifier tous les éléments le temps est forcément proportionnel au nombre d'éléments a vérifié.

- En revanche pour la ``table de hachage``,  nous pouvons  ignorer tous les auteurs n'ayant pas une clé de hachage identique au livre recherché, cela réduit drastiquement le temps de recherche