for pol in "eL_pR" "eR_pL" 
do
    
    for sample in "2f_hadronic_sample"
    do
	for dedx in 7
	do
	    hadd results/AFBc${dedx}_method0_${sample}_${pol}_250GeV.root output/AFBc${dedx}_method0_${sample}_${pol}_*250GeV.root &
	    hadd results/AFBc${dedx}_method1_${sample}_${pol}_250GeV.root output/AFBc${dedx}_method1_${sample}_${pol}_*250GeV.root &
	    hadd results/AFBc${dedx}_method2_${sample}_${pol}_250GeV.root output/AFBc${dedx}_method2_${sample}_${pol}_*250GeV.root
	done
    done
done


for pol in "eL_pR" "eR_pL"
do

    for sample in "2f_hadronic_sample"
    do
        for dedx in 1 7
        do
            hadd results/AFBb${dedx}_method0_${sample}_${pol}_250GeV.root output/AFBb${dedx}_method0_${sample}_${pol}_*250GeV.root &
            hadd results/AFBb${dedx}_method1_${sample}_${pol}_250GeV.root output/AFBb${dedx}_method1_${sample}_${pol}_*250GeV.root &
            hadd results/AFBb${dedx}_method2_${sample}_${pol}_250GeV.root output/AFBb${dedx}_method2_${sample}_${pol}_*250GeV.root
        done
    done
done

