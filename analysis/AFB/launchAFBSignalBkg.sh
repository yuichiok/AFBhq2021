for pol in "eL_pR" "eR_pL"
do
	source test_AFBSignalBkg.sh 2f_hadronic $pol 0 
	source test_AFBSignalBkg.sh 2f_hadronic_sample $pol 0
	source test_AFBSignalBkg.sh qqH $pol 1 
	source test_AFBSignalBkg.sh 4f_ZZ_hadronic $pol 1
	source test_AFBSignalBkg.sh 4f_WW_hadronic $pol 1 
	source test_AFBSignalBkg.sh 6f_ttbar $pol 1 
done



