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

		float dx;
		float dy;

		double y_scroll;

		MouseEvents m_State;

		void  mouseScroll(double xoff, double yoff)
		{
			
		}
		void resetScroll()
		{
			y_scroll = 0.0;
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


	struct Keys
	{
		int keys[348];
		static Keys & getKeys()
		{
			static Vis::Keys k;
			return k;
		}

	private:
		static Keys k;
	};
}



#endif