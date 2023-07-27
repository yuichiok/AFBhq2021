
process=$1
folder="/lustre/ific.uv.es/prj/ific/flc/ntuples-250GeV-2023/"${process}"/"
local=$PWD
counter=0

for file in ${folder}/*
do
    echo $file $counter
    name="000"$counter
    if [ $counter -gt 9 ]; then
        name="00"$counter
    fi

    if [ $counter -gt 99 ]; then
        name="0"$counter
    fi
    
    if [ $counter -gt 999 ]; then
        name=$counter
    fi


    for cuts in 0
    do

	cat > ${local}/steer/sel_${process}_${name}_cuts${cuts}.sh <<EOF
source ${local}/../init_ilcsoft.sh
root -l -q ${local}/test_selection.cc\(\"${file}\",\"${process}\",${counter},${cuts}\) > ${local}/output/log_sel_${process}_${name}_cuts${cuts}
mv selection*cuts${cuts}_${process}_file_${name}.root ${local}/output/.
EOF
	
	cat > ${local}/steer/sel_${process}_${name}_cuts${cuts}.sub <<EOF
# Unix submit description file
# kt_xNAMEfile.sub -- simple Marlin job
executable              = ${local}/steer/sel_${process}_${name}_cuts${cuts}.sh
log                     = ${local}/log/sel_${process}_${name}_cuts${cuts}.log
output                  = ${local}/log/outfile_sel_${process}_${name}_cuts${cuts}.txt
error                   = ${local}/log/errors_sel_${process}_${name}_cuts${cuts}.txt
should_transfer_files   = Yes
when_to_transfer_output = ON_EXIT
queue 1
EOF
	if [ -f ${local}/output/selection_cuts${cuts}_${process}_file_${name}.root ];
        then
            echo "Skip ${process}_${name}_cuts${cuts}"
        else	
	    condor_submit ${local}/steer/sel_${process}_${name}_cuts${cuts}.sub
	fi
    done
	
    counter=$((counter+1))

done



