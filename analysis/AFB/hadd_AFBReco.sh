for pol in "eL_pR" "eR_pL"
do
    for sample in "2f_hadronic"
    do
	for quark in 4 5 
	do
	    for method in 0 1 2
	    do
		hadd -f results/AFBreco_pdg${quark}_${sample}_${pol}_250GeV_cheatmethod_${method}.root output/AFBreco_quark${quark}_${sample}_${pol}_*250GeV_cheatmethod_${method}.root
	    done
	done
    done
done
