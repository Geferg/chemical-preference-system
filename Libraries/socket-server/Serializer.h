#ifndef CHEMICAL_PREFERENCE_SYSTEM_SERIALIZER_H
#define CHEMICAL_PREFERENCE_SYSTEM_SERIALIZER_H

namespace Libraries {
    class Serializer {
    public:
        static void unpack(unsigned char *buf, char *format, ...);
        static unsigned int pack(unsigned char *buf, char *format, ...);

    private:
        static uint64_t pack754(long double f, unsigned bits, unsigned expbits);
        static long double unpack754(uint64_t i, unsigned bits, unsigned expbits);
        static void packi16(unsigned char *buf, unsigned int i);
        static void packi32(unsigned char *buf, unsigned long int i);
        static void packi64(unsigned char *buf, unsigned long long int i);
        static int unpacki16(unsigned char *buf);
        static unsigned int unpacku16(unsigned char *buf);
        static long unpacki32(unsigned char *buf);
        static unsigned long unpacku32(unsigned char *buf);
        static long long int unpacki64(unsigned char *buf);
        static unsigned long long int unpacku64(unsigned char *buf);
    };

} // Libraries

#endif //CHEMICAL_PREFERENCE_SYSTEM_SERIALIZER_H
