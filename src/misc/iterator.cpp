class Iterator {
public:
    Iterator(){}
    virtual ~Iterator(){}
    virtual next() = 0;
    virtual bool atEnd() = 0;
};

