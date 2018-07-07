#!/bin/bash
additional=$1
todos=$(grep -REi 'TODO|FixMe' . | grep -vE 'Binary|grep_todos.sh|.git')

if [[ ! -z $additional ]]; then
	printf -- '%s\n' "${todos[@]}" | grep $additional
else
	printf '%s\n' "${todos[@]}"
fi
