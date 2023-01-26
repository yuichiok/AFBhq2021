#source launch_jettag.sh

for pol in "eL_pR" "eR_pL"
do
    source test_selection.sh 2f_hadronic $pol
    source test_selection.sh 2f_hadronic_sample $pol
    source test_selection.sh qqH $pol
    source test_selection.sh 4f_ZZ_hadronic $pol
    source test_selection.sh 4f_WW_hadronic $pol
    source test_selection.sh 6f_ttbar $pol

done

#for pol in "eL_pR" "eR_pL"
#do
#    source test_selection.sh 2f_hadronic $pol
#done



