#ifndef HUFFMAN_BITMASK_H
#define HUFFMAN_BITMASK_H
/*
    Verifica o bit na posição 'i' do byte 'c'. Retorna 1 caso esteja e 0 em negativa.
*/
int is_bit_i_set(unsigned char c, int i);

/*
    Recebe um byte, unsigned char 'c', e posição desejada, no caso 'i'. Retorna um byte igual a 'c' só que, obrigatoriamente, com o bit da posição 'i' igual a 1.
*/
unsigned char set_bit (unsigned char c, int i);

#endif //HUFFMAN_BITMASK_H
