#!/bin/bash

# Récupérer le répertoire courant
current_dir="$(dirname "$0")"

# Exécuter la commande norminette sur les répertoires src et libft et filtrer les erreurs avec grep
norminette "$current_dir/../src" "$current_dir/../libft" | grep "Error"

