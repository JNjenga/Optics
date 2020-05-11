#ifndef VISUAL_INPUT_H
#define VISUAL_INPUT_H

#include <glm/glm.hpp>

namespace Vis
{
	enum MouseEvents
	{
		RIGHT_CLICK,
		LEFT_CLICK,
		SCROLL,
		RESET
	};
	struct Mouse
	{
		float x;
		float y;

		MouseEvents m_State;

		glm::vec2  mouseScroll()
		{
			return glm::vec2();
		}

		bool mouseLeftClick()
		{
			return m_State == MouseEvents::LEFT_CLICK;
		}
		bool mouseRightClick()
		{
			return m_State == MouseEvents::RIGHT_CLICK;
		}

		void reset()
		{
			m_State = MouseEvents::RESET;
		}
		static Mouse & getMouse()
		{
			static Vis::Mouse m;
			return m;
		}

	private:
		static Mouse m;
	};
}

#endif