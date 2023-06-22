for pol in "eL_pR"
do
    #source test_selection_HV.sh HV_qv100GeV $pol
    #source test_selection_HV.sh HV_qv10GeV $pol
    source test_selection_HV.sh HV_qv50GeV $pol
    echo $pol
done

for pol in "eL_pR" "eR_pL"
do
    echo $pol
    #source test_selection.sh 2f_hadronic_sample $pol
    #source test_selection.sh 2f_hadronic $pol
    #source test_selection.sh qqH $pol
    #source test_selection.sh 4f_ZZ_hadronic $pol
    #source test_selection.sh 4f_WW_hadronic $pol
done




