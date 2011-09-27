#ifndef _IMMORAL_UI_MENU_HPP_
#define _IMMORAL_UI_MENU_HPP_

#include "immoral/types.hpp"
#include "immoral/ui/menu_item.hpp"

namespace immoral
{
	namespace ui
	{
		class menu
		{
		private:
			menu(void);
			
		private:
			menu_item * m_items;
			menu_item * m_current;
			u32 m_size;
		
		public:
			menu(const menu & other);
			menu(u32 size);
			~menu(void);
			
			u32 size(void) const { return m_size; }
			
			const menu_item * items(void) const { return m_items; }
		};
	}
}

#endif
