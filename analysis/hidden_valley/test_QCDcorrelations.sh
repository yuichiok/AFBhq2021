
process=$1
pol=$2
local=$PWD
counter=0


signal=1
process2=${process}


if [ "$process" = "2f_hadronic_sample" ];
then
    signal=-1
fi

if [ "$process" = "2f_hadronic" ];
then
    signal=0
    process2="2f_hadronic_sample"
fi

folder="/lustre/ific.uv.es/prj/ific/flc/ntuples-250GeV-2023/"${process2}"_"${pol}"/"


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

    for cuts in  0 1 2 3 4 5 6
    do

	cat > ${local}/steer/qcd_${process}_${pol}_${name}_cuts${cuts}.sh <<EOF
source ${local}/../init_ilcsoft.sh
root -l -q ${local}/test_QCDcorrelations.cc\(\"${file}\",\"${process}\",\"${pol}\",${counter},${cuts},${signal}\) > ${local}/output/log_QCDcorrelations_${process}_${pol}_${name}_cuts${cuts}
EOF
	
	cat > ${local}/steer/qcd_${process}_${pol}_${name}_cuts${cuts}.sub <<EOF
# Unix submit description file
# kt_xNAMEfile.sub -- simple Marlin job
executable              = ${local}/steer/qcd_${process}_${pol}_${name}_cuts${cuts}.sh
log                     = ${local}/log/qcd_${process}_${pol}_${name}_cuts${cuts}.log
output                  = ${local}/log/outfile_qcd_${process}_${pol}_${name}_cuts${cuts}.txt
error                   = ${local}/log/errors_qcd_${process}_${pol}_${name}_cuts${cuts}.txt
should_transfer_files   = Yes
when_to_transfer_output = ON_EXIT
queue 1
EOF
	if [ -f ${local}/output/QCDcorrelations_cuts${cuts}_${process}_${pol}_file_${name}.root ];
        then
            echo "Skip ${process}_${pol}_${name}_cuts${cuts}"
        else	
	    condor_submit ${local}/steer/qcd_${process}_${pol}_${name}_cuts${cuts}.sub
	fi
    done
	
    counter=$((counter+1))

done



