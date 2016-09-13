// This includes:
#include "animatedsprite.h"

// Local includes:
#include "texture.h"
#include "backbuffer.h"
#include "entity.h"

AnimatedSprite::AnimatedSprite()
	: m_frameSpeed(0.0f)
	, m_frameWidth(0)
	, m_timeElapsed(0.0f)
	, m_currentFrame(0)
	, m_paused(false)
	, m_loop(false)
	, m_animating(false)
	, yDrawPos(0)
{

}

AnimatedSprite::~AnimatedSprite()
{

}

bool
AnimatedSprite::Initialise(Texture& texture)
{
	m_frameWidth = 0;
	m_frameSpeed = 0;

	m_loop = false;
	m_paused = false;
	m_animating = true;

	Sprite::Initialise(texture);

	StartAnimating();

	return (true);
}

void
AnimatedSprite::AddFrame(int x)
{
	// W02.4: Add the x coordinate to the frame coordinate container.
	pAnimatedSpriteVector.push_back(&x);
}

void
AnimatedSprite::Process(float deltaTime)
{
	// W02.4: If not paused...
	if (!m_paused)
	{
		// W02.4: Count the time elapsed.
		m_timeElapsed += deltaTime;

		// W02.4: If the time elapsed is greater than the frame speed.
		if (m_timeElapsed >= m_frameSpeed)
		{
			// W02.4: Move to the next frame.
			m_currentFrame++;
			// W02.4: Reset the time elapsed counter.
			m_timeElapsed = 0;
		}

		// W02.4: If the current frame is greater than the number of frames in this animation...
		if (m_currentFrame > m_numOfFrames)
		{
			// W02.4: Reset to the first frame.
			if (m_loop)
				m_currentFrame = 0;
			// W02.4: Stop the animation if it is not looping...
			else
				Pause(true);
		}
	}
}


void
AnimatedSprite::Draw(BackBuffer& backbuffer)
{
	backbuffer.DrawAnimatedSprite(*this);
}

void 
AnimatedSprite::SetYDrawPos(int y)
{
	yDrawPos = y;
}

int
AnimatedSprite::getYDrawPos()
{
	return (yDrawPos);
}

void
AnimatedSprite::SetFrameSpeed(float f)
{
	m_frameSpeed = f;
}

void
AnimatedSprite::SetFrameWidth(int w)
{
	m_frameWidth = w;
}

void
AnimatedSprite::SetFrameHeight(int h) {
	m_frameHeight = h;
}

void
AnimatedSprite::Pause(bool pause)
{
	m_paused = pause;
	if (pause)
		m_currentFrame = 0;
}

bool
AnimatedSprite::IsPaused()
{
	return (m_paused);
}

bool
AnimatedSprite::IsAnimating()
{
	return (m_animating);
}

void
AnimatedSprite::StartAnimating()
{
	m_animating = true;

	m_timeElapsed = 0;
	m_currentFrame = 0;
}

bool
AnimatedSprite::IsLooping()
{
	return (m_loop);
}

void
AnimatedSprite::SetLooping(bool b)
{
	m_loop = b;
}

void
AnimatedSprite::SetNumOfFrames(int n)
{
	m_numOfFrames = n;
}

int
AnimatedSprite::GetNumOfFrames()
{
	return m_numOfFrames;
}

int
AnimatedSprite::GetFrameHeight()
{
	return m_frameHeight;
}

int
AnimatedSprite::GetFrameWidth()
{
	return m_frameWidth;
}

int
AnimatedSprite::GetCurrentFrame()
{
	return m_currentFrame;
}

float
AnimatedSprite::GetFrameSpeed()
{
	return m_frameSpeed;
}