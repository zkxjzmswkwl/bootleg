/*--------------------------------------------------
Value map is a system aiming to achieve similar functionality to Ultimap.
The goal is to make identifying one value in a sea of thousands much easier.
The initial motivation came from a need to identify which scripts were running when in a popular MMO game.

Example:
	In some accessible place:
	auto vmap = bootleg::value_map<int32_t>::create();

	void __fastcall some_script_engine_hook(uintptr_t* rcx, void** vm, int32_t script_id)
	{
		vmap->push(script_id);
		call original_script_engine(rcx, vm, script_id);
	}


	Somewhere else you then can do something like

	if (GetAsyncKeyState(VK_F1) & 1) {
		vmap->discard_all();
	}

	if (GetAsyncKeyState(VK_F2) & 1) {
		vmap->filter_duplicates();
		vmap->print_unfiltered_values();
	}
--------------------------------------------------*/
#include <vector>
#include <memory>

namespace bootleg {
	template <typename T>
	class value_map 
	{
	private:
		// Each value's first stop.
		std::vector<T> m_UnfilteredValues{};
		// Stores all unique values that are not of interest.
		std::vector<T> m_DiscardedValues{};

	public:
		typedef T SillyTemplateType; // Is there a better way of doing this???

		void print_unfiltered_values();

		std::vector<T>* unfiltered_values();

		std::vector<T>* discarded_values();

		bool is_new_value(T);

		void filter_duplicates();

		void discard_all();

		[[nodiscard]] static std::unique_ptr<value_map> create();

		void push(T);
	};
}

