#ifndef NAVCELL_H
#define NAVCELL_H

class NavCell
{
  public:
    NavCell(bool obstacle_ = false, unsigned int cost_ = 0);
    virtual ~NavCell();


  protected:
  public:
    unsigned int cost;
    bool obstacle;
};

#endif // NAVCELL_H
