#ifndef RANDOMIZER_H
#define RANDOMIZER_H
#include <random>
class Randomizer{
public:
    static void randomize(void *array_, size_t sizeInBytes_){
        rndGen__.seed(std::random_device()());
        while(sizeInBytes_)
            reinterpret_cast<uint8_t *>(array_)[--sizeInBytes_]=range__(rndGen__);
    }
    static int getRandom(int min_, int max_){
        std::uniform_int_distribution<int> range_(min_,max_);
        rndGen__.seed(std::random_device()());
        return range_(rndGen__);
    }
private:
    static std::default_random_engine rndGen__;
    static std::uniform_int_distribution<uint8_t> range__;
};


#endif // RANDOMIZER_H
