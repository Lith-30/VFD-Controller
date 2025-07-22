
class ByteSequenceController : public Iterator {
    private:
        ByteSequence seq;
        int pos;
    
    public:
        Iterator(ByteSequence seq):
        ~Iterator();
        int next();
        bool atEnd();
        
};