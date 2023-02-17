for quark in "cquark" "bquark"
do
#"cquark" "bquark" "udsquark"
#do
    for pol in "eL_pR"
    do
	    hadd -f -j 4 results/histos_${quark}_secondary_tracks_ignoreoverlay_2f_hadronic_sample_${pol}_0GeV.root output/*secondary_tracks_ignoreoverlay_2f_hadronic_sample_${pol}*cut_0_${quark}.root
	    hadd -f -j 4 results/histos_${quark}_secondary_tracks_ignoreoverlay_2f_hadronic_sample_${pol}_3GeV.root output/*secondary_tracks_ignoreoverlay_2f_hadronic_sample_${pol}*cut_3_${quark}.root
	    #hadd -f -j 4 results/histos_${quark}_secondary_tracks_ignoreoverlay_2f_hadronic_sample_${pol}_2GeV_costheta_lt0.8.root output/*secondary_tracks_ignoreoverlay_2f_hadronic_sample_${pol}*cut_2_coshteta_lt0.8_${quark}.root

        hadd -f -j 4 results/histos_${quark}_secondary_tracks_ignoreoverlay_improved_1_2f_hadronic_sample_${pol}_0GeV.root output/*secondary_tracks_ignoreoverlay_improved_1_2f_hadronic_sample_${pol}*cut_0_${quark}.root
	    hadd -f -j 4 results/histos_${quark}_secondary_tracks_ignoreoverlay_improved_1_2f_hadronic_sample_${pol}_3GeV.root output/*secondary_tracks_ignoreoverlay_improved_1_2f_hadronic_sample_${pol}*cut_3_${quark}.root
        
        hadd -f -j 4 results/histos_${quark}_secondary_tracks_ignoreoverlay_improved_2_2f_hadronic_sample_${pol}_0GeV.root output/*secondary_tracks_ignoreoverlay_improved_2_2f_hadronic_sample_${pol}*cut_0_${quark}.root
	    hadd -f -j 4 results/histos_${quark}_secondary_tracks_ignoreoverlay_improved_2_2f_hadronic_sample_${pol}_3GeV.root output/*secondary_tracks_ignoreoverlay_improved_2_2f_hadronic_sample_${pol}*cut_3_${quark}.root
 
    done
done

for pol in "eL_pR"
do
    hadd -k -f -j 4 results/dEdxdist_2f_hadronic_sample_${pol}_cutP_3.root output/dEdxdist_2f_hadronic_sample_${pol}_*root
done

#for cut in "0" "1" "2" "4" "5"
#do
#    for pol in "eL_pR" "eR_pL"
#    do
#        hadd -f results/histos_cquark_secondary_tracks_ignoreoverlay_2f_hadronic_${pol}_${cut}GeV_costheta_lt08.root output/*secondary_tracks_ignoreoverlay_2f_hadronic_${pol}*cut_${cut}_cquark_costheta_lt08.root
#        hadd -f results/histos_bquark_secondary_tracks_ignoreoverlay_2f_hadronic_${pol}_${cut}GeV_costheta_lt08.root output/*secondary_tracks_ignoreoverlay_2f_hadronic_${pol}*cut_${cut}_bquark_costheta_lt08.root
#    done
#done
