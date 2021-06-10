//
// Created by Charlotte Tumescheit on 2021/06/08.
//

#ifndef TEST_KERAS_SEQUENCETOPROFILE_H
#define TEST_KERAS_SEQUENCETOPROFILE_H

#include <vector>
#include <fdeep/fdeep.hpp>

class SequenceToProfile {
public:
    SequenceToProfile(int seqType);
    ~SequenceToProfile();

    // Use NN to generate profile for each 13-mer
    void sequenceToProfile(char *seq, unsigned int seqLen);
    // turn middle position into a kmer, add padding if needed
    std::vector<float> determineKmer(char *seq, unsigned int seqLen, int i);

private:
    int seqType;
    int kmerSize;
    fdeep::model model;
    std::vector<float> fkmer;
    std::vector<std::vector<float>> profile;

};


#endif //TEST_KERAS_SEQUENCETOPROFILE_H
