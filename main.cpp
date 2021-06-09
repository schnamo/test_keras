#include<string>
#include "SequenceToProfile.h"
#include "lib/fdeep/fdeep.hpp"

//using namespace std;

int main()
{
//    const auto model = fdeep::load_model("/Users/charlotte/NN/fdeep_model.json");
//    const auto result = model.predict(
//            {fdeep::tensor(fdeep::tensor_shape(static_cast<std::size_t>(13)),
//                           std::vector<float>{65, 71, 77, 67, 69, 73, 83, 68, 65, 84, 70, 69, 86})});
//    std::cout << fdeep::show_tensors(result) << std::endl;

    int seqLen = 17;
    char seq[] = "GDGIYEAHDFTYY\0";
    char seq2[18]  = {'A', 'G', 'M', 'C', 'E', 'I', 'S', 'D', 'A', 'T', 'F', 'E', 'V', 'S', 'D', 'E', 'I','\0'};
    char *seq_pointer = seq2;

    SequenceToProfile test_stp(0, 13);
    test_stp.sequenceToProfile(seq_pointer, seqLen);

}