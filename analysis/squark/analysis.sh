process=$1
pol=$2
folder="/lustre/ific.uv.es/prj/ific/flc/ntuples-2020/"${process}"_"${pol}"/"
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

    cat > ${local}/steer/s_AFB_tests_${process}_${pol}_${name}.sh <<EOF
source ${local}/../init_ilcsoft.sh 
cd ${local}/
root -l -q analysis.cc\(\"${file}\",\"${process}_${pol}_${name}\",0\)
root -l -q analysis.cc\(\"${file}\",\"${process}_${pol}_${name}\",1\)
mv s_AFB_loose_${process}_${pol}_${name}_250GeV.root ${local}/output/.
mv s_AFB_tight_${process}_${pol}_${name}_250GeV.root ${local}/output/.

EOF

	cat > ${local}/steer/s_AFB_tests_${process}_${pol}_${name}.sub <<EOF
# Unix submit description file
# kt_xNAMEfile.sub -- simple Marlin job
executable              = ${local}//steer/s_AFB_tests_${process}_${pol}_${name}.sh
log                     = ${local}/log//s_AFB_tests_${process}_${pol}_${name}.log
output                  = ${local}/log/outfile_s_AFB_tests_${process}_${pol}_${name}.txt
error                   = ${local}/log/errors_s_AFB_tests_${process}_${pol}_${name}.txt
should_transfer_files   = Yes
when_to_transfer_output = ON_EXIT
queue 1
EOF
	condor_submit ${local}/steer/s_AFB_tests_${process}_${pol}_${name}.sub
	counter=$((counter+1))
done
