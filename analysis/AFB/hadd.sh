for pol in "eL_pR" "eR_pL" 
do
    for dedx in 4
    do
	hadd results/AFBc${dedx}_method0_2f_hadronic_sample_${pol}_250GeV.root output/AFBc${dedx}_method0_2f_hadronic_sample_${pol}_*250GeV.root & 
	hadd results/AFBc${dedx}_method1_2f_hadronic_sample_${pol}_250GeV.root output/AFBc${dedx}_method1_2f_hadronic_sample_${pol}_*250GeV.root &
	hadd results/AFBc${dedx}_method2_2f_hadronic_sample_${pol}_250GeV.root output/AFBc${dedx}_method2_2f_hadronic_sample_${pol}_*250GeV.root
	
	hadd results/AFBb${dedx}_method0_2f_hadronic_sample_${pol}_250GeV.root output/AFBb${dedx}_method0_2f_hadronic_sample_${pol}_*250GeV.root &
	hadd results/AFBb${dedx}_method1_2f_hadronic_sample_${pol}_250GeV.root output/AFBb${dedx}_method1_2f_hadronic_sample_${pol}_*250GeV.root &
	hadd results/AFBb${dedx}_method2_2f_hadronic_sample_${pol}_250GeV.root output/AFBb${dedx}_method2_2f_hadronic_sample_${pol}_*250GeV.root
    done
done



