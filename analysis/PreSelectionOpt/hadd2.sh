for pol in "eL_pR" "eR_pL"
do
    hadd -f -j 4 results_500GeV/jettag_cuts5_2f_hadronic_sample_${pol}.root output/jettag_cuts5_2f_hadronic_sample_${pol}_file_*.root
    hadd -f -j 4 results_500GeV/jettag_cuts5_2f_hadronic_${pol}.root output/jettag_cuts5_2f_hadronic_${pol}_file_*.root
done
