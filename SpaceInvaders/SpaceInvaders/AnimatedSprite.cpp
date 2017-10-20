#ifndef __ANIMATEDSPRITE_H__
#define __ANIMATEDSPRITE_H__

#include "sprite.h"
#include <vector>

class CAnimatedSprite : public CSprite
{
	// Methods:
public:
	CAnimatedSprite();
	~CAnimatedSprite();

	bool Initialise(int _iResourceID, int _iMaskResourceID);
	void AddFrame(int x);

protected:
	// W02.4: Add a field, the container for frame coordinates.
	std::vector<int> coordContainer;

	//Texture* m_pTexture;
	float m_frameSpeed;
	int m_frameWidth;
	int m_frameHeight;

	float m_timeElapsed;
	int m_currentFrame;
	int m_numOfFrames;

	bool m_paused;
	bool m_loop;
	bool m_animating;

private:

};

#endif // __ANIMATEDSPRITE_H__