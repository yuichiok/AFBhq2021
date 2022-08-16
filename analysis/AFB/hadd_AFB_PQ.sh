for pol in "eL_pR" "eR_pL"
do
    for sample in "2f_hadronic_sample" "2f_hadronic" "qqH" "4f_ZZ_hadronic" "4f_WW_hadronic"
    do
	for quark in 4 5 
	do
	    hadd -f -j 4 results/AFB_PQ_pdg${quark}_${sample}_${pol}_250GeV.root output/AFB_quark${quark}_${sample}_${pol}_*250GeV.root
	done
    done
done

