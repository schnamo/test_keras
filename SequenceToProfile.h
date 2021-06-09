//
// Created by Charlotte Tumescheit on 2021/06/08.
//

#ifndef TEST_KERAS_SEQUENCETOPROFILE_H
#define TEST_KERAS_SEQUENCETOPROFILE_H

#include <vector>

class SequenceToProfile {
public:
    SequenceToProfile(char *seq, unsigned int seqLen, int seqType, int kmerSize);
    ~SequenceToProfile();

    // Use NN to generate profile for each 13-mer
    void sequenceToProfile();
    // turn middle position into a kmer, add padding if needed
    std::vector<float> determineKmer(int i);

    char *seq;
    int L; // length of the sequence
    int seqType;
    int kmerSize;

};


#endif //TEST_KERAS_SEQUENCETOPROFILE_H
