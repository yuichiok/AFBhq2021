for pol in "eL_pR" "eR_pL"
do
    sample="2f_hadronic_sample"
    hadd -f results/AFBenergyDep_${sample}_${pol}_250GeV.root output/AFBEnergyDep_${sample}_${pol}_file*.root
done
