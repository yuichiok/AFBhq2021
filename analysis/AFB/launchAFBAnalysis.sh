
#for pol in "eL_pR" "eR_pL"
#do
#    source test_AFBAnalysis.sh 2f_hadronic $pol 0
#    source test_AFBAnalysis.sh 2f_hadronic_sample $pol 0
#    source test_AFBAnalysis.sh qqH $pol 1
#    source test_AFBAnalysis.sh 4f_ZZ_hadronic $pol 1
#    source test_AFBAnalysis.sh 4f_WW_hadronic $pol 1
#    source test_AFBAnalysis.sh 6f_ttbar $pol 1
#done


source hadd_AFB_PQ.sh
cd macros
source Weights_c.sh
mkdir ../weights_dNdx_500GeV_2023
mv *root ../weights_dNdx_500GeV_2023/.
cd ..
##source test_AFBEnergy.sh
source launchAFBReco.sh
#source hadd_AFBReco.sh

source launchAFBSignalBkg.sh
#mv *root output/.
#source hadd_AFBSignalBkg.sh
