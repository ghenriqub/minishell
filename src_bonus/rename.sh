#!/bin/bash

# Renomear todos os .c para _bonus.c
for f in *.c; do
    new="${f%.c}_bonus.c"
    mv -- "$f" "$new"
    echo "Renomeado: $f -> $new"

    # Substituir include dentro do arquivo já renomeado
    sed -i 's/#include "minishell.h"/#include "minishell_bonus.h"/' "$new"
    echo "Atualizado include em: $new"
done
