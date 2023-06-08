process=$1
pol=$2
folder="/lustre/ific.uv.es/prj/ific/flc/ntuples-250GeV-2023/"${process}"_"${pol}"/"
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

    for quark in 4 5 3 
    do
	for cut_p in 0 3
	do
	    #0 2 3
	    for cut_theta in 0 0.8
	    do
		#0 0.8	       
		cat > ${local}/steer/dedx_${process}_${pol}_quark${quark}_${name}_cutsP${cut_p}_cutTheta${cut_theta}.sh <<EOF
source ${local}/../init_ilcsoft.sh 
cd ${local}/
root -l -q analysis.cc\(\"${file}\",\"${process}_${pol}_${name}\",true,${cut_p},${cut_theta},$quark\) > log/dedx_${pol}_quark${quark}_${name}_cutsP${cut_p}_cutTheta${cut_theta} 
#root -l -q analysis.cc\(\"${file}\",\"${process}_${pol}_${name}\",false,${cut_p},${cut_theta},$quark\) > log/dedx2_${pol}_quark${quark}_${name}_cutsP${cut_p}_cutTheta${cut_theta}
cd -
EOF

		cat > ${local}/steer/dedx_${process}_${pol}_quark${quark}_${name}_cutsP${cut_p}_cutTheta${cut_theta}.sub <<EOF
# Unix submit description file
# kt_xNAMEfile.sub -- simple Marlin job
executable              = ${local}/steer/dedx_${process}_${pol}_quark${quark}_${name}_cutsP${cut_p}_cutTheta${cut_theta}.sh
log                     = ${local}/log/dedx_${process}_${pol}_quark${quark}_${name}_cutsP${cut_p}_cutTheta${cut_theta}.log
output                  = ${local}/log/outfile_dedx_${process}_${pol}_quark${quark}_${name}_cutsP${cut_p}_cutTheta${cut_theta}.txt
error                   = ${local}/log/errors_dedx_${process}_${pol}_quark${quark}_${name}_cutsP${cut_p}_cutTheta${cut_theta}.txt
should_transfer_files   = Yes
when_to_transfer_output = ON_EXIT
queue 1
EOF
		condor_submit ${local}/steer/dedx_${process}_${pol}_quark${quark}_${name}_cutsP${cut_p}_cutTheta${cut_theta}.sub
	    done
	done
    done
    counter=$((counter+1))
done
