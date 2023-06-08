
#for process in "2f_hadronic_sample"
#do
#    source analysis_dEdxDist.sh $process "eL_pR"
#    source analysis_dEdxDist.sh $process "eR_pL"
#done

for process in "2f_hadronic_sample"
do
    source analysis.sh $process "eL_pR"
    source analysis.sh $process "eR_pL"
done



