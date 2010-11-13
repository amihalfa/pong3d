#!/bin/bash

# Retient le dossier d'appel
start_dir=`pwd`

# Recupere le dossier ou se trouve le script
script_dir="$(dirname "$(readlink -f ${BASH_SOURCE[0]})")";

# On va au dossier ou se trouve le script
cd $script_dir;

# On lance l'application
./Pong

# On retourne au dossier de depart
cd $start_dir;
