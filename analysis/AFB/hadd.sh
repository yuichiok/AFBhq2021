for pol in "eL_pR" "eR_pL" 
do
    hadd results/AFBc1_2f_hadronic_sample_${pol}_250GeV.root output/AFBc1_2f_hadronic_sample_${pol}_*250GeV.root &
    #hadd results/AFBc1_2f_hadronic_${pol}_250GeV.root output/AFBc1_2f_hadronic_${pol}_*250GeV.root
    
done



