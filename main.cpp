#include "SequenceToProfile.h"

//using namespace std;

int main()  {

    int seqLen = 17;
    //char seq[] = "GDGIYEAHDFTYY\0";
    char seq2[18]  = {'A', 'G', 'M', 'C', 'E', 'I', 'S', 'D', 'A', 'T', 'F', 'E', 'V', 'S', 'D', 'E', 'I','\0'};
    char *seq_pointer = seq2;

    SequenceToProfile test_stp(0);
    test_stp.sequenceToProfile(seq_pointer, seqLen);

}