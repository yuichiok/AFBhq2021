
for process in "2f_hadronic"
do
    source analysis.sh $process "eL_pR" 0
    source analysis.sh $process "eR_pL" 0
done

for process in "2f_hadronic_sample"
do
    source analysis.sh $process "eL_pR" 1
    source analysis.sh $process "eR_pL" 1
done



