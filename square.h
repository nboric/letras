//
// Created by Neven Boric on 4/19/25.
//

#ifndef SQUARE_H
#define SQUARE_H

class Square
{
public:
    const enum EFFECT
    {
        NONE,
        LETTER_MULTIPLIER,
        WORD_MULTIPLIER,
    } effect_;

    const int effect_value_;

    Square(EFFECT effect, int effect_value);
};

#endif //SQUARE_H
