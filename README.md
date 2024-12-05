

# Projet de compilation

Projet académique ayant pour but de réaliser en compilateur traduisant du code source écrit en\
langage **MyML** (un petit langage fonctionel similaire à ML/Haskell avec une syntaxe adhoc)\
vers le langage **P-Code** (un langage similaire à l'assembleur).

Le but etant que le compilateur fonctionne sur un ensemble de fonctionnalités du langage MyML.

Les attendus sont sur le site https://thor.enseirb-matmeca.fr/ruby/projects/if204/ sous forme de sections.

## Fonctionnalités

Notre compilateur final supporte (objectifs attendus):
- Les opérations arithmétiques d'entiers            (section 0)
- La gestion des variables globales                 (section 1)
- La gestion des variables locales (et masquage)    (section 2)
- Les conditionelles simples                        (section 3)
- Les conditionelles imbriquées                     (section 4)
- Les fonctions simples                             (section 5)
- Les fonctions récursives                          (section 6)

Ainsi tous les objectifs attendus sont bien supportés par le compilateur.

Il supporte aussi (objectifs d'initiative):
- La redéfinition des variables globales (utilisation de STORE)                 -> voir `tst/own/ecrase_var_globale.ml`
- L'appel imbriquées de fonctions (à ne pas confondre avec l'appel récursif)    -> voir `tst/own/multiple_fonctions.ml`

Mais il ne supporte pas (objectifs supplémentaires / idées d'amélioration):
- La redéfinition de fonctions (overriding)                                     -> voir `tst/own/fonction_redefinition.ml`
- La surcharge de fonctions (overloading)                                       -> voir `tst/own/fonction_surcharge.ml`
- Les types (autre que entier)                                                  -> voir `tst/own/float.ml`
- La gestion des fonctions locales                                              -> voir `tst/own/fonction_definitions_imbriquees.ml`
- La gestion des variables globales dans les fonctions                          -> voir `tst/own/fonction_et_var.ml`

De plus, pour ce projet nous avons codé un testeur (nommé `tester`) qui compare caractère par caractère deux fichiers
- un fichier compilé pcode (sortie du compilateur ML)
- un fichier solution pcode (attendu écrit sur thor)
A noter qu'il compare aussi les fichiers ".fp" où se trouvent les fonctions pcode.

Ensuite le fichier "compil.sh" permet de compiler un fichier source ".ml" en pcode ".p" et ".fp"
mais aussi en ".c" et executable (".exe" sur Windows et pas d'extension sur Linux).

Enfin, à la fin du fichier "=`src/Attribut.c` se trouve une section pour gérer les extensions des noms de fichiers.
Ainsi un fichier "test_format.ml" se compile en "test_format.p", "test_format.fp", "test_format.c", "test_format"
comme demandé sur thor.




## Utilisation

- Pour compiler tous les outils (compilateur ML, compilateur PCode, testeur)\
`$ make`

- Pour compiler un fichier ml en pcode, C et executable\
`$ ./compil.sh <chemin/vers/fichier.ml>`\
A noter que les fichiers pcode/fpcode obtenus sont ajoutés dans le répertoire du projet (où se trouve le makefile)
alors que les fichiers C et executable sont ajoutés dans le répertoire `build`

- Pour compiler un fichier ml en pcode (simplement)\
`$ ./myml <chemin/vers/fichier.ml>`

- Pour executer l'outil de test (comparaison de fichier pcode/fpcode avec l'attendu du sujet)\
`$ make test`

- Pour revenir sur un répertoire d'origine sans fichiers compilés\
`$ make clean`