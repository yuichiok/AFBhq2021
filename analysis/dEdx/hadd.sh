for quark in "cquark" "bquark" "udsquark"
do
    for pol in "eL_pR" "eR_pL"
    do
	hadd -f results/histos_${quark}_secondary_tracks_ignoreoverlay_2f_hadronic_sample_${pol}_0GeV.root output/*secondary_tracks_ignoreoverlay_2f_hadronic_sample_${pol}*cut_0_${quark}.root
	hadd -f results/histos_${quark}_secondary_tracks_ignoreoverlay_2f_hadronic_sample_${pol}_2GeV.root output/*secondary_tracks_ignoreoverlay_2f_hadronic_sample_${pol}*cut_2_${quark}.root
	hadd -f results/histos_${quark}_secondary_tracks_ignoreoverlay_2f_hadronic_sample_${pol}_3GeV.root output/*secondary_tracks_ignoreoverlay_2f_hadronic_sample_${pol}*cut_3_${quark}.root
        hadd -f results/histos_${quark}_secondary_tracks_ignoreoverlay_2f_hadronic_sample_${pol}_0GeV_costheta_lt0.8.root output/*secondary_tracks_ignoreoverlay_2f_hadronic_sample_${pol}*cut_0_coshteta_lt0.8_${quark}.root
	hadd -f results/histos_${quark}_secondary_tracks_ignoreoverlay_2f_hadronic_sample_${pol}_2GeV_costheta_lt0.8.root output/*secondary_tracks_ignoreoverlay_2f_hadronic_sample_${pol}*cut_2_coshteta_lt0.8_${quark}.root
        hadd -f results/histos_${quark}_secondary_tracks_ignoreoverlay_2f_hadronic_sample_${pol}_3GeV_costheta_lt0.8.root output/*secondary_tracks_ignoreoverlay_2f_hadronic_sample_${pol}*cut_3_coshteta_lt0.8_${quark}.root
    done
done

#for cut in "0" "1" "2" "4" "5"
#do
#    for pol in "eL_pR" "eR_pL"
#    do
#        hadd -f results/histos_cquark_secondary_tracks_ignoreoverlay_2f_hadronic_sample_${pol}_${cut}GeV_costheta_lt08.root output/*secondary_tracks_ignoreoverlay_2f_hadronic_sample_${pol}*cut_${cut}_cquark_costheta_lt08.root
#        hadd -f results/histos_bquark_secondary_tracks_ignoreoverlay_2f_hadronic_sample_${pol}_${cut}GeV_costheta_lt08.root output/*secondary_tracks_ignoreoverlay_2f_hadronic_sample_${pol}*cut_${cut}_bquark_costheta_lt08.root
#    done
#done
