//
// Created by Charlotte Tumescheit on 2021/06/08.
//

#include "SequenceToProfile.h"
#include <iostream>
#include <fdeep/fdeep.hpp>
#include <string>
#include <vector>

// todo: error handling
// todo: run in parallel

SequenceToProfile::SequenceToProfile(char *seq, unsigned int seqLen, int seqType, int kmerSize) {
    this->seq = seq;
    this->L = seqLen;
    this->seqType = seqType;
    this->kmerSize = kmerSize;

    //    std::cout << seq[13] << std::endl;
    //    if(fkmer.size() != 13 || seq[13] != '\0' || strlen(seq) != L ){
    //        std::cout << "error" << std::endl;
    //        std::exit(1);
    //    }

    // todo: take care of memory
}

SequenceToProfile::~SequenceToProfile() {

    // todo: delete and free all the stuff

}

// use NN to get profile for each 13-mer of the input sequence
// in: sequence of length 1xL
// out: profile of length 20xL
void SequenceToProfile::sequenceToProfile() {

    const auto model = fdeep::load_model("/Users/charlotte/NN/fdeep_model.json");
    std::vector<float> fkmer;
    std::vector<std::vector<float>> profile;

    for(int i = 0; i < L; i++) {
        fkmer = determineKmer(i);
        if(fkmer.size() != kmerSize){
            std::cout << "kmer size is " << fkmer.size() << " instead of " << kmerSize << std::endl;
        }
        const auto profileT = model.predict(
                {fdeep::tensor(fdeep::tensor_shape(static_cast<std::size_t>(13)), fkmer)});
        std::cout << fdeep::show_tensors(profileT) << std::endl;
        const std::vector<float> profileV = profileT[0].to_vector();
       profile.push_back(profileV);
    }

    if(profile.size() != L){
        std::cout << "Generating profile failed." << std::endl;
    }
}


std::vector<float> SequenceToProfile::determineKmer(int i){

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