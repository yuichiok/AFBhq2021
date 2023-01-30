for pol in "eL_pR" "eR_pL"
do
    sample="2f_hadronic_sample"
    hadd -f results_500GeV/AFBenergyDep_${sample}_${pol}.root output/AFBEnergyDep_${sample}_${pol}_file*.root
done
