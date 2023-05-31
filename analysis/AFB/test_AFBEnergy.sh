process="2f_hadronic_sample"
local=$PWD

for pol in "eL_pR" "eR_pL"
do

folder="/lustre/ific.uv.es/prj/ific/flc/ntuples-250GeV-2023/"${process}"_"${pol}"/"

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
	
	cat > ${local}/steer/afbenergy_${process}_${pol}_${name}.sh <<EOF
source ${local}/../init_ilcsoft.sh
root -l ${local}/AFBEnergyDep.cc\(\"${file}\",\"${process}\",\"${pol}\",${counter},0.3\) > ${local}/output/log_AFBEnergyDep_${process}_${pol}_${name}
mv AFBEnergyDep_${process}_${pol}_file_${name}.root ${local}/output/.
EOF
	
	cat > ${local}/steer/afbenergy_${process}_${pol}_${name}.sub <<EOF
# Unix submit description file
# kt_xNAMEfile.sub -- simple Marlin job
executable              = ${local}/steer/afbenergy_${process}_${pol}_${name}.sh
log                     = ${local}/log/afbenergy_${process}_${pol}_${name}.log
output                  = ${local}/log/outfile_afbenergy_${process}_${pol}_${name}.txt
error                   = ${local}/log/errors_afbenergy_${process}_${pol}_${name}.txt
should_transfer_files   = Yes
when_to_transfer_output = ON_EXIT
queue 1
EOF
	
	if [ -f ${local}/output/AFBEnergyDep_${process}_${pol}_file_${name}.root ];
	then
            echo "Skip _${process}_${pol}_${name}"
	else	
	    condor_submit ${local}/steer/afbenergy_${process}_${pol}_${name}.sub
	fi
	
	counter=$((counter+1))
    done
done




