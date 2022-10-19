for pol in "eL_pR" "eR_pL"
do
    hadd -f -j 4 results/s_AFB_doubletight_2f_hadronic_${pol}_250GeV.root output/s_AFB_doubletight_2f_hadronic_${pol}_*_250GeV.root
    hadd -f -j 4 results/s_AFB_tight_2f_hadronic_${pol}_250GeV.root output/s_AFB_tight_2f_hadronic_${pol}_*_250GeV.root
    hadd -f -j 4 results/s_AFB_loose_2f_hadronic_${pol}_250GeV.root output/s_AFB_loose_2f_hadronic_${pol}_*_250GeV.root
done
