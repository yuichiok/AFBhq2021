for pol in "eL_pR" "eR_pL"
do
    for cut in {0..3}
    do
		hadd -f -j 4 results/selection_cuts${cut}_4f_ZZ_hadronic_${pol}.root output/selection_cuts${cut}_4f_ZZ_hadronic_${pol}_*.root &
		hadd -f -j 4 results/selection_cuts${cut}_2f_hadronic_sample_${pol}.root output/selection_cuts${cut}_2f_hadronic_sample_${pol}_*.root 
		hadd -f -j 4 results/selection_cuts${cut}_qqH_${pol}.root output/selection_cuts${cut}_qqH_${pol}_*.root &
		hadd -f -j 4 results/selection_cuts${cut}_4f_WW_hadronic_${pol}.root output/selection_cuts${cut}_4f_WW_hadronic_${pol}_*.root 
		#hadd -f -j 4 results/selection_cuts${cut}_2f_hadronic_${pol}.root output/selection_cuts${cut}_2f_hadronic_${pol}_*.root
    done
done



