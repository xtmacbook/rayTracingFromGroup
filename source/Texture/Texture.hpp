
#ifndef _TEXT_H_
#define _TEXT_H_

#include <math.h>

#include "../Utilities/ShadeRec.hpp"
#include "../Utilities/RGBColor.hpp"

class Texture {
public:

	Texture(void);

	Texture(const Texture& texture);

	virtual Texture*
		clone(void) const = 0;

	virtual
		~Texture(void);

	virtual RGBColor
		get_color(const ShadeRec& sr) const = 0;

protected:

	Texture&
		operator= (const Texture& rhs);
};
#endif // !_TEXT_H_
