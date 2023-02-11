for pol in "eR_pL" "eL_pR"
do
    source test_QCDcorrelations.sh 2f_hadronic_sample $pol
    source test_QCDcorrelations.sh qqH $pol
    source test_QCDcorrelations.sh 4f_ZZ_hadronic $pol
    source test_QCDcorrelations.sh 4f_WW_hadronic $pol
done

for pol in "eR_pL" "eL_pR"
do
    source test_selection.sh 2f_hadronic_sample $pol
    source test_selection.sh qqH $pol
    source test_selection.sh 4f_ZZ_hadronic $pol
    source test_selection.sh 4f_WW_hadronic $pol
done




