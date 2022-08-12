#source launchAFBSignalBkg.sh

#for pol in "eL_pR" "eR_pL"
#do
#    source test_AFBAnalysis.sh 2f_hadronic $pol 0
#    source test_AFBAnalysis.sh 2f_hadronic_sample $pol 0
#    source test_AFBAnalysis.sh qqH $pol 1
#    source test_AFBAnalysis.sh 4f_ZZ_hadronic $pol 1
#    source test_AFBAnalysis.sh 4f_WW_hadronic $pol 1
#done

#source hadd_AFBSignalBkg.sh
#source hadd_AFB_PQ.sh
#cd macros
#source Weights_c.sh
#mv *root ../weights/.
#cd ..
source launchAFBReco.sh

