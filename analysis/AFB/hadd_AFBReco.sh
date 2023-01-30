for pol in "eL_pR" "eR_pL" 
do
    for sample in "2f_hadronic_sample" "2f_hadronic"
    do
	for quark in 4 5 
	do
	    for method in 0 1 2 3
	    do
			hadd -f -j 4 results_500GeV/AFBreco_pdg${quark}_${sample}_${pol}_cheatmethod_${method}.root output/AFBreco_quark${quark}_${sample}_${pol}_*cheatmethod_${method}.root
	    done
	done
    done
done
