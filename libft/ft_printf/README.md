# ft_printf

Ce projet consiste en une implémentation personnalisée de la fonction `printf` dans le cadre du cursus à l'école 42. La fonction `ft_printf` permet de formater et d'afficher du texte avec une syntaxe similaire à la fonction `printf` standard du langage C.

## Fonctionnalités

- Gestion des spécificateurs de format tels que `%s`, `%d`, `%x`, etc.
- Prise en charge de la largeur de champ, de la précision et d'autres options de formatage.

## Installation

Pour intégrer la fonction `ft_printf` dans votre projet, suivez ces étapes :

1. Clonez ce référentiel sur votre machine locale.
	```bash
   git clone https://github.com/votre_nom/ft_printf.git
   ```
   ```bash
   cd ft_printf
   ```
   ```bash
   make
   ```
## Utilisation

1. Incluez le fichier d'en-tête ft_printf.h dans vos fichiers source.
	```c
	#include "ft_printf.h"
	```
2. Utilisez la fonction ft_printf dans votre code
	```c
	int main() {
    char *name = "John";
    int age = 28;
    double salary = 50000.75;

    ft_printf("Bienvenue, %s!\n", name);
    ft_printf("Vous avez %d ans.\n", age);
    ft_printf("Votre salaire est de %.2f dollars par an.\n", salary);

    return 0;
	}
	```


