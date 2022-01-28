for pol in "eR_pL" "eL_pR"
do
    source test_AFBAnalysis.sh 2f_hadronic $pol 0
    source test_AFBAnalysis.sh 2f_hadronic_sample $pol 0
    source test_AFBAnalysis.sh qqH $pol 1
    source test_AFBAnalysis.sh 4f_ZZ_hadronic $pol 1
    source test_AFBAnalysis.sh 4f_WW_hadronic $pol 1
done



