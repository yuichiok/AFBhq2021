for pol in "eL_pR"
do
    echo $pol
    #source test_QCDcorrelations_HV.sh HV_qv100GeV $pol
    #source test_QCDcorrelations_HV.sh HV_qv10GeV $pol
    #source test_QCDcorrelations_HV.sh HV_qv50GeV $pol
done

for pol in "eL_pR" "eR_pL"
do
    echo $pol
    #source test_QCDcorrelations.sh 2f_hadronic_sample $pol
    #source test_QCDcorrelations.sh 2f_hadronic $pol
    source test_QCDcorrelations.sh 4f_ZZ_hadronic $pol
    source test_QCDcorrelations.sh 4f_WW_hadronic $pol
    source test_QCDcorrelations.sh qqH $pol
done
