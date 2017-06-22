#ifndef HZZUTILS_KD2MELA_H
#define HZZUTILS_KD2MELA_H

// Forward declaration(s):
class TLorentzVector;

namespace HZZUtils
{
    float c_factor	( float m4l_unconstrained, int event_type );
    void kd2mela    (float KD_discriminant, float m4l_unconstrained, int event_type, float& MELA );

}


#endif // HIGGSZZ4LUTILS_GETELICITYANGLES_H


