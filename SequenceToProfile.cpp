//
// Created by Charlotte Tumescheit on 2021/06/08.
//

#include "SequenceToProfile.h"
#include <iostream>
#include <fdeep/fdeep.hpp>
#include <string>
#include <vector>
#include <numeric>

// todo: error handling
// todo: run in parallel

SequenceToProfile::SequenceToProfile(int seqType)  :   model(fdeep::load_model("/Users/charlotte/NN/fdeep_model.json")) {

    this->seqType = seqType;

    model.generate_dummy_inputs();
    const std::vector<fdeep::tensor_shape> dummy_input = model.get_dummy_input_shapes();
    this->kmerSize = dummy_input[0].depth_;

    // todo: take care of memory
}

SequenceToProfile::~SequenceToProfile() {

    // todo: delete and free all the stuff

}

// use NN to get profile for each 13-mer of the input sequence
// in: sequence of length 1xL
// out: profile of length 20xL
void SequenceToProfile::sequenceToProfile(char *seq, unsigned int L) {

    fkmer.clear();
    profile.clear();
    fdeep::model model = fdeep::load_model("/Users/charlotte/NN/fdeep_model.json");

    for(int i = 0; i < L; i++) {
        fkmer = determineKmer(seq, L, i);
        if(fkmer.size() != kmerSize){
            std::cout << "kmer size is " << fkmer.size() << " instead of " << kmerSize << std::endl;
        }
        const auto profileT = model.predict(
                {fdeep::tensor(fdeep::tensor_shape(static_cast<std::size_t>(kmerSize)), fkmer)});
        std::cout << fdeep::show_tensors(profileT) << std::endl;
        std::vector<float> profileV = profileT[0].to_vector();
        // set all negative values to 0 todo: alternatively could shift all values of vector by negative value
        for(int m = 0; m < profileV.size(); m++){
                if(profileV[m] < 0){
                    profileV[m] = 0;
                }
        }
        // normalise profile
        float total_sum = std::accumulate(profileV.begin(), profileV.end(),decltype(profileV)::value_type(0));
        for(int n =  0; n < profileV.size(); n++){
            profileV[n] = profileV[n] / total_sum;
        }

        profile.push_back(profileV);
    }

    if(profile.size() != L){
        std::cout << "Generating profile failed." << std::endl;
    }
}


std::vector<float> SequenceToProfile::determineKmer(char *seq, unsigned int L, int i){

    std::vector<float> fkmer;
    int padding = 65;
    int padding_start = 0;
    int padding_end = 0;
    int halfK = (kmerSize - 1) / 2;

    while(i - halfK + padding_start < 0){ //padding start
        fkmer.push_back(padding);
        std::cout << "P:" << padding << ";";
        padding_start++;
    }

    for (int k = (-1* halfK) + padding_start; k < 0; k++) {
        int aa = seq[i + k];
        std::cout << seq[i + k] << ":" << aa << ";";
        fkmer.push_back(aa);
    }

    int aa = seq[i];
    std::cout << seq[i] << ":" << aa << ";";
    fkmer.push_back(aa);

    if((i + halfK) > (L - 1)){
        padding_end = L - i - 7;
    }

    for (int l = 1; l < halfK + 1 + padding_end; l++) {
        int aa = seq[i + l];
        std::cout << seq[i + l] << ":" << aa << ";";
        fkmer.push_back(aa);
    }

    while(padding_end < 0){ // padding end
        fkmer.push_back(padding);
        std::cout << "P:" <<  padding << ";";
        padding_end++;
    }

    std::cout << std::endl;

    return fkmer;
}