for pol in "eL_pR" "eR_pL" 
do
    for sample in "2f_hadronic_sample" "2f_hadronic"
    do
		for quark in 4 5 
		do
			hadd -f -j 4 results_250GeV_dEdx/AFBreco_pdg${quark}_${sample}_${pol}.root output/AFBreco_quark${quark}_${sample}_${pol}*root
		done
    done
done
