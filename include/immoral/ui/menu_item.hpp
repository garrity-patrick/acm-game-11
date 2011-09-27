#ifndef _IMMORAL_UI_MENU_ITEM_HPP_
#define _IMMORAL_UI_MENU_ITEM_HPP_

namespace immoral
{
	namespace ui
	{
		class menu_item
		{
		private:
			menu_item(void);
			
		private:
		
		public:
			menu_item(const menu_item & other);
			menu_item(u32 size);
			~menu_item(void);
		};
	}
}

#endif
