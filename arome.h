#ifndef AROME_H
#define AROME_H
#include "liquid.h"

class Arome : public Liquid
{
public:
    //constructeurs
    Arome(int p_numero, std::string p_nom, bool p_zeroStock, bool p_commande, std::string p_fabricant, float p_dosage, std::string p_path, int p_note);
    virtual ~Arome();
    //seters
    void setFabricant(std::string p_fabricant);
    void setDosage(float p_dosage);
    void setImage(std::string p_path);
    void setNote(int p_note);
    //geters
    std::string getFabricant() const;
    float getDosage() const;
    std::string getImage() const;
    int getNote() const;

private:
    std::string m_fabricant;
    float m_dosage;
    std::string m_image;
    int m_note;
};

class sortByName
{
public:
    bool operator() (const Arome* lhs, const Arome* rhs)
    {
        return (lhs->getNom() < rhs->getNom());
    }
};

#endif // AROME_H
