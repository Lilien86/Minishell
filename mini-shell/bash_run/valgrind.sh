#!/bin/bash

cd "/nfs/homes/lauger/Documents/PROJECT/cercle_4/aller/mini-shell"

make re

# Nom du fichier binaire à tester avec Valgrind
binary="./minishell"

# Options de Valgrind
valgrind_options="--leak-check=full --show-leak-kinds=all --track-origins=yes --trace-children=yes --track-fds=yes --suppressions=./del.supp"
# valgrind_options="--show-leak-kinds=all --track-origins=yes --trace-children=yes --track-fds=yes --suppressions=./del.supp"

# Exécuter Valgrind
valgrind $valgrind_options $binary
