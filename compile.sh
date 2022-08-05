#!/bin/bash


script_name=""
run_script=0
output_script_name=""


function show_usage {
	echo -e "help message"
}


function remove_extension {
	name=${1}
	name=$(echo "${name}" | cut -d '.' -f 1)

	echo "${name}"
}


function compile_file {
	input_file=${1}
	output_file=${2}

	if [[ -z ${output_file} ]]; then
		output_file="a.out"
	fi

	g++ "${input_file}" -lcpparser -I include -L lib -o "${output_file}"
}


if [[ $# -lt 1 && $# -gt 2 ]]; then
	echo "${0}: invalid usage"
	show_usage

	exit 1
fi


while [[ -n ${1} ]]; do
	case ${1} in
		--run)
			run_script=1

			shift
			;;
		*)
			if [[ ${1} == --* || ${1} == -* ]]; then
				echo "${0}: unknown flag found ('${1}')"
				show_usage

				exit 1
			fi

			script_name=${1}
			
			shift
			;;
	esac
done


# echo "Script name : ${script_name}"
# echo "Run script : ${run_script}"


if [[ -z ${script_name} ]]; then
	echo "${0}: no given filename"
	show_usage

	exit 1
fi

if [[ ! -f ${script_name} ]]; then
	echo "${0}: given filename does not exists or was not found in this directory"
	show_usage

	exit 1
fi



output_script_name=$(remove_extension "${script_name}")

if [[ -e ${output_script_name} ]]; then
	echo "${0}: '${output_script_name}' file already exists"
	exit 1
fi

compile_file "${script_name}" "${output_script_name}"


if [[ ${run_script} -eq 1 ]]; then
	./"${output_script_name}"
fi

