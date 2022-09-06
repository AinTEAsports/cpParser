#!/bin/bash


script_name="${1}"
run_script=0
output_script_name=""


function show_usage {
        echo -e "
Usage: ${0} <filename> [OPTIONS...]

Required arguments:
        <filename>                              The C++ script you want to compile

Optionnal arguments:
        --run [OPTIONS...]              If you want to run the script after compiling it.

                                        [OPTIONS...] corresponds to he flags you want to pass when
                                                     executing your script

Examples:
${0} main.cpp
${0} main.cpp --run \"--help\"
"
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


function compile_file {
        input_file=${1}
        output_file=${2}

        if [[ -z ${output_file} ]]; then
            output_file="a.out"
        fi

        g++ "${input_file}" -lcpparser -I include -L lib -o "${output_file}"
}




if [[ $# -eq 0 ]]; then
	show_usage

	exit 0
fi



while [[ -n ${1} ]]; do
	case ${1} in
		-h|--help)
			show_usage

			exit 0
			;;
		--run)
			run_script=1
			shift

			arguments="$*"
			shift

			;;
		*)
			shift

			;;
	esac
done


output_script_name=$(remove_extension "${script_name}")

compile_file "${script_name}" "${output_script_name}"


if [[ ${run_script} == 1 ]]; then
	./"${output_script_name}" ${arguments}
fi
