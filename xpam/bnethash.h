#ifndef BNETHASHCPP_H
#define BNETHASHCPP_H

#include <stdint.h>
#include <QDebug>

#define ROTL(x,n,w) (((x)<<((n)&(w-1))) | ((x)>>(((-(n))&(w-1)))))
#define ROTL32(x,n) ROTL(x,n,32)
#define ROTL16(x,n) ROTL(x,n,16)

typedef uint8_t  bn_basic;
typedef bn_basic bn_byte[1];
typedef bn_basic bn_short[2];
typedef bn_basic bn_int[4];
typedef bn_basic bn_long[8];

typedef enum {
    do_blizzard_hash,
    do_sha1_hash
} t_hash_variant;

typedef uint32_t t_hash[5];

class Bnethash
{
private:
    int bn_int_nset(bn_int * dst, uint32_t src);
    uint32_t bn_int_get(bn_int const src);

    void hash_init(t_hash * hash);
    void do_hash(t_hash * hash, uint32_t * tmp, t_hash_variant hash_variant);
    void hash_set_16(uint32_t * dst, unsigned char const * src, unsigned int count, t_hash_variant hash_variant);
    void hash_set_length(uint32_t * dst, unsigned int size);
    int sha1_hash(t_hash * hashout, unsigned int size, void const * datain);
    int little_endian_sha1_hash(t_hash * hashout, unsigned int size, void const * datain);
    int hash_eq(t_hash const h1, t_hash const h2);
    char const * little_endian_hash_get_str(t_hash const hash);
    int hash_set_str(t_hash * hash, char const * str);
    int bnet_hash(t_hash * hashout, unsigned int size, void const * data);
    char const * hash_get_str(t_hash const hash);

public:
    Bnethash();
    QString getHashString(QString input);
};

#endif // BNETHASHCPP_H
