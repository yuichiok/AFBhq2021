for cut in 0
do
	hadd -f -j 4 -k results/selection_cuts${cut}_HV_qv100GeV.root output/selection_cuts${cut}_HV_qv100GeV*.root
	hadd -f -j 4 -k results/selection_cuts${cut}_HV_qv50GeV.root output/selection_cuts${cut}_HV_qv50GeV*.root
	hadd -f -j 4 -k results/selection_cuts${cut}_HV_qv10GeV.root output/selection_cuts${cut}_HV_qv10GeV*.root
	hadd -f -j 4 -k results/selection_cuts${cut}_qqSM.root output/selection_cuts${cut}_qqSM*.root 

	hadd -f -j 4 -k results/selectionPL_cuts${cut}_HV_qv100GeV.root output/selectionPL_cuts${cut}_HV_qv100GeV*.root
	hadd -f -j 4 -k results/selectionPL_cuts${cut}_HV_qv50GeV.root output/selectionPL_cuts${cut}_HV_qv50GeV*.root
	hadd -f -j 4 -k results/selectionPL_cuts${cut}_HV_qv10GeV.root output/selectionPL_cuts${cut}_HV_qv10GeV*.root
	hadd -f -j 4 -k results/selectionPL_cuts${cut}_qqSM.root output/selectionPL_cuts${cut}_qqSM*.root
done
