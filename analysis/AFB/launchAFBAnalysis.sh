source launchAFBSignalBkg.sh

for pol in "eL_pR" "eR_pL"
do
    source test_AFBAnalysis.sh 2f_hadronic $pol 0
    source test_AFBAnalysis.sh 2f_hadronic_sample $pol 0
    source test_AFBAnalysis.sh qqH $pol 1
    source test_AFBAnalysis.sh 4f_ZZ_hadronic $pol 1
    source test_AFBAnalysis.sh 4f_WW_hadronic $pol 1
    source test_AFBAnalysis.sh 6f_ttbar $pol 1
done
source test_AFBEnergy.sh

sleep 24h

source hadd_AFBSignalBkg.sh
source hadd_AFB_PQ.sh
source hadd_AFBEnergy.sh

cd macros
source Weights_c.sh
mv *root ../weights_500GeV/.
cd ..
source launchAFBReco.sh

