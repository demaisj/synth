namespace MIDI {

  class Tuner {
  public:
    Tuner(int base=440);
    ~Tuner();

    void setBase(int base);
    int getBase() const;

    double getFreq(int note) const;

  private:
    int _base;
    double _table[128];

    void computeTable();
  };

}