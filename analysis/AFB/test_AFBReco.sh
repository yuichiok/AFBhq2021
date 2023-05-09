process=$1
pol=$2
folder="/lustre/ific.uv.es/prj/ific/flc/ntuples-250GeV-2023/"${process}"_"${pol}"/"
local=$PWD


for quark in 5 4
do
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
#int AFBAnalysis( TString file="", TString process="2f_hadronic", TString pol="eL", int file_n=0, int quark=4, int method=0){
	
	cat > ${local}/steer/afbreco_quark${quark}_${process}_${pol}_${name}.sh <<EOF
source ${local}/../init_ilcsoft.sh
root -l ${local}/AFBReco.cc\(\"${file}\",\"${process}\",\"${pol}\",${counter},${quark}\) > ${local}/output/log_AFBReco_quark${quark}_${process}_${pol}_${name}
mv AFBreco_quark${quark}_${process}_${pol}_file_${name}.root ${local}/output/.
EOF
	
	cat > ${local}/steer/afbreco_quark${quark}_${process}_${pol}_${name}.sub <<EOF
# Unix submit description file
# kt_xNAMEfile.sub -- simple Marlin job
executable              = ${local}/steer/afbreco_quark${quark}_${process}_${pol}_${name}.sh
log                     = ${local}/log/afbreco_quark${quark}_${process}_${pol}_${name}.log
output                  = ${local}/log/outfile_afbreco_quark${quark}_${process}_${pol}_${name}.txt
error                   = ${local}/log/errors_afbreco_quark${quark}_${process}_${pol}_${name}.txt
should_transfer_files   = Yes
when_to_transfer_output = ON_EXIT
queue 1
EOF
      	    
	if [ -f ${local}/output/AFBreco_quark${quark}_${process}_${pol}_file_${name}.root ];
	then
		echo "Skip quark${quark}_${process}_${pol}_${name}"
	else	
	    condor_submit ${local}/steer/afbreco_quark${quark}_${process}_${pol}_${name}.sub
	fi
	
	counter=$((counter+1))
    done
done



