process=$1
pol=$2
folder="/lustre/ific.uv.es/prj/ific/flc/ntuples-2023-test/"${process}"_"${pol}"/"
local=$PWD
counter=0

for file in ${folder}/*
do
    echo $file $counter
    name="00"$counter
    if [ $counter -gt 9 ]; then
        name="0"$counter
    fi

    if [ $counter -gt 99 ]; then
        name=$counter
    fi

	for cut_p in 3
	do
   	    cat > ${local}/steer/dedx_${process}_${pol}_${name}_cutsP${cut_p}.sh <<EOF
source ${local}/../init_ilcsoft.sh 
cd ${local}/
root -l -q analysis_dEdxDist.cc\(\"${file}\",\"${process}_${pol}_${name}\",${cut_p}\) > log/dedx_${pol}_${name}_cutsP${cut_p} 

cd -
EOF

    cat > ${local}/steer/dedx_${process}_${pol}_${name}_cutsP${cut_p}.sub <<EOF
# Unix submit description file
# kt_xNAMEfile.sub -- simple Marlin job
executable              = ${local}/steer/dedx_${process}_${pol}_${name}_cutsP${cut_p}.sh
log                     = ${local}/log/dedx_${process}_${pol}_${name}_cutsP${cut_p}.log
output                  = ${local}/log/outfile_dedx_${process}_${pol}_${name}_cutsP${cut_p}.txt
error                   = ${local}/log/errors_dedx_${process}_${pol}_${name}_cutsP${cut_p}.txt
should_transfer_files   = Yes
when_to_transfer_output = ON_EXIT
queue 1
EOF
        condor_submit ${local}/steer/dedx_${process}_${pol}_${name}_cutsP${cut_p}.sub
    done
    counter=$((counter+1))
done
