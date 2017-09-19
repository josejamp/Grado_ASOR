#!/bin/bash

file="contactos.txt"

function agenda {
	opt=("Listar" "Buscar" "Borrar" "Añadir" "Salir")
	select op in "${opt[@]}"
	do
	case $op in
		"Listar") listar;;
		"Buscar") buscar;;	
		"Borrar") borrar;;
		"Añadir") añadir;;
		"Salir") salir;;
		*) echo invalid option;;
	esac
	done
}

function listar {
#	while read line
#	do
	BCKFS=$IFS
	IFS=$'\n'
	if   test -s "$file" ; then
		for line in `cat $file`; do
			#convertimos los ":" en " " y hacemos un array
			IFS=$BCKFS
			nueva=(${line//:/ })
			nombre=${nueva[0]}
			telefono=${nueva[1]}
			mail=${nueva[2]}
			echo "Nombre: $nombre"
			echo "Telefono: $telefono"
			echo "Mail: $mail"
			echo -n -e "\n"
			IFS=$'\n'
		done
	else
		echo "La agenda está vacía"
	fi
	IFS=$BCKFS
#	done < "$file"
}

function buscar {
	encontrado=0
	echo -n "Buscar: "
	read buscar
	while read line 
	do
		result=$(grep $buscar <<<$line)
		if grep -q $buscar <<<$line; then
			nueva=(${result//:/ })
			nombre=${nueva[0]}
			telefono=${nueva[1]}
			mail=${nueva[2]}
			echo "Nombre: $nombre"
			echo "Telefono: $telefono"
			echo "Mail: $mail"
			echo -n -e "\n"
			encontrado=1
		fi
	done < "$file"
	if  [ $encontrado -eq 0 ]; then
		echo "No encontrado"
	fi
}

function borrar {
	encontrado=0
	echo -n "Nombre: "
	read b
	if grep -q ^$b: "$file"; then
		sed -i '/^'"$b"':.*:.*$/d' "contactos.txt"
	else
		echo "La persona no está en el archivo"
	fi
}

#function borrar {
#	encontrado=0
#	echo -n "Nombre: "
#	read b
#	if grep -q ^$b: "$file"; then
#		result=$(grep "^$b:" -v "$file")
#		echo "$result" > "$file"
#	else
#		echo "La persona no está en el archivo"
#	fi
#}

function añadir {
	echo -n "Nombre: "
	read nombre
	echo -n "Teléfono: "
	read telefono
	echo -n "Mail: "
	read mail
	echo "$nombre:$telefono:$mail" >> "$file"
}

function salir {
	exit 0
}

agenda
