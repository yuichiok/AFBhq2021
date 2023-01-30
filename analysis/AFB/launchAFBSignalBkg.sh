for pol in "eL_pR" "eR_pL"
do
    for method in 0 1 2 3
    do
	source test_AFBSignalBkg.sh 2f_hadronic $pol $method 0 
	source test_AFBSignalBkg.sh 2f_hadronic_sample $pol $method 0
	source test_AFBSignalBkg.sh qqH $pol $method 1 
	source test_AFBSignalBkg.sh 4f_ZZ_hadronic $pol $method 1
	source test_AFBSignalBkg.sh 4f_WW_hadronic $pol $method 1 
	source test_AFBSignalBkg.sh 6f_ttbar $pol $method 1 
    done
done



