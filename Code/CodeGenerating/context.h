#ifndef CONTEXT_H
#define CONTEXT_H


class Context
{
public:
    Context() : forCounter(0), whileCounter(0), ifCounter(0), elseCounter(0) {};
    int forCounter;
    int whileCounter;
    int ifCounter;
    int elseCounter;
};

#endif // CONTEXT_H
